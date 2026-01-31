use std::{
    ffi::CString,
    sync::{
        Mutex,
        atomic::{AtomicU8, AtomicU16, Ordering},
    },
};

use anyhow::Result;
use circular_buffer::CircularBuffer;
use log::info;

use crate::ui::{
    self, AVG_CONS, CLUTCH, COOLANT_TEMP, ENGINE_TEMP, FUEL_LEVEL, OIL_PRESS, SLIP, STATUS,
    TRANS_TEMP, VOLTAGE, update_trans_chart,
};

pub type Formula = Box<dyn FnMut(&[u8]) -> Result<f32> + Sync + Send + 'static>;

pub struct OBDCommand {
    pub name: String,
    pub _short_name: String,
    pub service: Vec<u8>, // 0104 or 22B011
    // pub formula: Formula,
    pub set_ui: Formula,
}

impl std::fmt::Debug for OBDCommand {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.debug_struct("OBDCommand")
            .field("name", &self.name)
            .field("service", &self.service)
            .field("formula", &format_args!("unknown"))
            .finish()
    }
}

static _VEHICLE_SPEED: AtomicU8 = AtomicU8::new(0);
static RPM: AtomicU16 = AtomicU16::new(0);
static FUEL_USED: Mutex<f32> = Mutex::new(0.0);

const CC_PER_MS: f32 = 285.0 / 60_000.0;
const GAL_PER_CC: f32 = 0.000_264_172;

impl OBDCommand {
    pub fn oil() -> Self {
        OBDCommand {
            name: "Engine Oil Temp VVT".to_owned(),
            _short_name: "OIL".to_owned(),
            // service: Vec::from(b"212D"), // engine oil temp (byte H)
            service: Vec::from(b"22069F"), // VVT Oil temp
            set_ui: Box::new(|data| {
                let value = engine_temp(data)?;

                let mut lock = match ENGINE_TEMP.write() {
                    Ok(l) => l,
                    Err(p) => p.into_inner(),
                };
                *lock = value;

                Ok(value)
            }),
        }
    }

    pub fn coolant() -> Self {
        OBDCommand {
            name: "Coolant Temp".to_owned(),
            _short_name: "CLNT".to_owned(),
            // service: Vec::from(b"0105"),
            service: Vec::from(b"22011D"),
            set_ui: Box::new(|data| {
                let value = coolant(data)?;

                let mut lock = match COOLANT_TEMP.write() {
                    Ok(l) => l,
                    Err(p) => p.into_inner(),
                };
                *lock = value;

                Ok(value)
            }),
        }
    }

    pub fn atf() -> Self {
        OBDCommand {
            name: "Trans Oil Temp".to_owned(),
            _short_name: "ATF".to_owned(),
            service: Vec::from(b"22B011"),
            set_ui: Box::new(|data| {
                let value = trans_oil_temp(data)?;

                update_trans_chart(f32::trunc(value) as i16);

                let mut lock = match TRANS_TEMP.write() {
                    Ok(l) => l,
                    Err(p) => p.into_inner(),
                };
                *lock = value;

                Ok(value)
            }),
        }
    }

    pub fn _vehicle_speed() -> Self {
        OBDCommand {
            name: "Vehicle Speed".to_owned(),
            _short_name: "SPD".to_owned(),
            service: Vec::from(b"010D"),
            set_ui: Box::new(|data| {
                let value = _vehicle_speed(data)?;

                _VEHICLE_SPEED.store(value, Ordering::Relaxed);

                Ok(value as f32)
            }),
        }
    }

    pub fn _engine_speed() -> Self {
        OBDCommand {
            name: "Engine Speed".to_owned(),
            _short_name: "RPM".to_owned(),
            service: Vec::from(b"2201D5"),
            set_ui: Box::new(|data| {
                let value = _rpm(data)?;

                RPM.store(value, Ordering::Relaxed);

                Ok(value as f32)
            }),
        }
    }

    pub fn _avg_cons() -> Self {
        let mut context = Box::new(CircularBuffer::<60, u16>::new());

        OBDCommand {
            name: "Avg Consumption".to_owned(),
            _short_name: "CONS".to_owned(),
            service: Vec::from(b"2201CA"), // MAF g/s
            set_ui: Box::new(move |data| {
                let maf = _maf(data)?;

                if maf.is_normal() {
                    let speed = _VEHICLE_SPEED.load(Ordering::Relaxed) as f32;

                    if speed.is_normal() {
                        // info!("MAF ({maf}) speed ({speed})");

                        // let inst_cons_mpg = speed * 7.718 / maf; // assuming speed is in kph
                        let inst_cons_mpg = speed * 7.1073357 / maf; // assuming speed is in kph
                        let inst_cons_mpg = (inst_cons_mpg * 10.0).trunc() * 0.1;

                        if inst_cons_mpg.is_normal() {
                            let now_mpg = 99.9_f32.min(inst_cons_mpg); // Don't exceed 99.9 mpg

                            let oldest_mpg = context.push_back((now_mpg * 10.0) as u16);

                            let cons_prev = AVG_CONS.load(Ordering::Acquire) as f32 * 0.1;

                            let cons_now = if oldest_mpg.is_none() {
                                // CA
                                let n = context.len() as f32;

                                cons_prev + ((now_mpg - cons_prev) / n)
                                // (now_mpg + (n - 1.0) * cons_prev) / n
                            } else {
                                // SMA
                                let oldest_mpg = oldest_mpg.unwrap_or(0) as f32 * 0.1;
                                cons_prev + ((now_mpg - oldest_mpg) / context.len() as f32)
                            };

                            // 18.3 mpg -> 183
                            AVG_CONS.store((cons_now * 10.0) as u16, Ordering::Release);

                            let log_msg = format!(
                                "speed ({speed}), maf ({maf}), inst_cons_mpg ({inst_cons_mpg}), inst_mpg ({now_mpg}), oldest ({oldest_mpg:?}), cons_prev ({cons_prev}), cons_now ({cons_now}), len ({})",
                                context.len()
                            );
                            STATUS
                                .write()
                                .unwrap()
                                .replace(CString::new(log_msg.as_str()).unwrap());

                            //info!("speed ({speed}), maf ({maf}), inst_cons_mpg ({inst_cons_mpg}), inst_mpg ({now_mpg}), oldest ({oldest_mpg:?}), cons_prev ({cons_prev}), cons_now ({cons_now}), len ({})", context.len());
                            info!("{log_msg}");
                        }
                    }
                }

                Ok(maf as f32)
            }),
        }
    }

    pub fn _fuel_cons() -> Self {
        // Miles, Fuel level
        let mut context = (None, None);

        OBDCommand {
            name: "Fuel Consumption".to_owned(),
            _short_name: "FCON".to_owned(),
            service: Vec::from(b"2214FA"), // Distance list last trip oil change (total km)
            set_ui: Box::new(move |data| {
                let mut cons: f32 = 0.0;

                let miles_now = miles_driven(data)?;

                let fuel_now = FUEL_LEVEL.load(Ordering::Relaxed) as f32 * 0.1;

                match context {
                    (None, None) => {
                        if fuel_now > 0.0 {
                            context = (None, Some(fuel_now));
                        }
                    }
                    (None, Some(fuel_prev)) => {
                        if fuel_prev < fuel_now {
                            context = (None, Some(fuel_now));
                        } else if fuel_prev > fuel_now {
                            context = (Some(miles_now), Some(fuel_now));
                        }
                    }
                    (Some(miles_prev), Some(fuel_prev)) => {
                        if fuel_prev < fuel_now {
                            context = (None, Some(fuel_now));
                        } else if fuel_prev > fuel_now {
                            cons = (miles_now - miles_prev) / (fuel_prev - fuel_now);

                            cons = 99.9_f32.min(cons);

                            let log_msg = format!(
                                "miles now ({miles_now}) prev ({miles_prev}), fuel prev ({fuel_prev}) now ({fuel_now}), cons_now ({cons})"
                            );
                            STATUS
                                .write()
                                .unwrap()
                                .replace(CString::new(log_msg.as_str()).unwrap());

                            info!("{log_msg}");

                            // 18.3 mpg -> 183
                            AVG_CONS.store((cons * 10.0) as u16, Ordering::Relaxed);

                            context = (Some(miles_now), Some(fuel_now));
                        }
                    }
                    _ => {}
                }

                Ok(cons)
            }),
        }
    }

    pub fn _maf() -> Self {
        OBDCommand {
            name: "MAF".to_owned(),
            _short_name: "MAF".to_owned(),
            service: Vec::from(b"2201CA"), // MAF g/s
            set_ui: Box::new(|data| {
                let maf = _maf(data)?;

                if maf.is_normal() {
                    // gallons of fuel = (grams of air) / (air/fuel ratio) / 6.17 (pounds per gallon) / 464 (grams per pound)
                    let gallons = maf / 14.7 / 6.1 / 464.0;

                    *FUEL_USED.lock().unwrap() += gallons;
                }

                Ok(maf)
            }),
        }
    }

    pub fn fuel_cons() -> Self {
        // Odometer
        let mut context = None;

        OBDCommand {
            name: "Fuel Consumption".to_owned(),
            _short_name: "FCON".to_owned(),
            service: Vec::from(b"2214FA"), // Distance list last trip oil change (total km)
            set_ui: Box::new(move |data| {
                let mut cons: f32 = 0.0;

                let miles_now = miles_driven(data)?;

                if let Some(miles_prev) = context {
                    let fuel_used = *FUEL_USED.lock().unwrap();

                    if fuel_used > 0.0 {
                        // gallons of fuel per sec = (total pulse widths in ms per sec) * (injector cc per ms) * (num cyl) * (gal per cc)
                        let fuel_used = fuel_used * CC_PER_MS * 6.0 * GAL_PER_CC;

                        // derate the mpg to closer match actual
                        cons = (miles_now - miles_prev) / fuel_used * 0.5;

                        cons = 99.9_f32.min(cons);

                        let log_msg = format!(
                            "miles now ({miles_now}) prev ({miles_prev}), fuel used ({fuel_used}), cons_now ({cons})"
                        );
                        STATUS
                            .write()
                            .unwrap()
                            .replace(CString::new(log_msg.as_str()).unwrap());

                        info!("{log_msg}");

                        // 18.3 mpg -> 183
                        AVG_CONS.store((cons * 10.0) as u16, Ordering::Relaxed);
                    }
                }

                *FUEL_USED.lock().unwrap() = 0.0;
                context = Some(miles_now);

                Ok(cons)
            }),
        }
    }

    pub fn ipw_1() -> Self {
        OBDCommand {
            name: "Injector 1 pulse width".to_owned(),
            _short_name: "IPW1".to_owned(),
            service: Vec::from(b"220234"),
            set_ui: Box::new(|data| {
                let ipw = injector_pulse_width(data)?;

                if ipw.is_normal() {
                    let rpm = RPM.load(Ordering::Relaxed) as f32;

                    // gallons of fuel per sec = (pulse width in ms per sec) * (rev per sec)
                    let gallons = ipw * (rpm * 0.016_667);

                    *FUEL_USED.lock().unwrap() += gallons;
                }

                Ok(ipw)
            }),
        }
    }

    pub fn fuel_level() -> Self {
        OBDCommand {
            name: "Fuel Level".to_owned(),
            _short_name: "FLV".to_owned(),
            // service: Vec::from(b"012F"),
            service: Vec::from(b"220227"),
            set_ui: Box::new(|data| {
                // 8.3 -> 83
                let value = (fuel_level(data)? * 10.0) as u16;

                FUEL_LEVEL.store(value, Ordering::Relaxed);

                Ok(value as f32)
            }),
        }
    }

    pub fn oil_pressure() -> Self {
        OBDCommand {
            name: "Oil Pressure".to_owned(),
            _short_name: "OPR".to_owned(),
            service: Vec::from(b"22022A"), // or 22069E VVT oil pressure
            set_ui: Box::new(move |data| {
                let value = oil_pressure(data)?;

                OIL_PRESS.store(value, Ordering::Relaxed);

                Ok(value as f32)
            }),
        }
    }

    pub fn rpm_tc_slip() -> Self {
        OBDCommand {
            name: "Slip".to_owned(),
            _short_name: "TCS".to_owned(),
            service: Vec::from(b"2162"),
            set_ui: Box::new(move |data| {
                let iss = iss(data)?;
                let oss = oss(data)?;

                SLIP.store(iss as i16 - oss as i16, Ordering::Relaxed);

                let value = iss; // Should be close enough to engine speed

                RPM.store(value, Ordering::Relaxed);

                Ok(value as f32)
            }),
        }
    }

    pub fn gear_clutches() -> Self {
        OBDCommand {
            name: "Gear & Clutches".to_owned(),
            _short_name: "GER".to_owned(),
            service: Vec::from(b"2165"),
            set_ui: Box::new(move |data| {
                ui::set_gear(gear_actual(data)?);

                let clutches = *data.get(9).unwrap_or(&0); // J

                CLUTCH.store(clutches, Ordering::Relaxed);

                Ok(clutches as f32)
            }),
        }
    }

    pub fn voltage() -> Self {
        OBDCommand {
            name: "Voltage".to_owned(),
            _short_name: "VLT".to_owned(),
            service: Vec::from(b"0142"),
            set_ui: Box::new(|data| {
                let value = voltage(data)?;

                let mut lock = match VOLTAGE.write() {
                    Ok(l) => l,
                    Err(p) => p.into_inner(),
                };
                *lock = value;

                Ok(value as f32)
            }),
        }
    }
}

#[derive(Debug)]
pub struct OBDResponse {
    pub can_id: String, // hex 4 bytes, i.e. 18DAF110
    pub _size: u8,      // if > 7 is multi frame
    pub _mode: String,  // hex str 0x40 + request mode, i.e 0x61 is mode 21
    pub _pid: String,   // hex str
    pub data: Vec<u8>,
}

impl OBDResponse {
    pub fn new(can_id: String, size: u8, mode: String, pid: String) -> Self {
        OBDResponse {
            can_id,
            _size: size,
            _mode: mode,
            _pid: pid,
            data: Vec::with_capacity(size as usize),
        }
    }

    pub fn add(&mut self, data: u8) {
        self.data.push(data);
    }
}

//===================
// Formula Functions
//===================
const fn combine(a: f32, b: f32) -> f32 {
    a * 256.0 + b
}

const fn combine_3(b: f32, c: f32, d: f32) -> f32 {
    b * 65536.0 + combine(c, d)
}

const fn c_to_f(c: f32) -> f32 {
    c * 1.8 + 32.0
}

const fn kpa_to_psi(kpa: f32) -> f32 {
    kpa * 0.145038
}

fn two_digits(v: f32) -> f32 {
    f32::trunc(v * 100.0) * 0.01
}

/// RPM
fn _rpm(data: &[u8]) -> Result<u16> {
    let a = *data.first().unwrap_or(&0) as f32;
    let b = *data.get(1).unwrap_or(&0) as f32;

    Ok(combine(a, b) as u16)
}

/// COOLANT - F
fn coolant(data: &[u8]) -> Result<f32> {
    // default 40F
    let a = *data.first().unwrap_or(&68) as f32;

    Ok(two_digits(c_to_f(a - 64.0)))
}

/// TRANSMISSION OIL - F
fn trans_oil_temp(data: &[u8]) -> Result<f32> {
    let a = *data.first().unwrap_or(&0) as f32;
    let b = *data.get(1).unwrap_or(&0) as f32;

    // I don't know the formula for the raw value in C...
    let ans = combine(a, b) * 0.015_625; // * 1/64 - in F

    Ok(two_digits(ans))
}

/// ENGINE TEMP / VVT - F
fn engine_temp(data: &[u8]) -> Result<f32> {
    // VVT Temp [22069F] (default 40F)
    let a = *data.first().unwrap_or(&68) as f32;

    Ok(two_digits(c_to_f(a - 64.0)))

    /* 212D.... returns a multiframe presumably with much more than just engine temp

        let h = data[7] as f32;

        // Ok(h*(9.0/5.0)-83.0)
        Ok((h - 63.0f32) * 1.8f32 + 32.0f32)
    */
}

/// SPEED - kph
fn _vehicle_speed(data: &[u8]) -> Result<u8> {
    Ok(*data.first().unwrap_or(&0)) // kph
}

fn _fuel_rate(data: &[u8]) -> Result<f32> {
    let a = *data.first().unwrap_or(&0) as f32;
    let b = *data.get(1).unwrap_or(&0) as f32;

    let ans = (a * 256.0f32 + b) / 20f32;
    Ok(f32::trunc(ans * 100.0f32) / 100.0f32)
}

/// IPW - ms
fn injector_pulse_width(data: &[u8]) -> Result<f32> {
    let c = *data.get(2).unwrap_or(&0) as f32;
    let d = *data.get(3).unwrap_or(&0) as f32;

    Ok(combine(c, d) * 0.001)
}

/// MAF - g/s
fn _maf(data: &[u8]) -> Result<f32> {
    let c = *data.get(2).unwrap_or(&0) as f32;
    let d = *data.get(3).unwrap_or(&0) as f32;

    // let ans = combine(c, d) * 0.000_977_021_2;
    let ans = combine(c, d) * 0.001;

    Ok(ans)
}

/// FUEL REMAINING - gal
fn fuel_level(data: &[u8]) -> Result<f32> {
    let a = *data.first().unwrap_or(&100) as f32;
    // FC
    // 0..100 pct of tank

    // 24 gal tank
    // let ans = a - 100.0; // PCT remaining
    let ans = 24.0 * ((a - 100.0) * 0.01);

    Ok(two_digits(ans))
}

fn miles_driven(data: &[u8]) -> Result<f32> {
    let b = *data.get(1).unwrap_or(&0) as f32;
    let c = *data.get(2).unwrap_or(&0) as f32;
    let d = *data.get(3).unwrap_or(&0) as f32;

    // km to miles
    let ans = (combine_3(b, c, d) * 0.1) * 0.621371;

    Ok(two_digits(ans))
}

fn voltage(data: &[u8]) -> Result<f32> {
    /*
    Alternator Duty Cycle (%)
    TXD: 10F12220A1
    RXF: C462052036A1
    RXD: 3010
    MTH: 00648000000
    NAME: ADC
    */

    /*

    TXD	RXF	RXD	MTH	Name
    Engine Oil Life (%)	07E01AEC	445A05EC2000	2808	006400FF0000	EOL
    Tire PSI #1	7452192	410742AC73C2	1808	01F300140000
    Tire PSI #2	7452192	410742AC73C2	2008	01F300140000
    Tire PSI #3	7452192	410742AC73C2	2808	01F300140000
    Tire PSI #4	7452192	410742AC73C2	3008	01F300140000
    Current Gear (#)	33F1227A15	C462057A3615	3008	100010000	GER
    Alternator Duty Cycle (%)	07E0220378	46205030678	3010	101480000

    */

    let a = *data.first().unwrap_or(&0) as f32;
    let b = *data.get(1).unwrap_or(&0) as f32;

    let ans = combine(a, b) * 0.001;

    Ok(two_digits(ans))
}

fn oil_pressure(data: &[u8]) -> Result<u8> {
    let a = *data.first().unwrap_or(&0) as f32;

    let ans = a * 4.0; // * 29/50 for psi  (*6.89476 back to kpa - or a*4; kpa to psi *.145038)

    Ok(kpa_to_psi(ans) as u8)
}

fn iss(data: &[u8]) -> Result<u16> {
    let a = *data.first().unwrap_or(&0) as f32;
    let b = *data.get(1).unwrap_or(&0) as f32;

    Ok(combine(a, b) as u16)
}

fn oss(data: &[u8]) -> Result<u16> {
    let c = *data.get(2).unwrap_or(&0) as f32;
    let d = *data.get(3).unwrap_or(&0) as f32;

    Ok(combine(c, d) as u16)
}

fn gear_actual(data: &[u8]) -> Result<u16> {
    let f = *data.get(5).unwrap_or(&0) as f32;
    let g = *data.get(6).unwrap_or(&0) as f32;

    Ok(combine(f, g) as u16)
}

//
// For signalling when one of the critical input variables has been received from the ECU/PCM
//
/*
typedef struct
{
    // 32 bits
    int    mph:1;
    int    map:1;
    int    iat:1;
    int    rpm:1;
    int   _PADDING:28;
} accessbits32;
 */
//
// MPGData is global data structure for calculating MPG
//
/*
typedef struct
{
    union
    {
        int          accessbit32:32;
        accessbits32 accessed;
    };

    double speed_kmh;
    double speed_mph;
    double map_inHg;
    double map_kPa;
    double rpm;
    double iat_c;
    double mpg_instant;
    double fuel_instant;
    double miles_instant;
    int    mpg_count;
    double mpg_avg;
    double imap;
    double maf_gs;
    double total_miles_travelled;
    double total_fuel_consumed;
} MPGData;

MPGData m;
*/

//
// Drivetrain specific variables that can be loaded from a file
//
/*
typedef struct
{
    double ed;             // Engine Displacement
    double ve;             // Volumetric Efficiency
    double odo_correction; // odometer correction
} DriveTrain;

DriveTrain dt;
 */

//
// calc_mpg_formula
//
/*
int calc_mpg_formula()
{
    int ret;
    double iat_k;
    int kmh_zero;

    iat_k = m.iat_c + 273.15;

    if ( iat_k == 0.0)
        iat_k = ALMOST_ZERO;

    // IMAP =  RPM   * MAP:kPa    / IAT:K
    m.imap  = (m.rpm * m.map_kPa) / iat_k;

    // MAF = (IMAP/120)*(VE/100)*(ED)*(MM)/(R)
    // MAF   = ((   IMAP / 120  )*(VE:% /100)*(ED:liters)*(MM)   )/(R)
    m.maf_gs = (( m.imap / 120.0)*(dt.ve/100)*(dt.ed)    *(28.97))/(8.314);

    if ( m.maf_gs == 0.0)
        // then protect against divide by zero later on
        m.maf_gs = ALMOST_ZERO;

    // where manifold absolute pressure (MAP) is in kPa,
    // intake air temp (IAT) is in degrees Kelvin,
    // R is 8.314 J/°K/mole and
    // MM is the average molecular mass of air (MM) = 28.97 g/mole.
    // Note that, in the above formula, the volumetric
    // efficiency of the (4-cycle!) engine is measured in
    // percent and the engine displacement (ED) is in liters.

    if ( m.speed_kmh == 0.0)
    { // Not a good solution for 0 MPH, but lets give it a try
        m.speed_kmh = 0.161 / 1000.0;
        m.speed_mph = 0.10  / 1000.0;
        kmh_zero = 1;
    }
    else
    {
        kmh_zero = 0;
    }

    // miles travelled in 1 second
    m.miles_instant = m.speed_mph / 3600.0;

    if (( m.rpm < 100) && (kmh_zero == 1))
    { // then EOC
        m.mpg_instant = 9999.0;
        m.fuel_instant = 0.0;
    }
    else
    {
        // MPG - miles per gallon
        // 14.7 grams of air to 1 gram of gasoline - ideal air/fuel ratio
        // 6.17 pounds per gallon - density of gasoline
        // 454 grams per pound - conversion
        // VSS - vehicle speed in kilometers per hour
        // 0.621371 miles per hour/kilometers per hour - conversion
        // 3600 seconds per hour - conversion
        // MAF - mass air flow rate in 100 grams per second
        // 100 - to correct MAF to give grams per second => NOT NEEDED

        //MPG = (14.7*6.17*454*KPH*0.621371)/((3600*MAF)/100)
        //            => 710.7335739 * KPH          / MAF
        //            => 7.107335739 * KPH          / MAF_gs
        m.mpg_instant = (7.107335739 * m.speed_kmh) / m.maf_gs;

        // GPH / 3600 = GPSecond = ( MPH         / MPG          ) / 3600.0
        m.fuel_instant    = ( m.speed_mph / m.mpg_instant) / 3600.0;
    }

    m.mpg_count++;
    m.total_miles_travelled += m.miles_instant;
    m.total_fuel_consumed   += m.fuel_instant;

    if ( m.total_fuel_consumed != 0.0)
    {
        m.mpg_avg = m.total_miles_travelled / m.total_fuel_consumed;
    }
    else
    {
        m.mpg_avg = 0.0;
    }

    ret = m.accessbit32;
    m.accessbit32 = 0;
    return (ret);
} // END calc_mpg_formula()
  */

#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SD.h>

TinyGPS gps;
SoftwareSerial ssGPS(5, 6);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void smartdelay(unsigned long ms);
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps,String DataGPS1=" ");
static void print_str(const char *str, int len);
String DataGPS = " ";


//SD card
int CS_PIN = 4;
bool read_time;
int time_0;
unsigned int LED = 2;
const int LED1 = 8;
const int Button = 7;
boolean writeCD = false;
boolean lastButton = HIGH;
boolean currentButton = HIGH;
boolean LedOn = false;
float Hightcode = 1000000.00;
uint8_t IMUAddress = 0x68;
int32_t accX;
int16_t WlenAcc = 8;
int cou_a = 0;
int flg_fi = 1;
int32_t Accl_S = 0;
int32_t Accl_wi[8];
int n = 2;
int k = 2;
int p = 2;
int32_t Hight[3];
int32_t XAcc[3];
int32_t XSNS[3];
int32_t Accel_out = 0;

int32_t Accel_OUT = 0;
float Acc = 0;
float HightOut = 0;
//uint32_t timer;
void setup() {
pinMode(LED1,OUTPUT);
pinMode(Button,INPUT);
pinMode(LED, OUTPUT);
 Serial.begin(9600);
 ssGPS.begin(9600);
 Wire.begin();
 i2cWrite(0x6B,0x00); // Disable sleep mode
 if(i2cRead(0x75,1)[0] != 0x68) {
 Serial.print(F("MPU-6050 with address 0x"));
 Serial.print(IMUAddress,HEX);
 Serial.println(F(" is not connected"));
 while(1);
 }
 pinMode(CS_PIN, OUTPUT);

 if (!SD.begin(CS_PIN))
 {
 Serial.println("NO CARD");
 } else {Serial.println("CARD READY");
 LedOn = !LedOn;
 }

 // LED indicates GPS signal's valid

}
boolean vibro (boolean last)
{
 boolean current = digitalRead(Button);
 if (last != current)
 {
 delay(5);
 current = digitalRead(Button);
 return current;
 }
}
void loop() {

unsigned long age, date, time, chars = 0;
 currentButton = vibro(lastButton);
 if (lastButton == HIGH && currentButton == LOW)
 {
 // LedOn = !LedOn;
 writeCD = !writeCD;
 }
 lastButton = currentButton;
digitalWrite(LED1,LedOn);
 /* Update all the values */
 uint8_t* data = i2cRead(0x3B,14);
 accX = ((data[0] << 8) | data[1]);
/**/ if (flg_fi == 1)
 {
 if (cou_a < WlenAcc)
 {
 Accl_wi[cou_a] = accX; cou_a++;
 }
 else {
 flg_fi = 0;
 for (cou_a = 0; cou_a < WlenAcc; cou_a++) {Accl_S += Accl_wi[cou_a];}
 cou_a = 0;
 }
 }
 else {
 if (cou_a < WlenAcc)
 {
 Accl_S -= Accl_wi[cou_a];
 Accl_wi[cou_a] = accX;
 Accl_S += Accl_wi[cou_a];
 Accel_OUT =((Accl_S>>3) - Accel_out); // Acceleromrter Zero correction
 cou_a++;
 }
 else cou_a = 0;
 }
Acc=float(Accel_OUT);
Acc=Acc/16384;
Acc=(Acc-1)*9.728;
//DataGPS = print_date(sz);
// DataGPS = (month, day, year, hour, minute, second);
 // remember time_0 when GPS get signal
 if (!TinyGPS::GPS_INVALID_F_ALTITUDE && !read_time)
 time_0 = millis()/1000;
if (!TinyGPS::GPS_INVALID_F_ALTITUDE) {

Serial.print(" Time stamp from get GPS signal ");
Serial.print(millis()/1000 - time_0);
}
else {
 Serial.print(" Time stamp from start Arduino ");
Serial.print(millis()/1000);
}
Serial.print(" ----- Acceleration ");
Serial.print(Acc);
Serial.print(" ----- GPS altitude ");
print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);
Serial.print(" ----- accurate acceleration ");
Serial.print(HightOut);
Serial.print(" ----- test ");
// Serial.print(DataGPS);
// Serial.println(gps.date.value);
// Serial.print("Date(ddmmyy): "); Serial.print(date); Serial.print(" Time(hhmmsscc): ");
// Serial.print(time/100);
// Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
/**/
Serial.println();
delay(100); // The accelerometer's maximum samples rate is 1kHz
// Indicates working GPS
// Blink - YES data
// Continious light - NO data
 if ( gps.f_altitude()== Hightcode)
 digitalWrite(LED, HIGH); // turn the LED on (HIGH is the voltage level)
 else {
 digitalWrite(LED, HIGH);
 delay (50);
 digitalWrite(LED, LOW);
 }
 HightOut = 0.050197*XSNS[k]+0.003324*XSNS[k-1]-0.046872*XSNS[k2]+0.002374*XAcc[n]+0.004749*XAcc[n-1]+0.002374*XAcc[n-2]+1.896281*Hight[p-1]-
0.902930*Hight[p-2];
XAcc[n-2] = XAcc[n-1];
XSNS[k-2] = XSNS[k-1];
XAcc[n-1] = XAcc[n];
XSNS[k-1] = XSNS[k];


XAcc[n] = Acc;
XSNS[k] = gps.f_altitude();
Hight[p-2] = Hight[p-1];
Hight[p-1] = HightOut;
/* SD card*/
if(writeCD == true){
File dataFile = SD.open("log.csv", FILE_WRITE);
if (dataFile)
 {
// dataFile.printlngps.get_datetime(&date, &time, &age);
// dataFile.println("Date(ddmmyy): ");
// dataFile.println(date);
// dataFile.println(" Time(hhmmsscc): ");
time_0 = millis()/1000;
 dataFile.print(millis()/1000 - time_0);
 dataFile.println("sec");
 dataFile.println("Accelerate");
 dataFile.println(Acc);
 dataFile.println(", Hight GPS ");
 dataFile.println(gps.f_altitude(), 3);
 dataFile.println(", correct Hight ");
 dataFile.println(HightOut);
 dataFile.println("\n");
 dataFile.close();
 digitalWrite(LED1,LOW);
 delay(50);
 digitalWrite(LED1,HIGH);
 }
 else Serial.println("Cant open log file");
}
}
void i2cWrite(uint8_t registerAddress, uint8_t data){
 Wire.beginTransmission(IMUAddress);
 Wire.write(registerAddress);
 Wire.write(data);
 Wire.endTransmission();
}
uint8_t* i2cRead(uint8_t registerAddress, uint8_t nbytes) {
 uint8_t data[nbytes];
 Wire.beginTransmission(IMUAddress);
 Wire.write(registerAddress);
 Wire.endTransmission(false);
 Wire.requestFrom(IMUAddress, nbytes);
 
 for(uint8_t i = 0; i < nbytes; i++)
 data[i] = Wire.read();
 return data;
}
static void smartdelay(unsigned long ms)
{
 unsigned long start = millis();
 do
 {
 while (ssGPS.available())
 gps.encode(ssGPS.read());
 } while (millis() - start < ms);
}
static void print_float(float val, float invalid, int len, int prec)
{
 if (val == invalid)
 {
 while (len-- > 1)
 Serial.print('*');
 Serial.print(' ');
 }
 else
 {
 Serial.print(val, prec);
 int vi = abs((int)val);
 int flen = prec + (val < 0.0 ? 2 : 1); // . and -
 flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
 for (int i=flen; i<len; ++i)
 Serial.print(' ');
 }
 smartdelay(0);
}
static void print_int(unsigned long val, unsigned long invalid, int len)
{
 char sz[32];
 if (val == invalid)
 strcpy(sz, "*******");
 else
 sprintf(sz, "%ld", val);
 sz[len] = 0;
 for (int i=strlen(sz); i<len; ++i)
 sz[i] = ' ';
 if (len > 0) 
 
 sz[len-1] = ' ';
 Serial.print(sz);
 smartdelay(0);
}
static void print_date(TinyGPS &gps)
{
 int year;
 byte month, day, hour, minute, second, hundredths;
 unsigned long age;
 unsigned long datego;
 String DataGPS1;
 gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
 if (age == TinyGPS::GPS_INVALID_AGE)
 Serial.print("********** ******** ");
 else
 {
 char sz[32];
 sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
 month, day, year, hour, minute, second);
 Serial.print(sz);
 DataGPS1 = sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
 month, day, year, hour, minute, second);
 }
 print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
 smartdelay(0);
}
static void print_str(const char *str, int len)
{
 int slen = strlen(str);
 for (int i=0; i<len; ++i)
 Serial.print(i<slen ? str[i] : ' ');
 smartdelay(0);
}

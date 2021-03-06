IntervalTimer ATimer; 

#include "HX711.h"

#define calibration_factor 105000.00 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  23
#define CLK  22

HX711 scale;

//Pi constants 
#define PI 3.1415926535897932384626433832795 
#define HALF_PI 1.5707963267948966192313216916398 
#define TWO_PI 6.283185307179586476925286766559 
#define SAMPLING_RATE 10000 // in Hz 
#define SAMPLING_RATE_KHZ 10 // in KHz 

#define R1 11.9 //in KOhms 

int fsr=0; 
int Vin; 
float rFSR_inv, fFSR, fFilt, phyVin; 
float Theta,facTheta, dTheta; 
float fac1=10.0; // factor for adjusting resitance to force 
float fac2=20.0; //factor for relation from force to vibration frequency 
float adjF=0.02; // adjustment to add/subtract in force value 
float adjFrq = 0.0; // to adjust frequency 
float outFreq ; // the vibration frequency 
float outAmp = 1.0 ; // vibration amplitude 
float facADCToV = 3.3/4096; 
float outDAC; 
float fac; 
float fac_vibro; 
float fup;
static int setting=0;   
String inString = "";
float prev=0; 

static float filterloop(float in){ 
  static float flt = 0.; 
  static float a = .01; 
  flt = a * in + (1.-a) * flt; 
  return flt; 
} 


void setup() { 
// put your setup code here, to run once: 
  pinMode(15, OUTPUT); //e at BBB 
  pinMode(16, OUTPUT); //d at BBB 
  pinMode(17, OUTPUT); //c at BBB 
  pinMode(18, OUTPUT); //b at BBB 
  pinMode(19, OUTPUT); //a at BBB 

  pinMode(14, INPUT); 
  Serial.begin(9600); 
  int time_us; 

  analogWriteResolution(12); 
  analogReadResolution(12); 

  Theta = 0.0; // everything in radians 
  facTheta = (TWO_PI / SAMPLING_RATE);// to simplifiy calculation 

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  time_us = 1000/SAMPLING_RATE_KHZ; 
  ATimer.begin(Task1, time_us); // Task1 runs at every 100us or 10KHz 
} 

void loop() { 

  int inChar = Serial.read(); 
  if(isDigit(inChar)){
    inString+=(char)inChar;
  }
  if(inChar == '\n'){
    setting=inString.toInt();
    inString = "";
  }
  
  Serial.print("voltage= "); 
  Serial.print(phyVin);
  Serial.print(" || force= "); 
  Serial.print(fFilt);  
  Serial.print(" || mode= "); 
  Serial.print(setting);
  Serial.print(" || weight= "); 
  Serial.println(scale.get_units(), 1);
   
  if(setting==0){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==1){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==2){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==3){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==4){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==5){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==6){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==7){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==8){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==9){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==10){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 0); //e 
  }   
  if(setting==11){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==12){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==13){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==14){ 
    digitalWrite(19, 0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 0); //e 
  } 
  if(setting==15){ 
    digitalWrite(19,0); //a 
    digitalWrite(18, 1); //b 
    digitalWrite(17, 1); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==16){ 
    digitalWrite(19, 1); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 0); //e  
  } 
  if(setting==17){ 
    digitalWrite(19, 1); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 0); //d 
    digitalWrite(15, 1); //e 
  } 
  if(setting==18){ 
    digitalWrite(19, 1); //a 
    digitalWrite(18, 0); //b 
    digitalWrite(17, 0); //c 
    digitalWrite(16, 1); //d 
    digitalWrite(15, 0); //e 
  } 
  delay(10); 
} 

void Task1(void){   
  if(setting==0){ 
    fac_vibro=0.0; fup=0.0; 
  } 
  if(setting==1){ 
    fac_vibro=0.0; fup=4.0; 
  } 
  if(setting==2){ 
    fac_vibro=0.0; fup=8.0; 
  } 
  if(setting==3){ 
    fac_vibro=0.0; fup=20.0; 
  } 
  if(setting==4){ 
    fac_vibro=2.0; fup=4.0; 
  } 
  if(setting==5){ 
    fac_vibro=2.0; fup=8.0; 
  } 
  if(setting==6){ 
    fac_vibro=2.0; fup=20.0; 
  } 
  if(setting==7){ 
    fac_vibro=5.0; fup=4.0; 
  } 
  if(setting==8){ 
    fac_vibro=5.0; fup=8.0; 
  }   
  if(setting==9){ 
    fac_vibro=5.0; fup=20.0; 
  } 
  if(setting==10){ 
    fac_vibro=0.0; fup=4.0; 
  } 
  if(setting==11){ 
    fac_vibro=0.0; fup=8.0; 
  } 
  if(setting==12){ 
    fac_vibro=0.0; fup=20.0; 
  } 
  if(setting==13){ 
    fac_vibro=2.0; fup=4.0; 
  } 
  if(setting==14){ 
    fac_vibro=2.0; fup=8.0; 
  } 
  if(setting==15){ 
    fac_vibro=2.0; fup=20.0; 
  }
  if(setting==16){ 
    fac_vibro=5.0; fup=4.0; 
  } 
  if(setting==17){ 
    fac_vibro=5.0; fup=8.0; 
  } 
  if(setting==18){ 
    fac_vibro=5.0; fup=20.0; 
  } 

  Vin = analogRead(14); 
  if(Vin<250){  
    Vin=0; 
  } 
  phyVin = Vin * facADCToV; 

  // resistance of rFSR is = ((3.3v-Vin) * R1)/Vin 
  rFSR_inv = phyVin / ((3.3 - phyVin) * R1); 
  fFSR = fac1 * rFSR_inv; 

  fFilt = filterloop(fFSR); 

  fFilt = fFilt-adjF; 
  if (fFilt <= 0.0) 
    fFilt = 0; 

  if ( (fFilt < 3.0) || (fFilt > fup) ){ 
    fac = 0.; 
  } 
  // else if ( (fFilt >= 0.5) && (fFilt <= 1.0) ) 
  // { 
  // fac = 20.; 
  // } 
  else{ 
    fac = fac_vibro; 
  } 

  if(abs(fFilt/prev)>0.999 && abs(fFilt/prev)<1.001){ 
    fac = 0.; 
  } 

  outAmp = sin(TWO_PI*fac*fFilt); 

  outDAC = outAmp * 400 + 2048; 

  analogWrite(A14, (int)outDAC); 

  prev=fFilt; 
//calculate the output 
//send it to DAQ 
}

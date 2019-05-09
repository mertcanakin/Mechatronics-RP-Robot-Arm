#include "Adafruit_VL53L0X.h"
#include <Wire.h>
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#include <Servo.h>
#include <X113647Stepper.h>
#include <math.h>

Servo servo_hareket;
Servo servo_sensor;

//Step motor tanımlanması.
static const int in1= 8;
static const int in2= 9;
static const int in3= 10;
static const int in4= 11;
static const int STEPS_PER_REVOLUTION = 32 * 64;

float hipo;
float devir;    //step motorun donmesi 
float aci;      //servonun doneceği aci

int x;
int y;
float angle_degree;
float devir2;
float aci2;

tardate::X113647Stepper myStepper(
  STEPS_PER_REVOLUTION,
  in1, in2, in3, in4);


void setup(){
  servo_hareket.attach(5);
  servo_sensor.attach(3);
  myStepper.setSpeed(10);
  Serial.begin(9600); 

  // Seri portun açılması
  while(! Serial){
    delay(1);
  }
  Serial.println("Mesafe sensor testi");
  if(!lox.begin()){
    Serial.println(F("Senor calismiyor."));
    while(1);
  }
  Serial.println(F("Sensor mesafe testi\n\n")); 
}

void loop(){

VL53L0X_RangingMeasurementData_t measure;
  Serial.print("Olcum aliniyor...");
  lox.rangingTest(&measure,false);

  if(measure.RangeStatus !=4){
    Serial.print("Mesafe (mm) : ");
    Serial.println(measure.RangeMilliMeter);
  }
  else{
    Serial.println(" Araliğin disinda ");
  }
  delay(100);

  if(measure.RangeMilliMeter>300){
  aci=++aci;
  servo_sensor.write(aci);
}
  if(measure.RangeMilliMeter<300){
    Serial.println("Cisim bulundu.");
    Serial.print("Aci degeri: ");
    Serial.println(aci);
    delay(1000);
    
    servo_hareket.write(aci); 
    delay(2000);
    x=measure.RangeMilliMeter*sin(aci);
    y=measure.RangeMilliMeter*cos(aci);
    devir=62.83*measure.RangeMilliMeter;    //step motorun döndürmesi gereken açı miktarınn hesaplanması
    Serial.print("Step motorun ötelemesi :");
    Serial.println(devir);
    myStepper.step(devir);      //step motorun döndürülmesi
    delay(200);
    Serial.println("Istenen konuma gelindi");


    aci2=atan2(y,(x+50));     //Servonun öteleme yapacağı açı miktarı
    angle_degree=57.29577*aci2;    //radyanın dereceye çevrilmesi.
    Serial.print("Servonun 2.aci degeri: ");
    Serial.println(angle_degree);
    servo_hareket.write(angle_degree); 
    delay(2000);


    hipo=sqrt(50*50+y*y);     //Oteleme icin hipotenusun hesaplanması
    devir=62.83*hipo;    //step motorun döndürmesi gereken açı miktarınn hesaplanması
    Serial.print("Step motorun 2. ötelemesi :");
    Serial.println(devir);
    myStepper.step(devir);      //step motorun döndürülmesi
    Serial.print(hipo);
    delay(200);
    Serial.println("Oteleme yapildi.");

    aci2=atan2(y+50,x);     //Servonun öteleme yapacağı açı miktarı
    angle_degree=57.29577*aci2;    //radyanın dereceye çevrilmesi.
    Serial.print("Servonun 3.aci degeri: ");
    Serial.println(angle_degree);
    servo_hareket.write(angle_degree); 
    delay(2000);


    hipo=sqrt(x*x+50*50);     //Oteleme icin hipotenusun hesaplanması
    devir=62.83*hipo;    //step motorun döndürmesi gereken açı miktarınn hesaplanması
    Serial.print("Step motorun 3. ötelemesi :");
    Serial.println(devir);
    myStepper.step(devir);      //step motorun döndürülmesi
    Serial.print(hipo);
    delay(200);
    Serial.println("Oteleme yapildi.");

    servo_hareket.write(0);
    //limit switch eklencek.
    //öteleme için 50/50 hipotenüs kullan.
    Serial.println("Home pozisyonuna gelindi.");  
}
}

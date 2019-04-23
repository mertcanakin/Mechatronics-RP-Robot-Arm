#include <Servo.h>
#include <X113647Stepper.h>
#include <math.h>

Servo r_servo;

//Step motor tanımlanması.
static const int in1= 8;
static const int in2= 9;
static const int in3= 10;
static const int in4= 11;
static const int STEPS_PER_REVOLUTION = 32 * 64;

float hipo;     //öteleme için hipotenus
float devir;    //step motorun donmesi 
float angle;    //step motorun dönmesi

int x=150;
int y=68;

float angle2;
float hipo2;
float devir2;
tardate::X113647Stepper myStepper(
  STEPS_PER_REVOLUTION,
  in1, in2, in3, in4);


void setup(){
  r_servo.attach(5);
  myStepper.setSpeed(10);
  Serial.begin(9600); 
}

void loop(){

angle=atan2(y,x);     //Servonun döneceği açı miktarının radyan cinsinden hesaplanması.
float angle_degree=57.29577*angle;    //radyanın dereceye çevrilmesi.
Serial.print("Servonun aci degeri: ");
Serial.println(angle_degree);
r_servo.write(angle_degree); 
delay(2000);

hipo=sqrt(x*x+y*y);     //hipotenüsün hesaplanması
devir=62.83*hipo;    //step motorun döndürmesi gereken açı miktarınn hesaplanması
Serial.print("Step motorun ötelemesi :");
Serial.println(devir);
myStepper.step(devir);      //step motorun döndürülmesi
delay(200);
Serial.println("Istenen konuma gelindi");


angle=atan2(y,(x+50));     //Servonun öteleme yapacağı açı miktarı
angle_degree=57.29577*angle;    //radyanın dereceye çevrilmesi.
Serial.print("Servonun 2.aci degeri: ");
Serial.println(angle_degree);
r_servo.write(angle_degree); 
delay(2000);


hipo=sqrt(50*50+y*y);     //Oteleme icin hipotenusun hesaplanması
devir=62.83*hipo;    //step motorun döndürmesi gereken açı miktarınn hesaplanması
Serial.print("Step motorun 2. ötelemesi :");
Serial.println(devir);
myStepper.step(devir);      //step motorun döndürülmesi
Serial.print(hipo);
delay(200);
Serial.println("Oteleme yapildi.");

angle=atan2(y+50,x);     //Servonun öteleme yapacağı açı miktarı
angle_degree=57.29577*angle;    //radyanın dereceye çevrilmesi.
Serial.print("Servonun 3.aci degeri: ");
Serial.println(angle_degree);
r_servo.write(angle_degree); 
delay(2000);


hipo=sqrt(x*x+50*50);     //Oteleme icin hipotenusun hesaplanması
devir=62.83*hipo;    //step motorun döndürmesi gereken açı miktarınn hesaplanması
Serial.print("Step motorun 3. ötelemesi :");
Serial.println(devir);
myStepper.step(devir);      //step motorun döndürülmesi
Serial.print(hipo);
delay(200);
Serial.println("Oteleme yapildi.");

r_servo.write(0);
//limit switch eklencek.
//öteleme için 50/50 hipotenüs kullan.
Serial.println("Home pozisyonuna gelindi.");


}

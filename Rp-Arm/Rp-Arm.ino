#include <Servo.h>
#include <X113647Stepper.h>
#include <math.h>

Servo r_servo;

static const int in1= 8;
static const int in2= 9;
static const int in3= 10;
static const int in4= 11;
static const int STEPS_PER_REVOLUTION = 32 * 64;

float hipo;
float devir;
float angle;
int x=150;
int y=68;

int a0;

tardate::X113647Stepper myStepper(
  STEPS_PER_REVOLUTION,
  in1, in2, in3, in4
);

void setup(){
  r_servo.attach(5);
  myStepper.setSpeed(10);
  Serial.begin(9600); 
}

void loop(){
a0=analogRead(A0);
if(a0>500){  
angle=atan2(x,y);
float angle_degree=57.29577*angle;
Serial.print("Servonun aci degeri: ");
Serial.println(angle_degree);
r_servo.write(angle_degree);
delay(2000);

hipo=sqrt(x*x+y*y);
devir=62.83*hipo;
Serial.print("Step motorun ötelemesi :");
Serial.println(devir);
myStepper.step(devir);
delay(200);
Serial.println("Istenen konuma gelindi");
}
}

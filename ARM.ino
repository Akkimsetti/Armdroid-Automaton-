#define BLYNK_PRINT Serial//redefine  BLYNK_PRINT as Serial
#include <ESP8266WiFi.h>//header file for controlling wifi
#include <BlynkSimpleEsp8266.h>//header for blynk
#include<Servo.h>


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

char auth[] = "7JooLeAbGED_4YgKo-jD-EFE_jj2aBwv";// indentification of your board like phone number
char ssid[] = "OnePlus 8T";// your Hotspot name
char pass[] = "chandupurna";// your Hotspot password


//......................motor................................
//#define SC1 D0 // ena1 pin of motor driver/speed control of motor 1
//#define SC2 D1 // ena2 pin of motor driver/speed control of motor 2
#define M1 D5 // motor1 wire 1
#define M2 D6 // motor1 wire 2
#define M3 D7 // motor2 wire 1
#define M4 D8 // motor2 wire 2

int spd=1024;

//....................forward()....................
void forward()
{
 // analogWrite(SC1, spd); // writing the speed to left motor
 // analogWrite(SC2, spd); // writing the speed to right motor
  // left motor forward direction
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  //right motor forward direction
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("FORWARD");
}
//....................backward()....................
void backward()
{
 // analogWrite(SC1, spd); // writing the speed to left motor
 // analogWrite(SC2, spd); // writing the speed to right motor
  // left motor backward direction
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  //right motor backward direction
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
  delay(50);
  Serial.println("BACKWARD");
}
//....................left()....................
void left()
{
 // analogWrite(SC1, spd); // writing the speed to left motor
 // analogWrite(SC2, spd); // writing the speed to right motor
  // left motor backward direction
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  //right motor forward direction
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("LEFT");
}
//....................right()....................
void right()
{
 // analogWrite(SC1, spd); // writing the speed to left motor
//  analogWrite(SC2, spd); // writing the speed to right motor
  // left motor forward direction
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  //right motor backward direction
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
  delay(50);
  Serial.println("RIGHT");
}
//....................STOP()....................
void STOP()
{
 
 // analogWrite(SC1, spd); // writing the speed to left motor
 // analogWrite(SC2, spd); // writing the speed to right motor
  // left motor stop
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  //right motor stop
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("STOP");
}

//....................setup()....................
void setup() {
 // pinMode(SC1,OUTPUT);
 // pinMode(SC2,OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  // initially stop the motor
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);

  
  servo1.attach(D2); // NodeMCU D4 pin
  servo2.attach(0);
  servo3.attach(4);
  servo4.attach(5);
 
  Serial.begin(9600);//setting the speed of communication between your laptop and board

  Blynk.begin(auth, ssid, pass);// connecting to Network
}

//......................speed adjustment..................
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  spd=pinValue;// adjusting the speed
 
}

//.................reading joystick.............
BLYNK_WRITE(V1) {
  int y = param[0].asInt();//range from 0 to 1023
  int x = param[1].asInt();

  if(x>700&&y>200&&y<900) //x>700 and y in between 200 to 900
  {
    forward();
  }
  else if(x<200&&y>200&&y<900) //x<200 and y in between 200 to 900
  {
    backward();
  }
   else if(y>700&&x>200&&x<900) //y>700 and x in between 200 to 900
  {
    right();
  }
   else if(y<200&&x>200&&x<900) //y<200 and y in between 200 to 900
  {
    left();
  }
  else
  {
    STOP();
  }
}
BLYNK_WRITE(V3)

{

   servo1.write(param.asInt());

}
BLYNK_WRITE(V4)

{

   servo2.write(param.asInt());

}
BLYNK_WRITE(V5)

{

   servo3.write(param.asInt());

}
BLYNK_WRITE(V6)

{

   servo4.write(param.asInt());

}

//....................loop()....................

void loop() {
  
 Blynk.run();//communicate to mobile
  
}

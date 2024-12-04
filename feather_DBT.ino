#include <Adafruit_MotorShield.h>
#include <IRremote.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

#define IRsense 6
#define F 24
#define S 28
#define B 82
#define L 8
#define R 90
#define O 94
#define C 12
#define D 22 //down button; Arm down button
#define U 13 //up button; Arm up button
#define END 71 //func stop button; turn led back on
#define START 69

Servo s1;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);
Adafruit_DCMotor *myMotorL = AFMS.getMotor(1);
Adafruit_StepperMotor *myStepper = AFMS.getStepper(2038, 2);

int pos = 90;
int command = 69 ; 
int LED = 9;

unsigned long preMillis;

void End()
{
  digitalWrite(LED, HIGH);
  Serial.println("HOORAYYYY");
}
void Start()
{
  digitalWrite(LED, LOW);
  Serial.println("lets go!");
}
void Open()
{
  pos = pos + 10;
  s1.write(pos);
  Serial.println("Round 1");
  if (pos >= 180)
  {
  pos = 180;
  }
}
void Close()
{
  pos = pos - 10;
  s1.write(pos);
  Serial.println("fetch me their souls");
  if (pos <= 30)
  {
  pos = 5;
  }
}
void Forward()
  {

  myMotorR->setSpeed(210);
  myMotorL->setSpeed(210);

  myMotorR->run(FORWARD);
  myMotorL->run(FORWARD);

  }
void Backward()
  {

  myMotorR->setSpeed(210);
  myMotorL->setSpeed(210);

  myMotorR->run(BACKWARD);
  myMotorL->run(BACKWARD);
  }
void Left()
  {

  myMotorR->setSpeed(130);
  myMotorL->setSpeed(130);

  myMotorL->run(FORWARD);
  myMotorR->run(BACKWARD);

  }
void Right()
  {

  myMotorR->setSpeed(130);
  myMotorL->setSpeed(130);

  myMotorR->run(FORWARD);
  myMotorL->run(BACKWARD);

  }
void stop()
{

    myMotorR->run(RELEASE);
    myMotorL->run(RELEASE);

}
void Up()
{
myStepper->step(100,FORWARD,SINGLE);
}
void Down()
{
myStepper->step(100,BACKWARD,SINGLE);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
IrReceiver.begin(IRsense, ENABLE_LED_FEEDBACK);
AFMS.begin();
pinMode(LED, OUTPUT);
myStepper->setSpeed(20);
s1.attach(11);
s1.write(pos);
digitalWrite(LED, HIGH);
}

void loop() {
  if (IrReceiver.decode())
  {
    preMillis = millis();
    command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    IrReceiver.resume();
    switch (command) {
    case F : Forward(); break;
    case B : Backward(); break;
    case L : Left(); break;
    case R : Right(); break;
    case S : stop(); break;
    case U : Up(); break;
    case D : Down(); break;
    case C : Close(); break;
    case O : Open(); break;
    case START: Start(); break;
    case END: End(); break;
    }

  }
    else{
    if(millis() - preMillis > 100){
      stop();
      preMillis = millis();
      }
    }

}
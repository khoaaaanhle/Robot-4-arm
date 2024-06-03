#include <Ps3Controller.h>
#include <ESP32_Servo.h>
Servo servoL;
Servo servoR;
Servo servoB;
Servo servoC;
int rX;
int rY;
int lX;
int lY;
int posR = 50;
int posL = 50;
int posB = 0;
int posC = 90;
int enableRightMotor=22; 
int rightMotorPin1=16;
int rightMotorPin2=17;
int enableLeftMotor=23;
int leftMotorPin1=18;
int leftMotorPin2=19;
#define MAX_MOTOR_SPEED 200 
const int PWMFreq = 1000; 
const int PWMResolution = 8;

const int PWMSpeedChannel = 4; 
void notify()
{
lX =(Ps3.data.analog.stick.lx);
lY =(Ps3.data.analog.stick.ly);
rX =(Ps3.data.analog.stick.rx);
rY =(Ps3.data.analog.stick.ry);
Serial.print(lX);
Serial.print(" ");
Serial.print(lY);
Serial.print(" ");
Serial.print(rX);
Serial.print(" ");
Serial.println(rY);
 if(lX < -5 && posC < 180)
{
 posC=posC+5;
 servoC.write(posC);
}
if(lX > 5 && posC > 0)

{
 posC=posC-5;
 servoC.write(posC);
}
if(lY < -5 && posR < 180)
{
 posR=posR+5;
 servoR.write(posR);
}
if(lY > 5 && posR > 0)
{
 posR=posR-5;
 servoR.write(posR);
}
if(rY < -5 && posL < 180)
{
 posL=posL+5;
 servoL.write(posL);
}
if(rY > 5 && posL > 0)
{

 posL=posL-5;
 servoL.write(posL);
}
if(rX < -5 && posB < 180)
{
 posB=posB+5;
 servoB.write(posB);
}
if(rX > 5 && posB > 0)
{
posB=posB-5;
 servoB.write(posB);
}
if( abs(Ps3.event.analog_changed.button.l2) ){
 servoC.write(0);
 }
if( abs(Ps3.event.analog_changed.button.r2) ){
 servoC.write(170);
 }
 if (Ps3.data.button.up) 
 {
rotateMotor(MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
 }
 else if (Ps3.data.button.down) 
 {
 rotateMotor(-MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
 }
 else if (Ps3.data.button.right) 
 {
 rotateMotor(-MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
 }
 else if (Ps3.data.button.left) 
 {
 rotateMotor(MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
 }
 else 
 {
 rotateMotor(0, 0);
 } 
 delay(10);
}
void onConnect()
{
 Serial.println("Connected!.");
}
void onDisConnect()
{
 Serial.println("Disconnected!."); 
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
 if (rightMotorSpeed < 0)
 {
 digitalWrite(rightMotorPin1,LOW);
 digitalWrite(rightMotorPin2,HIGH); 
 }
 else if (rightMotorSpeed > 0)
 {
 digitalWrite(rightMotorPin1,HIGH);
 digitalWrite(rightMotorPin2,LOW); 
 }
else
 {
 digitalWrite(rightMotorPin1,LOW);
 digitalWrite(rightMotorPin2,LOW); 
 }
 if (leftMotorSpeed < 0)
 {
 digitalWrite(leftMotorPin1,LOW);
 digitalWrite(leftMotorPin2,HIGH); 
 }
 else if (leftMotorSpeed > 0)
 {
 digitalWrite(leftMotorPin1,HIGH);
 digitalWrite(leftMotorPin2,LOW); 
 }
 else//Xe dừng
 {
 digitalWrite(leftMotorPin1,LOW);
 digitalWrite(leftMotorPin2,LOW); 
 } 
}
void setUpPinModes()
{
 pinMode(enableRightMotor,OUTPUT);
 pinMode(rightMotorPin1,OUTPUT);
 pinMode(rightMotorPin2,OUTPUT);
 pinMode(enableLeftMotor,OUTPUT);
 pinMode(leftMotorPin1,OUTPUT);
 pinMode(leftMotorPin2,OUTPUT);
 ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);
 ledcAttachPin(enableRightMotor, PWMSpeedChannel);
 ledcAttachPin(enableLeftMotor, PWMSpeedChannel);
 ledcWrite(PWMSpeedChannel, MAX_MOTOR_SPEED);
 rotateMotor(0, 0); 
}
void setup()
{
 setUpPinModes();
 Ps3.attachOnDisconnect(onDisConnect);
 Serial.begin(115200);
 Ps3.attach(notify);
 Ps3.attachOnConnect(onConnect);
 Ps3.begin("01:02:03:04:05:06");
 Serial.println("Ready.");
 servoL.attach(25); 
 servoR.attach(26);
 servoB.attach(27);
 servoC.attach(33);
 servoL.write(posL);
 servoR.write(posR);
 servoB.write(posB);
 servoC.write(posC);
}void loop()
{
}

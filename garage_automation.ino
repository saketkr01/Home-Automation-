#include <Servo.h>

int pos = 0;

int red = 13,
	blue = 12,
	green = 11;

Servo servo_9;

int cm = 0,
	cm1 = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  for(int x=11; x<=13; x++)
    pinMode(x, OUTPUT);
  Serial.begin(9600);
  //servo_9.attach(9);
  servo_9.attach(9, 500, 2500);
  servo_9.write(pos);
  digitalWrite(red, HIGH);	//starts red
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  cm1 = 0.01723 * readUltrasonicDistance(8, 8);
  
  if(cm<200) {
    digitalWrite(red, HIGH);	//turn yellow
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    
    //Opens shutter
    for (pos; pos <= 180; pos += 1) {
      servo_9.write(pos);
      delay(15); }
    digitalWrite(red, LOW);	//turn green
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    
    while(cm1>200) {
      delay(500);
      cm1 = 0.01723 * readUltrasonicDistance(8, 8); }
    while(cm1<200) {
      delay(500);
      cm1 = 0.01723 * readUltrasonicDistance(8, 8); }
    digitalWrite(red, HIGH);	//turn red
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    
    //Closes shutter
    for (pos=pos; pos >= 0; pos -= 1) {
      servo_9.write(pos);
      delay(15); }
  }
  
  if(cm1<200) {
    digitalWrite(red, HIGH);	//turn yellow
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    
    //Opens shutter
    for (pos; pos <= 180; pos += 1) {
      servo_9.write(pos);
      delay(15); }
    digitalWrite(red, LOW);	//turn green
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    
    while(cm>200) {
      delay(500);
      cm = 0.01723 * readUltrasonicDistance(7, 7); }
    while(cm<200) {
      delay(500);
      cm = 0.01723 * readUltrasonicDistance(7, 7); }
    digitalWrite(red, HIGH);	//turn red
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    for (pos=pos; pos >= 0; pos -= 1) {
      servo_9.write(pos);
      delay(15); }
  }
}
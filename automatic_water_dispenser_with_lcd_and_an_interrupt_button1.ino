
#include <LiquidCrystal.h>

#define trigPin 9
#define echoPin 8
#define motorPin 7
#define buttonPin 2

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 6, 5, 4, 3); 

int Contrast=20;

volatile long duration;
volatile int distance;

volatile boolean glassPresent;
volatile boolean isPouring;
volatile int seconds;
volatile int buttonState = 0;

void setup() {
  isPouring = false;
  analogWrite(10,Contrast);
  pinMode(motorPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  glassPresent = true;
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(buttonPin), interrupt, CHANGE);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  measureDistance();

  if (distance<80){
    pour();
  }
  else{
    glassPresent = true;
  stopPump();
  }
  delay(50);
  
}

void printReady(){
  lcd.setCursor(0, 0);
lcd.print("Water dispenser");
  lcd.setCursor(0, 1);
  lcd.print("*****Ready******");
}
void printBusy(){
  lcd.setCursor(0, 0);
lcd.print("Water dispenser");
  lcd.setCursor(0, 1);
  lcd.print("*****Busy*********");
}

void removeGlass(){
  if(glassPresent){
    digitalWrite(motorPin, LOW);
    lcd.setCursor(0, 0);
lcd.print("Please remove   ");
  lcd.setCursor(0, 1);
  lcd.print("glass!!!        ");
  }
}

void pour(){
  while(!glassPresent){
    isPouring = true;
  printBusy();
digitalWrite(motorPin, HIGH);
    glassPresent = true;
  delay(5000);
 
  } 
  removeGlass();
  isPouring = false;
}
void stopPump(){
  isPouring = false;
    digitalWrite(motorPin, LOW);
    glassPresent = false;
    printReady();
}
void interrupt(){
  if(glassPresent && isPouring){
    digitalWrite(motorPin, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Interrupted!!!  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(3000);
    lcd.clear();
    isPouring = false;
     removeGlass();
  } else{
  return;}
}

void measureDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance= duration*0.034/2;
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
}
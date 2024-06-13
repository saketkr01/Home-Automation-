// C++ code
//
#include<LiquidCrystal.h>
 LiquidCrystal lcd(12,11,4,5,6,7);
int ledPin = 13;
int inputPin = 10;
int pirState = LOW;
int val = 2;
int piezoPin = 8;

void setup()
{
 lcd.begin(16,2); 
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(inputPin, INPUT);
  lcd.print("Autometrons");
   for (int i = 0; i <= 100; i++){  // you can change the increment value here
    lcd.setCursor(13,0);
    lcd.print(i);
    lcd.print("%");
    delay(25);  //change the delay to change how fast the boot up screen changes
   }
  for (int i = 0; i < 15; i++) {
    lcd.setCursor(i, 2);
    lcd.print("->");
    delay(70);
  }
  lcd.clear();
  lcd.print("It seems safe");
}

void loop()
{
  
  val = digitalRead(inputPin);
  if(val == HIGH){
   digitalWrite(ledPin, HIGH);

   digitalWrite(ledPin, HIGH);
    tone (piezoPin, 1000, 500);
    
    if(pirState == LOW){
      lcd.setCursor(0,0);
      lcd.clear();
     lcd.print("Someone is there");
      delay(1000);
      pirState = HIGH;
    }
        } else{
          digitalWrite(ledPin, LOW);
          
          if(pirState == HIGH){
            lcd.setCursor(0,1);
            lcd.clear();
           lcd.print("No Movement");
            delay(1000);
            pirState = LOW;
          }
        }
}
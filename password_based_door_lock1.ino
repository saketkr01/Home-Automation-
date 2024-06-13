#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define Password_Length 5

#define buzzer 8

Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int pos = 0;

char Data[Password_Length];		//to store entered password
char Master[Password_Length] = "1234";
byte data_count = 0, master_count = 0;

bool Pass_is_good;
bool door = false;
char customKey;


/*---preparing keypad---*/

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


/*--- Main Action ---*/
void setup()
{
  myservo.attach(9, 500, 2400);
  ServoClose();
  lcd.begin(16, 2);
  lcd.print("Autometrons");
   for (int i = 0; i <= 100; i++){  // you can change the increment value here
    lcd.setCursor(13,0);
    lcd.print(i);
    lcd.print("%");
    delay(25);  //change the delay to change how fast the boot up screen changes
   }
  lcd.clear();
  lcd.setCursor(0,0);
  loading("Initiating");
  lcd.clear();
}


void loop()
{
  if (door == true)
  {
    customKey = customKeypad.getKey();
    if (customKey == '#')
    {
      lcd.clear();
      ServoClose();
      lcd.print("Door is Locked");
      delay(3000);
      door = false;
    }
  }
  else
    Open();

}

void loading (char msg[]) {
  lcd.setCursor(0, 0);
  lcd.print(msg);
  for (int i = 0; i < 15; i++) {
    lcd.setCursor(i, 2);
    lcd.print("->");
    delay(70);
  }
  
}

//to clear the entered password
void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0;
  }
  return;
}

void ServoClose()
{
  for (pos = 90; pos >= 0; pos -= 10) { 
    myservo.write(pos);
  }
}

void ServoOpen()
{
  for (pos = 0; pos <= 90; pos += 10) {
    myservo.write(pos);  
  }
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey)
  {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == Password_Length - 1)
  {
    if (!strcmp(Data, Master))
    {
      lcd.clear();
      ServoOpen();
      lcd.print("Door is Unlocked");
      door = true;
      delay(5000);
      lcd.clear();
      loading("Waiting");
      delay(5000);
      lcd.clear();
      lcd.print("Time is up!");
      lcd.setCursor(0,1);
      lcd.print("Door locked");
      delay(1000);
      ServoClose();
      door = false;      
    }
    else
    {
      lcd.clear();
      lcd.print(" Wrong Password ");
      door = false;
      tone(buzzer, 700, 100);
    }
    delay(1000);
    lcd.clear();
    clearData();
  }
}
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include "IRremote.h"
#include "IR.h"
IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

int led_speaker_pin = 13;
int testplay = 3;
#define RED 9
#define GREEN 5
#define BLUE 6

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

void setup() {
  lcd.begin();
   
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
  
  pinMode(led_speaker_pin, OUTPUT);
  pinMode(testplay, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);      
  // Initiate the LCD:
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(BLUE,LOW);
  
}

bool runIt = true;
void loop() {
  #define delayTime 100

  delay(500);
  runIt = true;
  //delay(100);
  lcd.clear();
  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(1, 0); // Set the cursor on the third column and first row.
  lcd.print("[. .] < Yo"); // Print the string "Hello World!"
  int tmpValue;
  digitalWrite(testplay, HIGH);
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    for (int i = 0; i < 23; i++)
    {
      if ((keyValue[i] == results.value) && (i<KEY_NUM))
      {
        Serial.println(keyBuf[i]);
        tmpValue = results.value;

        if (keyValue[i] == KEY_PAUSE) {
            lcd.backlight(); 
            lcd.clear();
            lcd.setCursor(1, 0); // Set the cursor on the third column and first row.
            lcd.print("[^ ^] < Music"); // Print the string "Hello World!"
            Serial.print("On\n");
            digitalWrite(led_speaker_pin, HIGH);
            delay(3000);
            digitalWrite(testplay, LOW);
            digitalWrite(RED,HIGH);
            digitalWrite(GREEN,LOW);
            digitalWrite(BLUE,HIGH);
            } else if (keyValue[i] == KEY_POWER) {
              lcd.clear();
              lcd.setCursor(1, 0); // Set the cursor on the third column and first row.
              lcd.print("[x x] < OFF"); // Print the string "Hello World!"
              Serial.print("OFF\n");
              digitalWrite(led_speaker_pin, LOW);
              digitalWrite(RED,LOW);
              digitalWrite(GREEN,LOW);
              digitalWrite(BLUE,LOW);
              delay(500);
              lcd.noBacklight();
          
            } else if (keyValue[i] == KEY_UP) {
              lcd.clear();
              lcd.setCursor(1, 0); // Set the cursor on the third column and first row.
              lcd.print("[. .] < Next"); // Print the string "Hello World!"
              digitalWrite(testplay, LOW); 
            }
            else if (keyValue[i] == KEY_EQ) {
              lcd.backlight();
              lcd.clear();
              lcd.setCursor(1, 0); // Set the cursor on the third column and first row.
              lcd.print("[. .] < lights"); // Print the string "Hello World!"
           
              
                digitalWrite(RED,HIGH);
                digitalWrite(GREEN,LOW);
                digitalWrite(BLUE,HIGH);
                delay(100);
                digitalWrite(RED,LOW);
                digitalWrite(GREEN,HIGH);
                digitalWrite(BLUE,HIGH);
                delay(100);
                digitalWrite(RED,HIGH);
                digitalWrite(GREEN,HIGH);
                digitalWrite(BLUE,LOW);
                delay(100);
                digitalWrite(RED,HIGH);
                digitalWrite(GREEN,LOW);
                digitalWrite(BLUE,LOW);
                delay(100);
                digitalWrite(RED,LOW);
                digitalWrite(GREEN,LOW);
                digitalWrite(BLUE,HIGH);
                delay(100);
                digitalWrite(RED,LOW);
                digitalWrite(GREEN,LOW);
                digitalWrite(BLUE,LOW);
                lcd.clear();
              lcd.setCursor(1, 0); // Set the cursor on the third column and first row.
              lcd.print("[* *] < neat");
              delay(500);
              lcd.noBacklight();
              
            }
        } else if(REPEAT==i)
          {
        results.value = tmpValue;
        }
      }
      irrecv.resume(); // receive the next value
  }
}

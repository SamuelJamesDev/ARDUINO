#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>
Servo servo;
constexpr uint8_t RST_PIN = 9;
constexpr uint8_t SS_PIN = 10;

// light
int led1 = 6;

// for RFID Reader
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
int angle = 90;
int count;
void setup() {;
  pinMode(led1, OUTPUT);
  servo.attach(8);
  servo.write(angle);
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  Serial.println("Validating access.....");
}
//End Setup__________________________________________________________

void loop() {
  digitalWrite(led1, LOW);
  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  //__________________________________________________________
  // Dump UID
  String content= "";
  byte letter;
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  } 
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  // check card _____________change here for UID of the card/cards_________________________
  if (content.substring(1) == "29 9C 04 B3" || content.substring(1) == "CA 73 F4 81") { 
  //_______________________________________________________________________________________
    Serial.println("Authorized access");
    Serial.println();
    // scan from 0 to 180 degrees
    //__________________________________________________________
    if(count == 0) {
      digitalWrite(led1, HIGH); 
      count = count + 1;
      Serial.println(count);
      for(angle = 90; angle > 0; angle--)  {                                  
        servo.write(angle);              
        delay(15);                   
      } 
      return;
    }
    if(count == 1){   
      digitalWrite(led1, HIGH); 
      count = 0;
      // now scan back from 180 to 0 degrees
      for(angle = 0; angle < 90; angle++)    {                                
        servo.write(angle);          
        delay(15);       
      } 
    }

  }
 // if not card_______________________________________________________________________________________
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
 delay(3000);
}
//End Loop _______________________________________________________________________________________

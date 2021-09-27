#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     15 // Number of snowflakes in the animation example
long randomNumber;
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    32
// this is the reaper character to move:
static const unsigned char PROGMEM reaper_bmp[] =
{
0b00000000, 0b00001111, 0b11110000, 0b00000000,
0b00000011, 0b11111111, 0b11111000, 0b00000000,
0b00011100, 0b10001000, 0b10000111, 0b00000000,
0b00100010, 0b00010000, 0b00100000, 0b10000000,
0b01000001, 0b10100011, 0b00010000, 0b01000000,
0b10001011, 0b10000110, 0b10001000, 0b00100000,
0b10000011, 0b10110111, 0b10000100, 0b00010000,
0b10010000, 0b01110000, 0b00000100, 0b00100000,
0b10001110, 0b01110000, 0b10000100, 0b00100000,
0b10010111, 0b11111111, 0b10001000, 0b01000000,
0b01000011, 0b11111111, 0b00010000, 0b10000000,
0b00110010, 0b01000000, 0b00100001, 0b00000000,
0b00001111, 0b11110000, 0b01000110, 0b00000000,
0b00000000, 0b00001111, 0b11111000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
};

// this is the pumpkin for getting points
static const unsigned char PROGMEM pumpkin_bmp[] =
{
0b00000000, 0b00000111, 0b00000000, 0b00000000,
0b00000000, 0b00001000, 0b11000000, 0b00000000,
0b00000001, 0b11010101, 0b01100000, 0b00000000,
0b00000111, 0b11110000, 0b01100000, 0b00000000,
0b00011110, 0b00110111, 0b11100000, 0b00000000,
0b00111000, 0b00011000, 0b00010000, 0b00000000,
0b01110000, 0b00011100, 0b00001000, 0b00000000,
0b11000000, 0b00010110, 0b01000100, 0b00000000,
0b10000000, 0b00010011, 0b00100010, 0b00000000,
0b00000000, 0b00010001, 0b10100010, 0b00000000,
0b00000000, 0b00010000, 0b11000100, 0b00000000,
0b00000000, 0b00010000, 0b01111000, 0b00000000,
0b00000000, 0b00010000, 0b00111000, 0b00000000,
0b00000000, 0b00010000, 0b00011000, 0b00000000,
0b00000000, 0b00010000, 0b00001000, 0b00000000,
0b00000000, 0b00011111, 0b11111100, 0b00000000,
};

// Declare both button pins for L & R
int buttonPin = 5;
int buttonPinL = 9;
// initialize our points for the game
int pnt = 0;

// begin serial monitor, start button input, begin display
void setup() {
  randomSeed(analogRead(A0));
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPinL, INPUT_PULLUP);
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
  Hello2(); // prompt player to begin
  
}
//////////////////////////////////////////////////LOOOOOp
String comp;
// Loop holding the movement which calls the game functions.
void loop() {
  comp = Command();
  delay(1
  if(digitalRead(buttonPin) == LOW) {    
    testdrawbitmap(comp);
    delay(100);
  } else if(digitalRead(buttonPinL) == LOW){
    testdrawbitmap2(comp);
    delay(100);
  } 
}
//////////////////////////////////////////////////LOOOOOp

// initialize X as our movement variable
int x = 1;
void testdrawbitmap(String comp) {
  display.clearDisplay();
  // display the points
  points();
  if(!comp.equals("RIGHT")){
    pnt-=1;
    return;
  } else {
    pnt += 1;
  }
  x+=10;
  if(x >= 64){
    // give 10 point if they can make it to one end without mistakes
    pnt+=10;
    pumpkin();
    return;
  }
  // display actual bitmap character mvoement
  display.drawBitmap(
    (((display.width()  - LOGO_WIDTH ) / 2) + x),
    (display.height() - LOGO_HEIGHT) / 2,
    pumpkin_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(100);
}

void testdrawbitmap2(String comp) {
  display.clearDisplay();
  points();
  if(!comp.equals("LEFT")){
    pnt-=1;
    return;
  } else {
    pnt += 1;
  }
  x-=10;
  if(x <= -64){
    // give 10 point if they can make it to one end without mistakes
    pnt+=10;
    pumpkin();
    return;
  }
  // display actual bitmap character mvoement
  display.drawBitmap(
    (((display.width()  - LOGO_WIDTH ) / 2) + x),
    (display.height() - LOGO_HEIGHT) / 2,
    pumpkin_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(100);
}

void pumpkin(void) {
  display.clearDisplay();
  display.drawBitmap(
    (((display.width()  - LOGO_WIDTH ) / 2)),
    (display.height() - LOGO_HEIGHT) / 2,
    reaper_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(100);
  x = 1;
}

void Hello2() {
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1,20);
display.print("Begin...");
display.display();
}

void points() {
if(pnt > 20){
  testanimate(pumpkin_bmp, LOGO_WIDTH, LOGO_HEIGHT);
}
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1,10);
display.print(pnt);
display.display();
}

String Command() {
randomNumber = random(0,2);
String test[] = {"LEFT","RIGHT"};
String choice = test[randomNumber];
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(50,10);
display.print(choice);
display.display();
return choice;
}


#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}

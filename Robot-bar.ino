
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Servo.h>

// TFT 1.8" module pins
#define TFT_CS     5
#define TFT_RST    7 
#define TFT_DC     8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
#define TFT_SCLK 13   
#define TFT_MOSI 11  


Servo myservo;
Servo myservo2;
const int PUMPPIN = 9;    //peristaltic pump control pin, connect to arduino digital pin 9
const int PUMPPIN2 = 10;  //peristaltic pump control pin, connect to arduino digital pin 10
#define waitTime 10000 //interval time(ms) between every state
const int buttonPin = 12;
int buttonState = 0;

void setup(void) {
  Serial.begin(9600);

  // pump setup
  myservo.attach(PUMPPIN);
  myservo2.attach(PUMPPIN2);
  pinMode(buttonPin, INPUT);

  // Display setup
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  // large block of text
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setTextSize(3);
  testdrawtext(0, 20, "Skal du ha GT?", ST7735_WHITE);
  // draws arrow
  tft.drawLine(20, 100, 100, 100, ST7735_WHITE);
  tft.drawLine(70, 80, 100, 100, ST7735_WHITE);
  tft.drawLine(70, 120, 100, 100, ST7735_WHITE);

  delay(1000);

}

void loop() {
  //cheking if the button is pressed. If pressed, turns on pumps
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState == HIGH) {
    // pumpspeed range from 0-180 where 0 and 180 i max speed in different direction. 90 is stop
    myservo.write(180);
    myservo2.write(180);
    delay(waitTime);

    myservo.write(90);
    myservo2.write(180);
    delay(waitTime);
  } else {
    // turn LED off:
    myservo.write(90); 
    myservo2.write(90); 
    delay(100);
  }
  delay(10);
}

void testdrawtext(int wid, int hei, char *text, uint16_t color) {
  tft.setCursor(wid, hei);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}



// Version 1.1: OO version
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#include <ByteBuffer.h>
#include <ooPinChangeInt.h> // necessary otherwise we get undefined reference errors.

#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#define DEBUG
#ifdef DEBUG
ByteBuffer printBuffer(200);
#endif
#include <AdaEncoder.h>

#define ENCA_a 0
#define ENCA_b 1

AdaEncoder encoderA = AdaEncoder('a', ENCA_a, ENCA_b);

int8_t clicks=0;
char id=0;

void setup()
{
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  testdrawtext("Starting Up", ST7735_WHITE);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(5000);
}

void loop() 
{
  AdaEncoder *thisEncoder=NULL;
  thisEncoder=AdaEncoder::genie();
  if (thisEncoder != NULL) {
    tft.print(thisEncoder->getID()); tft.print(':');
    clicks=thisEncoder->query();
    if (clicks > 0) {
      tft.println(" CW");
      digitalWrite(13, HIGH);
    }
    if (clicks < 0) {
       tft.println(" CCW");
      digitalWrite(13, LOW);
    }
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

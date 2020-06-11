#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library

// ST7789 TFT module connections
#define TFT_CS    10  // define chip select pin
#define TFT_DC     9  // define data/command pin
#define TFT_RST    8  // define reset pin, or set to -1 and connect to Arduino RESET pin

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
const int center = tft.width() / 2; // width & heigth are both 240 so it's the same for X and Y

float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));

  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel

  // if the screen is flipped, remove this command
  tft.setRotation(2);

  Serial.println(F("Initialized"));

  //  uint16_t time = millis();
  //  tft.fillScreen(ST77XX_BLACK);
  //  time = millis() - time;

  tft.fillScreen(ST77XX_BLACK);
  tft.fillCircle(center, center, 90, 0xFF4C4C);

  float width = 440;
  float height = 380;
  float x = -100;
  float y = -50;
  float yy = 280;
  while (width >= 180 &&  height >= 120) {
    tft.drawRoundRect(x, y, width, height, 180, ST77XX_WHITE);
    x += 0.5;
    y += 0.5;
    width -= 1;
    height -= 1;
  }

  width = 440;
  height = 380;
  x = -100;
  y = 290;
  while (width >= 180 &&  height >= 120) {
    tft.drawRoundRect(x, y, width, height, 180, ST77XX_WHITE);
    x += 0.5;
    y -= 0.5;
    width -= 1;
    height -= 1;
  }
}

void loop() {

}

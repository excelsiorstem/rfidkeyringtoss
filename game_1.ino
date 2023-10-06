// rfid key ring toss
// maker faire coney island

#include <TM1637Display.h>
#define CLK 5
#define DIO 6
TM1637Display display = TM1637Display(CLK, DIO);

#include "FastLED.h"
#define NUM_LEDS 212
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
const int NEO = 7;
int w, y, z;

#include <SPI.h>
#include <MFRC522.h>
#define SS_1_PIN  8
#define SS_2_PIN 11
#define SS_3_PIN 10
#define SS_4_PIN  9
#define RST_PIN  12
MFRC522 rfid100(SS_1_PIN, RST_PIN);
MFRC522 rfid150(SS_2_PIN, RST_PIN);
MFRC522 rfid200(SS_3_PIN, RST_PIN);
MFRC522 rfid250(SS_4_PIN, RST_PIN);

const int photoresistor = 3;
int term;
int loc100;
int loc150;
int loc200;
int loc250;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, NEO, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  display.clear();
  display.setBrightness(4);
  SPI.begin();
  rfid100.PCD_Init();
  rfid150.PCD_Init();
  rfid200.PCD_Init();
  rfid250.PCD_Init();
  pinMode(photoresistor, INPUT);
  neo_win(0, 0, 255);
}

void loop() {
  neo_loop(0, 0, 255);
}

void neo_loop(int r, int g, int b) {
  z = random(5, 60);
  for (w = 0; w < NUM_LEDS; w++) {
    pixel(r, g, b, w);
    display.clear();
    display.showNumberDec(w);
    if (w < 5) {
      if (w == 0) {
        y = NUM_LEDS - 5;
        pixel(0, 0, 0, y);
      } else if (w == 1) {
        y = NUM_LEDS - 4;
        pixel(0, 0, 0, y);
      } else if (w == 2) {
        y = NUM_LEDS - 3;
        pixel(0, 0, 0, y);
      } else if (w == 3) {
        y = NUM_LEDS - 2;
        pixel(0, 0, 0, y);
      } else if (w == 4) {
        y = NUM_LEDS - 1;
        pixel(0, 0, 0, y);
      } else if (w == 5) {
        y = NUM_LEDS;
        pixel(0, 0, 0, y);
      }
    } else {
      y = w - 5;
      pixel(0, 0, 0, y);
    }

    // tom servo
    if (digitalRead(photoresistor) == LOW) {
      for (int m = 500; m > 0; m--) {
        display.clear();
        display.showNumberDec(m);
      }
    }

    // 100
    if (w < 42 || w > 183) {
      pixel(255, 125, 0, 47);
    }
    if (w == 41) {
      pixel(0, 0, 0, 47);
      check_rfid();
      // win
      while (loc100 == 1) {
        display.clear();
        display.showNumberDec(100);
        neo_win(0, 255, 0);
        check_rfid();
      }
      // lose
      while (loc150 == 1 || loc200 == 1 || loc250 == 1) {
        display.clear();
        display.showNumberDec(-0);
        neo_lose(255, 0, 0);
        check_rfid();
      }
      z = random(5, 60);
    }

    // 200
    if (w < 67 && w > 41) {
      pixel(255, 125, 0, 63);
    }
    if (w == 66) {
      pixel(0, 0, 0, 63);
      check_rfid();
      // win
      while (loc200 == 1) {
        display.clear();
        display.showNumberDec(200);
        neo_win(0, 255, 0);
        check_rfid();
      }
      // lose
      while (loc100 == 1 || loc200 == 1 || loc250 == 1) {
        display.clear();
        display.showNumberDec(-0);
        neo_lose(255, 0, 0);
        check_rfid();
      }
      z = random(5, 60);
    }

    // 250
    if (w < 139 && w > 66) {
      pixel(255, 125, 0, 134);
    }
    if (w == 138) {
      pixel(0, 0, 0, 134);
      check_rfid();
      // win
      while (loc250 == 1) {
        display.clear();
        display.showNumberDec(250);
        neo_win(0, 255, 0);
        check_rfid();
      }
      // lose
      while (loc100 == 1 || loc150 == 1 || loc200 == 1) {
        display.clear();
        display.showNumberDec(-0);
        neo_lose(255, 0, 0);
        check_rfid();
      }
      z = random(5, 60);
    }

    // 150
    if (w < 184 && w > 138) {
      pixel(255, 125, 0, 177);
    }
    if (w == 183) {
      pixel(0, 0, 0, 177);
      check_rfid();
      // win
      while (loc150 == 1) {
        display.clear();
        display.showNumberDec(150);
        neo_win(0, 255, 0);
        check_rfid();
      }
      // lose
      while (loc100 == 1 || loc200 == 1 || loc250 == 1) {
        display.clear();
        display.showNumberDec(-0);
        neo_lose(255, 0, 0);
        check_rfid();
      }
      z = random(5, 60);
    }
    delay(z);
  }
}

void check_rfid() {
  if (rfid100.PICC_IsNewCardPresent()) {
    if (rfid100.PICC_ReadCardSerial()) {
      loc100 = 1;
    }
  } else {
    loc100 = 0;
  }
  delay(20);
  if (rfid150.PICC_IsNewCardPresent()) {
    if (rfid150.PICC_ReadCardSerial()) {
      loc150 = 1;
    }
  } else {
    loc150 = 0;
  }
  delay(20);
  if (rfid200.PICC_IsNewCardPresent()) {
    if (rfid200.PICC_ReadCardSerial()) {
      loc200 = 1;
    }
  } else {
    loc200 = 0;
  }
  delay(20);
  if (rfid250.PICC_IsNewCardPresent()) {
    if (rfid250.PICC_ReadCardSerial()) {
      loc250 = 1;
    }
  } else {
    loc250 = 0;
  }
  digitalWrite(RST_PIN, LOW);
  delay(20);
  rfid100.PCD_Init();
  rfid150.PCD_Init();
  rfid200.PCD_Init();
  rfid250.PCD_Init();
}

void neo_win(int r, int g, int b) {
  for (w = 0; w < NUM_LEDS; w++) {
    pixel(r, g, b, w);
    delay(10);
  }
  for (w = 0; w < NUM_LEDS; w++) {
    pixel(0, 0, 0, w);
    delay(10);
  }
}

void neo_lose(int r, int g, int b) {
  for (w = 0; w < NUM_LEDS; w++) {
    pixel(r, g, b, w);
    delay(10);
  }
  for (w = 0; w < NUM_LEDS; w++) {
    pixel(0, 0, 0, w);
    delay(10);
  }
}

void pixel(int r, int g, int b, int p) {
  leds[p] = CRGB (r, g, b);
  FastLED.show();
}

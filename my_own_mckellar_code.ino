#include <FastLED.h>
#include "ledstrip.h"

// TO CHANGE NUMBER OF STRIPS - CHANGE THE DEFINED LED PINS, CHANGE NUM_STRIPS, AND ADD THE NEEDED AMOUNT OF INITIALIZATION LINES IN THE BEGINNING OF initializeLeds()

// default variables
#define LED1_PIN     35
#define LED2_PIN     37
#define LED3_PIN     39
#define LED4_PIN     41
#define SENSOR1_PIN 43

#define LED5_PIN     45
#define LED6_PIN     47
#define LED7_PIN     49
#define LED8_PIN     51
#define SENSOR2_PIN 53

#define LED9_PIN     34
#define LED10_PIN     36
#define LED11_PIN     38
#define LED12_PIN     40
#define SENSOR3_PIN 42

#define LED13_PIN     44
#define LED14_PIN     46
#define LED15_PIN     48
#define LED16_PIN     50
#define SENSOR4_PIN 52

#define NUM_LEDS    70
#define BRIGHTNESS  255
#define NUM_STRIPS  10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define NUM_LEDS    70
#define BRIGHTNESS  255
#define NUM_STRIPS  16
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
//CRGB leds1[NUM_LEDS];
//CRGB leds2[NUM_LEDS];
//CRGB leds3[NUM_LEDS];
float b;
CRGB leds[NUM_STRIPS][NUM_LEDS];

// abhi's variables
int pins[] = {6, 7, 9};
ledstrip strips[NUM_STRIPS];
int pos[NUM_STRIPS];
int col[NUM_STRIPS];
int frames = 0;
int bright;
int n;

// mckellar's variables
byte receivedChar;
boolean newData = false;
int mode = 0;

int motionDetected = 0;

int PIRVal;


// initialize led strip
void initializeLeds() {

  // using pins[x] as a parameter causes compile errors so you've gotta hard code for each strip

  //  for (int x = 0; x < NUM_STRIPS; x++) {
  //    FastLED.addLeds<LED_TYPE, pins[x], COLOR_ORDER>(leds[x], NUM_LEDS).setCorrection( TypicalLEDStrip );
  //  }

  FastLED.addLeds<LED_TYPE, LED1_PIN, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED2_PIN, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED3_PIN, COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED4_PIN, COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection( TypicalLEDStrip );


  FastLED.addLeds<LED_TYPE, LED5_PIN, COLOR_ORDER>(leds[4], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED6_PIN, COLOR_ORDER>(leds[5], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED7_PIN, COLOR_ORDER>(leds[6], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED8_PIN, COLOR_ORDER>(leds[7], NUM_LEDS).setCorrection( TypicalLEDStrip );


  FastLED.addLeds<LED_TYPE, LED9_PIN, COLOR_ORDER>(leds[8], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED10_PIN, COLOR_ORDER>(leds[9], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED11_PIN, COLOR_ORDER>(leds[10], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED12_PIN, COLOR_ORDER>(leds[11], NUM_LEDS).setCorrection( TypicalLEDStrip );
  //
  FastLED.addLeds<LED_TYPE, LED13_PIN, COLOR_ORDER>(leds[12], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED14_PIN, COLOR_ORDER>(leds[13], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED15_PIN, COLOR_ORDER>(leds[14], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED16_PIN, COLOR_ORDER>(leds[15], NUM_LEDS).setCorrection( TypicalLEDStrip );


  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}

// clear all lights on strip
void clearLed() {
  for (int a = 0; a < NUM_STRIPS; a++) {
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[a][x] = ColorFromPalette( currentPalette, 0, 0, currentBlending);
    }
  }
}

void recOneChar() {


  //  Serial.println(PIRVal);
  if (PIRVal == 1) {
    motionDetected = 1;

  } else {
    motionDetected = 0;

  }

  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    newData = true;
  }
}

void updateLED(int first, int last) {
  //  clearLed();

  // uodate the strip, get pos of raindrop
  for (int x = first; x < last; x++) {
    pos[x] = strips[x].update(frames, motionDetected);
    col[x] = strips[x].getColor();

  }

  // draw the raindrop with fade
  for (int x = first; x < last; x++) {

    // start at lower brightness if below 10
    int inc = 30;
    if (pos[x] < 10) {
      bright = map(pos[x], 0, 10, 0, 225);
      //      inc = map(pos[x], 0, 10, 0, 30); // raindrops get shorter at bottom if this is commented out
    } else {
      bright = 255;
    }

    if (pos[x] >= 0) {
      leds[x][pos[x]] = ColorFromPalette( currentPalette, col[x], bright, currentBlending);
    }

    bright -= inc;
    pos[x]++;

    // draw fade up
    while (pos[x] < 50 && bright > 0) {
      leds[x][pos[x]] = ColorFromPalette( currentPalette, col[x], bright, currentBlending);
      bright -= inc;
      pos[x]++;
    }
  }


  // push to strip
  FastLED.show();

}

//void initializeTwinkle() {
//  for (int x = 0; x < NUM_STRIPS; x++) {
//    for (int y = 0; y < NUM_LEDS; y++) {
//      brightness[x][y] = 0;
//    }
//  }
//
//}

//void twinkle() {
//  for (int x = 0; x < NUM_STRIPS; x++) {
//    if (frames % 17 == 0) {
//      brightness[x][random(0, 50)] = 15;
//    }
//
//    for (int y = 0; y < NUM_LEDS; y++) {
//      if (brightness[x][y] > 0.03) {
//        brightness[x][y] -= .03;
//      } else {
//        brightness[x][y] = 0;
//      }
//
//
//      leds[x][y].r = brightness[x][y];
//      leds[x][y].g = brightness[x][y];
//      leds[x][y].b = brightness[x][y];
//    }
//  }
//}

void twinkle2() {
  //  for (int x = 0; x < NUM_STRIPS; x++) {
  for (int y = 0; y < NUM_LEDS; y ++) {
    b = (map(inoise8(y * 300, n / 5.0), 0, 255, -255, 200));
    if (b > 0) {
      b = map(b, -255, 200, 0, 12);
      //        leds[x][y] = ColorFromPalette( currentPalette, 0, b, currentBlending);
      for (int x = 0; x < NUM_STRIPS; x++) {
        leds[x][y].r = b;
        leds[x][y].g = b;
        leds[x][y].b = b;
      }

    }
  }
  //  }

}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); // to get random() to work differently every execution

  pinMode(SENSOR1_PIN, INPUT);
  pinMode(SENSOR2_PIN, INPUT);
  pinMode(SENSOR3_PIN, INPUT);
  pinMode(SENSOR4_PIN, INPUT);

  n = 0;
  Serial.begin(9600);
  delay( 3000 ); // power-up safety delay

  initializeLeds();
  //  initializeTwinkle();
}

// groups the strips to their sensor reading
void stripGroup1() {
  PIRVal = digitalRead(SENSOR1_PIN); // read PIRVal
  recOneChar(); // update motionDetected
  updateLED(0, 4); // write 4 strips based on motionDetected
}

void stripGroup2() {
  PIRVal = digitalRead(SENSOR2_PIN);
  recOneChar();
  updateLED(4, 8);
}

void stripGroup3() {
  PIRVal = digitalRead(SENSOR3_PIN);
  recOneChar();
  updateLED(8, 12);
}

void stripGroup4() {
  PIRVal = digitalRead(SENSOR4_PIN);
  recOneChar();
  updateLED(12, 16);
}

void loop() {
  n += 20;
  clearLed();
  twinkle2();

  stripGroup1();
  stripGroup2();
  stripGroup3();
  stripGroup4();
  
  frames++;
}

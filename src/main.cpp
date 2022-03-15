#include <Arduino.h>
#include <IRremote.h>

#include <FastLED.h>

#define LED_PIN     11
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    21

CRGB leds[NUM_LEDS];
bool activeLEDS[NUM_LEDS];

int brightness = 80;
int timeTospendPerWay = 3000;
CRGB currentColor = CRGB::Yellow;
CRGB colorArray[5] = {CRGB::White,CRGB::Red,CRGB::Yellow,CRGB::Blue,CRGB::Green};

/*
Remote hex values map
FF00FF  FF40BF  FF609F  FFE01F
FF10EF  FF906F  FF50AF  FFC03F
FF30CF  FFB04F  FF708F  FFF00F
FF08F7  FF8877  FF48B7  FFC837
FF28D7  FFA857  FF6897  FFE817
FF18E7  FF9867  FF58A7  FFD827
*/

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;

int b1Val;
int b2Val;
int b3Val;
int lastb2Val = HIGH;
int buttonStatus = HIGH;


unsigned long lastToogledTime = 0;
unsigned long lastHightoLowTime = 0;
unsigned long debounceDelay = 30;

int currentButtonPosition = 0;

void setColor() {

  FastLED.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    if (activeLEDS[i]) {
      leds[i] = currentColor;
    }
    //leds[i] = activeLEDS[i] ? currentColor : CRGB::Black;
  }
  FastLED.show();
}

void setup() {
  
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);

  Serial.begin(9600);

  FastLED.addLeds<WS2811, LED_PIN,BRG>(leds, NUM_LEDS);
  irrecv.enableIRIn(); // Start the receiver
  
  //FastLED.setMaxPowerInMilliWatts(9200);  

  FastLED.clear();
  for (int led_i = 0; led_i < NUM_LEDS; led_i++) {
    activeLEDS[led_i]=true;
    leds[led_i]=currentColor;
  }
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void loop() {

  b1Val = digitalRead(8);
  b2Val = digitalRead(10);
  b3Val = digitalRead(9);
  
  if (b1Val == LOW) {
    Serial.println("B1 pressed");
    for (int i = 0; i < NUM_LEDS/2; i++) {
      activeLEDS[i] =  !(activeLEDS[i]);
    }
    setColor();
    delay(300);
  }
  if (b2Val != lastb2Val) {
    lastToogledTime = millis();
    Serial.println(lastToogledTime);
  }

  if ((millis() - lastToogledTime) > debounceDelay) {
    if (b2Val != buttonStatus) {
      buttonStatus = b2Val;
      if (buttonStatus == HIGH) {
        if ((millis() - lastHightoLowTime) < 1000) {
          currentButtonPosition=(currentButtonPosition+1) % 5;
          currentColor = colorArray[currentButtonPosition];
          setColor();
          //Serial.println ("change color");
        }
      } else {
        lastHightoLowTime = millis();
        //Serial.println ("button pressed");
      }
    } else {
      if (((millis() - lastHightoLowTime) > 1000) && buttonStatus == LOW) {
        brightness-=2;
        FastLED.setBrightness(brightness);
        FastLED.show();
        //Serial.println("change brightness");
        delay(100);
      }
    }

  }
  lastb2Val = b2Val;

  if (b3Val == LOW) {
    //Serial.println("B3 pressed");
    for (int i = NUM_LEDS/2; i < NUM_LEDS; i++) {
      activeLEDS[i] =  !(activeLEDS[i]);
    }
    setColor();

    delay(300);
  }

  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value

    switch(results.value) {
      case 16728255 : // LESS
        brightness-=20;
        FastLED.setBrightness(brightness);
        FastLED.show();
        break;
      case 16711935 : // MORE
        brightness+=20;
        FastLED.setBrightness(brightness);
        FastLED.show();
        break;
      case 16736415 : // OFF BUTTON - LEFT SIDE
        for (int i = 0; i < NUM_LEDS/2; i++) {
          activeLEDS[i] =  !(activeLEDS[i]);
        }
        setColor();
        break;
      case 16769055 : // ON BUTTON - RIGHT SIDE
        for (int i = NUM_LEDS/2; i < NUM_LEDS; i++) {
          activeLEDS[i] =  !(activeLEDS[i]);
        }
        setColor();
        break;
      case 16716015 : // RED
        currentColor = CRGB::Red;
        setColor();
        break;
      case 16748655 : // GREEN
        currentColor = CRGB::Green;
        setColor();
        break;
      case 16732335 : // BLUE
        currentColor = CRGB::Blue;
        setColor();
        break;
      case 16760895 : // WHITE
        currentColor = CRGB::White;
        setColor();
        break;
      case 16724175 : // RED ORANGE
        currentColor = CRGB::OrangeRed;
        setColor();
        break;
      case 16756815 : // SEA GREEN
        currentColor = CRGB::SeaGreen;
        setColor();
        break;
      case 16740495 : // PALE BLUE
        currentColor = CRGB::PaleTurquoise;
        setColor();
        break;
      case 16713975 : // DARK ORANGE
        currentColor = CRGB::DarkOrange;
        setColor();
        break;
      case 16746615 : // TURQUOISE
        currentColor = CRGB::Turquoise;
        setColor();
        break;
      case 16730295 : // PINK
        currentColor = CRGB::HotPink;
        setColor();
        break;
      case 16722135 : // ORANGE
        currentColor = CRGB::Orange;
        setColor();
        break;
      case 16754775 : // SKY BLUE
        currentColor = CRGB::SkyBlue;
        setColor();
        break;
      case 16738455 : // INDIGO
        currentColor = CRGB::Indigo;
        setColor();
        break;
      case 16718055 : // Yellow
        currentColor = CRGB::Goldenrod;
        setColor();
        break;
      case 16750695 : // Dark Blue
        currentColor = CRGB::DarkBlue;
        setColor();
        break;
      case 16734375 : // Purple
        currentColor = CRGB::Purple;
        setColor();
        break;
      case 16773135 : // FLASH - Alternate
        {
          for (int i = 0; i < NUM_LEDS; i+=2) {
            activeLEDS[i] =  !(activeLEDS[i]);
          }
          setColor();
          break;
        }
      case 16762935 : // STROBE - 12 seconds trailing dot
        {
          //FastLED.clear();
          for (int i = 0; i < NUM_LEDS; i++) {
          activeLEDS[i] =  false;
        }
          int j = 4;
          do {
          for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = currentColor;
            FastLED.show();
            delay(timeTospendPerWay/NUM_LEDS);
            leds[i] = CRGB::Black;
          }
          for (int i = NUM_LEDS-1; i >=0; i--) {
            leds[i] = currentColor;
            FastLED.show();
            delay(timeTospendPerWay/NUM_LEDS);
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          } while (j--,j>0);
          break;
        }
      case 16771095 : // SMOOTH - Forth & back whanging color
        {
          //FastLED.clear();
          for (int i = 0; i < NUM_LEDS; i++) {
            activeLEDS[i] =  false;
          }
          int h = 0;
          do {
            for (int i = 0; i < NUM_LEDS; i++) {
              leds[i] = CHSV(h,200,122);
              FastLED.show();
              delay(timeTospendPerWay/NUM_LEDS);
            }
            for (int k = NUM_LEDS-1; k >= 0; k--) {
              leds[k] = CHSV(255-h,200,122);
              FastLED.show();
              delay(timeTospendPerWay/NUM_LEDS);
            }
          } while (h+=10,h<255);
          break;
        }
      case 16767015 : // MODE - Rainbow fading
        //FastLED.clear();
        for (int i = 0; i < NUM_LEDS; i++) {
          activeLEDS[i] =  true;
        }
        int l = 0;
        do {
          for (int i = 0; i < NUM_LEDS;i++) {
            leds[i] = CHSV(l,200,122);
          }
          FastLED.show();
          delay(200);
        } while (l+=3,l<255);
        break;
    }
  }
}

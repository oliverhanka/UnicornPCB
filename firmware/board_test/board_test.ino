/*
 * unicorn ctf pcb test programm
 * 2019 (c) Oliver Hanka
 */

#include <Adafruit_NeoPixel.h>
#include "config.h"

// WS2812b setup (a.k.a. Adafruit NeoPixel)
Adafruit_NeoPixel tail_pixels = Adafruit_NeoPixel(TAIL_LED_NUM, TAIL_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel body_pixels = Adafruit_NeoPixel(BODY_LED_NUM, BODY_LED_PIN, NEO_GRB + NEO_KHZ800);

// led mode control
#define NUM_OF_MODES 2
int current_mode = 0;



/* Interrupt handler */
volatile int interruptCounter = 0;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
  interruptCounter++;             // record that an interrupt was fired
  portEXIT_CRITICAL_ISR(&mux);
}

void setup() {

  // Initialize the NeoPixel library.
  tail_pixels.begin(); 
  body_pixels.begin();
  tail_pixels.setBrightness(DEFAULT_BRIGHTNESS);
  body_pixels.setBrightness(DEFAULT_BRIGHTNESS);

  // Register interrupt
  pinMode(SW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_PIN), handleInterrupt, RISING);
}

void loop() {

  // Check for interrupt
  if(interruptCounter > 0){
 
      portENTER_CRITICAL(&mux);
      interruptCounter--;
      portEXIT_CRITICAL(&mux);

      //Handle the interrupt -> change the led mode
      current_mode++;
      if (current_mode > NUM_OF_MODES)
        current_mode = 0;
  }

  // execute the current led mode
  switch (current_mode) {
    case 0:
      rainbowCycle(10);
      break;
    case 1:
      colorWipe(&body_pixels,body_pixels.Color(112, 0, 129),50);
      colorWipe(&tail_pixels,tail_pixels.Color(112, 0, 129),50);
      break;
    case 2:
      theaterChase(&body_pixels,body_pixels.Color(0, 0, 255),50);
      break;
    default:
      Serial.println("UPS...");
      delay(10*1000);
  }

}


void colorWipe(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip->numPixels(); i++) {
    strip->setPixelColor(i, c);
    strip->show();
    delay(wait);
  }
  
  if(interruptCounter > 0) return;
  for(uint16_t i=0; i<strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->Color(0,0,0));
    strip->show();
    delay(wait);
  }  
}

void theaterChase(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip->show();

      if(interruptCounter > 0) return;
      delay(wait);

      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i_b, i_t, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i_b=0; i_b< body_pixels.numPixels(); i_b++) {
      body_pixels.setPixelColor(i_b, Wheel_body(((i_b * 256 / tail_pixels.numPixels()) + j) & 255));
    }
    tail_pixels.show();
    for(i_t=0; i_t< tail_pixels.numPixels(); i_t++) {
      tail_pixels.setPixelColor(i_t, Wheel_tail(((i_t * 256 / tail_pixels.numPixels()) + j) & 255));
    }
    body_pixels.show();
    tail_pixels.show();
    
    if(interruptCounter > 0) return;
    
    delay(wait);
  }
}

uint32_t Wheel_body(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return body_pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return body_pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return body_pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


uint32_t Wheel_tail(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return tail_pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return tail_pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return tail_pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

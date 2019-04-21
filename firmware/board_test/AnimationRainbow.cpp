/*
 * AnimationRainbow.cpp
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#include "AnimationRainbow.h"

AnimationRainbow::AnimationRainbow(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels) : Animation(body_pixels,tail_pixels) {
}

void AnimationRainbow::init() {
  rainbowCycle = 0;
  allOff();
}

void AnimationRainbow::advance() {
  uint8_t loop;
  
  rainbowCycle++;
  if (rainbowCycle > 256*5)   // after 5 cycles of all colors on wheel start again
    rainbowCycle = 0;
    
  for(loop=0; loop < BODY_LED_NUM; loop++) {
    currentState.body[loop] = Wheel(((loop * 256 / 9) + rainbowCycle) & 255);
  }

  for(loop=0; loop < TAIL_LED_NUM; loop++) {
    currentState.tail[loop] = Wheel(((loop * 256 / 9) + rainbowCycle) & 255);
  }
  
  show();
}


uint32_t AnimationRainbow::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

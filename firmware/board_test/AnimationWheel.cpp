/*
 * AnimationWheel.cpp
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#include "AnimationWheel.h"

AnimationWheel::AnimationWheel(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels) : Animation(body_pixels,tail_pixels) {
}

void AnimationWheel::init() {
  curPixel = 1;
  timeTickCountdown = 0;
  allOff();
}

void AnimationWheel::advance() {
  // only update every 8th advance
  if (timeTickCountdown > 0) {
    timeTickCountdown--;
    return;
  }
  timeTickCountdown = 8;

  // set "fade out" pixels
  switch (curPixel) {
    case 1:
      currentState.body[BODY_LED_NUM-1] = Color(0,0,0);
      currentState.body[1] = Color(128,0,0);
      break;
    default:
      currentState.body[curPixel-1] = Color(0,0,0);
      currentState.body[curPixel] = Color(128,0,0);
  }
  
  curPixel++;
  if (curPixel >= BODY_LED_NUM)
    curPixel = 1;
  currentState.body[curPixel] = Color(255,0,0);
  show();
}

/*
 * AnimationRSSI.cpp
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#include "AnimationRSSI.h"

AnimationRSSI::AnimationRSSI(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels) : Animation(body_pixels,tail_pixels) {
}

void AnimationRSSI::init() {
  timeTickCountdown = 0;
  curStep = 0;
  allOff();
}

void AnimationRSSI::advance() {
  // only update every 8th advance
  if (timeTickCountdown > 0) {
    timeTickCountdown--;
    return;
  }
  timeTickCountdown = 15;

  // use the tail as RSSI
  uint8_t loop;
  if (signalStrength < 16) {
    currentState.tail[0] = Color(255,0,0);
  } else if (signalStrength < 33) {
    for (loop = 0; loop < 2; loop++)
      currentState.tail[loop] = Color(255,80,0);
  } else if (signalStrength < 50) {
    for (loop = 0; loop < 3; loop++)
      currentState.tail[loop] = Color(230,230,0);
  } else if (signalStrength < 67) {
    for (loop = 0; loop < 4; loop++)
      currentState.tail[loop] = Color(173,240,0);
  } else if (signalStrength < 84) {
    for (loop = 0; loop < 5; loop++)
    currentState.tail[loop] = Color(40,255,0);
  } else if (signalStrength > 84) {
    for (loop = 0; loop < 6; loop++)
      currentState.tail[loop] = Color(0,255,0);
  }

  // all black
  for (loop = 1; loop < 9; loop++)
    currentState.body[loop] = Color(0,0,0);

  currentState.body[0] = Color(0,0,128);

  switch (curStep) {
    case 0:
      currentState.body[1] = Color(0,0,128);
      currentState.body[5] = Color(0,0,128);
      curStep++;
      break;
    case 1:
      currentState.body[2] = Color(0,0,128);
      currentState.body[6] = Color(0,0,128);
      curStep++;
      break;
    case 2:
      currentState.body[3] = Color(0,0,128);
      currentState.body[7] = Color(0,0,128);
      curStep++;
      break;
    case 3:
      currentState.body[4] = Color(0,0,128);
      currentState.body[8] = Color(0,0,128);
      curStep = 0;
      break;
  }

  show();
}

void AnimationRSSI::setSignalStrength(uint8_t value) {
  signalStrength = value;
}

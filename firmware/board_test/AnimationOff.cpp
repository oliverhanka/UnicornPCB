/*
 * AnimationOff.cpp
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#include "AnimationOff.h"

AnimationOff::AnimationOff(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels) : Animation(body_pixels,tail_pixels) {
}

void AnimationOff::init() {
  allOff();
}

void AnimationOff::advance() {
    return;
}

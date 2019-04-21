/*
 * AnimationWheel.h
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#ifndef ANIMATIONWHEEL_H
#define ANIMATIONWHEEL_H

#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "config.h"


class AnimationWheel : public Animation {
  public:
    AnimationWheel(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels);
    void init();
    void advance();
  private:
    uint8_t curPixel;
    uint16_t timeTickCountdown;
};


#endif /* ANIMATIONWHEEL_H */

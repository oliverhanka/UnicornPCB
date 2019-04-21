/*
 * AnimationRainbow.h
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#ifndef ANIMATIONRAINBOW_H
#define ANIMATIONRAINBOW_H

#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "config.h"

class AnimationRainbow : public Animation {
  public:
    AnimationRainbow(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels);
    void init();
    void advance();
  private:
    uint16_t rainbowCycle;
    uint32_t Wheel(byte WheelPos);
};


#endif /* ANIMATIONRAINBOW_H */

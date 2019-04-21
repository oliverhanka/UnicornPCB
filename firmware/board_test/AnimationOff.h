/*
 * AnimationOff.h
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#ifndef ANIMATIONOFF_H
#define ANIMATIONOFF_H

#include <Adafruit_NeoPixel.h>
#include "Animation.h"


class AnimationOff : public Animation {
  public:
    AnimationOff(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels);
    void init();
    void advance();
};

#endif /* ANIMATIONOFF_H */

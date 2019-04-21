/*
 * AnimationRSSI.h
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#ifndef ANIMATIONRSSI_H
#define ANIMATIONRSSI_H

#include <Adafruit_NeoPixel.h>
#include "Animation.h"


class AnimationRSSI : public Animation {
  public:
    AnimationRSSI(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels);
    void init();
    void advance();
    void setSignalStrength(uint8_t value);
  private:
    uint8_t signalStrength;
    uint16_t timeTickCountdown;
    uint8_t curStep;
};

#endif /* ANIMATIONRSSI_H */

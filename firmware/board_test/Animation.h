/*
 * Animation.h
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <Adafruit_NeoPixel.h>

class Animation {
  
  public:
    Animation(Adafruit_NeoPixel *body_pixels, Adafruit_NeoPixel *tail_pixels) {
      _body_pixels = body_pixels;
      _tail_pixels = tail_pixels;
    }
    
    virtual void init() = 0;
    virtual void advance() = 0;
    
  protected:

    Adafruit_NeoPixel *_body_pixels;
    Adafruit_NeoPixel *_tail_pixels;

    // hold the values for the current animation state
    struct currentState_t {
      uint32_t body[9];
      uint32_t tail[6];
    } currentState;

    void allOff() {
      for (uint16_t loop = 0; loop < 9; loop++)
        currentState.body[loop] = 0;
      for (uint16_t loop = 0; loop < 6; loop++)
        currentState.tail[loop] = 0;
      show();
    }

    // show current animation state
    void show() {
      for (uint16_t loop = 0; loop < 9; loop++)
        _body_pixels->setPixelColor(loop,currentState.body[loop]);
      for (uint16_t loop = 0; loop < 6; loop++)
        _tail_pixels->setPixelColor(loop,currentState.tail[loop]);
      _body_pixels->show();
      _tail_pixels->show();
    }

    // convert seperate red, green, blue 8bit values into a packed 32bit value
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
      return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
  
};
  

#endif /* ANIMATION_H */

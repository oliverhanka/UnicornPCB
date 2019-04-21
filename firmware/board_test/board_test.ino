/*
 * Unicorn PCD boardice test
 * (c) 2019 Oliver Hanka - mail@oliverhanka.de
 */
 
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "AnimationWheel.h"
#include "AnimationRainbow.h"
#include "AnimationOff.h"
#include "config.h"

/*
 * NEO PIXEL SETUP
 */
Adafruit_NeoPixel tail_pixels = Adafruit_NeoPixel(TAIL_LED_NUM, TAIL_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel body_pixels = Adafruit_NeoPixel(BODY_LED_NUM, BODY_LED_PIN, NEO_GRB + NEO_KHZ800);

/*
 * ANIMATION SETUP
 */
#define NUM_OF_ANIMATIONS 3
Animation* animations[NUM_OF_ANIMATIONS];
AnimationWheel* animationWheel = new AnimationWheel(&body_pixels,&tail_pixels);
AnimationRainbow* rainbow = new AnimationRainbow(&body_pixels,&tail_pixels);
AnimationOff* animOff = new AnimationOff(&body_pixels,&tail_pixels);
uint8_t currentAnim;


/*
 * TIMER SETUP
 */
volatile int animTimerInterruptCounter;

hw_timer_t * animTimer = NULL;
portMUX_TYPE animTimerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onAnimTimer() {
  portENTER_CRITICAL_ISR(&animTimerMux);
  animTimerInterruptCounter++;         // record that an interrupt was fired
  portEXIT_CRITICAL_ISR(&animTimerMux);
 
}

/*
 * GPIO INTERRUPT SETUP
 */
volatile int gpioInterruptCounter = 0;
portMUX_TYPE gpioMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleGPIOInterrupt() {
  portENTER_CRITICAL_ISR(&gpioMux);
  gpioInterruptCounter++;             // record that an interrupt was fired
  portEXIT_CRITICAL_ISR(&gpioMux);
}

void setup() {
  Serial.begin(250000);  

  // Initialize the NeoPixel library.
  tail_pixels.begin(); 
  body_pixels.begin();
  tail_pixels.setBrightness(DEFAULT_BRIGHTNESS);
  body_pixels.setBrightness(DEFAULT_BRIGHTNESS);  

  // init animations
  animationWheel->init();
  rainbow->init();
  animOff->init();

  // set current animation
  animations[0] = animationWheel;
  animations[1] = rainbow;
  animations[2] = animOff;
  currentAnim = 0;

  // setup and start animation timer
  animTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(animTimer, &onAnimTimer, true);
  timerAlarmWrite(animTimer, ANIMATION_TICK_INTERVALL, true);
  timerAlarmEnable(animTimer);

  // Register GPIO interrupt
  pinMode(SW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_PIN), handleGPIOInterrupt, RISING);

}

void loop() {
  if (animTimerInterruptCounter > 0) {
 
    portENTER_CRITICAL(&animTimerMux);
    animTimerInterruptCounter--;
    portEXIT_CRITICAL(&animTimerMux);
 
    animations[currentAnim]->advance();
  }  
  
  if(gpioInterruptCounter > 0){
 
      portENTER_CRITICAL(&gpioMux);
      gpioInterruptCounter--;
      portEXIT_CRITICAL(&gpioMux);

      currentAnim++;
      if (currentAnim >= NUM_OF_ANIMATIONS)
        currentAnim = 0;
      animations[currentAnim]->init();
  }
}

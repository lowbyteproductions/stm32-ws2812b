#ifndef INC_WS2812B_H
#define INC_WS2812B_H

#include <stdint.h>

typedef struct RGB_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB_t;

typedef struct WS2812B_t {
  RGB_t* leds;
  uint16_t num_leds;
  uint32_t port;
  uint16_t pin;
} WS2812B_t;

void WS2812B_Write(WS2812B_t* ws2812b);

#endif // INC_WS2812B_H

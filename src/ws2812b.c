#include <libopencm3/stm32/gpio.h>
#include "ws2812b.h"

static inline void send_zero(uint32_t port, uint16_t pin) {
  gpio_port_write(port, pin); // 120ns

  // +300ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  gpio_port_write(port, 0); // 120ns

  // +680ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
}

static inline void send_one(uint32_t port, uint16_t pin) {
  gpio_port_write(port, pin); // 120ns

  // +680ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");

  gpio_port_write(port, 0); // 120ns

  // +300ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
}

void WS2812B_Write(WS2812B_t* ws2812b) {
  for (uint16_t i = 0; i < ws2812b->num_leds; i++) {
    RGB_t led = ws2812b->leds[i];

    // Green
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (led.g & 0x80) {
        send_one(ws2812b->port, ws2812b->pin);
      } else {
        send_zero(ws2812b->port, ws2812b->pin);
      }
    }

    // Red
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (led.r & 0x80) {
        send_one(ws2812b->port, ws2812b->pin);
      } else {
        send_zero(ws2812b->port, ws2812b->pin);
      }
    }

    // Blue
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (led.b & 0x80) {
        send_one(ws2812b->port, ws2812b->pin);
      } else {
        send_zero(ws2812b->port, ws2812b->pin);
      }
    }
  }

  // Reset code
  for (uint16_t i = 0; i < 600; i++) {
    __asm__ volatile("nop\nnop\n");
  }
}
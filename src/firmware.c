#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <string.h>

#include "core/system.h"
#include "ws2812b.h"

#define LED_PORT (GPIOC)
#define LED_PIN  (GPIO8)

static void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOC);
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
  gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);
}

int main(void) {
  system_setup();
  gpio_setup();

  RGB_t leds[8] = {0};
  WS2812B_t ws2812b = {
    .leds = leds,
    .num_leds = 8,
    .pin = GPIO8,
    .port = GPIOC
  };

  uint64_t start_time = system_get_ticks();
  uint8_t current_led = 0;

  while (1) {
    if (system_get_ticks() - start_time >= 250) {
      memset(&leds[current_led], 0, sizeof(RGB_t));
      current_led = (current_led + 1) % ws2812b.num_leds;
      leds[current_led].r = 255;

      WS2812B_Write(&ws2812b);
      start_time = system_get_ticks();
    }
  }

  return 0;
}

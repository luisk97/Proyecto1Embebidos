#include <home-control.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char* argv[]) {
  int arg = 1;

  if (argc == 2) {
    if (!strcmp(argv[arg], "LED_KITCKEN")) {
      printf("%d\n", state_led(LED_KITCKEN));
    }
    else if(!strcmp(argv[arg], "LED_BEDROOM_A")) {
      printf("%d\n", state_led(LED_BEDROOM_A));
    }
    else if (!strcmp(argv[arg], "LED_LIVING_ROOM")) {
      printf("%d\n", state_led(LED_LIVING_ROOM));
    }
    else if (!strcmp(argv[arg], "LED_BEDROOM_B")) {
      printf("%d\n", state_led(LED_BEDROOM_B));
    }
    else if (!strcmp(argv[arg], "LED_BATHROOM")) {
      printf("%d\n", state_led(LED_BATHROOM));
    }
    else if (!strcmp(argv[arg], "STATE_FRONT_DOOR")) {
      printf("%d\n", state_door(STATE_FRONT_DOOR));
    }
    else if (!strcmp(argv[arg], "STATE_BACK_DOOR")) {
      printf("%d\n", state_door(STATE_BACK_DOOR));
    }
    else if (!strcmp(argv[arg], "STATE_BEDROOM_A")) {
      printf("%d\n", state_door(STATE_BEDROOM_A));
    }
    else if (!strcmp(argv[arg], "STATE_BEDROOM_B")) {
      printf("%d\n", state_door(STATE_BEDROOM_B));
    }
    else if (!strcmp(argv[arg], "HOME_OFF")) {
      home_off();
    }
    else if (!strcmp(argv[arg], "HOME_ON")) {
      home_on();
    }
    else if (!strcmp(argv[arg], "RESERVE")) {
      reserve_all();
    }
    else if (!strcmp(argv[arg], "FREE")) {
      free_all();
    }
    else {
      printf("[Error] There is no object %s\n", argv[arg]);
    }
  }
  if (argc == 3) {
    if (!strcmp(argv[arg], "LED_KITCKEN")) {
      if (atoi (argv[arg+1]) == 1) {
        led_on(LED_KITCKEN);
      }
      else {
        led_off(LED_KITCKEN);
      }
    }
    else if(!strcmp(argv[arg], "LED_BEDROOM_A")) {
      if (atoi (argv[arg+1]) == 1) {
        led_on(LED_BEDROOM_A);
      }
      else {
        led_off(LED_BEDROOM_A);
      }
    }
    else if (!strcmp(argv[arg], "LED_LIVING_ROOM")) {
      if (atoi (argv[arg+1]) == 1) {
        led_on(LED_LIVING_ROOM);
      }
      else {
        led_off(LED_LIVING_ROOM);
      }
    }
    else if (!strcmp(argv[arg], "LED_BEDROOM_B")) {
      if (atoi (argv[arg+1]) == 1) {
        led_on(LED_BEDROOM_B);
      }
      else {
        led_off(LED_BEDROOM_B);
      }
    }
    else if (!strcmp(argv[arg], "LED_BATHROOM")) {
      if (atoi (argv[arg+1]) == 1) {
        led_on(LED_BATHROOM);
      }
      else {
        led_off(LED_BATHROOM);
      }
    }
    else {
      printf("[Error] There is no object %s\n", argv[arg]);
    }
  }

}

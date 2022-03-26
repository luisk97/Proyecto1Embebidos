#include "../include/home-control.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* NAMES[9] = {"LED_BATHROOM", "LED_BEDROOM_B", "LED_LIVING_ROOM", "LED_BEDROOM_A", 
  "LED_KITCHEN", "STATE_BACK_DOOR", "STATE_BEDROOM_A", "STATE_BEDROOM_B", "STATE_FRONT_DOOR"};

int GPIOs[9] = {LED_BATHROOM, LED_BEDROOM_B, LED_LIVING_ROOM, LED_BEDROOM_A, LED_KITCHEN,
  STATE_BACK_DOOR, STATE_BEDROOM_A, STATE_BEDROOM_B, STATE_FRONT_DOOR};

//int Home[9];

/* LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL */

/**
 * Turn on a specific led
 * @param id  of the led to be turned on
 * @return 0 if all its ok, -1 if there was an error
 */
int led_on(int id_led) {
  write_GPIO (GPIOs[id_led],1);
  printf("Led %s is on\n", NAMES[id_led]);
}

/**
 * Turn off a specific led
 * @param id of the led to be turned off
 * @return 0 if all its ok, -1 if there was an error
 */
int led_off (int id_led){
  write_GPIO (GPIOs[id_led],0);
  printf("Led %s is off\n", NAMES[id_led]);

}

/* LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL - LEDs CONTROL */

/* DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL */

/**
 * Update a state of specific door in the log
 * @param id of the led to be consulted
 * @return sate of the door: 0 off, 1 on
 */
int state_door (int id_door){
  int val = read_GPIO (GPIOs[id_door]);
  printf("Door %s state is: %d", NAMES[id_door],val);
  return read_GPIO (GPIOs[id_door]);
}

/* DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL - DOORs CONTROL */

/**
 * Reserve all pins in the house
 * @return 0 if all its ok, -1 if there was an error
 */
int reserve_all () {
  for (int i=0; i<5; i++) {
    reserve_GPIO (GPIOs[i], OUT);
  }
  for (int i=5; i<9; i++) {
    reserve_GPIO (GPIOs[i], IN);
  }
}

/**
 * Free all pins in the house
 * @return 0 if all its ok, -1 if there was an error
 */
int free_all () {
  for (int i=0; i<5; i++) {
    free_GPIO (GPIOs[i]);
  }
  for (int i=5; i<9; i++) {
    free_GPIO (GPIOs[i]);
  }
}


/**
 * Set a pin as input or output
 * @param pin port of the pin that you want to reserve and configure
 * @param mode 0 if you want to use as input, 1 as output 
 * @return 0 if all its ok, -1 if there was an error
 */
int reserve_GPIO (int pin, int mode) {
  /* Reserve (export) the GPIO: */
  int fd;
  char buf[MAXBUF];
  fd = open("/sys/class/gpio/export", O_WRONLY);
  sprintf(buf, "%d", pin);
  write(fd, buf, strlen(buf));
  close(fd);

  /* Set the direction in the GPIO folder created: */
  sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
  fd = open(buf, O_WRONLY);

  if (mode == OUT) { // Set out direction
    write(fd, "out", 3);
  }
  else { // Set in direction
    write(fd, "in", 2);
  }
  close(fd);
}

/**
 * Write a digital value to a specific pin
 * @param pin GPIO where to write the value
 * @param value value to write to the pin: 1 for HIGH, 0 for LOW
 * @return 0 if all its ok, -1 if there was an error
 */
int write_GPIO (int pin, int value) {
  int fd;
  char buf[MAXBUF];
  sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
  fd = open(buf, O_WRONLY);

  if (value) { // Set GPIO high status
    write(fd, "1", 1);
  }
  else { // Set GPIO low status
    write(fd, "0", 1);
  }

  close(fd);
}

/**
 * Read a digital value from a specific pin
 * @param pin GPIO to be read
 * @return 0 if read LOW, 1 if read HIGH, -1 there was an error
 */
int read_GPIO (int pin) {
  char value;
  int fd;
  char buf[MAXBUF];
  sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
  fd = open(buf, O_RDONLY);
  read(fd, &value, 1);
  close(fd);
  return (value == 49 ? 1 : 0);
}

/**
 * 
 * @param pin Free the GPIO
 * @return 0 if all its ok, -1 if there was an error
 */
int free_GPIO (int pin) {
  int fd;
  char buf[MAXBUF];
  fd = open("/sys/class/gpio/unexport", O_WRONLY);
  sprintf(buf, "%d", pin);
  write(fd, buf, strlen(buf));
  close(fd);
}

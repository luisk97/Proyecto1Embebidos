#ifndef HOME_CONTROL_H
#define HOME_CONTROL_H

#define LED_KITCKEN 16
#define LED_BEDROOM_A 20
#define LED_LIVING_ROOM 17
#define LED_BEDROOM_B 18
#define LED_BATHROOM 19
#define STATE_FRONT_DOOR 21
#define STATE_BACK_DOOR 22
#define STATE_BEDROOM_A 23
#define STATE_BEDROOM_B 24

#define IN 0
#define OUT 1

#define FILENAME "home.txt"
#define MAXBUF 1024
#define DELIM "="

int led_on (int);
int led_off (int);
int state_led (int);
int state_door (int);

int reserve_all ();
int free_all ();

int write_log ();
int read_log ();
int reserve_GPIO (int, int);
int write_GPIO (int, int);
int read_GPIO (int);
int free_GPIO (int);


#endif

#ifndef CONTROL_CASA_H
#define CONTROL_CASA_H

#define LED_COCINA 17
#define LED_CUARTO_A 20
#define LED_SALA 16
#define LED_CUARTO_B 18
#define LED_BANO 19
#define PUERTA_PRINC 21
#define PUERTA_TRAS 22
#define PUERTA_CUARTO_A 23
#define PUERTA_CUARTO_B 24

#define IN 0
#define OUT 1

#define FILENAME "Casa.txt"
#define MAXBUF 1024
#define DELIM "="

int apagar_casa ();
int encender_casa ();
int encender_led (int);
int apagar_led (int);
int estado_led (int);
int estado_puerta (int);

int reservar_todo ();
int liberar_todo ();

int escribir_log ();
int leer_log ();
int reservar_GPIO (int, int);
int escribir_GPIO (int, int);
int leer_GPIO (int);
int liberar_GPIO (int);


#endif
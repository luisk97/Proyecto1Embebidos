#include "GPIOControl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* NAMES[9] = {"LED_COCINA", "LED_CUARTO_A", "LED_SALA", "LED_CUARTO_B", "LED_BANO",
  "PUERTA_PRINC", "PUERTA_TRAS", "PUERTA_CUARTO_A", "PUERTA_CUARTO_B"};

int GPIOs[9] = {LED_COCINA, LED_CUARTO_A, LED_SALA, LED_CUARTO_B, LED_BANO,
  PUERTA_PRINC, PUERTA_TRAS, PUERTA_CUARTO_A, PUERTA_CUARTO_B};

int Casa[9];

/**
 * Apaga todos los leds de la casa
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int apagar_casa (){
  leer_log ();
  for (int i=0; i<5; i++) {
    escribir_GPIO(GPIOs[i], 0);
    Casa[i] = 0;
  }
  escribir_log();
  printf("Apagar todos los leds\n");
}

/**
 * Enciende todos los leds de la casa
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int encender_casa (){
  leer_log ();
  for (int i=0; i<5; i++) {
    escribir_GPIO(GPIOs[i], 1);
    Casa[i] = 1;
  }
  escribir_log();
  printf("Encender todos los leds\n");
}

/**
 * Enciende un led especifico
 * @param id del led que se va a encender
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int encender_led (int id_led) {
  for (int i=0; i<5; i++) {
    if (GPIOs[i]==id_led) {                                //ESTA
      escribir_GPIO (GPIOs[i],1);
      printf("Encender el led %s\n", NAMES[i]);
      break;
    }
  }
  //liberar_GPIO (id_led);
}

/**
 * Apaga un led especifico
 * @param id del led que se va a apagar
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int apagar_led (int id_led){
  for (int i=0; i<5; i++) {
    if (GPIOs[i]==id_led) {                                //ESTA
      escribir_GPIO (GPIOs[i],0);
      printf("Apagar el led %s\n", NAMES[i]);
      break;
    }
  }
  escribir_log();

  //liberar_GPIO (id_led);
}

/**
 * Lee el estado de un led desde el log
 * @param id_led identificador del led que se quiere consultar
 * @return estado del led
 */
int estado_led (int id_led) {
  leer_log ();
  for (int i=0; i<5; i++) {
    if (GPIOs[i]==id_led) {
      return Casa[i];
    }
  }
}

/**
 * Apaga todos los leds de la casa
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int estado_puertas (){
  //leer_log ();
  for (int i=5; i<9; i++) {
    estado_puerta(GPIOs[i]);
  }
  //escribir_log();
  printf("Apagar todos los leds\n");
}

/**
 * Actualiza el estado de una puerta especifica en el log
 * @param id de la puerta que se quiere consultar
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int estado_puerta (int id_puerta){
  leer_log ();
  int state = 0;
  for (int i=5; i<9; i++) {
    if (GPIOs[i]==id_puerta) {                        //ESTA
      int val = leer_GPIO (GPIOs[i]);
      //Casa[i] = val;
      state = val;
      break;
    }
  }
  escribir_log();
  return state;
}
/**
 * Reserva todos los pines de la casa.
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int reservar_todo () {
  for (int i=0; i<5; i++) {
    reservar_GPIO (GPIOs[i], OUT);
  }                                                      //ESTA
  for (int i=5; i<9; i++) {
    reservar_GPIO (GPIOs[i], IN);
  }
}

/**
 * Libera todos los pines de la casa
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int liberar_todo () {
  for (int i=0; i<5; i++) {
    liberar_GPIO (GPIOs[i]);
  }                                                      //ESTA
  for (int i=5; i<9; i++) {
    liberar_GPIO (GPIOs[i]);
  }
}

/**
 * Escribe el contenido de la estructura infoCasa en el archivo Casa.txt
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int escribir_log (){
  FILE *f = fopen(FILENAME, "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  fprintf(f, "LED_COCINA = %d\n", Casa[0]);
  fprintf(f, "LED_CUARTO_A = %d\n", Casa[1]);
  fprintf(f, "LED_SALA = %d\n", Casa[2]);
  fprintf(f, "LED_CUARTO_B = %d\n", Casa[3]);
  fprintf(f, "LED_BANO = %d\n", Casa[4]);
  fprintf(f, "PUERTA_PRINCIPAL = %d\n", Casa[5]);
  fprintf(f, "PUERTA_PATIO = %d\n", Casa[6]);
  fprintf(f, "PUERTA_CUARTO_A = %d\n", Casa[7]);
  fprintf(f, "PUERTA_CUARTO_B = %d\n", Casa[8]);

  fclose(f);
}

/**
 * Lee el contenido del archivo Casa.txt y lo carga en la estructura infoCasa
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int leer_log (){
  FILE *file = fopen (FILENAME, "r");

  if (file != NULL)
  {
    char line[MAXBUF];
    int i = 0;

    while(fgets(line, sizeof(line), file) != NULL)
    {
      char *cfline;
      cfline = strstr((char *)line,DELIM);
      cfline = cfline + strlen(DELIM);
      Casa[i] = atoi(cfline);
      i++;
    } // End while

    fclose(file);

  } // End if file

}

/**
 * Establece un pin como entrada o como salida
 * @param pin puerto del pin que se quiere reservar y configurar
 * @param mode 0 si se quiere usar como entrada 1 como salida
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int reservar_GPIO (int pin, int mode) {
  /* Reserve (export) the GPIO: */
  int fd;
  char buf[MAXBUF];
  fd = open("/sys/class/gpio/export", O_WRONLY);
  sprintf(buf, "%d", pin);
  write(fd, buf, strlen(buf));
  close(fd);
                                                                  //ESTA
  /* Set the direction in the GPIO folder just created: */
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
 * Escribe un valor digital en un pin especifico
 * @param pin GPIO donde se va a escribir el valor
 * @param value valor que se va a escribir en el pin: 1 para HIGH, 0 para LOW
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int escribir_GPIO (int pin, int value) {
  int fd;
  char buf[MAXBUF];
  sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
  fd = open(buf, O_WRONLY);
                                                                      //ESTA
  if (value) { // Set GPIO high status
    write(fd, "1", 1);
  }
  else { // Set GPIO low status
    write(fd, "0", 1);
  }

  close(fd);
}

/**
 * Lee un valor digital de un pin especifico
 * @param pin GPIO que se va a leer
 * @return 0 si lee LOW, 1 si lee HIGH, -1 si hubo algun error
 */
int leer_GPIO (int pin) {
  char value;
  int fd;
  char buf[MAXBUF];                                                     //ESTA
  sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
  fd = open(buf, O_RDONLY);
  read(fd, &value, 1);
  close(fd);
  return (value == 49 ? 1 : 0);
}

/**
 * Libera el GPIO (no apropiatividad)
 * @param pin GPIO que se va a liberar
 * @return 0 si todo se hizo bien, -1 si hubo algun error
 */
int liberar_GPIO (int pin) {
  int fd;
  char buf[MAXBUF];
  fd = open("/sys/class/gpio/unexport", O_WRONLY);                      //ESTA
  sprintf(buf, "%d", pin);
  write(fd, buf, strlen(buf));
  close(fd);
}
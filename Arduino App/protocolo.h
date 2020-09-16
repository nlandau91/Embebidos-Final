#include <stdint.h>
#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

// Definimos constantes para el armado de paquetes
static const uint8_t SET_SPEED = 1;
static const uint8_t SET_DIRECTION = 2;
static const uint8_t SET_MODE = 3;
static const uint8_t INIT_SYMBOL = 35; //  #
static const uint8_t END_SYMBOL = 64; //  @
static const uint8_t ESCAPE_SYMBOL = 92; //  \

// Definimos constantes de configuracion
static const uint8_t PAYLOAD_SIZE = 3;

/*Inicia la comunicacion con el celular*/
void initProtocolo(long int valor);

/*Retorna true si recibio un mensaje. False en caso contrario*/
bool newMessage();

/*Lee y procesa el mensaje, retornando true si fue correcto y false en caso contrario*/
bool readMessage();

/*Devuelve el paquete de datos recibido*/
uint8_t* getPacket();

#endif /* PROTOCOLO_H_ */

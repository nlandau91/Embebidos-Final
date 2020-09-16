#include <SoftwareSerial.h>
#include "protocolo.h"

static const uint8_t PIN_TX = 18;
static const uint8_t PIN_RX = 19;

SoftwareSerial miBT(PIN_TX,PIN_RX);
int8_t indice = -1;
static uint8_t paquete[PAYLOAD_SIZE];

void initProtocolo(long int valor)
{
  miBT.begin(valor); //Si tira cualquier cosa la comunicacion poner 38400 hardcodeado.
}

bool newMessage()
{
  return miBT.available();
}

bool procesar(char valor)
{
  if(indice == -1){ //Si todavia no lei nada y recibo mensaje...
    if(valor == INIT_SYMBOL) //Si coincide con el inicio
    {  
      indice = 0; //Empiezo a leer
    }
  }
  else //Como indice es distinto de -1, ya lei el simbolo de inicio y debo guardar datos
  {
    if(indice<3)
    {
      paquete[indice] = (uint8_t)valor;
      indice++;
    }
   else
   {
    if(valor == END_SYMBOL) //Si ya llene el paquete y es el simbolo final
    {
      indice = -1;
      return true; //El paquete es correcto
    }
    else //Sino lo descarto, pues es erroneo.
    { 
      for(int i = 0; i<3; i++)
      {
        paquete[i] = 0;
      }
       indice = -1;
       return false;
    }
   }
  }
}

bool readMessage()
{
    char valor = miBT.read();
    return procesar(valor);
}

uint8_t* getPacket()
{
  return paquete;
}

#include "motores.h"
#include "protocolo.h"
#include "sensorDistancia.h"
#include "timer.h"

/*Definicion de constantes*/
static const uint8_t PIN_LED_ROJO = 13;
static const uint8_t PIN_LED_AMARILLO = 10;
static const uint8_t DISTANCIA = 20;
static const uint8_t TICKS_PARA_UN_SEG = 1;

/*Definicion de variables*/
volatile int contador = 0;
uint16_t valor;
uint8_t* p;
uint8_t modo = 0;
uint8_t direccion = 0;
uint8_t velocidad = 0;
bool apagado = true;
bool amarilloApagado = true;

/*Metodo inicializador*/
void setup()
{
  initMotores(); //Inicializo motores
  initProtocolo(38400); //Inicializo protocolo.
  initSensor(); //Inicializo sensor.
  initTimer(); //Inicializo timer.
  pinMode(PIN_LED_ROJO, OUTPUT); //Inicializo pines de salida para leds.
  pinMode(PIN_LED_AMARILLO, OUTPUT);
  for(uint8_t i=0; i<3; i++) //Inicializo el arreglo.
    p[i] = 0;
}

/*Metodo de ejecucion continua*/
void loop()
{
  if(newMessage()) //Si se recibio un mensaje
  {
    readMessage(); //Leo el mensaje.
    p = getPacket(); //Obtengo el paquete.
    modo = p[0]; //Seteo variables con los datos obtenidos.
    direccion = p[1];
    velocidad = p[2];
  }
  cambiarLedModo(); //Seteo los leds de manera correspondiente.
  checkMode(modo); //Chequeo el modo actual y que hacer.
}

/*Metodo que sirve para mostrar los leds de manera correcta.
  LED ROJO: Colision enfrente.
  LED AMARILLO: Modo de ejecucion.
    Apagado = Manual.
    Fijo = Asistido
    Parpadeando = Automatico.
*/
void cambiarLedModo()
{
  switch(modo)
  {
    case 0: if(!amarilloApagado)
            {
              apagarLed(PIN_LED_AMARILLO);
              amarilloApagado = true;
            }
            if(!apagado)
            {
              apagarLed(PIN_LED_ROJO);
              apagado = true;
            }
            break;
    case 1: if(amarilloApagado)
            {
              encenderLed(PIN_LED_AMARILLO);
              amarilloApagado = false;
            }
            break;
    case 2: if(contador >= TICKS_PARA_UN_SEG) //Si paso el tiempo necesario...
            {
              if(amarilloApagado) //Si esta apagado
              {
                encenderLed(PIN_LED_AMARILLO); //Prendo el led
                amarilloApagado = false;
              }
              else //Sino...
              {
                apagarLed(PIN_LED_AMARILLO);//Lo apago.
                amarilloApagado = true;
              }
              contador = 0; //Reseteo el contador.
            }
            break;
  }
}

/*Metodo auxiliar para encender el led en el pin elegido*/
void encenderLed(uint8_t pin)
{
  digitalWrite(pin,HIGH);
}

/*Metodo auxiliar para apagar el led en el pin elegido*/
void apagarLed(uint8_t pin)
{
  digitalWrite(pin,LOW);
}

/*Metodo auxiliar para el movimiento del modo manual*/
void mover()
{
  switch(direccion)
  {
    case 1: avanzar(velocidad);
            break;
    case 2: retroceder(velocidad);
            break;
    case 3: moverIzq(velocidad);
            break;
    case 4: moverDer(velocidad);
            break;
    case 0: noMover();
            break;
  }
}

/*Metodo auxiliar para el movimiento del modo asistido*/
void moverAsistido()
{
  valor = readSensor(); //Leo el valor del sensor
  if(valor < DISTANCIA) //Si la distancia leida es menor a la maxima distancia permitida...
  {
    if(apagado) //Si esta apagado...
    {
      encenderLed(PIN_LED_ROJO); //Lo enciendo
      apagado = false;  
    }
  }
  else //Si es mayor...
  {
    if(!apagado) //Y no esta apagado
    {
      apagarLed(PIN_LED_ROJO); //Lo apago
      apagado = true;
    }
  }
  switch(direccion) //Reviso la direccion
  {
    case 1: if(valor > DISTANCIA) //Si es adelante y no tengo nada adelante
              avanzar(velocidad);  //Avanzo
            else
              noMover(); //Sino no muevo
            break;
    case 2: retroceder(velocidad); 
            break;
    case 3: moverIzq(velocidad);
            break;
    case 4: moverDer(velocidad);
            break;
    case 0: noMover();
            break;
  }
}

/*Metodo auxiliar para el movimiento en modo automatico*/
void moverAutomatico()
{
  valor = readSensor(); //Leo el valor del sensor
    if(valor > DISTANCIA)
    { //Si no tengo nada adelante
    avanzar(velocidad); //Avanzo
    if(!apagado) //Si el led rojo no esta apagado
    { 
      apagarLed(PIN_LED_ROJO); //Lo apago.
      apagado = true;
    }
  }
  else  //Si tengo algo adelante
  { 
    if(apagado) //Si el led Rojo esta apagado
    { 
      encenderLed(PIN_LED_ROJO); //Lo enciendo
      apagado = false;
    }
    moverDer(velocidad); //Me muevo a la derecha
  }  
 
}

/*Chequeo el modo actual y elijo el metodo correcto*/
void checkMode(int modo)
{
  switch(modo)
  {
    case 0: //Estoy en modo manual
            mover();
            break;
    case 1: //Estoy en modo Asistido
            moverAsistido();
            break;
    case 2: //Estoy en modo automatico
            moverAutomatico();
            break;
  }
}

/*Interrupcion del timer 1*/
ISR(TIMER1_COMPA_vect)
{
  contador++;
}

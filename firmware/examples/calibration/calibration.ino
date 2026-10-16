/**************************************************************************************
*                                                                                     *
*   Programa de calibracion de Zowi                                                   *
*   Javier Isabel, 02/06/2015                                                         *
*                                                                                     *
*   En este programa se indica como calibrar a Zowi utilizando                        *
*   la librera diseñada especificamente para el, zowi.h                               *
*                                                                                     *
**************************************************************************************/

#include <Zowi.h> //Libreria Zowi, disponible en el repositorio de GitHub de Zowi
#include <Servo.h>
#include <Oscillator.h> //Librera ArduSnake de Obijuan, en GitHub
#include <EEPROM.h>

/**************************************************************************************
*                                                                                     *
* Empezamos por declarar un objeto de la clase Zowi. La clase Zowi                    *
* contiene funciones para calibrar a Zowi y para crear y ejecutar                     *
* diversos tipos de movimientos                                                       *
*                                                                                     *
**************************************************************************************/

Zowi zowi;

void setup()
{

/**************************************************************************************
*                                                                                     *
* La funcion init sirve para configurar a Zowi, y se le pasan cinco parametros:       *
*  - (int) pin del servo superior izquierdo                                           *
*  - (int) pin del servo superior derecho                                             *
*  - (int) pin del servo inferior izquierdo                                           *
*  - (int) pin del servo inferior derecho                                             *
*  - (boolean) booleano que indica si quieren cargarse los valores de calibracion     *
*    de la memoria EEPROM (1, true) o no (0, false). Este valor puede omitirse, por   *
*    defecto sera 0                                                                   *
*                                                                                     *
**************************************************************************************/

  zowi.init(2, 3, 4, 5, true);

/**************************************************************************************
*                                                                                     *  
* Como hemos puesto el booleano a 0 (false), necesitaremos darle unos valores de      *
* calibracion manualmente. Estos valores, en grados, son offsets a la orientacion     *
* el servo. Estos valores deberan variarse poco a poco, hasta que el robot quede      *
* totalmente recto. El orden de los valores respecto a los servos sera nuevamente     *
* de izquiera a derecha y de arriba a abajo                                           *
*                                                                                     *
**************************************************************************************/

  //zowi.setTrims(-14,-6,-15,-3);

/**************************************************************************************
*                                                                                     *  
* Una vez que se han obtenido empiricamente valores correctos de calibracion, se      *
* puede utilizar la funcion saveTrimsOnEEPROM para guardar los valores en la          *
* memoria de la placa, asi la proxima vez que se programe a Zowi, se podra utilizar   *
* funcion init con un 1 al final, para cargar los valores guardados de la EEPROM.     *
* Sin embargo es MUY IMPORTANTE solo guardar los valores una vez. En posteriores      *
* cargas del programa a la placa, debe eliminarse la linea para evitar deteriorar la  *
* EEPROM                                                                              *
*                                                                                     *
**************************************************************************************/

  //zowi.saveTrimsOnEEPROM();



}

int posiciones[] = {90, 90, 90, 90};

void loop() 
{

/**************************************************************************************
*                                                                                     *
* Durante las pruebas utilizaremos la funcion moveServos para poner todos los servos  *
* a 90º y comparar su posicion real con la posicion buscada                           *
*                                                                                     *
**************************************************************************************/
  
  zowi.walk(4,1800);
 
}


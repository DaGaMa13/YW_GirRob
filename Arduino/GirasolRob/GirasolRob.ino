/******************************
 *    YOUNGSTERS WORKSHOP
 *    DaGaMa13
 *    
 *    PROYECTO GIRASOL ROBOTICO
 *    Marzo 2021
 ****************************************/

/*DEFINICIÓN DE LOS PINES
 * 
 * //[A0:A8] :: Fotoresistores arreglo:     | 8 1 5 |
 *                                          | 4 0 2 |
 * //>>DaGaMa13<<                           | 7 3 6 |
 * 
 * D5: Servo1  || D6: Servo 2
 * Servo1: giro 360° eje Z || Servo2: giro 180° de <1> a <3>
 */

//Declaración de las bibliotecas
#include <Servo.h> //Biblioteca para el control de los servomotores

//Declaración de las variables generales

int i=0, j=0, k=0; //contadores

//Variables de manejo de datos FOTORESISTORES
int numFoto = 5; //Numero de Fotoresistores utilizados, MIN:5 || MAX:8
int fotoR[5]= {A0,A1,A2,A3,A4}; //Temporalmente los 5 sensores principales, total asginados 8
int lumen[5]= {0,0,0,0,0}; //Valores de los Fotoresistores
int fotoMax = 0; //Número del fotoresitor con la mayor media registrada
int lumenMax = 0; //Valor registrado del fotoresistor de mayor medida registrada

//Variables de manejo de datos de movimiento SERVOMOTORES
int posActualS1= 0;
int posActualS2= 0;

//Declaración del objeto Servo
Servo servoMotor1; //Servomotor del eje Z, giro total de 360°
Servo servoMotor2; //Servomotor de movimiento de flor, giro total de 180°


//************************************************************************
void setup() {
  
  Serial.begin(9600);

  //Declaración de los pines correspondientes de los servos
  servoMotor1.attach(5);
  servoMotor2.attach(6);

  //Posición Inicial 0° ServoMotores
  posActualS1= 0;
  posActualS2= 0;
  servoMotor1.write(0); 
  servoMotor2.write(0);
  
}//Fin del SET UP
//************************************************************************

void loop() {

  //Lectura de los Fotoresistores y obtención del más alto
  for(i=0;i<numFoto;i++){

    lumen[i]=analogRead(fotoR[i]);

    if(i == 0){ //Primer valor
      fotoMax =0;
      lumenMax= lumen[0]; }

    else{
      if(lumen[i] > lumenMax){ //Valor actual mayor
        fotoMax = i;
        lumenMax = lumen[i]; } }
    
  }//Fin del FOR lectura
  //---------------------------------------------------------------------------

  //Asignación del movimiento de los motores

  switch(fotoMax){

                  case 0:
                         servoMotor1.write(0); 
                         break;

                  case 1:
                         posActualS2=posActualS2-45;
                         servoMotor2.write(posActualS2);
                         break;

                  case 2:
                         posActualS1=posActualS1+90;
                         servoMotor1.write(posActualS1);
                         break;

                  case 3:
                          posActualS2=posActualS2+45;
                         servoMotor2.write(posActualS2);
                         break;

                  case 4:
                         posActualS1=posActualS1-90;
                         servoMotor1.write(posActualS1);
                         break;

                  default: //Posición Inicial 0° ServoMotores
                         posActualS1= 0;
                         posActualS2= 0;
                         servoMotor1.write(0); 
                         servoMotor2.write(0);
                         break;
    
  }//Fin del switch de movimiento
  
  delay(1000); //Espera de 1 segundo

}//Fin MAIN LOOP

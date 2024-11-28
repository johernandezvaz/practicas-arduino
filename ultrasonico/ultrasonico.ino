  /*
  
- Proyecto :  Práctica 3.2 Sensor Ultrasonico

- Instituto Tecnológico: Tecnológico Nacional de México Campus Chihuahua II

- Materia: Sistemas Programables

- Autores:
  - Sebastian Roesner Gomez 22550007
  - Felix Ulises Mancinas Zamora 22550029
  - José de Jesús Hernández Vázquez

- Fecha: 14/10/2024

  */  



#define led 0
#define Trigger 5
#define Echo 18

void setup() {
  //LED en el pin 8 //Trigger en el pin 13 //Echo en el pin 12
  Serial.begin(115200);
  pinMode (led, OUTPUT);
  pinMode (Trigger, OUTPUT);
  pinMode (Echo, INPUT);
  //definimos el led como salida
//definimos el pin trigger como salida //definimos el pin echo como entrada
  digitalWrite(Trigger, LOW); //Inicializamos el pin con 0
  }

void loop()
{
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite (Trigger, HIGH); //Mandamos un pulso a Trigger delayMicroseconds (10);
  /*Con un delay de 10us (este valor lo
  definimos según las especificaco¿iones tecnicas del componente*/ 
  digitalWrite (Trigger, LOW);
  t = pulseIn (Echo, HIGH); 
  d = t/59;
  //encontramos el ancho del pulso
  //hacemos la relación de la distancia en cm según el tiempo
  if (d<10){
    //Si la distancia es menor a 10 cm
    digitalWrite(led, HIGH); //Se enciende el led
  }else{
    //Sino
    digitalWrite(led, LOW); //Se mantiene apagado
  }
  Serial.print ("Distancia: ");
  Serial.print(d);
  //Se imprime el valor de la distancia en el monitor serial
  Serial.println();
  delay(100);
  }
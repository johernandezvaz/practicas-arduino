  /*
  
- Proyecto :  Práctica 4.1 Sensor Luminosidad

- Instituto Tecnológico: Tecnológico Nacional de México Campus Chihuahua II

- Materia: Sistemas Programables

- Autores:
  - Sebastian Roesner Gomez 22550007
  - Felix Ulises Mancinas Zamora 22550029
  - José de Jesús Hernández Vázquez

- Fecha: 03/11/2024

  */  


const int ldrPin = A0;      // Pin de entrada para la LDR
const int lampPin = 9;      // Pin de salida para la lámpara
const int threshold = 500;  // Umbral para determinar si es de noche

/* 
Justificación del umbral: Necesitamos un umbral para poder decidir cuándo la cantidad de luz es suficiente para considerar que es "de día" (y apagar la lámpara) y cuándo es "de noche" (y encender la lámpara). 
La LDR no nos dice directamente si es de día o de noche; solo mide la intensidad de luz en valores analógicos. Estos valores pueden cambiar mucho según la iluminación ambiente, 
por lo que el umbral nos permite establecer un punto de referencia.
*/

void setup() {
  pinMode(lampPin, OUTPUT); // Configura el pin de la lámpara como salida
  Serial.begin(9600);       // Inicializa la comunicación serial para depuración
}

void loop() {
  int ldrValue = analogRead(ldrPin);  // Lee el valor de la LDR
  Serial.println(ldrValue);           // Imprime el valor leído para verificación

  if (ldrValue > threshold) {
    digitalWrite(lampPin, HIGH);  // Enciende la lámpara si es de noche (valor alto)
  } else {
    digitalWrite(lampPin, LOW);   // Apaga la lámpara si hay luz (valor bajo)
  }

  delay(1000);  // Retraso para evitar lecturas rápidas y permitir una respuesta estable
}

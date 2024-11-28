  /*
  
- Proyecto :  Práctica 5.1 Comunicación I2C con Arduino

- Instituto Tecnológico: Tecnológico Nacional de México Campus Chihuahua II

- Materia: Sistemas Programables

- Autores:
  - Sebastian Roesner Gomez 22550007
  - Felix Ulises Mancinas Zamora 22550029
  - José de Jesús Hernández Vázquez

- Fecha: 28/11/2024

  */  

#include <Wire.h>

// Pines para los LEDs
#define LED1 4
#define LED2 5
#define LED3 6

// Dirección I2C del esclavo
#define SLAVE_ADDRESS 0x08

void setup() {
  Wire.begin(SLAVE_ADDRESS);  // Inicializar I2C con la dirección del esclavo
  Wire.onReceive(recibirComando);  // Configurar función de recepción

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.begin(9600);
  while (!Serial); // Esperar a que se establezca la conexión serial
  Serial.println("Arduino Esclavo I2C iniciado");
}

void loop() {
  // El esclavo no necesita hacer nada en el loop principal
  // Responderá automáticamente a las solicitudes del maestro
}

void recibirComando(int numBytes) {
  if (Wire.available()) {
    byte comando = Wire.read();  // Leer comando enviado por el maestro
    
    // Controlar LEDs según el comando recibido
    digitalWrite(LED1, comando & 0x01);  // Bit menos significativo
    digitalWrite(LED2, (comando >> 1) & 0x01);  // Segundo bit
    digitalWrite(LED3, (comando >> 2) & 0x01);  // Tercer bit

    // Imprimir comando recibido y estado de los LEDs
    Serial.print("Comando recibido: ");
    Serial.print(comando);
    Serial.print(" - Estado LEDs: ");
    Serial.print(digitalRead(LED1));
    Serial.print(digitalRead(LED2));
    Serial.println(digitalRead(LED3));
  }
}


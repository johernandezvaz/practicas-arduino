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

// Dirección del esclavo (Arduino)
#define SLAVE_ADDRESS 0x08

// Pines de los botones en el ESP32
#define BUTTON_1 16
#define BUTTON_2 17
#define BUTTON_3 5

// Variable para almacenar el último comando enviado
uint8_t lastCommand = 255; // Inicializado a un valor que no se usará como comando válido

// Variables para debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // 50 ms de debounce

void setup() {
  // Inicializar comunicación I2C como maestro
  Wire.begin();

  // Configurar los pines de los botones con resistencias pull-up internas
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);

  Serial.begin(115200);
  while (!Serial) {
    ; // Esperar a que se establezca la conexión serial
  }
  Serial.println("ESP32 Maestro I2C iniciado");
}

void loop() {
  // Leer el estado de los botones (invertido debido al pull-up)
  bool button1 = digitalRead(BUTTON_1);
  bool button2 = digitalRead(BUTTON_2);
  bool button3 = digitalRead(BUTTON_3);

  // Calcular el comando basado en los botones presionados
  uint8_t comando = (button1 ? 1 : 0) | (button2 ? 2 : 0) | (button3 ? 4 : 0);

  // Imprimir el estado de los botones y el comando calculado
  Serial.print("Estado botones: ");
  Serial.print(button1);
  Serial.print(button2);
  Serial.print(button3);
  Serial.print(" Comando calculado: ");
  Serial.println(comando);

  // Verificar si ha pasado suficiente tiempo desde el último cambio
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si el comando ha cambiado, enviarlo
    if (comando != lastCommand) {
      enviarComando(comando);
      lastCommand = comando;
      lastDebounceTime = millis(); // Actualizar el tiempo del último cambio
    }
  }

  // Pequeña pausa para estabilidad
  delay(10);
}

// Función para enviar un comando al esclavo
void enviarComando(uint8_t comando) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(comando);  // Enviar el comando al esclavo
  int error = Wire.endTransmission();

  if (error == 0) {
    Serial.print("Comando enviado correctamente: ");
    Serial.println(comando);
  } else {
    Serial.print("Error al enviar comando. Código de error: ");
    Serial.println(error);
  }
}


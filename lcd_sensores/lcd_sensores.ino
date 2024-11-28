#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Configuración de la pantalla LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Configuración del teclado 4x4
const byte FILAS = 4; // Número de filas
const byte COLUMNAS = 4; // Número de columnas
char keys[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[FILAS] = {2, 3, 4, 5};     // Pines conectados a las filas del teclado
byte colPins[COLUMNAS] = {6, 7, 8, 9};  // Pines conectados a las columnas del teclado

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, FILAS, COLUMNAS);

// Pines de los sensores
const int sensor1Pin = A0;
const int sensor2Pin = A1;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16,2);
  lcd.backlight();

  // Inicialización de pantalla y mensaje de bienvenida
  lcd.clear();
  lcd.print("Proyecto Arduino");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leer estado de los sensores
  int sensor1State = analogRead(sensor1Pin);
  int sensor2State = analogRead(sensor2Pin);

  // Leer tecla presionada
  char key = keypad.getKey();

  // Mostrar en LCD y Monitor Serie
  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(sensor1State);
  lcd.print(" S2:");
  lcd.print(sensor2State);

  // Mostrar tecla si se presiona
  lcd.setCursor(0, 1);
  if (key) {
    lcd.print("Tecla:");
    lcd.print(key);
    Serial.print("Tecla presionada: ");
    Serial.println(key);
  }

  // Enviar datos de los sensores al Monitor Serie
  Serial.print("Sensor 1: ");
  Serial.print(sensor1State);
  Serial.print(" | Sensor 2: ");
  Serial.println(sensor2State);

  delay(500); // Esperar medio segundo para no saturar la LCD y el Monitor Serie
}

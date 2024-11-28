#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Inicializa el objeto LCD con dirección 0x27 y tamaño 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Se declaran las dimensiones del teclado
const byte ROWS = 4;
const byte COLS = 4;

// Se define el arreglo de teclas
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'=','0','.','/'}
};

// Pines conectados al teclado
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

// Se crea el objeto Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variable de tipo entero para lecturas analógicas
int lectura = 0;

void setup() {
  Wire.begin();
  // Inicializamos el LCD y la comunicación serial
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
  
  // Mensaje inicial en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Leyendo sensor...");
  
  delay(2000);  // Pausa inicial
  lcd.clear();
}

void loop() {
  // Leer el valor analógico del fotorresistor (suponiendo que está en el pin A0)
  lectura = analogRead(A0);
  
  // Mostrar el valor de la luz en la fila 0
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.setCursor(5, 0);
  lcd.print(lectura);  // Mostramos el valor de la luz

  // Obtener el valor de la tecla presionada
  char key = keypad.getKey();

  // Si una tecla es presionada
  if (key != NO_KEY) {
    // Mostrar el valor del botón presionado en la fila 1
    lcd.setCursor(0, 1);
    lcd.print("Tecla: ");
    lcd.setCursor(7, 1);
    lcd.print(key);

    // También imprimimos el valor en el monitor serial
    Serial.print("Tecla presionada: ");
    Serial.println(key);
  }
  
  // Pausa para evitar refrescos rápidos
  delay(500);
}

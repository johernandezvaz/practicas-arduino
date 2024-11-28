  /*
  
- Proyecto :  Práctica 2.3 Control de Bombas

- Instituto Tecnológico: Tecnológico Nacional de México Campus Chihuahua II

- Materia: Sistemas Programables

- Autores:
  - Sebastian Roesner Gomez 22550007
  - Felix Ulises Mancinas Zamora 22550029
  - José de Jesús Hernández Vázquez

- Fecha: 30/09/2024

  */  


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definir pines para LEDs

#define I2C_ADDRESS 0x27

LiquidCrystal_I2C lcd(I2C_ADDRESS, 16, 2);

const int ledVacio = 6;
const int ledLlenandose = 5;
const int ledLleno = 4;
const int ledRebose = 3;
const int ledAlarma = 2;

// Definir pines para las bombas y LCD
const int bombas = 13;  // Control de las bombas
const int lleno = 80;   // Nivel de lleno (80%)
const int rebose = 100; // Nivel de rebose (100%)

float status = 0; // Variable que representa el estado actual del tanque


void setup() {
  Wire.begin(); 
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  // Configurar los pines como salida
  pinMode(ledVacio, OUTPUT);
  pinMode(ledLlenandose, OUTPUT);
  pinMode(ledLleno, OUTPUT);
  pinMode(ledRebose, OUTPUT);
  pinMode(ledAlarma, OUTPUT);
  pinMode(bombas, INPUT);


  lcd.begin(16, 2);  // Inicializar pantalla LCD de 16x2
  lcd.clear();       // Limpiar la pantalla
}

void loop() {
  // Verificar si hay un error en el sistema
  if (detectarError()) {
    // Encender el LED de alarma y mostrar el mensaje de error
    digitalWrite(ledAlarma, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error en el sistema");

    // Detener el proceso de llenado
    digitalWrite(ledLlenandose, LOW);
    return;  // Salir del loop para evitar que continúe llenando
  }

  // Verificar si las bombas están encendidas (pin 13 en HIGH)
  if (digitalRead(bombas) == HIGH) {
    // Incrementar el estado del nivel
    if (status < lleno) {
      status++;
    } else if (status >= lleno && status < rebose) {
      status += 0.5; // Simular llenado más lento después de 80%
    } else if (status >= rebose) {
      status = rebose; // Para que no sobrepase el valor de rebose
      vaciarTanque();  // Iniciar proceso de vaciado si llega a rebose
    }
  }

  // Si las bombas están apagadas, apagar el LED de "Llenándose"
  if (digitalRead(bombas) == LOW) {
    digitalWrite(ledLlenandose, LOW);
  }

  actualizarPantalla();
  actualizarLEDs();
  delay(100); // Simular el llenado del tanque cada segundo
}

// Función para detectar si hay un error
bool detectarError() {
  int ledsEncendidos = 0;

  // Contar cuántos LEDs de estado están encendidos
  if (digitalRead(ledVacio) == HIGH) {
    ledsEncendidos++;
  }
  if (digitalRead(ledLleno) == HIGH) {
    ledsEncendidos++;
  }
  if (digitalRead(ledRebose) == HIGH) {
    ledsEncendidos++;
  }

  // Si hay dos o más LEDs encendidos, hay un error
  if (ledsEncendidos >= 2) {
    return true;
  }
  
  return false;
}

// Función para vaciar el tanque si llega a rebose
void vaciarTanque() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Rebose, Vaciando");
  
  // Apagar todos los LEDs excepto el de rebose durante el vaciado
  apagarTodosLEDs();
  digitalWrite(ledRebose, HIGH); // Mantener el LED de "Rebose" encendido
  
  while (status > 0) {
    status--;
    lcd.setCursor(0, 0);  // Primera línea
    lcd.print("Status: ");
    lcd.print(status);
    lcd.print("%");
    delay(500); // Simular vaciado cada medio segundo
  }
  
  // Al finalizar el vaciado, apagar el LED de "Rebose" y encender el de "Vacío"
  digitalWrite(ledRebose, LOW);
  digitalWrite(ledVacio, HIGH);
}

// Función para apagar todos los LEDs
void apagarTodosLEDs() {
  digitalWrite(ledVacio, LOW);
  digitalWrite(ledLlenandose, LOW);
  digitalWrite(ledLleno, LOW);
  digitalWrite(ledRebose, LOW);
  digitalWrite(ledAlarma, LOW);
}

// Función para actualizar los LEDs de estado
void actualizarLEDs() {
  // Si las bombas están activas, el LED de "Llenándose" sigue encendido
  if (digitalRead(bombas) == HIGH) {
    if (status < lleno) {
      digitalWrite(ledLlenandose, HIGH); // Llenándose antes del nivel lleno
      digitalWrite(ledVacio, LOW);       // Apagar el LED de "Vacío" si empieza a llenarse
    } else if (status >= lleno && status < rebose) {
      digitalWrite(ledLleno, HIGH);      // Lleno
      digitalWrite(ledLlenandose, HIGH); // Sigue llenándose aunque esté cerca de lleno
    }
  } else {  // Si las bombas están apagadas o se ha alcanzado el rebose
    if (status == 0) {
      digitalWrite(ledVacio, HIGH);  // Si está vacío, encender LED de "Vacío"
    } else if (status >= rebose) {
      digitalWrite(ledRebose, HIGH); // Encender LED de "Rebose" en el nivel máximo
    }
  }
}

// Función para actualizar la información en la pantalla LCD
void actualizarPantalla() {
  lcd.clear();
  lcd.setCursor(0, 0);  // Primera línea
  lcd.print("Status: ");
  lcd.print(status);
  lcd.print("%");

  lcd.setCursor(0, 1);  // Segunda línea
  if (status == 0) {
    lcd.print("Vacio");
  } else if ((status > 0 && status < lleno) && digitalRead(bombas) == HIGH) {
    lcd.print("Llenandose");
  } else if  ((status > 0 && status < lleno) && digitalRead(bombas) == LOW){
    lcd.print("En Pausa");
  }else if ((status >= lleno && status < rebose)){
    lcd.print("Lleno");
  } else if (status >= rebose) {
    lcd.print("Rebose!");
  }
}

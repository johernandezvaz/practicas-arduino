#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuración del LCD en dirección 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definimos los pines de los LEDs
const int leds[] = {2, 3, 4, 5, 6, 7};
const int boton = 8;

void setup() {
    Wire.begin();
    // Inicializar LEDs como salida
    for (int i = 0; i < 6; i++) {
        pinMode(leds[i], OUTPUT);
    }

    // Configurar el botón como entrada con resistencia pull-up
    pinMode(boton, INPUT_PULLUP);

    // Inicializar LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Presiona el boton");
}

void loop() {
    if (digitalRead(boton) == LOW) { // Se presionó el botón
        delay(200); // Pequeño retardo para evitar rebotes

        // Apagar todos los LEDs antes de lanzar el dado
        for (int i = 0; i < 6; i++) {
            digitalWrite(leds[i], LOW);
        }

        // Generar número aleatorio entre 1 y 6
        int numero = random(1, 7);

        // Encender LEDs según el número obtenido
        for (int i = 0; i < numero; i++) {
            digitalWrite(leds[i], HIGH);
        }

        // Mostrar el número en el LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Numero: ");
        lcd.print(numero);
        
        delay(1000); // Pequeña pausa antes de permitir otro lanzamiento
    }
}

// Define el pin al que está conectado el LED
#define LED 15

void setup() {
  // Inicializa el pin como salida
  pinMode(LED, OUTPUT);
}

void loop() {
  // Enciende el LED
  digitalWrite(LED, HIGH);
  Serial.print("Alto");
  // Espera 1 segundo
  delay(1000);
  // Apaga el LED
  digitalWrite(LED, LOW);
  Serial.print("Bajo");
  // Espera 1 segundo
  delay(1000);
}

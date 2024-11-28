  /*
  
- Proyecto :  Práctica 2.2 Semáforo peatonal.

- Instituto Tecnológico: Tecnológico Nacional de México Campus Chihuahua II

- Materia: Sistemas Programables

- Autores:
  - Sebastian Roesner Gomez 22550007
  - Felix Ulises Mancinas Zamora 22550029
  - José de Jesús Hernández Vázquez

- Fecha: 19/09/2024

  */  
  
  
  
  // Definimos los pines para cada LED
  const int ledVerde1 = 13;
  const int ledAmarillo1 = 12;
  const int ledRojo1 = 8;
  const int ledVerde2 = 7;
  const int ledRojo2 = 4;
  
  
  // Pin para la señal de inicio de la secuencia
  const int pinSenal = 2;

  void setup() {
    // Configuramos los pines de los LEDs como salida
    pinMode(ledVerde1, OUTPUT);
    pinMode(ledAmarillo1, OUTPUT);
    pinMode(ledRojo1, OUTPUT);
    pinMode(ledVerde2, OUTPUT);
    pinMode(ledRojo2, OUTPUT);

    // Configuramos el pin de la señal como entrada
    pinMode(pinSenal, INPUT);

    // Estado inicial: semáforo 1 en verde, semáforo 2 en rojo
    digitalWrite(ledVerde1, HIGH);
    digitalWrite(ledAmarillo1, LOW);
    digitalWrite(ledRojo1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledRojo2, HIGH);
  }

  void loop() {
    // Leemos la señal para iniciar la secuencia
    int senal = digitalRead(pinSenal);

    // Si la señal es 1, iniciamos la secuencia
    if (senal == HIGH) {
      // Semáforo 1 en verde durante 10 segundos
      digitalWrite(ledVerde1, HIGH);
      digitalWrite(ledAmarillo1, LOW);
      digitalWrite(ledRojo1, LOW);
      digitalWrite(ledVerde2, LOW);
      digitalWrite(ledRojo2, HIGH);
      delay(10000);  // 10 segundos

      // Semáforo 1 en amarillo durante 5 segundos
      digitalWrite(ledVerde1, LOW);
      digitalWrite(ledAmarillo1, HIGH);
      digitalWrite(ledRojo1, LOW);
      delay(5000);  // 5 segundos

      // Semáforo 1 en rojo y semáforo 2 en verde durante 15 segundos
      digitalWrite(ledVerde1, LOW);
      digitalWrite(ledAmarillo1, LOW);
      digitalWrite(ledRojo1, HIGH);
      digitalWrite(ledVerde2, HIGH);
      digitalWrite(ledRojo2, LOW);
      delay(15000);  // 15 segundos

      // Regresamos al estado inicial: semáforo 1 en verde y semáforo 2 en rojo
      digitalWrite(ledVerde1, HIGH);
      digitalWrite(ledAmarillo1, LOW);
      digitalWrite(ledRojo1, LOW);
      digitalWrite(ledVerde2, LOW);
      digitalWrite(ledRojo2, HIGH);
    }

    // Pequeño delay para no saturar el ciclo
    delay(100);
  }

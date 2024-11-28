  /*
  
- Proyecto :  Práctica 4.3 Control de Motores

- Instituto Tecnológico: Tecnológico Nacional de México Campus Chihuahua II

- Materia: Sistemas Programables

- Autores:
  - Sebastian Roesner Gomez 22550007
  - Felix Ulises Mancinas Zamora 22550029
  - José de Jesús Hernández Vázquez

- Fecha: 27/11/2024

  */  


#include <Servo.h>
#include <Stepper.h>

#define STEPS 32

// Definición de pines para los switches
#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5

// Pines del motor de CD (control directo con transistores)
#define PWM_MOTOR 9   // Pin PWM para velocidad
#define DIR1 6        // Dirección CW
#define DIR2 7        // Dirección CCW

// Pines para el ULN2003 (motor paso a paso)
#define IN1 10
#define IN2 11
#define IN3 12
#define IN4 13

// Definición del servomotor
Servo servo;
Stepper stepper(STEPS, IN4, IN3, IN2, IN1);
#define SERVO_PIN 8

void setup() {
  // Configuración de pines de entrada
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);

  // Configuración de pines de salida para motor de CD
  pinMode(PWM_MOTOR, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);

  // Inicialización del servomotor
  servo.attach(SERVO_PIN);
  servo.write(0);  // Inicializar el servo en 0 grados

  // Detener todo inicialmente
  detenerMotores();
}

void loop() {
  int sw1 = digitalRead(SW1);
  int sw2 = digitalRead(SW2);
  int sw3 = digitalRead(SW3);
  int sw4 = digitalRead(SW4);

  // Decodificar selección de motor
  if (sw1 == 0 && sw2 == 0) {
    detenerMotores();
  } else if (sw1 == 0 && sw2 == 1) {
    controlarMotorCD(sw3, sw4);
  } else if (sw1 == 1 && sw2 == 0) {
    controlarMotorPasoPaso(sw3, sw4);
  } else if (sw1 == 1 && sw2 == 1) {
    controlarServo(sw3, sw4);
  }
}

void detenerMotores() {
  // Detener motor de CD
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  analogWrite(PWM_MOTOR, 0);

  // Detener motor paso a paso
  stepper.step(0);

  // Posición inicial del servomotor
  servo.write(0);
}

void controlarMotorCD(int sentido, int velocidad) {

  analogWrite(PWM_MOTOR, 255);  // 100%

  // Configurar sentido de giro
  if (sentido == 0) {  // CW
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
  } else if(sentido == 1) {  // CCW
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
  }

  // Configurar velocidad
  if (velocidad == 0) {
    analogWrite(PWM_MOTOR, 128);  // 50%
  } else if(velocidad == 1) {
    analogWrite(PWM_MOTOR, 255);  // 100%
  }
}

void controlarMotorPasoPaso(int sentido, int velocidad) {
  // Configurar velocidad
  int speed = (velocidad == 0) ? 60 : 120;  // RPM
  stepper.setSpeed(speed);

  // Configurar dirección y mover el motor
  int steps = (sentido == 0) ? 512 : -512;  // Una vuelta completa en sentido horario o antihorario
  stepper.step(steps);
}

void controlarServo(int sw3, int sw4) {
  int angle = 0;

  if (sw3 == 0 && sw4 == 0) {
    angle = 0;
  } else if (sw3 == 0 && sw4 == 1) {
    angle = 60;
  } else if (sw3 == 1 && sw4 == 0) {
    angle = 76;
  } else if (sw3 == 1 && sw4 == 1) {
    angle = 180;
  }

  // Mover el servo gradualmente para mayor precisión
  int currentAngle = servo.read();
  int step = (angle > currentAngle) ? 1 : -1;
  
  while (currentAngle != angle) {
    currentAngle += step;
    servo.write(currentAngle);
    delay(15);  // Pequeña pausa entre cada incremento
  }
  
  delay(500);  // Tiempo adicional para que el servo se estabilice
}


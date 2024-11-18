#include <Servo.h>

// Crear objetos Servo para cada servomotor
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Pines donde están conectados los servos
const int servoPin1 = 9;
const int servoPin2 = 10;
const int servoPin3 = 11;
const int servoPin4 = 12;

// Variables para el tiempo de espera
const unsigned long delayTime = 5000; // 5 segundos de retraso

void setup() {
  // Inicializar la comunicación serial
  Serial.begin(9600);

  // Conectar los servos a sus respectivos pines
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);

  // Colocar los servos en la posición inicial (0 grados)
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  Serial.println("Sistema listo. Esperando comandos...");
}

void loop() {
  // Verificar si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');  // Leer el comando enviado

    // Eliminar espacios en blanco si es necesario
    comando.trim();  

    // Comparar el comando recibido con las palabras clave
    if (comando.equalsIgnoreCase("cebolla")) {
      moverServo(servo1);
    } else if (comando.equalsIgnoreCase("tomate")) {
      moverServo(servo2);
    } else if (comando.equalsIgnoreCase("cafe")) {
      moverServo(servo3);
    } else if (comando.equalsIgnoreCase("zanahoria")) {
      moverServo(servo4);
    } else {
      Serial.println("Comando no reconocido. Prueba con: cebolla, tomate, cafe, zanahoria.");
    }
  }
}

// Función para mover el servo
void moverServo(Servo &servo) {
  // Mover el servo a 180 grados
  servo.write(180);
  Serial.println("Servo movido a 180 grados");

  // Esperar 5 segundos
  delay(delayTime);

  // Regresar el servo a la posición inicial (0 grados)
  servo.write(0);
  Serial.println("Servo regresado a 0 grados");
}



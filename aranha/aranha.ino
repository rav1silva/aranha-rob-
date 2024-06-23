#include <Servo.h>

// Definindo as portas dos servos
#define SERVO2_PORT 2
#define SERVO1_PORT 3
#define SERVO3_PORT 4
#define SERVO4_PORT 5
#define SERVO6_PORT 6
#define SERVO5_PORT 7
#define SERVO8_PORT 8
#define SERVO7_PORT 9

// Criando variáveis Servo para cada motor
Servo servo2;
Servo servo1;
Servo servo3;
Servo servo4;
Servo servo6;
Servo servo5;
Servo servo8;
Servo servo7;

void setup() {
  Serial.begin(9600);

  // Anexando os servos às portas correspondentes
  servo2.attach(SERVO2_PORT);
  servo1.attach(SERVO1_PORT);
  servo3.attach(SERVO3_PORT);
  servo4.attach(SERVO4_PORT);
  servo6.attach(SERVO6_PORT);
  servo5.attach(SERVO5_PORT);
  servo8.attach(SERVO8_PORT);
  servo7.attach(SERVO7_PORT);

  // Iniciando todos os servos na posição 0
  servo2.write(0);
  servo1.write(0);
  servo3.write(0);
  servo4.write(0);
  servo6.write(0);
  servo5.write(0);
  servo8.write(0);
  servo7.write(0);
}

void loop() {
  // Movendo todos os servos para a posição 90
  servo2.write(90);
  servo1.write(90);
  servo3.write(90);
  servo4.write(90);
  servo6.write(90);
  servo5.write(90);
  servo8.write(90);
  servo7.write(90);

  // Aguarde um pouco para garantir que todos os servos se movam para a posição
  delay(1000);

  // Você pode adicionar código adicional aqui para outras operações
}

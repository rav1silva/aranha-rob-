#include <Servo.h>

// Definindo os objetos servo
Servo frontServo1;
Servo frontServo2;
Servo backServo1;
Servo backServo2;
Servo armServo;
Servo eyeServo;

void setup() {
  // Inicializando os servos nos pinos correspondentes
  frontServo1.attach(2);
  frontServo2.attach(3);
  backServo1.attach(4);
  backServo2.attach(5);
  armServo.attach(6);
  eyeServo.attach(7);

  // Sequência inicial de piscar os olhos
  piscarOlhos();

  // Movimentos iniciais
  moverFrente(5000);   // Ir para frente por 5 segundos
  moverTras(5000);     // Ir para trás por 5 segundos
  virarEsquerda(5000); // Virar à esquerda por 5 segundos
  virarDireita(5000);  // Virar à direita por 5 segundos
}

void loop() {
  // Coloque aqui o que o robô deve fazer no loop principal após os movimentos iniciais
}

// Função para piscar os olhos
void piscarOlhos() {
  for (int i = 0; i < 3; i++) {
    eyeServo.write(0);
    delay(200);
    eyeServo.write(180);
    delay(200);
  }
  eyeServo.write(90);
}

// Função para mover para frente
void moverFrente(int tempo) {
  frontServo1.write(0);
  frontServo2.write(180);
  backServo1.write(0);
  backServo2.write(180);
  delay(tempo);
  pararMovimento();
}

// Função para mover para trás
void moverTras(int tempo) {
  frontServo1.write(180);
  frontServo2.write(0);
  backServo1.write(180);
  backServo2.write(0);
  delay(tempo);
  pararMovimento();
}

// Função para virar à esquerda
void virarEsquerda(int tempo) {
  frontServo1.write(180);
  frontServo2.write(180);
  backServo1.write(0);
  backServo2.write(0);
  delay(tempo);
  pararMovimento();
}

// Função para virar à direita
void virarDireita(int tempo) {
  frontServo1.write(0);
  frontServo2.write(0);
  backServo1.write(180);
  backServo2.write(180);
  delay(tempo);
  pararMovimento();
}

// Função para parar o movimento
void pararMovimento() {
  frontServo1.write(90);
  frontServo2.write(90);
  backServo1.write(90);
  backServo2.write(90);
}

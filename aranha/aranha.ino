#include <Servo.h>    // include servo library

//===== Globals ============================================================================

// Define USRF pins and variables
#define SPIDER_EYE_1   10
#define SPIDER_EYE_2   11

// calibration
int da = -12,  // Left Front Pivot
    db = 10,   // Left Back Pivot
    dc = -18,  // Right Back Pivot
    dd = 12;   // Right Front Pivot

// servo initial positions + calibration
int a90  = (90  + da),
    a120 = (120 + da),
    a150 = (150 + da),
    a180 = (180 + da);

int b0   = (0   + db),
    b30  = (30  + db),
    b60  = (60  + db),
    b90  = (90  + db);

int c90  = (90  + dc),
    c120 = (120 + dc),
    c150 = (150 + dc),
    c180 = (180 + dc);

int d0   = (0   + dd),
    d30  = (30  + dd),
    d60  = (60  + dd),
    d90  = (90   + dd);

// start points for servo
int s11 = 90; // Front Left Pivot Servo
int s12 = 90; // Front Left Lift Servo
int s21 = 90; // Back Left Pivot Servo
int s22 = 90; // Back Left Lift Servo
int s31 = 90; // Back Right Pivot Servo
int s32 = 90; // Back Right Lift Servo
int s41 = 90; // Front Right Pivot Servo
int s42 = 90; // Front Right Lift Servo

int f    = 0;
int b    = 0;
int l    = 0;
int r    = 0;
int spd  = 3;  // Speed of walking motion, larger the number, the slower the speed
int high = 0;   // How high the robot is standing

// Define 8 Servos
Servo myServo1; // Front Left Pivot Servo
Servo myServo2; // Front Left Lift Servo
Servo myServo3; // Back Left Pivot Servo
Servo myServo4; // Back Left Lift Servo
Servo myServo5; // Back Right Pivot Servo
Servo myServo6; // Back Right Lift Servo
Servo myServo7; // Front Right Pivot Servo
Servo myServo8; // Front Right Lift Servo

//==========================================================================================

//===== Setup ==============================================================================

void setup() {
  // Attach servos to Arduino Pins
  myServo1.attach(2);
  myServo2.attach(3);
  myServo3.attach(4);
  myServo4.attach(5);
  myServo5.attach(6);
  myServo6.attach(7);
  myServo7.attach(8);
  myServo8.attach(9);

  pinMode(SPIDER_EYE_1, OUTPUT);
  pinMode(SPIDER_EYE_2, OUTPUT);

  Serial.begin(9600);   // UART for Bluetooth Module with baudrate of 9600 bps

  // Spider eye animation
  for (int i = 0; i < 3; i++) {
    digitalWrite(SPIDER_EYE_1, LOW);
    digitalWrite(SPIDER_EYE_2, LOW);
    delay(300);
    digitalWrite(SPIDER_EYE_1, HIGH);
    digitalWrite(SPIDER_EYE_2, HIGH);
    delay(300);
  }
  forward();
  delay (500);
  back ();
  delay (500);  
  turn_left ();
  delay (500);
  turn_right ();
  delay (500);
  dance();
}

//==========================================================================================

//== Loop ==================================================================================

char Received_Command = 'S', Valid_Received_Command = 'S';    // By default stop command is selected.

void loop() {
  center_servos();  // Center all servos
  high = 15;        // Set height to 15
  spd = 3;          // Set speed to 3

  while (true) {    // Loop forever
    if (Serial.available()) {                // Command from Bluetooth Module
      Received_Command = Serial.read();
      if (strchr("FBRLXYS", Received_Command)) {
        Valid_Received_Command = Received_Command;
        Serial.println(Received_Command);
      }
    }

    switch (Valid_Received_Command) {
      case 'F': forward(); break;            // Move forward
      case 'B': back(); break;               // Move reverse
      case 'L': turn_left(); break;          // Turn left
      case 'R': turn_right(); break;         // Turn right
      case 'X': dance(); Valid_Received_Command = 'S'; break;  // Dance once
      case 'Y': wave(); Valid_Received_Command = 'S'; break;   // Wave once
      case 'S':
      default:
        center_servos();                     // Stop
        high = 15;                           // Set height to 15
        spd = 3;                             // Set speed to 3
        Valid_Received_Command = 'P';
        break;
    }
    delay(1000);  // Pause for 1000 ms before executing next movement
  }
}

// Function implementations (e.g., forward, back, turn_left, turn_right, etc.)

void forward() {
  // calculation of points
  a90 = (90 + da);
  a120 = (120 + da);
  a150 = (150 + da);
  a180 = (180 + da);

  b0 = (0 + db);
  b30 = (30 + db);
  b60 = (60 + db);
  b90 = (90 + db);

  c90 = (90 + dc);
  c120 = (120 + dc);
  c150 = (150 + dc);
  c180 = (180 + dc);

  d0 = (0 + dd);
  d30 = (30 + dd);
  d60 = (60 + dd);
  d90 = (90 + dd);

  // set servo positions and speeds needed to walk forward one step
  srv(a180, b0 , c120, d60, 42,  33,  33,  42,  1,  3,  1,  1);
  srv( a90, b30, c90,  d30, 6,   33,  33,  42,  3,  1,  1,  1);
  srv( a90, b30, c90,  d30, 42,  33,  33,  42,  3,  1,  1,  1);
  srv(a120, b60, c180, d0,  42,  33,  6,   42,  1,  1,  3,  1);
  srv(a120, b60, c180, d0,  42,  33,  33,  42,  1,  1,  3,  1);
  srv(a150, b90, c150, d90, 42,  33,  33,  6,   1,  1,  1,  3);
  srv(a150, b90, c150, d90, 42,  33,  33,  42,  1,  1,  1,  3);
  srv(a180, b0,  c120, d60, 42,  6,   33,  42,  1,  3,  1,  1);
}

void back() {
  srv(180, 0,  120, 60, 42, 33, 33, 42, 3,  1, 1, 1);
  srv(150, 90, 150, 90, 42, 18, 33, 42, 1,  3, 1, 1);
  srv(150, 90, 150, 90, 42, 33, 33, 42, 1,  3, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1,  1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1,  1, 1, 3);
  srv(90,  30, 90,  30, 42, 33, 18, 42, 1,  1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 42, 1,  1, 3, 1);
  srv(180, 0,  120, 60, 6,  33, 33, 42, 3,  1, 1, 1);
}

void turn_left() {
  srv(120, 60, 150, 90, 42, 33, 33, 6,  3, 1, 1, 1);
  srv(120, 60, 150, 90, 42, 33, 33, 42, 3, 1, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 33, 42, 1, 3, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 33, 6,  1, 3, 1, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 42, 1, 1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 6,  1, 1, 3, 1);
}

void turn_right() {
  srv(120, 60, 150, 90, 42, 33, 6,  33, 3, 1, 1, 1);
  srv(120, 60, 150, 90, 42, 33, 42, 33, 3, 1, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 42, 33, 1, 3, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 6,  33, 1, 3, 1, 1);
  srv(90,  30, 90,  30, 42, 33, 42, 33, 1, 1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 6,  33, 1, 1, 3, 1);
}

// srv function to set servo positions and delay
void srv(int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int d1, int d2, int d3, int d4) {
  delay(spd * d1);
  myServo1.write(s1);
  myServo2.write(s2);
  delay(spd * d2);
  myServo3.write(s3);
  myServo4.write(s4);
  delay(spd * d3);
  myServo5.write(s5);
  myServo6.write(s6);
  delay(spd * d4);
  myServo7.write(s7);
  myServo8.write(s8);
}

void center_servos() {
  myServo1.write(90); 
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);
}

// Dummy functions for dance and wave
void dance() {
  // Implement the dance moves
  Serial.println("Dancing...");
}

void wave() {
  // Implement the wave moves
  Serial.println("Waving...");
}


//***************Ravi**************//
// aranha robo bluetooth
//==========================================================================================

#include <Servo.h>    // include servo library

//===== Globals ============================================================================

// Define USRF pins and variables

#define SPIDER_EYE_1    10
#define SPIDER_EYE_2    11

// calibration
int da =  -12,  // Left Front Pivot
    db =   10,  // Left Back Pivot
    dc =  -18,  // Right Back Pivot
    dd =   12;  // Right Front Pivot

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
    d90  = (90  + dd);

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

void setup()
{
  
  // Attach servos to Arduino Pins
//  myServo1.attach(2);
//  myServo2.attach(3);
//  myServo3.attach(4);
//  myServo4.attach(5);
//  myServo5.attach(6);
//  myServo6.attach(7);
//  myServo7.attach(8);
//  myServo8.attach(9);

//Servo myServo1; // Front Left Pivot Servo
//Servo myServo2; // Front Left Lift Servo
//Servo myServo3; // Back Left Pivot Servo
//Servo myServo4; // Back Left Lift Servo
//Servo myServo5; // Back Right Pivot Servo
//Servo myServo6; // Back Right Lift Servo
//Servo myServo7; // Front Right Pivot Servo
//Servo myServo8; // Front Right Lift Servo

  myServo1.attach(2);
  myServo2.attach(3);
  myServo3.attach(4);
  myServo4.attach(5);
  myServo5.attach(6);
  myServo6.attach(7);
  myServo7.attach(8);
  myServo8.attach(9);

//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);

  pinMode(SPIDER_EYE_1, OUTPUT);
  pinMode(SPIDER_EYE_2, OUTPUT);

  Serial.begin(9600);   // UART for Bluetooth Module with baudrate of 9600 bps
  

  digitalWrite(SPIDER_EYE_1, LOW);
  digitalWrite(SPIDER_EYE_2, LOW);
  delay(300);
  digitalWrite(SPIDER_EYE_1, HIGH);
  digitalWrite(SPIDER_EYE_2, HIGH);
  delay(300);

  digitalWrite(SPIDER_EYE_1, LOW);
  digitalWrite(SPIDER_EYE_2, LOW);
  delay(300);
  digitalWrite(SPIDER_EYE_1, HIGH);
  digitalWrite(SPIDER_EYE_2, HIGH);
  delay(300);

  digitalWrite(SPIDER_EYE_1, LOW);
  digitalWrite(SPIDER_EYE_2, LOW);
  delay(300);
  digitalWrite(SPIDER_EYE_1, HIGH);
  digitalWrite(SPIDER_EYE_2, HIGH);


  // Centraliza os servos
  center_servos();

  // Move para frente durante 5 segundos

  // Executa movimentos em todas as direções
 

  // ... (outras configurações)


}//setup

//==========================================================================================

//== Loop ==================================================================================

char Received_Command = 'S',Valid_Received_Command = 'S';    // By default stop command is selected.

void loop()
{
  unsigned long value;
  unsigned long lastValue;
  
  center_servos();  // Center all servos
  high = 15;        // Set hight to 15
  spd = 3;          // Set speed to 3

  while (1 == 1)    // Loop forever
  {

    if(Serial.available())                // Command from Bluetooth Module
    {
        Received_Command = Serial.read();
        //Serial.println(Received_Command);
  
        if((Received_Command == 'F')||(Received_Command == 'B')||(Received_Command == 'R')||(Received_Command == 'L')||(Received_Command == 'X')||(Received_Command == 'Y')
       ||(Received_Command == 'M')||(Received_Command == 'm')||(Received_Command == 'N')||(Received_Command == 'n')||(Received_Command == 'S'))
       {
            Valid_Received_Command =  Received_Command;
            Serial.println(Received_Command);
       }
    }

    if(Valid_Received_Command == 'F')            //move forward
    {
      forward();
    }
    else if(Valid_Received_Command == 'B')      //move reverse
    {
      back();
    }
    else if(Valid_Received_Command == 'L')      //turn right
    {
      turn_left();
    }
    else if(Valid_Received_Command == 'R')      //turn left
    {
      turn_right();
    }
    else if(Valid_Received_Command == 'X')      //Dance once
    {
      dance();
      Valid_Received_Command = 'S';
    }
    else if(Valid_Received_Command == 'Y')      //Wave once
    {
      wave();
      Valid_Received_Command = 'S';
    }
    else if((Valid_Received_Command == 'S')||(Valid_Received_Command == 'm')||(Valid_Received_Command == 'n'))      //STOP
    {      
      center_servos();  // Center all servos
      high = 15;        // Set hight to 15
      spd = 3;          // Set speed to 3
      Valid_Received_Command = 'P';
    }
      
//      Serial.println(Received_Command);
      delay(1000);  // Pause for 1000 ms before executing next movement

  }//while

}//loop

void dance()
{
  center_servos();
  delay(100);
  lean_left();
  delay(1000);
  lean_right();
  delay(1000);
  lean_left();
  delay(1000);
  lean_right();
  delay(1000);
  lean_left();
  delay(1000);
  lean_right();
  delay(1000);
  lean_left();
  delay(1000);
  lean_right();
  delay(1000);
  center_servos();
  delay(1000);
  bow();
  delay(1000);
  center_servos();

  digitalWrite(SPIDER_EYE_1, LOW);
  digitalWrite(SPIDER_EYE_2, LOW);
  delay(300);
  digitalWrite(SPIDER_EYE_1, HIGH);
  digitalWrite(SPIDER_EYE_2, HIGH);
  delay(300);

  digitalWrite(SPIDER_EYE_1, LOW);
  digitalWrite(SPIDER_EYE_2, LOW);
  delay(300);
  digitalWrite(SPIDER_EYE_1, HIGH);
  digitalWrite(SPIDER_EYE_2, HIGH);
  delay(300);

  digitalWrite(SPIDER_EYE_1, LOW);
  digitalWrite(SPIDER_EYE_2, LOW);
  delay(300);
  digitalWrite(SPIDER_EYE_1, HIGH);
  digitalWrite(SPIDER_EYE_2, HIGH);
  //delay(300);
}

//== Wave ==================================================================================

void wave()
{
  /*
  myServo1 - Front Left Pivot Servo
  myServo2 - Front Left Lift Servo
  myServo3 - Back Left Pivot Servo
  myServo4 - Back Left Lift Servo
  myServo5 - Back Right Pivot Servo
  myServo6 - Back Right Lift Servo
  myServo7 - Front Right Pivot Servo
  myServo8 - Front Right Lift Servo
  */

  center_servos();
  myServo4.write(45);
  myServo6.write(45);
  delay(1000);
  myServo8.write(0);
  delay(1000);
  myServo7.write(180);
  delay(1000);
  myServo7.write(30);
  delay(1000);
  myServo7.write(150);
  delay(1000);
  myServo7.write(30);
  delay(1000);
  myServo7.write(s41);
  delay(1000);
  myServo8.write(s42);
  center_servos();

}

//== Bow ===================================================================================

void bow()
{
  center_servos();
  delay(1000);
  myServo2.write(15);
  myServo8.write(15);
  delay(1000);
  myServo2.write(90);
  myServo8.write(90);
  delay(1000);
}

//== Lean_Left =============================================================================

void lean_left()
{
  myServo2.write(15);
  myServo4.write(15);
  myServo6.write(150);
  myServo8.write(150);
}

//== Lean_Right ============================================================================

void lean_right()
{
  myServo2.write(150);
  myServo4.write(150);
  myServo6.write(15);
  myServo8.write(15);
}

//== Lean_Left =============================================================================

void trim_left()
{
  da--; // Left Front Pivot
  db--; // Left Back Pivot
  dc--; // Right Back Pivot
  dd--; // Right Front Pivot
}

//== Lean_Right ============================================================================

void trim_right()
{
  da++; // Left Front Pivot
  db++; // Left Back Pivot
  dc++; // Right Back Pivot
  dd++; // Right Front Pivot
}

//== Forward ===============================================================================

void forward()
{
  // calculation of points

  // Left Front Pivot
  a90 = (90 + da),
  a120 = (120 + da),
  a150 = (150 + da),
  a180 = (180 + da);

  // Left Back Pivot
  b0 = (0 + db),
  b30 = (30 + db),
  b60 = (60 + db),
  b90 = (90 + db);

  // Right Back Pivot
  c90 = (90 + dc),
  c120 = (120 + dc),
  c150 = (150 + dc),
  c180 = (180 + dc);

  // Right Front Pivot
  d0 = (0 + dd),
  d30 = (30 + dd),
  d60 = (60 + dd),
  d90 = (90 + dd);

  // set servo positions and speeds needed to walk forward one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(a180, b0 , c120, d60, 42,  33,  33,  42,  1,  3,  1,  1);
  srv( a90, b30, c90,  d30, 6,   33,  33,  42,  3,  1,  1,  1);
  srv( a90, b30, c90,  d30, 42,  33,  33,  42,  3,  1,  1,  1);
  srv(a120, b60, c180, d0,  42,  33,  6,   42,  1,  1,  3,  1);
  srv(a120, b60, c180, d0,  42,  33,  33,  42,  1,  1,  3,  1);
  srv(a150, b90, c150, d90, 42,  33,  33,  6,   1,  1,  1,  3);
  srv(a150, b90, c150, d90, 42,  33,  33,  42,  1,  1,  1,  3);
  srv(a180, b0,  c120, d60, 42,  6,   33,  42,  1,  3,  1,  1);
  //srv(a180, b0,  c120, d60, 42,  15,  33,  42,  1,  3,  1,  1);
  
}

//== Back ==================================================================================

void back ()
{
  // set servo positions and speeds needed to walk backward one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(180, 0,  120, 60, 42, 33, 33, 42, 3,  1, 1, 1);
  srv(150, 90, 150, 90, 42, 18, 33, 42, 1,  3, 1, 1);
  srv(150, 90, 150, 90, 42, 33, 33, 42, 1,  3, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1,  1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1,  1, 1, 3);
  srv(90,  30, 90,  30, 42, 33, 18, 42, 1,  1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 42, 1,  1, 3, 1);
  srv(180, 0,  120, 60, 6,  33, 33, 42, 3,  1, 1, 1);

}

//== Left =================================================================================

void turn_left ()
{
  // set servo positions and speeds needed to turn left one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(150,  90, 90,  30, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(150,  90, 90,  30, 42, 33, 33, 42, 1, 3, 1, 1);
  srv(120,  60, 180, 0,  42, 33, 6,  42, 1, 1, 3, 1);
  srv(120,  60, 180, 0,  42, 33, 33, 24, 1, 1, 3, 1);
  srv(90,   30, 150, 90, 42, 33, 33, 6,  1, 1, 1, 3);
  srv(90,   30, 150, 90, 42, 33, 33, 42, 1, 1, 1, 3);
  srv(180,  0,  120, 60, 6,  33, 33, 42, 3, 1, 1, 1);
  srv(180,  0,  120, 60, 42, 33, 33, 33, 3, 1, 1, 1);
}

//== Right ================================================================================

void turn_right ()
{
  // set servo positions and speeds needed to turn right one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv( 90, 30, 150, 90, 6,  33, 33, 42, 3, 1, 1, 1);
  srv( 90, 30, 150, 90, 42, 33, 33, 42, 3, 1, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1, 1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1, 1, 1, 3);
  srv(150, 90, 90,  30, 42, 33, 6,  42, 1, 1, 3, 1);
  srv(150, 90, 90,  30, 42, 33, 33, 42, 1, 1, 3, 1);
  srv(180, 0,  120, 60, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 33, 42, 1, 3, 1, 1);
}

//== Center Servos ========================================================================

void center_servos()
{
  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);

  int s11 = 90; // Front Left Pivot Servo
  int s12 = 90; // Front Left Lift Servo
  int s21 = 90; // Back Left Pivot Servo
  int s22 = 90; // Back Left Lift Servo
  int s31 = 90; // Back Right Pivot Servo
  int s32 = 90; // Back Right Lift Servo
  int s41 = 90; // Front Right Pivot Servo
  int s42 = 90; // Front Right Lift Servo
}

//== Increase Speed ========================================================================

void increase_speed()
{
  if (spd > 3)
    spd--;
}

//== Decrease Speed ========================================================================

void decrease_speed()
{
  if (spd < 50)
    spd++;
}

//== Srv ===================================================================================

void srv( int  p11, int p21, int p31, int p41, int p12, int p22, int p32, int p42, int sp1, int sp2, int sp3, int sp4)
{

  // p11: Front Left Pivot Servo
  // p21: Back Left Pivot Servo
  // p31: Back Right Pivot Servo
  // p41: Front Right Pivot Servo
  // p12: Front Left Lift Servo
  // p22: Back Left Lift Servo
  // p32: Back Right Lift Servo
  // p42: Front Right Lift Servo
  // sp1: Speed 1
  // sp2: Speed 2
  // sp3: Speed 3
  // sp4: Speed 4

  // Multiply lift servo positions by manual height adjustment
  p12 = p12 + high * 3;
  p22 = p22 + high * 3;
  p32 = p32 + high * 3;
  p42 = p42 + high * 3;

  while ((s11 != p11) || (s21 != p21) || (s31 != p31) || (s41 != p41) || (s12 != p12) || (s22 != p22) || (s32 != p32) || (s42 != p42))
  {

    // Front Left Pivot Servo
    if (s11 < p11)            // if servo position is less than programmed position
    {
      if ((s11 + sp1) <= p11)
        s11 = s11 + sp1;      // set servo position equal to servo position plus speed constant
      else
        s11 = p11;
    }

    if (s11 > p11)            // if servo position is greater than programmed position
    {
      if ((s11 - sp1) >= p11)
        s11 = s11 - sp1;      // set servo position equal to servo position minus speed constant
      else
        s11 = p11;
    }

    // Back Left Pivot Servo
    if (s21 < p21)
    {
      if ((s21 + sp2) <= p21)
        s21 = s21 + sp2;
      else
        s21 = p21;
    }

    if (s21 > p21)
    {
      if ((s21 - sp2) >= p21)
        s21 = s21 - sp2;
      else
        s21 = p21;
    }

    // Back Right Pivot Servo
    if (s31 < p31)
    {
      if ((s31 + sp3) <= p31)
        s31 = s31 + sp3;
      else
        s31 = p31;
    }

    if (s31 > p31)
    {
      if ((s31 - sp3) >= p31)
        s31 = s31 - sp3;
      else
        s31 = p31;
    }

    // Front Right Pivot Servo
    if (s41 < p41)
    {
      if ((s41 + sp4) <= p41)
        s41 = s41 + sp4;
      else
        s41 = p41;
    }

    if (s41 > p41)
    {
      if ((s41 - sp4) >= p41)
        s41 = s41 - sp4;
      else
        s41 = p41;
    }

    // Front Left Lift Servo
    if (s12 < p12)
    {
      if ((s12 + sp1) <= p12)
        s12 = s12 + sp1;
      else
        s12 = p12;
    }

    if (s12 > p12)
    {
      if ((s12 - sp1) >= p12)
        s12 = s12 - sp1;
      else
        s12 = p12;
    }

    // Back Left Lift Servo
    if (s22 < p22)
    {
      if ((s22 + sp2) <= p22)
        s22 = s22 + sp2;
      else
        s22 = p22;
    }

    if (s22 > p22)
    {
      if ((s22 - sp2) >= p22)
        s22 = s22 - sp2;
      else
        s22 = p22;
    }

    // Back Right Lift Servo
    if (s32 < p32)
    {
      if ((s32 + sp3) <= p32)
        s32 = s32 + sp3;
      else
        s32 = p32;
    }

    if (s32 > p32)
    {
      if ((s32 - sp3) >= p32)
        s32 = s32 - sp3;
      else
        s32 = p32;
    }

    // Front Right Lift Servo
    if (s42 < p42)
    {
      if ((s42 + sp4) <= p42)
        s42 = s42 + sp4;
      else
        s42 = p42;
    }

    if (s42 > p42)
    {
      if ((s42 - sp4) >= p42)
        s42 = s42 - sp4;
      else
        s42 = p42;
    }

    // Write Pivot Servo Values
    myServo1.write(s11 + da);
    myServo3.write(s21 + db);
    myServo5.write(s31 + dc);
    myServo7.write(s41 + dd);

    // Write Lift Servos Values
    myServo2.write(s12);
    myServo4.write(s22);
    myServo6.write(s32);
    myServo8.write(s42);

    delay(spd); // Delay before next movement

  }//while
} //srv

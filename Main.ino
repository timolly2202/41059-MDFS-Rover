#include <Servo.h>
 
// Pin definitions
#define BUTTON_PIN 52
#define LED_PIN 53
 
//Servos
Servo servoLeft;
Servo servoRight;
#define L_SERVO 11
#define R_SERVO 13
 
//Left Forward
#define LENB_PIN 2   // PWM
#define LIN3_PIN 34   // Direction pin 1
#define LIN4_PIN 35   // Direction pin 2
//Encoder
#define L_INTERRUPT 3
#define L_SENSORA 18 // interrupt
#define L_SENSORB 19 // digital pin
byte L_SENSORA_LAST;
int L_duration;
bool L_direction;
 
//Right Forward
#define RENA_PIN 5   // PWM
#define RIN1_PIN 44   // Direction pin 1
#define RIN2_PIN 45   // Direction pin 2
//Encoder
#define R_INTERRUPT 1
#define R_SENSORA 20 // interrupt
#define R_SENSORB 21 // digital pin
byte R_SENSORA_LAST;
int R_duration;
bool R_direction;
 
bool start = false;
 
int max_speed = 165;
int current_speed = 0;
 
// const int WHEEL_DIAMETER = 85; //mm
const int WHEEL_CIRCUMFERENCE = 267; //mm (approx, it is 267.035 mm more exactly)
const int CPM_PER_REVOLUTION = 700;
 
void setup() {
  Serial.begin(57600);//Initialize the serial port
 
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
 
  pinMode(LENB_PIN, OUTPUT);
  pinMode(LIN3_PIN, OUTPUT);
  pinMode(LIN4_PIN, OUTPUT);
 
  pinMode(RENA_PIN, OUTPUT);
  pinMode(RIN1_PIN, OUTPUT);
  pinMode(RIN2_PIN, OUTPUT);
 
  //left forward
  digitalWrite(LIN3_PIN, LOW);
  digitalWrite(LIN4_PIN, HIGH);
 
  //right forward
  digitalWrite(RIN1_PIN, HIGH);
  digitalWrite(RIN2_PIN, LOW);
 
  //Encoders
  L_direction = true; //default -> Forward
  pinMode(L_SENSORB, INPUT);
  attachInterrupt(digitalPinToInterrupt(L_SENSORA),leftWheelSpeed,CHANGE);
 
  R_direction = true;
  pinMode(R_SENSORB, INPUT);
  attachInterrupt(digitalPinToInterrupt(R_SENSORA),rightWheelSpeed,CHANGE);
 
  // Attach servos
  servoLeft.attach(L_SERVO);
  servoRight.attach(R_SERVO);
 
  servoLeft.write(0);
  servoRight.write(180);
}
 
void loop() {
  // Serial.println(digitalRead(BUTTON_PIN));
  if (digitalRead(BUTTON_PIN) == 0){
    start = true;
 
    while(digitalRead(BUTTON_PIN) == 0);
  }
 
  if (start) {
    digitalWrite(LED_PIN, HIGH);
 
    current_speed = 75;
 
    // travelSteps(700,current_speed);
    // distanceTravel(350,current_speed); // travel 350 mm to the balls
    delay(100);
    // resetArm();
    collectPayload();
 
    digitalWrite(LED_PIN, LOW);
    start = false;
  }
 
  delay(10);
}
 
void leftWheelSpeed()
{
  int Lstate = digitalRead(L_SENSORA);
  if((L_SENSORA_LAST == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(L_SENSORB);
    if(val == LOW && L_direction)
    {
      L_direction = false; //Reverse
    }
    else if(val == HIGH && !L_direction)
    {
      L_direction = true;  //Forward
    }
  }
  L_SENSORA_LAST = Lstate;
 
  if(!L_direction)  L_duration  ;
  else  L_duration--;
}
 
void rightWheelSpeed()
{
  int Lstate = digitalRead(R_SENSORA);
  if((R_SENSORA_LAST == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(R_SENSORB);
    if(val == LOW && R_direction)
    {
      R_direction = false; //Reverse
    }
    else if(val == HIGH && !R_direction)
    {
      R_direction = true;  //Forward
    }
  }
  R_SENSORA_LAST = Lstate;
 
  if(!R_direction)  R_duration  ;
  else  R_duration--;
}
 
void printSpeed(){
  Serial.print("Pulse Left:");
  Serial.println(L_duration);
  // L_duration = 0;
 
  Serial.print("Pulse Right:");
  Serial.println(R_duration);
  // R_duration = 0;
}
 
void resetDuration()
{
  L_duration = 0;
  R_duration = 0;
}
 
int speedUp(int maxSpeed)
{
  for (int speed = 0; speed <= maxSpeed; speed++) {
      analogWrite(LENB_PIN, speed);
      analogWrite(RENA_PIN, speed);
      printSpeed();
      delay(10);
    }
}
 
void slowDown(int maxSpeed)
{
  for (int speed = maxSpeed; speed >= 0; speed--) {
      analogWrite(LENB_PIN, speed);
      analogWrite(RENA_PIN, speed);
      printSpeed();
      delay(20);
    }
}
 
// 700 steps per revolution
void travelSteps (int steps, int maxSpeed)
{
  resetDuration();
  delay(10);
  speedUp(maxSpeed);
 
  do {
    delay(10);
    printSpeed();
  }while (abs(R_duration) < steps);
 
  slowDown(maxSpeed);
  resetDuration();
  delay(10);
  // analogWrite(LENB_PIN, 0);
  // analogWrite(RENA_PIN, 0);
}
 
void distanceTravel(int distance, int maxSpeed)
{
  // WHEEL_CIRCUMFERENCE = 267; //mm (approx, it is 267.035 mm more exactly)
  // CPM_PER_REVOLUTION = 700;
  float revolutions = distance/WHEEL_CIRCUMFERENCE;
  int steps = int(trunc(revolutions*CPM_PER_REVOLUTION));
  travelSteps(steps,maxSpeed);
}
 
void collectPayload()
{
  int delayTime = 25;
  int maxAngle = 175;
  for (int angle = 0; angle <= 160; angle++) {
    servoLeft.write(angle);
    servoRight.write(180 - angle);
    delay(delayTime);
  }
 
  servoLeft.write(maxAngle);
  servoRight.write(180 - maxAngle);
  delay(200);
 
  // Sweep: Left 180→0, Right 0→180
  // Serial.println("--- Sweeping to 0° ---");
  for (int angle = maxAngle; angle >= 0; angle--) {
    servoLeft.write(angle);
    servoRight.write(180 - angle);
    delay(delayTime);
  }
}
 
void resetArm()
{
 
}
 
 

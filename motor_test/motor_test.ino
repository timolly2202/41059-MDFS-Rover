// Pin definitions
#define BUTTON_PIN 52
#define LED_PIN 53

bool start = false;

//Left Back
// #define LENA_PIN 3   // PWM
// #define LIN1_PIN 36   // Direction pin 1
// #define LIN2_PIN 37   // Direction pin 2

//Left Forward
#define LENB_PIN 2   // PWM
#define LIN3_PIN 34   // Direction pin 1
#define LIN4_PIN 35   // Direction pin 2
//Encoder
#define L_SENSORA 18 // interrupt
#define L_SENSORB 19 // interrupt

//Right Forward
#define RENA_PIN 5   // PWM
#define RIN1_PIN 44   // Direction pin 1
#define RIN2_PIN 45   // Direction pin 2
//Encoder
#define L_SENSORA 20 // interrupt
#define L_SENSORB 21 // interrupt

//Right Back
// #define RENB_PIN 4   // PWM
// #define RIN3_PIN 46   // Direction pin 1
// #define RIN4_PIN 47   // Direction pin 2

int max_speed = 165;
int time_in_motion = 2350;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  // Serial.begin(9600);

  // pinMode(LENA_PIN, OUTPUT);
  // pinMode(LIN1_PIN, OUTPUT);
  // pinMode(LIN2_PIN, OUTPUT);

  pinMode(LENB_PIN, OUTPUT);
  pinMode(LIN3_PIN, OUTPUT);
  pinMode(LIN4_PIN, OUTPUT);
  
  pinMode(RENA_PIN, OUTPUT);
  pinMode(RIN1_PIN, OUTPUT);
  pinMode(RIN2_PIN, OUTPUT);

  // pinMode(RENB_PIN, OUTPUT);
  // pinMode(RIN3_PIN, OUTPUT);
  // pinMode(RIN4_PIN, OUTPUT);

  // Set direction: forward
  //left back
  // digitalWrite(LIN1_PIN, HIGH);
  // digitalWrite(LIN2_PIN, HIGH);

  //left forward
  digitalWrite(LIN3_PIN, LOW);
  digitalWrite(LIN4_PIN, HIGH);

  //right forward
  digitalWrite(RIN1_PIN, HIGH);
  digitalWrite(RIN2_PIN, LOW);

  // digitalWrite(RIN3_PIN, HIGH);
  // digitalWrite(RIN4_PIN, HIGH);
}

void loop() {
  // Serial.println(digitalRead(BUTTON_PIN));
  if (digitalRead(BUTTON_PIN) == 0){
    start = true;

    while(digitalRead(BUTTON_PIN) == 0);
  }

  if (start) {
    digitalWrite(LED_PIN, HIGH);

    //starting seesaw
    for (int speed = 0; speed <= max_speed; speed++) {
      // analogWrite(LENA_PIN, speed);
      analogWrite(LENB_PIN, speed);
      analogWrite(RENA_PIN, speed);
      // analogWrite(RENB_PIN, speed);
      delay(20);
    }

    delay(time_in_motion);

    for (int speed = max_speed; speed >= 0; speed--) {
      // analogWrite(LENA_PIN, speed);
      analogWrite(LENB_PIN, speed);
      analogWrite(RENA_PIN, speed);
      // analogWrite(RENB_PIN, speed);
      delay(20);
    }

    // delay(1000);

    // for (int speed = 0; speed <= 40; speed++) {
    //   analogWrite(LENA_PIN, speed);
    //   analogWrite(LENB_PIN, speed);
    //   analogWrite(RENA_PIN, speed);
    //   analogWrite(RENB_PIN, speed);
    //   delay(20);
    // }

    // delay(1000);

    // for (int speed = 40; speed >= 0; speed--) {
    //   analogWrite(LENA_PIN, speed);
    //   analogWrite(LENB_PIN, speed);
    //   analogWrite(RENA_PIN, speed);
    //   analogWrite(RENB_PIN, speed);
    //   delay(20);
    // }

    // //Reverse the direction
    // //left forward
    // digitalWrite(LIN3_PIN, HIGH);
    // digitalWrite(LIN4_PIN, LOW);

    // //right forward
    // digitalWrite(RIN1_PIN, HIGH);
    // digitalWrite(RIN2_PIN, LOW);

    // for (int speed = 0; speed <= max_speed; speed++) {
    //   analogWrite(LENA_PIN, speed);
    //   analogWrite(LENB_PIN, speed);
    //   analogWrite(RENA_PIN, speed);
    //   analogWrite(RENB_PIN, speed);
    //   delay(20);
    // }

    // delay(1000);

    // for (int speed = max_speed; speed >= 0; speed--) {
    //   analogWrite(LENA_PIN, speed);
    //   analogWrite(LENB_PIN, speed);
    //   analogWrite(RENA_PIN, speed);
    //   analogWrite(RENB_PIN, speed);
    //   delay(20);
    // }

    // 

    // //Turn Left
    // //left forward
    // digitalWrite(LIN3_PIN, LOW);
    // digitalWrite(LIN4_PIN, HIGH);

    // //right forward
    // digitalWrite(RIN1_PIN, HIGH);
    // digitalWrite(RIN2_PIN, LOW);

    // for (int speed = 0; speed <= max_speed; speed++) {
    //   analogWrite(LENA_PIN, speed);
    //   analogWrite(LENB_PIN, speed);
    //   analogWrite(RENA_PIN, speed);
    //   analogWrite(RENB_PIN, speed);
    //   delay(20);
    // }

    // delay(1000);

    // for (int speed = max_speed; speed >= 0; speed--) {
    //   analogWrite(LENA_PIN, speed);
    //   analogWrite(LENB_PIN, speed);
    //   analogWrite(RENA_PIN, speed);
    //   analogWrite(RENB_PIN, speed);
    //   delay(20);
    // }

    digitalWrite(LED_PIN, LOW);
    start = false;

    // delay(1000); // Pause before repeating
  }
  delay(10);
}
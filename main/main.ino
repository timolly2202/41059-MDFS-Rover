// Pin definitions
#define BUTTON_PIN 52
#define LED_PIN 53

bool start = false;

//Left Forward
#define LENB_PIN 2   // PWM
#define LIN3_PIN 34   // Direction pin 1
#define LIN4_PIN 35   // Direction pin 2
//Encoder
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
#define R_SENSORA 20 // interrupt
#define R_SENSORB 21 // digital pin
byte R_SENSORA_LAST;
int R_duration;
bool R_direction;

int max_speed = 165;

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

}

void loop() {
  // Serial.println(digitalRead(BUTTON_PIN));
  if (digitalRead(BUTTON_PIN) == 0){
    start = true;

    while(digitalRead(BUTTON_PIN) == 0);
  }

  if (start) {
    digitalWrite(LED_PIN, HIGH);

    for (int speed = 0; speed <= max_speed; speed++) {
      analogWrite(LENB_PIN, speed);
      analogWrite(RENA_PIN, speed);
      printSpeed();
      delay(20);
    }

    delay(1000);

    for (int speed = max_speed; speed >= 0; speed--) {
      analogWrite(LENB_PIN, speed);
      analogWrite(RENA_PIN, speed);
      printSpeed();
      delay(20);
    }

    digitalWrite(LED_PIN, LOW);
    start = false;
    printSpeed();
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
  L_duration = 0;

  Serial.print("Pulse Right:");
  Serial.println(R_duration);
  R_duration = 0;
}
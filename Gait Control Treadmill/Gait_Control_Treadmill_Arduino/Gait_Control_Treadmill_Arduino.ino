#define NUM_SENSOR    3
#define TrigPin       9
#define FREQ          5000
#define PRESCALE      64
struct table{
  //const int trigPin;
  int echoPin;
  float cur_dist;
  float prev_dist[10];
  int i1, i2;  
};
typedef struct table sensor;

sensor sensors[NUM_SENSOR];

void PWM_Init(){
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  // FAST PWM mode with TOP(OCR0A)
  
  TCCR2A |= (1<<WGM21) | (1<<WGM20) | (1<<COM2B1) | (1<<COM2A0); 
  TCCR2B |= (1<<CS22) | (1<<WGM22); 
   
  OCR2A = 49; // 5KHz
  OCR2B = 24; //
}

void PWM_Increase_duty_8(){
  uint8_t period = OCR0A;
  uint8_t duty = OCR0B;

  if (duty < period) duty++;
  else duty = 0;

  OCR0B = duty;
}
void PWM_Decrease_duty_8(){
  uint8_t duty = OCR0B;

  if (duty > 0) duty--;
  else duty = 0;

  OCR0B = duty;
}

void setup() {
  int i;
  noInterrupts();
  pinMode(9, OUTPUT); // Sets the trigPin as an Output
  for (i = 0; i < NUM_SENSOR; i++){
    //sensors[i].trigPin = 9;
    sensors[i].echoPin = 10;
    sensors[i].i1 = -1;
    sensors[i].i2 = 0;
    pinMode(sensors[i].echoPin, INPUT); // Sets the echoPin as an Input
  }
  PWM_Init();
  Serial.begin(9600); // Starts the serial communication
}


void loop() {
  //digitalWrite(3, OC0A);
  int i;
  // Clears the TrigPin
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  
  for (i = 0; i < NUM_SENSOR; i++){
    // Reads the echoPin, returns the sound wave travel time in microseconds
    sensors[i].cur_dist = pulseIn(sensors[i].echoPin, HIGH) * 0.034 / 2;
  }

}

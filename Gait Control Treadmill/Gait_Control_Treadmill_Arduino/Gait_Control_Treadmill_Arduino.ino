#define NUM_SENSOR    3
#define FREQ          5000
#define PRESCALE      64
#define ABNORMAL      10
#define CENTER        50.0

struct table{
  int trigPin;
  int echoPin;
  float test_model;
  float prev_diff;
  float prev_dist[10];
  int next; 
  int count; 
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
  uint8_t period = OCR2A;
  uint8_t duty = OCR2B;

  if (duty < period) duty++;
  else duty = period;

  OCR2B = duty;
}
void PWM_Decrease_duty_8(){
  uint8_t duty = OCR2B;

  if (duty > 1) duty--;
  else duty = 1;

  OCR2B = duty;
}

float sensor_interp(int idx, float test_model){
  float perc_err; 
  int count = 0;
  float valid = 0; 
    
  for(int i = 0; i < 10; i++){
    float cur_val = sensors[idx].prev_dist[i];
    perc_err = cur_val - test_model;
    if (perc_err < 20.0f){ 
      count++; 
      valid += cur_val;
    }
  }
  return valid/count; 
}

float sensors_interp(){
  float sum = 0.0;
  for (int i = 0; i < NUM_SENSOR; i++){
    if (i == 2) sensors[i].test_model = sensor_interp(i, sensors[i].test_model);  
  }
  //return sum / 3.0;
  return sensors[2].test_model;
}

float eliminate(int idx){
  int cur = sensors[idx].next;
  if (cur == 0){
    if ()  
  }  
}

void setup() {
  sensors[0].trigPin = 9;
  sensors[0].echoPin = 4;

  sensors[1].trigPin = 10;
  sensors[1].echoPin = 5;
  
  sensors[2].trigPin = 12;
  sensors[2].echoPin = 6;
  
  for (int i = 0; i < NUM_SENSOR; i++){
    sensors[i].next = 0;
    sensors[i].test_model = CENTER;
    pinMode(sensors[i].echoPin, INPUT);  // Sets the echoPin as an Input
    pinMode(sensors[i].trigPin, OUTPUT); // Sets the trigPin as an Output
    for (int j = 0; j < 10; j++) sensors[i].prev_dist[j] = 0.0;
  }
  PWM_Init();
  Serial.begin(9600); // Starts the serial communication
}




void loop() {
  //PWM_Increase_duty_8();

  for (int i = 0; i < NUM_SENSOR; i++){
     if (i == 0){
      // Clears the TrigPin
      digitalWrite(sensors[i].trigPin, LOW);
      delayMicroseconds(2);
      
      // Sets the trigPin on HIGH state for at least 10 micro seconds
      digitalWrite(sensors[i].trigPin, HIGH);
      delayMicroseconds(12);
      digitalWrite(sensors[i].trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      sensors[i].prev_dist[sensors[i].next] = pulseIn(sensors[i].echoPin, HIGH) * 0.034 / 2;
      sensors[i].prev_diff = sensors[i].prev_dist[sensors[i].next] - CENTER;
      
      Serial.print("Distance: ");
      Serial.println(sensors[i].prev_dist[sensors[i].next]);
      sensors[i].next = (sensors[i].next + 1) % 10;
     }
  }
  //if (sensors[0].prev_diff > 10.0f && sensors[1].prev_diff > 10.0f && sensors[2].prev_diff > 10.0f) PWM_Increase_duty_8();
  //else if (sensors[0].prev_diff < -10.0f && sensors[1].prev_diff < -10.0f && sensors[2].prev_diff < -10.0f) PWM_Increase_duty_8();
  //if (sensors[0].prev_diff > 10.0f) PWM_Increase_duty_8();
  //else if (sensors[0].prev_diff < -10.0f) PWM_Decrease_duty_8();
}

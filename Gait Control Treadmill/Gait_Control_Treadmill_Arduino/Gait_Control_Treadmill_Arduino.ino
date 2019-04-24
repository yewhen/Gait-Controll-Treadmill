#define NUM_SENSOR    3
#define TrigPin       9
#define FREQ          5000
#define F_CPU         16000000
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
  // FAST PWM mode with TOP(OCR0A)
  
  TCCR0A |= (1<<WGM01) | (1<<WGM00) | (1<<COM0A0); 
  TCCR0B |= (1<<CS01) | (1<<CS00) | (1<<WGM02); 
  TCCR0B &= ~(1<<CS02);
  //TIMSK0 |= (1<<OCIE0A) | (1<<OCIE0B);
   
  OCR0A = F_CPU / PRESCALE / 50 / 2; // 5KHz
  //OCR0B = (F_CPU / PRESCALE / FREQ) * 0.5 - 1; 
}


/*ISR(TIMER0_COMPB_vect){
  digitalWrite(3, LOW);
}

ISR(TIMER0_COMPA_vect){
  digitalWrite(3, HIGH);
  
}*/

void setup() {
  int i;
  pinMode(9, OUTPUT); // Sets the trigPin as an Output
  for (i = 0; i < NUM_SENSOR; i++){
    //sensors[i].trigPin = 9;
    sensors[i].echoPin = 10;
    sensors[i].i1 = -1;
    sensors[i].i2 = 0;
    pinMode(sensors[i].echoPin, INPUT); // Sets the echoPin as an Input
  }
  //noInterrupts(); //disable all interupts
  PWM_Init();
  
  //interrupts(); //re-enable all interrupts
  Serial.begin(9600); // Starts the serial communication
}


void loop() {
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
  

  

  /*
  //if statement is here to fill up first 10 data values before doing the processing
  if(count > 10){
  //DATA PROCESSING ALGORITHM: don't forget to push array values as stacks
  // in addition, this section 
  }
  else
  count++;
  
  //DATA INTERPOLATION TO SPEED
  
  //Next up is the controls algorithm
  
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance1 distance2 distance3);*/
}

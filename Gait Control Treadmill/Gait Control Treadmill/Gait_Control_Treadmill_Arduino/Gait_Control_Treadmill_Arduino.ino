#define NUM_SENSOR    3

struct table{
  const int trigPin;
  const int echoPin;
  float cur_dist;
  float prev_dist[10];
  int i1, i2;  
};
typedef struct table sensor;

static sensor sensors[NUM_SENSOR];

// defines variables
long duration[2];
int distance[3][10];
long duty;
int count;

void setup() {
  int i;
  pinMode(9, OUTPUT); // Sets the trigPin as an Output
  for (i = 0; i < NUM_SENSOR; i++){
    sensors[i].trigPin = 9;
    sensors[i].echoPin = 10;
    sensors[i].i1 = -1;
    sensors[i].i2 = 0;
    pinMode(sensors[i].echoPin, INPUT); // Sets the echoPin as an Input
  }
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1*0.034/2;
  
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*0.034/2;
  
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3*0.034/2;
  
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
  Serial.println(distance1 distance2 distance3);
}

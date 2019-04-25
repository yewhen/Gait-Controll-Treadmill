#include <I2C.h>
#define NUM_SENSOR    2
#define FREQ          5000
#define PRESCALE      64
#define SIZE          10
#define CENTER        500

struct table{
  uint16_t prev_dist[SIZE];
  int next;  
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

  /*pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  // FAST PWM mode with TOP(OCR0A)
  TCCR0A = 0;
  TCCR0B = 0;
  
  TCCR0A |= (1<<WGM01) | (1<<WGM00) | (1<<COM0B1) | (1<<COM0A0); 
  TCCR0B |= (1<<CS01) | (1<<CS00) | (1<<WGM02); 
   
  OCR0A = 49; // 5KHz
  OCR0B = 24; //
  */
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

uint16_t eliminate(int idx){
  int cur = sensors[idx].next;
  if (cur == 0){
    if (sensors[idx].prev_dist[SIZE-1] == 0) return sensors[idx].prev_dist[cur];
    else if (abs(sensors[idx].prev_dist[SIZE-1] - sensors[idx].prev_dist[cur]) > 100) return sensors[idx].prev_dist[SIZE-1];
    else return sensors[idx].prev_dist[cur]; 
  }  
  else{
    if (abs(sensors[idx].prev_dist[cur-1] - sensors[idx].prev_dist[cur]) > 100) return sensors[idx].prev_dist[cur-1];
    else return sensors[idx].prev_dist[cur];    
  }
  return 0;
}

void setup() {
  for (int i = 0; i < NUM_SENSOR; i++){
    sensors[i].next = 0;
    for (int j = 0; j < 10; j++) sensors[i].prev_dist[j] = 0;
  }
  PWM_Init();
  Serial.begin(115200); //setup the serial port
  I2c.begin();
}
void loop(){
  uint16_t i;  
  //Lidar 1
  i = 0;
  I2c.write(0x10,'D'); //take single measurement
  I2c.read(0x10,2); // request 2 bytes from tinyLiDAR
  i = I2c.receive(); // receive MSB byte
  i = i<<8 | I2c.receive(); // receive LSB byte and put them together
  Serial.print("0x10: ");
  Serial.println(i); // print distance in mm
  sensors[0].prev_dist[sensors[0].next] = i; 
  
  //Lidar 2
  /*i = 0;
  I2c.write(0x21,'D'); //take single measurement
  I2c.read(0x21,2); // request 2 bytes from tinyLiDAR
  i = I2c.receive(); // receive MSB byte
  i = i<<8 | I2c.receive(); // receive LSB byte and put them together
  Serial.print("0x21: ");
  Serial.println(i); // print distance in mm
  sensors[1].prev_dist[sensors[1].next] = i; */
  
  //if (abs(sensors[0].prev_dist[sensors[0].next] - sensors[1].prev_dist[sensors[1].next]) < 100){
    uint16_t average = sensors[0].prev_dist[sensors[0].next]/* + sensors[1].prev_dist[sensors[1].next]) / 2*/;
    
    if (average > CENTER){
      if (average - CENTER > 50) PWM_Decrease_duty_8();
    }
    else if (average < CENTER){
      if (CENTER - average > 50) PWM_Increase_duty_8();    
    }
    //else PWM_Decrease_duty_8();
  //}
  sensors[0].next = (sensors[0].next + 1) % SIZE;
  //sensors[1].next = (sensors[1].next + 1) % SIZE;  

  delay(100); // delay as required (30ms or higher in default single step mode)
}

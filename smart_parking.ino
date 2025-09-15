// Pin Definitions
const int led1 = 4;   // green LED(parking space free)
const int led2 = 5;  // red LED(parking space occupied)
const int echopin = 2; //Set echopin to read input from sensor 
const int trigpin = 3; //to send output pulse for sensor  
const int buzzerpin = 6;   // Buzzer pin
const int Threshold= 30;  //30cm threshold
long Duration; // long contains 4 bytes of memory (32-bit)
int Distance; // int contains 2 bytes of memory(16-bit)

void setup() // it runs once when the program starts
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  Serial.begin(9600);
  Serial.println("starts the ultrasonic sensor detection....");
}

void loop() 
{
  // Send ultrasonic pulse
  digitalWrite(trigpin, HIGH);//ON trigpin to send pulse
  delayMicroseconds(10);      // wait for 0.00001 seconds
  digitalWrite(trigpin, LOW); //OFF trigpin to finish pulse

  // Read echo time
  Duration = pulseIn(echopin, HIGH);// waits for the pin to go the specific value and duration is calculated in microseconds 

  // Calculate distance (in cm)
  Distance = Duration * 0.034 / 2; // Sound of speed 3.4 m/s (0.034 cm per microsecond)
  Serial.print("Distance: ");
  Serial.print(Distance);
  Serial.println(" cm");

  // Parking logic: adjust thresholds as needed and it represents the minimum distance in cm
  if(Distance < Threshold) 
  {
    tone(buzzerpin, 2000); // tone is for generating a sound in 2000 Hz
    digitalWrite(led2, HIGH);
    delay(400);           // 0.0004 seconds
    noTone(buzzerpin);   // stop the buzzer
    delay(300);         //0.0003 seconds
    digitalWrite(led2, LOW);
  }
  
  else 
  {
    digitalWrite(led1, HIGH);
    delay(400); //0.0004 seconds
    digitalWrite(led1, LOW);
  }
}

  
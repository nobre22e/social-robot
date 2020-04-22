int g_led = 13;
int y_led = 12;
int r_led = 11;

int good = 7;
int meh = 6;
int bad = 5;

//int photocell = A0;
//
//int rangeTriggerPin = 2;
//int rangeEchoPin = 3;

int g_light = LOW;
int y_light = LOW;
int r_light = LOW;

int g_press;
//int g_press_l = LOW;
int m_press;
int b_press;

//long currentDistance; // (cm)

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(g_led, OUTPUT);
  pinMode(y_led, OUTPUT);
  pinMode(r_led, OUTPUT);
  
  pinMode(good, INPUT);
  pinMode(meh, INPUT);
  pinMode(bad, INPUT);
  
//  pinMode(photocell, INPUT);
//  
//  pinMode(rangeTriggerPin, OUTPUT);
//  pinMode(rangeEchoPin, INPUT);
}

void loop() {
  // read in the light value and current distance to set up gate
//  int lightvalue = analogRead(photocell);
//  currentDistance = senseCurrentDistance();
  
//  Serial.println( currentDistance );
//  Serial.println( lightvalue );
//  if(lightvalue > 75 && currentDistance < 15){
//    
//    if(light_value == LOW){
//      button_pressed = digitalRead(button_on);
//      if(button_pressed == HIGH){
//        light_value = HIGH;
//      }
//    } else if(light_value = HIGH){
//      button_pressed = digitalRead(button_off);
//      if(button_pressed == HIGH){
//        light_value = LOW;
//      }
//    }
//  }
  //Serial.println(button_pressed);
  digitalWrite(g_led, g_light);
  digitalWrite(y_led, y_light);  
  digitalWrite(r_led, r_light);
  //delay( 500 );
}

/**
 * Use the range finder to determine distance to the 
 * closest object. 
 **/
long senseCurrentDistance() 
{
  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(rangeTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rangeTriggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(rangeTriggerPin, LOW);

  // A different pin is used to read the signal from the PING: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  long duration = pulseIn(rangeEchoPin, HIGH);
  
  return microsecondsToCentimeters( duration );
}

/** 
 * Determine the distance based on how long it took to echo back.
 **/
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

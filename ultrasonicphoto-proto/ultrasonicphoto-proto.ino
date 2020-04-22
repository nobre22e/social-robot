int g_led = 13;
int y_led = 12;
int r_led = 11;
int indicator = 9;

int good = 7;
int meh = 6;
int bad = 5;

int g_light = LOW;
int y_light = LOW;
int r_light = LOW;

int g_press;
int lastg_press = LOW;
int m_press;
int lastm_press = LOW;
int b_press;
int lastb_press = LOW;

int photocell = A0;

int rangeTriggerPin = 2;
int rangeEchoPin = 3;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long lastLEDchange = 0;
unsigned long LEDoffDelay = 15000; // turn off the LEDs after 15 sec

long currentDistance; // (cm)

void setup() {
  Serial.begin(9600);
  pinMode(g_led, OUTPUT);
  pinMode(y_led, OUTPUT);
  pinMode(r_led, OUTPUT);
  pinMode(indicator, OUTPUT);
  
  pinMode(good, INPUT);
  pinMode(meh, INPUT);
  pinMode(bad, INPUT);
  
  pinMode(photocell, INPUT);
  
  pinMode(rangeTriggerPin, OUTPUT);
  pinMode(rangeEchoPin, INPUT);

  
  digitalWrite(g_led, g_light);
  digitalWrite(y_led, y_light);
  digitalWrite(r_led, r_light);
  digitalWrite(indicator, LOW);
  
}

void loop() {
  int lightvalue = analogRead(photocell);
  currentDistance = senseCurrentDistance();
//  Serial.println( currentDistance );
//  Serial.println( lightvalue );
  
  if(lightvalue > 75 && currentDistance < 15){
    digitalWrite(indicator, HIGH);
    debouncedButtons();
  } else{
    digitalWrite(indicator, LOW);
  }
  
  if(millis()-lastLEDchange > LEDoffDelay){
    g_light = LOW;
    y_light = LOW;
    r_light = LOW;
  }

  digitalWrite(g_led, g_light);
  digitalWrite(y_led, y_light);
  digitalWrite(r_led, r_light);
}

void debouncedButtons(){  
  int g_reading = digitalRead(good);
  int m_reading = digitalRead(meh);
  int b_reading = digitalRead(bad);

  if(g_reading != lastg_press || m_reading != lastm_press || b_reading != lastb_press){
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay){
    if(g_reading != g_press){
      g_press = g_reading;

      if(g_press == HIGH){
        g_light = HIGH;
        if(g_light == HIGH && (y_light == HIGH || r_light == HIGH)){
          y_light = LOW;
          r_light = LOW;
        }
        goodBlink();
      }
    }
    if(m_reading != m_press){
      m_press = m_reading;

      if(m_press == HIGH){
        y_light = HIGH;
        if(y_light == HIGH && (g_light == HIGH || r_light == HIGH)){
          g_light = LOW;
          r_light = LOW;
        }
        mehBlink();
      }
    }
    if(b_reading != b_press){
      b_press = b_reading;

      if(b_press == HIGH){
        r_light = HIGH;
        if(r_light == HIGH && (g_light == HIGH || y_light == HIGH)){
          g_light = LOW;
          y_light = LOW;
        }
        badBlink();
      }
    }
  }

  lastg_press = g_reading;
  lastm_press = m_reading;
  lastb_press = b_reading;
}

void goodBlink(){
  digitalWrite(g_led, LOW);
  digitalWrite(y_led, LOW);
  digitalWrite(r_led, LOW);
  delay(300);
  digitalWrite(g_led, HIGH);
  delay(500);
  digitalWrite(g_led, LOW);
  delay(200);
  digitalWrite(g_led, HIGH);
  delay(200);
  digitalWrite(g_led, LOW);
  delay(200);
  digitalWrite(g_led, HIGH);
  delay(200);
  digitalWrite(g_led, LOW);
  delay(200);
  digitalWrite(g_led, HIGH);
  lastLEDchange = millis();
}

void mehBlink(){
  digitalWrite(g_led, LOW);
  digitalWrite(y_led, LOW);
  digitalWrite(r_led, LOW);
  delay(300);
  digitalWrite(y_led, HIGH);
  delay(500);
  digitalWrite(y_led, LOW);
  delay(500);
  digitalWrite(y_led, HIGH);
  delay(500);
  digitalWrite(y_led, LOW);
  delay(500);
  digitalWrite(y_led, HIGH);
  lastLEDchange = millis();
}

void badBlink(){
  digitalWrite(g_led, LOW);
  digitalWrite(y_led, LOW);
  digitalWrite(r_led, LOW);
  delay(300);
  digitalWrite(r_led, HIGH);
  delay(400);
  digitalWrite(r_led, LOW);
  delay(550);
  digitalWrite(r_led, HIGH);
  delay(600);
  digitalWrite(r_led, LOW);
  delay(750);
  digitalWrite(r_led, HIGH);
  lastLEDchange = millis();
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

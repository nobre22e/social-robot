int g_led = 13;
int y_led = 12;
int r_led = 11;

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
  
  digitalWrite(g_led, g_light);
  digitalWrite(y_led, y_light);
  digitalWrite(r_led, r_light);
  
}

void loop() {
  // put your main code here, to run repeatedly:
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
        g_light = !g_light;
      }
    }
    if(m_reading != m_press){
      m_press = m_reading;

      if(m_press == HIGH){
        y_light = !y_light;
      }
    }
    if(b_reading != b_press){
      b_press = b_reading;

      if(b_press == HIGH){
        r_light = !r_light;
      }
    }
  }

  digitalWrite(g_led, g_light);
  digitalWrite(y_led, y_light);
  digitalWrite(r_led, r_light);

  lastg_press = g_reading;
  lastm_press = m_reading;
  lastb_press = b_reading;
}

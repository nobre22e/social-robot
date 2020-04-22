#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIXEL_PIN    10  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 16  // Number of NeoPixels

#define GOOD 7
#define MEH  6
#define BAD  5

#define PIR 2

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

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
  pinMode(GOOD, INPUT);
  pinMode(MEH, INPUT);
  pinMode(BAD, INPUT);

  pinMode(PIR, INPUT);

  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'

}

void loop() {
  int val = digitalRead(PIR);
  if(val == HIGH) {
    colorWipe(strip.Color(255,   0,   150), 0);
    debouncedButtons();
  } else{
    colorWipe(strip.Color(  0,   0,   0), 0);
  }
}

void debouncedButtons(){  
  int g_reading = digitalRead(GOOD);
  int m_reading = digitalRead(MEH);
  int b_reading = digitalRead(BAD);
  

  if(g_reading != lastg_press || m_reading != lastm_press || b_reading != lastb_press){
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay){
//    Serial.println(g_reading);
//    Serial.println(m_reading);
//    Serial.println(b_reading);
    if(g_reading != g_press){
      g_press = g_reading;

      if(g_press == HIGH){
        colorWipe(strip.Color(  0, 255,   0), 50);    // Green
      }
    }
    if(m_reading != m_press){
      m_press = m_reading;

      if(m_press == HIGH){
        colorWipe(strip.Color(  0,   0, 255), 50);    // Blue
      }
        
    }
    if(b_reading != b_press){
      b_press = b_reading;

      if(b_press == HIGH){
        colorWipe(strip.Color(255,   0,   0), 50);    // Red
      }
    }
  }

  lastg_press = g_reading;
  lastm_press = m_reading;
  lastb_press = b_reading;
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

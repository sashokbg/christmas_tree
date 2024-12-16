/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ws2812b-led-strip
 */

#include <Adafruit_NeoPixel.h>


#define PIN_WS2812B 12
#define NUM_PIXELS 70
#define BAUD_RATE 9600
#define BUTTON1_PIN 5
#define BUTTON2_PIN 4
#define BUTTON3_PIN 3
#define BUTTON4_PIN 2
#define MAX_PROGRAM 4

#define POT_1_PIN A7


Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);


int lastButton1State = LOW;
int lastButton2State = LOW;
int lastButton3State = LOW;
int lastButton4State = LOW;

int red = 128;
int green = 0;
int blue = 0;
long unsigned last_blink = 0;
long unsigned next_blink = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
long blink_delay = 1000;
int brightness = 40;
int last_pot_val = 0;
bool pot_function = true;
int current_program = 0;

void button_1_callback() {
  int reading = digitalRead(BUTTON1_PIN);

  if (reading != lastButton1State) {
    lastButton1State = reading;

    if (reading == HIGH) {
      Serial.println("Butoon 1 pressed");
      current_program += 1;

      if(current_program > MAX_PROGRAM) {
        current_program = 0;
      }
    }

  }
}

void button_2_callback() {
  int reading = digitalRead(BUTTON2_PIN);

  if (reading != lastButton2State) {
    lastButton2State = reading;

    if (reading == HIGH) {
      Serial.println("Butoon 2 pressed");
      current_program -= 1;

      if(current_program  < 0) {
        current_program = MAX_PROGRAM;
      }
    }

  }
}

void button_3_callback() {
  int reading = digitalRead(BUTTON3_PIN);

  if (reading != lastButton3State) {
    lastButton3State = reading;

    if (reading == HIGH) {
      Serial.println("Butoon 3 pressed");
      pot_function = !pot_function;
    }

  }
}

void button_4_callback() {
  int reading = digitalRead(BUTTON4_PIN);

  if (reading != lastButton4State) {
    lastButton4State = reading;

    if (reading == HIGH) {
      Serial.println("Butoon 4 pressed");
    }
  }
}

void pot_1_callback() {
  int pot_val = analogRead(POT_1_PIN);

  if (abs(last_pot_val - pot_val) > 5) {
    last_pot_val = pot_val;

    if (pot_function) {
      if (pot_val > 50) {
        blink_delay = pot_val;
      }
    } 
    else {
      brightness = map(pot_val, 0, 1023, 10, 90);
    }
  }
}

void program_random() {
  for(int i = 0; i < NUM_PIXELS; i++) {
    red = random(0, 256);
    green = random(0, 256);
    blue = random(0, 256);
    
    ws2812b.setPixelColor(i, ws2812b.Color(red, green, blue));
  }
}

int window_start = 0;
int window_end = 10;

void program_serpant() {
  for(int i = window_start; i < window_end; i++) {
    red = random(0, 256);
    green = random(0, 256);
    blue = random(0, 256);
    
    ws2812b.setPixelColor(i, ws2812b.Color(red, green, blue));
  }

  window_start +=1;
  window_end +=1;

  if(window_start > NUM_PIXELS) {
    window_start = 0;
    window_end = 10;
  }
}

void program_red() {
  for(int i = 0; i < NUM_PIXELS; i++) {
    red = random(0, 256);
    green = 0;
    blue = 0;

    ws2812b.setPixelColor(i, ws2812b.Color(red, green, blue));
  }
}

void program_green() {
  for(int i = 0; i < NUM_PIXELS; i++) {
    red = 0;
    green = random(256);
    blue = 0;

    ws2812b.setPixelColor(i, ws2812b.Color(red, green, blue));
  }
}

void program_blue() {
  for(int i = 0; i < NUM_PIXELS; i++) {
    red = 0;
    green = 0;
    blue = random(256);

    ws2812b.setPixelColor(i, ws2812b.Color(red, green, blue));
  }
}

void show_leds() {
  ws2812b.setBrightness(brightness);

  switch(current_program) {
    case 0:
      blink_delay = last_pot_val;
      program_random();
      break;
    case 1:
      blink_delay = 20;
      program_serpant();
      break;
    case 2:
      blink_delay = last_pot_val;
      program_red();
      break;
    case 3:
      blink_delay = last_pot_val;
      program_green();
      break;
    case 4:
      blink_delay = last_pot_val;
      program_blue();
      break;
  }


  ws2812b.show();
  Serial.println("Showing leds");

  last_blink = millis();
  next_blink = last_blink + blink_delay;
}

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Starting");

  pinMode(BUTTON1_PIN, INPUT);

  ws2812b.begin();
}

void loop() {
  ws2812b.clear();
  button_1_callback();
  button_2_callback();
  button_3_callback();
  button_4_callback();


  pot_1_callback();

  unsigned long time = millis();

  if (time > next_blink) {
    show_leds();
  }
  
}
/*
  Lamps controller
  Source code is owned by Piotr Trybała. All rights reserved 2020.
*/


#define out OUTPUT
#define in  INPUT


enum Mode {
  LAMPS,
  TIME, 
  NONE
};

const unsigned int pins[] = {0, 1, 2, 3, 4};
/*
  0 - minus button
  1 - plus button
  2 - ok button
  3 - mode button
  4 - reset button
*/
const unsigned int pins_size = sizeof(pins) / sizeof(unsigned int);

const unsigned int offset = 5;

unsigned int low_bound_time = 1000,
             curr_time = 2000,
             high_bound_time = 10000;

const unsigned int timestamp = 1000;
const unsigned int pinlen = 1;

unsigned int low_bound_pins = 3,
             curr_pins = 4,
             high_bound_pins = 8;

Mode m = Mode::TIME;

void setup() {
  init_out();
  init_in();
}

void loop() {
  
  /*
    0 - minus button
    1 - plus button
    2 - play button
    3 - mode button
    4 - reset button
  */
  int states[5] = {
    digitalRead(pins[0]),
    digitalRead(pins[1]),
    digitalRead(pins[2]),
    digitalRead(pins[3]),
    digitalRead(pins[4])
  };

  if (states[0] == 1) {
    substract();
  }
  if (states[1] == 1) {
    add();
  }
  if (states[2] == 1) {
    sequence();
  }
  if (states[3] == 1) {
    mode();
  }
  if (states[4] == 1) {
    reset();
  }
}

void add() {
    if (m == Mode::TIME) {
     if (curr_time + timestamp <= high_bound_time) {
        curr_time += timestamp;
     } else {
      Serial.print("Nie można zwiększyć czasu!");
     }
  } else if (m == Mode::LAMPS) {
    if (curr_pins + pinlen <= high_bound_pins) {
        curr_pins += pinlen;
     } else {
      Serial.print("Nie można zwiększyć liczby lamp!");
     }
  }
}

void substract() {
  if (m == Mode::TIME) {
     if (curr_time - timestamp >= low_bound_time) {
        curr_time -= timestamp;
     } else {
      Serial.print("Nie można zmiejszyć czasu!");
     }
  } else if (m == Mode::LAMPS) {
    if (curr_pins - pinlen >= low_bound_pins) {
        curr_pins -= pinlen;
     } else {
      Serial.print("Nie można zmiejszyć liczby lamp!");
     }
  }
}

void sequence() {
  
}

void mode() {
  if (m == Mode::TIME) {
    m = Mode::LAMPS;
    Serial.print("Zmieniono tryb wyboru na: [LAMPY]");
  } else {
    m = Mode::TIME;
    Serial.print("Zmieniono tryb wyboru na: [CZAS]");
  }
}

void reset() {
  delay(0); 
  for (unsigned int i = offset; i < offset + curr_pins; i++) {
     digitalWrite(i, LOW);
  }
}

void init_out() {
  for (unsigned int i = offset; i < offset + curr_pins; i++) {
    pinMode(i, out);
  }
}
void init_in() {
  for (unsigned int j = 0; j < pins_size; j++) {
    pinMode(j, in);
  }
}

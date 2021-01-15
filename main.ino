const int in = 2;
const int out = 7;

const int t = 10 * 1000;
const int tm = 1 * 1000;

const int a = 1;

void setup() {
  pinMode(in, INPUT);
  pinMode(out,OUTPUT);
}

void off() {
  digitalWrite(out, LOW);
}

void on() {
  digitalWrite(out, HIGH);
  delay(t - tm);
  for (int i = 1; i <= tm; i++) {
    delay(a);
    if (digitalRead(in) == 1) {
      on();
      break;
    }
  }
  off();
}

void loop() {
  int inputIn = digitalRead(in);
  if (inputIn == 1) {
    on();
  } else {
    off();
  }
}

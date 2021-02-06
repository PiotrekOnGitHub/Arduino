const int[] in = {2, 3};
const int[] out = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

const int in_size = 2;
const int out_size= 10;

void setup() {
  for (int i = 0; i < in_size; i++) {
    pinMode(in[i], INPUT);
  }
  for (int j = 0; j < out_size; j++){
    pinMode(out[j], OUTPUT);
  }
}
int totalTime = 20000;
int threashold = 1000;

int sleepTime = totalTime - (out_size * threashold);

bool blocked = false;
void on() {
  for (int i = 0; i < out_size; i++) {
    digitalWrite(out[i], HIGH);
    delay(threashold);
  }
  delay(sleepTime);
  for (int i = 0; i < out_size; i++) {
    digitalWrite(out[i], LOW);
  }
}

void loop() {
  int s1 = digitalRead(in[0]);
  int s2 = digitalRead(in[0]);
  if (s1 == 1 && !blocked) {
    blocked = true;
    on();
    blocked = false;
  } else if (s2 == 1 && !blocked) {
    blocked = true;
    on();
    blocked = false;
  }
}

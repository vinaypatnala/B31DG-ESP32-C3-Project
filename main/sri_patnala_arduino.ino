#define DEBUG_MODE 
#ifdef DEBUG_MODE
#define FACTOR 1
#else
#define FACTOR 1000
#endif
const int PB1 = 5;
const int PB2 = 6;
const int DATA = 2;
const int SYNC = 10;
const int delay200 = 200 * FACTOR;
const int delay50 = 50 * FACTOR;
const int magic50 = 50 * FACTOR;
bool enable_output = false;
bool select_waveform = false;
int a = 1100 * FACTOR;  // TON(1) in µs
int b = 2600 * FACTOR;  // OFF time in µs
int c = 11;             // Pulses per cycle (unchanged)
int d = 6500 * FACTOR;  // Idle time in µs

void setup() {
  pinMode(PB1, INPUT_PULLDOWN);
  pinMode(PB2, INPUT_PULLDOWN);
  pinMode(DATA, OUTPUT);
  pinMode(SYNC, OUTPUT);

  Serial.begin(115200);
  Serial.println("ESP32-C3 Waveform Generator - PATN");
  Serial.println("Alternative Behaviour Selected: Reverse Pulse Order (Mode 2)");
  Serial.print("Adjusted Timing Values (Factor = ");
  Serial.print(FACTOR);
  Serial.println("):");
  Serial.print("TON(1) = "); Serial.println(a);
  Serial.print("OFF Time = "); Serial.println(b);
  Serial.print("Pulses per Cycle = "); Serial.println(c);
  Serial.print("Idle Time = "); Serial.println(d);
}

void loop() {
  if (digitalRead(PB1) == HIGH) {
    enable_output = !enable_output;
    Serial.print("PB1 Pressed - Output ");
    Serial.println(enable_output ? "Enabled" : "Disabled");
    delay(delay200);
  }
  if (digitalRead(PB2) == HIGH) {
    select_waveform = !select_waveform;
    Serial.print("PB2 Pressed - Mode: ");
    Serial.println(select_waveform ? "Alternative Waveform" : "Normal Waveform");
    delay(delay200);
  }

  if (enable_output) {
    if (select_waveform) {
      alternative_waveform();
    } else {
      normal_waveform();
    }
  } else {
    digitalWrite(DATA, LOW);
    digitalWrite(SYNC, LOW);
    Serial.println("Output Disabled - DATA and SYNC LOW");
  }
}
void normal_waveform() {
  digitalWrite(SYNC, HIGH);
  delayMicroseconds(delay50);
  digitalWrite(SYNC, LOW);
  Serial.println("Generating Normal Waveform...");
  for (int i = 0; i < c; i++) {
    digitalWrite(DATA, HIGH);
    Serial.print("DATA HIGH - Pulse ");
    Serial.println(i + 1);
    delayMicroseconds(a + (i * magic50));

    digitalWrite(DATA, LOW);
    Serial.print("DATA LOW - OFF Time ");
    Serial.println(b);
    delayMicroseconds(b);
  }
  delayMicroseconds(d);

}
void alternative_waveform() {
  Serial.println("Generating Alternative Waveform...");

  digitalWrite(SYNC, HIGH);
  delayMicroseconds(delay50);
  digitalWrite(SYNC, LOW);

  for (int i = 0; i < c; i++) {
    digitalWrite(DATA, HIGH);
    Serial.print("DATA HIGH - Pulse ");
    Serial.println(i + 1);
    delayMicroseconds(a + ((c - i - 1) * magic50));

    digitalWrite(DATA, LOW);
    Serial.print("DATA LOW - OFF Time ");
    Serial.println(b);

    delayMicroseconds(b);
  }
  delayMicroseconds(d);
}



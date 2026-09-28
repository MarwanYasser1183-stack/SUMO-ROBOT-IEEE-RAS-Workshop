const int PIN_ENA = 22; // Speed Control (PWM)
const int PIN_IN1 = 4;  // Direction Control 1
const int PIN_IN2 = 16; // Direction Control 2

void setup() {
  // Configure control pins as outputs
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  // Initial Safe Stop
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 0);
}

void loop() {
  // 1. Forward Rotation at Speed 200 (out of 255)
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 200);
  delay(3000);

  // 2. Dynamic Brake STOP
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 0);
  delay(1000);

  // 3. Reverse Rotation at Speed 200
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_ENA, 200);
  delay(3000);

  // 4. Dynamic Brake STOP
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 0);
  delay(2000);
}
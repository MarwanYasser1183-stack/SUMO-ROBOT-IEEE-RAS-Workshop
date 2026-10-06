
// ---------- PINS ----------
#define ENA 25
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12
#define ENB 13

#define IR_FRONT 34
#define IR_BACK  35

#define TRIG 5
#define ECHO 18

// ---------- SETTINGS ----------
#define WHITE_LINE LOW     // value your IR gives on the white edge line (flip to HIGH if reversed)
#define FULL_SPEED 255     // max speed (0-255)
#define SEARCH_SPEED 120   // slow turn while searching
#define ATTACK_DIST 20     // cm

// ---------- MOTOR FUNCTIONS ----------
void moveForward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ---------- ULTRASONIC ----------
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 20000);  // timeout ~3 m
  if (duration == 0) return 999;               // nothing seen
  return duration * 0.034 / 2;                 // cm
}

// ---------- SETUP ----------
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(IR_FRONT, INPUT);
  pinMode(IR_BACK, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  stopMotor();
  delay(3000);  // sumo rule: wait 3 seconds before starting
}

// ---------- MAIN LOOP ----------
void loop() {
  // 1) Front edge detected -> back up and turn away
  if (digitalRead(IR_FRONT) == WHITE_LINE) {
    moveBackward(FULL_SPEED);
    delay(300);
    turnRight(FULL_SPEED);
    delay(400);
  }
  // 2) Back edge detected -> drive forward
  else if (digitalRead(IR_BACK) == WHITE_LINE) {
    moveForward(FULL_SPEED);
    delay(300);
  }
  // 3) Enemy close -> ATTACK at max speed
  else if (getDistance() < ATTACK_DIST) {
    moveForward(FULL_SPEED);
  }
  // 4) Nothing found -> turn slowly and search
  else {
    turnRight(SEARCH_SPEED);
  }
}

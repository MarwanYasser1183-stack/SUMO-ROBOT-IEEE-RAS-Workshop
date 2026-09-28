#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// L298N Speed Control Pins (PWM)
const int ENA = 22; // Left Motor Speed
const int ENB = 23; // Right Motor Speed

// L298N Direction Control Pins
const int IN1 = 4;  // Left Motor Direction 1
const int IN2 = 16; // Left Motor Direction 2
const int IN3 = 17; // Right Motor Direction 1
const int IN4 = 5;  // Right Motor Direction 2

void setup() {
  Serial.begin(115200);

  // Configure direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configure speed control pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ensure motors are off at start
  stopMotors();

  // Initialize Dabble BLE
  Dabble.begin("ESP32_Robot");
}

void loop() {
  // Process incoming BLE data from Dabble
  Dabble.processInput();

  // Read Joystick Analog values (-7 to 7)
  int xAxis = GamePad.getx_axis(); 
  int yAxis = GamePad.gety_axis(); 

  // =======================================================
  // 1. ANALOG JOYSTICK MODE (Active when joystick is moved)
  // =======================================================
  if (xAxis != 0 || yAxis != 0) {
    // Map joystick distance (1 to 7) to PWM speed (100 to 255)
    int motorSpeed = map(max(abs(xAxis), abs(yAxis)), 1, 7, 100, 255);

    if (yAxis > 1) {
      moveForward(motorSpeed);
      Serial.println("Joystick: Forward");
    } 
    else if (yAxis < -1) {
      moveBackward(motorSpeed);
      Serial.println("Joystick: Backward");
    } 
    else if (xAxis < -1) {
      turnLeft(motorSpeed);
      Serial.println("Joystick: Left");
    } 
    else if (xAxis > 1) {
      turnRight(motorSpeed);
      Serial.println("Joystick: Right");
    }
  }
  // =======================================================
  // 2. DIGITAL D-PAD MODE (Active when arrow buttons pressed)
  // =======================================================
  else if (GamePad.isUpPressed()) {
    moveForward(255); // Full speed
    Serial.println("D-Pad: UP");
  } 
  else if (GamePad.isDownPressed()) {
    moveBackward(255);
    Serial.println("D-Pad: DOWN");
  } 
  else if (GamePad.isLeftPressed()) {
    turnLeft(255);
    Serial.println("D-Pad: LEFT");
  } 
  else if (GamePad.isRightPressed()) {
    turnRight(255);
    Serial.println("D-Pad: RIGHT");
  } 
  // =======================================================
  // 3. STOP MOTORS (No input detected)
  // =======================================================
  else {
    stopMotors();
  }
}

// --- Movement & Speed Helper Functions ---

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

void turnLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); // Left motor reverses
  digitalWrite(IN3, HIGH); // Right motor moves forward
  digitalWrite(IN4, LOW);
}

void turnRight(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH); // Left motor moves forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Right motor reverses
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
/*
 * H-Bridge 6A Motor Control
 * Author: Example Author
 * Date: 2024-07-XX
 *
 * Description:
 *  - Controls direction and speed of a DC motor
 *  - Uses PWM on enable pin and digital pins for direction
 *  - Prevents simultaneous reversal of polarity
 */

#define PIN_IN1 8  // Direction input 1
#define PIN_IN2 9  // Direction input 2
#define PIN_ENA 10 // PWM pin for speed control

void setup() {
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);

  // Motor stopped initially
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 0);
}

void loop() {
  // Spin forward
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 150); // ~60% speed

  delay(3000);

  // Stop the motor
  analogWrite(PIN_ENA, 0);
  delay(1000);

  // Spin backward
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_ENA, 150);

  delay(3000);

  // Stop again
  analogWrite(PIN_ENA, 0);
  delay(1000);
}


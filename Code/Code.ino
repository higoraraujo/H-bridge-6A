/*
 * Advanced DC Motor control with 6A H-bridge
 * - Flexible PWM frequency via Timer1
 * - Ramp support for smooth acceleration
 * - Direction control using only two PWM channels
 *
 * Pins are configurable and must be PWM-capable.
 */

#include <Arduino.h>

const uint8_t PIN_INA = 9;   // OC1A
const uint8_t PIN_INB = 10;  // OC1B
const uint16_t DEFAULT_PWM_FREQUENCY = 20000; // 20 kHz

int currentSpeed = 0;        // -100 to 100
uint16_t pwmTop = 0;         // Timer1 TOP value

void setup() {
  setupPWM(DEFAULT_PWM_FREQUENCY);
  brake();
}

void loop() {
  // Example usage: ramp forward, then reverse
  rampTo(100, 5, 20);   // to 100% speed
  delay(1000);
  rampTo(-100, 5, 20);  // to -100% speed
  delay(1000);
}

// Configure Timer1 for Fast PWM with configurable frequency
void setupPWM(uint16_t freq) {
  pinMode(PIN_INA, OUTPUT);
  pinMode(PIN_INB, OUTPUT);

  // Reset Timer1 configuration
  TCCR1A = 0;
  TCCR1B = 0;

  // Fast PWM, TOP=ICR1, non-inverted on A/B
  TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
  TCCR1B |= _BV(WGM13) | _BV(WGM12) | _BV(CS10); // no prescaler

  setPWMFrequency(freq);
}

// Change PWM frequency at runtime
void setPWMFrequency(uint16_t freq) {
  pwmTop = F_CPU / freq - 1;
  ICR1 = pwmTop;
  applyPWM(currentSpeed); // keep current duty
}

// Apply PWM value according to desired speed (-100..100)
void applyPWM(int speed) {
  speed = constrain(speed, -100, 100);
  uint16_t duty = (uint32_t)abs(speed) * pwmTop / 100;

  if (speed >= 0) {
    OCR1A = duty;
    OCR1B = 0;
  } else {
    OCR1A = 0;
    OCR1B = duty;
  }
  currentSpeed = speed;
}

// Smoothly ramp to target speed
void rampTo(int target, int step, uint16_t delayMs) {
  target = constrain(target, -100, 100);
  while (currentSpeed != target) {
    int next = currentSpeed < target
                ? min(currentSpeed + step, target)
                : max(currentSpeed - step, target);
    applyPWM(next);
    delay(delayMs);
  }
}

// Coast / brake the motor
void brake() {
  OCR1A = 0;
  OCR1B = 0;
  digitalWrite(PIN_INA, LOW);
  digitalWrite(PIN_INB, LOW);
  currentSpeed = 0;
}


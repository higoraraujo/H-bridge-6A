/*
Code - Controling one motor DC +  H-bridge 6A + Arduino  - by Igor Araujo 2014
2x pins PWM for control.

0 = Low Speed
100 = Full Speed

https://github.com/higoraraujo/H-bridge-6A
http://www.igoraraujo.eng.br

*/




#define INA 5
#define INB 6

void setup() {


  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);



}

void loop() {


  motor(50); // 50% Speed forward
  delay(2000);
  motor(-50); // 50% Speed backward
  delay(2000);

}



void motor (float a) {
  // Ensure the requested speed is within the valid range to avoid
  // overflow when converting to the 0-255 PWM scale.
  a = constrain(a, -100, 100);

  // Convert percentage to a PWM value. Using an intermediate variable
  // prevents writing floats directly to analogWrite and keeps the value
  // within the expected byte range.
  int pwm = (int)((a >= 0 ? a : -a) * 2.55);

  if (a >= 0) {
    analogWrite(INA, pwm);
    analogWrite(INB, 0);
  } else {
    analogWrite(INA, 0);
    analogWrite(INB, pwm);
  }
}











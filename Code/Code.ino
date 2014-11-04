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


  if (a >= 0) {
    a = (a * 2.55);
    analogWrite(INA, a);
    analogWrite(INB, 0);

  }
  if (a < 0) {

    a = a * (-2.55);
    analogWrite(INA, 0);
    analogWrite(INB, a);


  }

}











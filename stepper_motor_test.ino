#include<Arduino.h>
#include<AccelStepper.h>
 
#define HALFSTEP 8   

// useful links
// russian example:  http://robotosha.ru/arduino/stepper-motor-28byj-uln2003-arduino.html
// ULN2003:   https://rudatasheet.ru/datasheets/uln2003/
// BYJ48:   https://www.instructables.com/id/BYJ48-Stepper-Motor/

// Определение пинов для управления двигателем
#define motorPin1  8 // IN1 на 1-м драйвере ULN2003
#define motorPin2  9 // IN2 на 1-м драйвере ULN2003
#define motorPin3  10 // IN3 на 1-м драйвере ULN2003
#define motorPin4  11 // IN4 на 1-м драйвере ULN2003
 
// Инициализируемся с последовательностью выводов IN1-IN3-IN2-IN4 
// для использования AccelStepper с 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
 
void setup(){
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(10.0);
  stepper1.setSpeed(100);
  stepper1.moveTo(2048);
}
 
void loop(){
  // Изменяем направление, если шаговик достигает заданного положения
  if(stepper1.distanceToGo()==0)
    stepper1.moveTo(-stepper1.currentPosition());
  stepper1.run();
}

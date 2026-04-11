#include <ESP32Servo.h>

#define TRIG 5
#define ECHO 18
#define IR 19
#define LED 2
#define SERVO_PIN 21

Servo myServo;

long duration;
int distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(IR, INPUT);
  pinMode(LED, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0); // initial position
}

void loop() {

  // Ultrasonic distance measurement
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  int irValue = digitalRead(IR);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" | IR: ");
  Serial.println(irValue);

  // CONDITION: threat detection
  if (distance < 50 && irValue == LOW) {
    
    digitalWrite(LED, HIGH);   // LED ON
    myServo.write(90);         // Servo rotates

  } else {
    
    digitalWrite(LED, LOW);    
    myServo.write(0);          

  }

  delay(300);
}

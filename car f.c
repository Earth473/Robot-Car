const int sensorLeft = 18;   
const int sensorRight = 19;  

const int motorLeftForward = 14;
const int motorLeftBackward = 27;
const int motorRightForward = 26;
const int motorRightBackward = 25;

const int enA = 33;  
const int enB = 32;  
const int speed = 100;

void setup() {
  pinMode(sensorLeft, INPUT);
  pinMode(sensorRight, INPUT);

  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, speed);  
  analogWrite(enB, speed);  
  Serial.begin(115200);
}

void loop() {
  int leftValue = digitalRead(sensorLeft);    
  int rightValue = digitalRead(sensorRight);  

  
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print("  Right: ");
  Serial.println(rightValue);

  if (leftValue == 0 && rightValue == 0) {
    moveForward();  
  }
  else if (leftValue == 0 && rightValue == 1) {
    turnLeft();  
  }
  else if (leftValue == 1 && rightValue == 0) {
    turnRight(); 
  }
  else {
    stopMotors();  
}

void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);  
  digitalWrite(motorRightForward, HIGH);  
  digitalWrite(motorRightBackward, LOW);
}

void turnRight() {
  digitalWrite(motorLeftForward, HIGH);  
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);  
  digitalWrite(motorRightBackward, LOW);
}

void stopMotors() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}
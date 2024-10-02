#define BLYNK_TEMPLATE_ID "TMPL6aRfAcVCu"
#define BLYNK_TEMPLATE_NAME "house1"
#define BLYNK_AUTH_TOKEN "2CPp_uCKXbklhmGVhNz34SqcBmrQQxH9"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "IRETUTOR_AZ-TRUE_2.4G";
char pass[] = "5687862020";

const int trigPin = 16;  
const int echoPin = 17;  
const int sensorLeft = 18;   
const int sensorRight = 19;  


const int motorLeftForward = 14;   
const int motorLeftBackward = 27;  
const int motorRightForward = 26;  
const int motorRightBackward = 25; 
const int enA = 33;  
const int enB = 32;  
const int speed = 60;  

int currentMode = 1; 

long duration;
int distance;

void setup() {
  Serial.begin(115200);
 
  
  pinMode(sensorLeft, INPUT);
  pinMode(sensorRight, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  Blynk.run();   
  Ultrasonic();  
  Linetracking();  
  sendDHTData();  
  checkMode();    
}


BLYNK_WRITE(V4) {
  int currentMode2 = param.asInt();
  currentMode = currentMode2;  
}


BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    forward();  
  } else {
    stopMotors();  
  }
}


BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value == 1) {
    turnLeft();  
    delay(400);  
    Blynk.virtualWrite(V2, 0);  
    forward();  
  } else {
    stopMotors();  
  }
}

// ฟังก์ชันควบคุมการเลี้ยวขวาจาก Blynk (V3)
BLYNK_WRITE(V3) {
  int value = param.asInt();
  if (value == 1) {
    turnRight();  
    delay(400);  
    Blynk.virtualWrite(V3, 0);  
    forward();  
  } else {
    stopMotors();  
  }
}

void Ultrasonic() {
  if (currentMode == 2) {
    distance = getDistance();  

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    
    if (distance < 25) {
      backward();
      delay(500);
      turnRight();
      delay(500);
    } else {
      forward();  
    }
    delay(100);  
  }
  Serial.println(distance);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  
  int distance = duration * 0.034 / 2;  

  return distance;
}

void Linetracking() {
  if (currentMode == 3) {
    int leftValue = digitalRead(sensorLeft);    // อ่านค่าจากเซ็นเซอร์ซ้าย
    int rightValue = digitalRead(sensorRight);  // อ่านค่าจากเซ็นเซอร์ขวา

    Serial.print("Left: ");
    Serial.print(leftValue);
    Serial.print("  Right: ");
    Serial.println(rightValue);

    
    if (leftValue == 0 && rightValue == 0) {
      forward();  
    } else if (leftValue == 0 && rightValue == 1) {
      turnLeft();  
    } else if (leftValue == 1 && rightValue == 0) {
      turnRight();  
    } else {
      stopMotors();  
    }
  }
}


void sendDHTData() {
  float h = dht.readHumidity();  // อ่านค่าความชื้น
  float t = dht.readTemperature();  // อ่านค่าอุณหภูมิ

 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  String SumString = "Temp: " + String(t) + " °C " + "Humidity: " + String(h) + " %";
  Blynk.virtualWrite(V0, SumString);  // ส่งค่าที่อ่านได้ไปยัง Blynk
}


void checkMode() {
  if (currentMode == 2 || currentMode == 3) {
    // ปิดการทำงานของปุ่ม V1, V2, V3 เมื่ออยู่ในโหมด 2 หรือ 3
    Blynk.virtualWrite(V1, 0);  // ปิดปุ่ม V1
    Blynk.virtualWrite(V2, 0);  // ปิดปุ่ม V2
    Blynk.virtualWrite(V3, 0);  // ปิดปุ่ม V3
  }
}


void forward() {
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


void backward() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
}{
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

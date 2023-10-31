#include <ArduinoJson.h>

#define trigPin 6
#define echoPin 7

int counter;
float duration;
float distance;
unsigned long time;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = 0;
  counter = 0;
  while (--counter != 0) 
  {
    if (PINB & 2) 
    {
      time = micros();
      break;
    }
  }
  while (--counter != 0) 
  {
    if ((PINB & 2) == 0) 
    {
      duration = micros() - time;
      break;
    }
  }

  distance = (duration / 2) * 0.0344;

  StaticJsonDocument<100> json; // Tamanho do buffer para o JSON

  if (distance < 100) 
  {
    json["distance"] = "Muito perto, pare agora";
  } 
  else if (distance >= 100 && distance <= 300) 
  {
    json["distance"] = "Se aproximando, tome cuidado";
  } 
  else 
  {
    json["distance"] = "Objeto Longe";
  }

  String jsonString;
  serializeJson(json, jsonString);
  
  Serial.println(jsonString);

  delay(1000);
}

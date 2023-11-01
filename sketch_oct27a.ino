#include <ArduinoJson.h>

#define trigPin 10
#define echoPin 9
#define ledRedpin 5
#define ledBluepin 4
#define ledGreenpin 3
#define buzzer 2

int counter;
float duration;
float distance;
unsigned long time;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRedpin, OUTPUT);
  pinMode(ledBluepin, OUTPUT);
  pinMode(ledGreenpin, OUTPUT);
  pinMode(buzzer, OUTPUT);
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

  if (distance < 10)
  {
    digitalWrite(5, HIGH);
    digitalWrite(2, HIGH);
    json["distance"] = distance; // Adicione a distância ao JSON
    json["status"] = "Muito perto, pare agora";
    delay(200);
    digitalWrite(5, LOW);
    digitalWrite(2, LOW );
    delay(10);
  }
  else if (distance >= 10 && distance <= 30)
  {
    digitalWrite(4, HIGH);
    json["distance"] = distance; // Adicione a distância ao JSON
    json["status"] = "Se aproximando, tome cuidado";
    delay(2000);
    digitalWrite(4, LOW);
    delay(10);
  }
  else
  {
    digitalWrite(3, HIGH);
    json["distance"] = distance; // Adicione a distância ao JSON
    json["status"] = "Objeto Longe";
    delay(2000);
    digitalWrite(3, LOW);
    delay(10);
  }

  String jsonString;
  serializeJson(json, jsonString);

  Serial.println(jsonString);

  delay(1000);
}

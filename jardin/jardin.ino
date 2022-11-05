#include <DHT.h>
#include <DHT_U.h>

int temp_sensor = 9;
int water_pulp = 8;
int led = 7;
int temp;
int hum;

DHT dht(temp_sensor, DHT11);


void setup() {
  pinMode(water_pulp, OUTPUT)
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("C");
  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.print("%");
  delay(500);

  if (hum < 5){
    digitalWrite(water_pulp, LOW);
    delay(5000);
  }

  if (temp < 10){
    digitalWrite(led, HIGH;)
  }



}

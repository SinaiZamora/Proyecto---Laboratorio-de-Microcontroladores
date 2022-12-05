#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>

const int dry_value = 442; //valor que mide el sensor en seco
const int water_value = 186; //valor que mide el sensor cuando esta en agua
int intervals = (dry_value - water_value)/3;
int soil_moisture_value = 0; // variable para guardar el valor de humedad de la tierra
int water_pulp = 8; // pin digital donde se conecta la bomba de agua
int state = 1; // valor para medir estado de la humedad, 1 es mojado, 0 es seco
int temp_pin = 9; //pin digital donde se conecta el sensor
int temp; //variable para almacenar la temperatura
int hum; //variable para almacenar la humedad
float sen_ter; // variable para almacenar la sensacion termica

const int LED = 13;
const int BT_power = 12;
int temp_prueba;

char name[11] = "SmartGarden";
char speed ='4';//9600
char pin [5]= "0000";


DHT dhtsensor(temp_pin, DHT11); //se crea objeto sensor
SoftwareSerial blue(2,3);

void setup() {

 Serial.begin(9600);
 pinMode(water_pulp, OUTPUT);
 dhtsensor.begin(); // se inicializa el sensor
 pinMode(LED, OUTPUT);
 pinMode(BT_power, OUTPUT);

 digitalWrite(LED, LOW);
 digitalWrite(BT_power, HIGH);

 Serial.begin(9600);

 Serial.print("AT"); //comando AT para indicar que va a configurar
 delay(1000); //delay para que sepa que se termino el primer comando

 Serial.print("AT+NAME"); //se le cambia el nombre
 Serial.print(name);
 delay(1000);

 Serial.print("AT+BAUD");//se configura la velocidad
 Serial.print(speed);
 delay(1000);

 Serial.print("AT+PIN");
 Serial.print(pin);
 delay(1000);

 digitalWrite(LED, HIGH); //aqui sabemos que se ha configurado porque el led se enciende


}


void loop() {

 temp = dhtsensor.readTemperature();
 hum = dhtsensor.readHumidity();
 sen_ter = dhtsensor.computeHeatIndex(temp, hum, false); //obtenemos la sensacion termica a partir de la temperatura y la humedad
 //blue.print(temp);

  Serial.println("\n");
  Serial.print("Temperatura del ambiente: ");
  Serial.print(temp);
  Serial.print(" °C");
  Serial.print("\n");
  Serial.print("Humedad del ambiente: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.print("\n");
  Serial.print("Sensación térmica del ambiente: ");
  Serial.print(sen_ter);
  Serial.print(" °C");
  Serial.print("\n");
  Serial.println("\n");
  delay(1000);



 soil_moisture_value = analogRead(A0); // se lee el valor de humedad la tierra

 if(soil_moisture_value > water_value && soil_moisture_value < (water_value + intervals)){

  state = 1;
  Serial.println("Estado de la tierra: Mojada");
  Serial.println("\n");
  delay(1000);

}

 else if(soil_moisture_value > (water_value + intervals) && soil_moisture_value < (dry_value - intervals)){
  
  state = 1;
  Serial.println("Estado de la tierra: Húmeda");
  Serial.println("\n");
  delay(1000);

}

 else if(soil_moisture_value < dry_value && soil_moisture_value > (dry_value - intervals)){
  
  state = 0;
  Serial.println("Estado de la tierra: Seca");
  Serial.println("\n");
  delay(1000);
  Serial.println("Encendiendo la bomba de agua...");


}

 delay(1000);

  if(state == 0){
    delay(2000);
    digitalWrite(water_pulp, HIGH);
    
    Serial.println("Suministrando agua...");
    delay(5000);
  }

  else if(state == 1){
    digitalWrite(water_pulp, LOW);
    delay(1000);
  }


} 
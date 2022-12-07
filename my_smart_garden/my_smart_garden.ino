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
int water_sensor = 3;
int water_level;
int temp_led = 4;

//variables para para modulo bluetooth
const int LED = 13;
const int BT_power = 12;
char name[14] = "MySmartGarden";
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
 pinMode(water_sensor, INPUT_PULLUP);

 pinMode(temp_led, OUTPUT);

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
  water_level = digitalRead(water_sensor);

  if(temp < 10){
    Serial.println("Baja temperatura, led encendido");
    digitalWrite(temp_led,  HIGH);
  }

  else{
    digitalWrite(temp_led, LOW);
  }

  soil_moisture_value = analogRead(A0); // se lee el valor de humedad la tierra

  Serial.println("\n");
  Serial.print("Temperatura del ambiente: ");
  Serial.print(temp);
  Serial.print(" C");
  Serial.print("\n");
  Serial.print("Humedad del ambiente: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.print("\n");
  Serial.print("Sensacion termica del ambiente: ");
  Serial.print(sen_ter);
  Serial.print(" C");
  Serial.print("\n");
  Serial.println("\n");
  delay(1000);


  if(soil_moisture_value > water_value && soil_moisture_value < (water_value + intervals)){

    state = 1;
    Serial.println("Estado de la tierra: Mojada");
    Serial.println("\n");
    delay(1000);}

  else if(soil_moisture_value > (water_value + intervals) && soil_moisture_value < (dry_value - intervals)){
  
    state = 1;
    Serial.println("Estado de la tierra: Humeda");
    Serial.println("\n");
    delay(1000);}

  else if(soil_moisture_value < dry_value && soil_moisture_value > (dry_value - intervals)){
  
    state = 0;
    Serial.println("Estado de la tierra: Seca");
    Serial.println("\n");
    delay(1000);
    Serial.println("Encendiendo la bomba de agua...");}

  delay(1000);

  if(state == 0){

    if(water_level == 0){
      delay(2000);
      digitalWrite(water_pulp, HIGH);
      Serial.println("Suministrando agua...");
      delay(5000);}

    else if (water_level == 1){
      digitalWrite(water_pulp, LOW);
      Serial.println("Insuficiente nivel de agua, llenar el tanque");
      delay(5000);}
  }

  else if(state == 1){

    digitalWrite(water_pulp, LOW);
    delay(1000);
    
  }


} 

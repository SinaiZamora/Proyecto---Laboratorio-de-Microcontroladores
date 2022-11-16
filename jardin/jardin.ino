int water_pulp = 13;
int soil_moisture = 0
const int dry_value = 448;
const int wet_value = 190;
int intervals = (dry_value - wet_value)/3;


void setup() {

 Serial.begin(9600);
 pinMode(water_pulp,OUTPUT);

}

void loop() {

soil_moisture = analogRead(A0);//se lee el valor de la humedad del suelo
delay(500);

if(soil_moisture > wet_value && soil_moisture < (wet_value + intervals)){
  Serial.println("Estado de la tierra: Muy mojada");
}

else if(soil_moisture > (wet_value + intervals) && soil_moisture < (dry_value - intervals)){
 Serial.println("Estado de la tierra: Humeda");
}

else if(soil_moisture < dry_value && soil_moisture > (dry_value - intervals)){
  Serial.println("Estado de la tierra: Seca");
  delay(1000);
  Serial.println("Encendiendo water_pulp de agua...");
  delay(1000);
  Serial.println("Suministrando agua");
  digitalWrite(water_pulp, HIGH); //se enciende la bomba con el rele
  delay(5000);
  digitalWrite(water_pulp, LOW); ..se apaga la bomba
}

delay(100);

}
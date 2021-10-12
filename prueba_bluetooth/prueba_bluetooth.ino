#include <DHT_U.h>
#include <DHT.h>
#include <NewPing.h>
#define DHTPIN 22
#define DHTTYPE DHT11

int contador = 1;

int pinTrigger = 52;
int pinEcho = 53;

DHT dht(DHTPIN, DHTTYPE);

NewPing sonar(pinTrigger, pinEcho, 200);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial1.print(cadena);
  //Serial.println(cadena);
  //Serial.println("Entro");
  // CALCULAR LA DISTANCIA PARA LA DIRECCION DEL VIENTO //
  int duracion, distancia;

  duracion = sonar.ping();
  distancia = duracion * 0.171;
  String direccion = "";
  
  //Serial.println((String)distancia);
  if(distancia >= 100) {
    //Serial.println("N1");
    direccion = "N1";
  }else if(distancia < 100 && distancia >= 90){
    //Serial.println("N2");
    direccion = "N2";
  }else if(distancia < 90 && distancia >= 77){
    //Serial.println("N3");
    direccion = "N3";
  }else if(distancia < 77){
    //Serial.println("N4");
    direccion = "N4";
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)){
    Serial.println("Error");
    return;
  }

  //Serial.print("humedad ");
  //Serial.println(h);
  //Serial.print("temperatura ");
  //Serial.println(t);

  String direccion1 = "\"distancia\":\"";
  direccion1.concat(direccion);
  direccion1.concat("\"");
  String humedad = "\"humedad\":";
  humedad.concat(h);
  String temperatura = "\"temperatura\":";
  temperatura.concat(t);

  String json = "{";
  json.concat(direccion1);
  json.concat(",");
  json.concat(humedad);
  json.concat(",");
  json.concat(temperatura);
  json.concat("}\n");
//  Serial.println(json);
  Serial1.println(json);
  Serial.println(Serial1.readStringUntil('\n'));
  delay(10000);
}
/*
String getJson(){

  int t=10;
  int h = 10;

  // CALCULAR LA HUMEDAD Y LA TEMPERATURA //
  
  String temperatura = "\"temperatura\":";
  temperatura.concat(t);
  //Serial.println(temperatura);
  String humedad = "\"humedad\":";
  humedad.concat(h);
  //Serial.println(humedad);
  String velocidad="\"velocidad\":";
  velocidad.concat(100);
  //Serial.println(velocidad);
  String direccion1="\"direccion\":\"";
  direccion1.concat(direccion1);
  direccion1.concat("\"");
  //Serial.println(direccion1);
  String luz="\"luz:\"";
  luz.concat(50);
  //Serial.println(luz);
  String json = "{";
  json.concat(temperatura);
  json.concat(",");
  json.concat(humedad);
  json.concat(",");
  json.concat(velocidad);
  json.concat(",");
  json.concat(direccion);
  json.concat(",");
  json.concat(luz);
  json.concat("}");
  //Serial.println(json);
  return json;
}*/

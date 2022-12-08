/**
Tesis.ino
Este archivo será el punto de entrada del proyecto, controlará todo el funcionamiento total
del proyecto.

*/

#include "math.h"

#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1;
#include <Wire.h>
int var = 100;
int option = 0;
const int ledPIN = 13;
bool monutitoreo_cont;
String entrada;
float adc_1_0;
int n_rand;
bool prod = false;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  if (prod == true ){
    if (!ads1.begin(0x48)) {
      Serial.println("Failed to initialize ADS1.");
      while (1); 
    }

    ads1.begin();
  }  


}


/**
 * @brief Esperará a que haya información en el puerto serie para continuar la ejecución
 * 
 */
void waitForSerial(){
  // Serial.flush();
  while (!Serial.available()){
    // Wait
  }
}


void loop() {

  waitForSerial();
  
}
void serialEvent(){
  entrada = Serial.readString();
  entrada.trim();
    // Control de flujo
  if(entrada.equals("sensores")){
    Serial.print("{");
    Serial.print("\"accion\":\"changeMenu\",");
    Serial.print("\"menu\":\"monitorear\"");
    Serial.println("}");
    enviarSensores();
  } 

  if(entrada.equals("sensor_1_inf")){
    Serial.print("{");
    Serial.print("\"accion\":\"changeMenu\",");
    Serial.print("\"menu\":\"monitorear\"");
    Serial.println("}");
    sensor_1();
  }

  if(entrada.equals("sensor_0")){
    Serial.print("{");
    Serial.print("\"accion\":\"changeMenu\",");
    Serial.print("\"menu\":\"monitorear\"");
    Serial.println("}");
    sensor_0();
  } 

  if(entrada.equals("probar")){
    testProject();
  }

  Serial.flush();
  Serial.print("{");
  Serial.print("\"accion\":\"changeMenu\",");
  Serial.print("\"menu\":\"home\"");
  Serial.println("}");

  delay(50);                       // wait for a second

}

void enviarSensores(){
  monutitoreo_cont = true;
  while (true)
  {
    digitalWrite(ledPIN,HIGH);
    Serial.print("{");
    Serial.print("\"accion\":\"monitoreo\",");
    Serial.print("\"sensor1\":");
    Serial.print(read_data(0));
    Serial.print(",\"sensor2\":");
    Serial.print(read_data(1));
    Serial.print(",\"sensor3\":");
    Serial.print(read_data(2));
    Serial.print(",\"sensor4\":");
    Serial.print(read_data(3));
    Serial.println("}");


    digitalWrite(ledPIN,HIGH);
    Serial.print("{");
    Serial.print("\"accion\":\"monitoreo\",");
    Serial.print("\"sensor1\":");
    Serial.print(read_data(0));
    Serial.print(",\"sensor2\":");
    Serial.print(read_data(1));
    Serial.print(",\"sensor3\":");
    Serial.print(read_data(2));
    Serial.print(",\"sensor4\":");
    Serial.print(read_data(3));
    Serial.println("}");
    if (Serial.available())
    {
      entrada = Serial.readString();
      Serial.println(entrada);
      entrada.trim();
      if (entrada=="salir")
      {
        //monutitoreo_cont = false;
        Serial.println("ENTRE AL WHILE");
        break;
      }
    }

    delay(300);

  }
  
}

int read_data(int sensor){
  if (prod==true){
    return ads1.readADC_SingleEnded(sensor);
  }
  else{
    return random(15,100);
  }
}

String get_data_array(int &quantity){
  String string_c;
  string_c = "\"[";
  String b;
  for (int i = 0; i<quantity;i++){
    b = read_data(0);
    string_c = string_c + String(b) + ",";
  }
  string_c = string_c + String(b);
  string_c = string_c + "]\"";
  return string_c;
}


void get_json(int &quantity){
  String string_c;
  Serial.print("{");
  Serial.print("\"accion\":\"monitoreo\",");
  Serial.print("\"sensor1\":");
  string_c = get_data_array(quantity);
  Serial.print(string_c);
  Serial.println("}");
}

void sensor_1(){

  while (true){
    
    digitalWrite(ledPIN,HIGH);
    get_json(var);

    digitalWrite(ledPIN,LOW);
    get_json(var);

    if (Serial.available())
    {
      entrada = Serial.readString();
      entrada.trim();
      if (entrada=="salir")
      {
        break;
      }
    }

    delay(50);

  }
  
}


void sensor_0(){
  digitalWrite(ledPIN,HIGH);
  get_json(var);

  digitalWrite(ledPIN,LOW);
  get_json(var);

  delay(50);
}



void testProject(){
  Serial.println("{\"accion\":\"test\",\"message\":\"successful\"}");
}

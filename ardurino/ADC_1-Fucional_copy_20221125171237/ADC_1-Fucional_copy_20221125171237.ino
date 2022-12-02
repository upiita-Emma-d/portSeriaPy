#include <Adafruit_ADS1X15.h>

#include <Wire.h>


// Crear objeto de la clase
const int ledPIN = 13;
Adafruit_ADS1115 ads1;
String teststr = "____";
float ciclos = 15;
float adc_1_0 = 0;
float nueva;
void setup(void) 
{
  Serial.begin(9600);
  pinMode(ledPIN , OUTPUT);  //definir pin como salida
  delay(200);
  if (!ads1.begin(0x48)) {
    Serial.println("Failed to initialize ADS1.");
    while (1);
  }
  
  ads1.begin();
}
void write_and_read(int frecuencia) {
  //frecuencia = 3;
  if (frecuencia<=0){
    frecuencia = 2;
  }
  frecuencia = frecuencia * 2 ;
  int steps = 5;
  ciclos = frecuencia;
  int retardo = 1000/(frecuencia*steps);
  for (int repet = 0; repet <= 100; repet++){
    digitalWrite(ledPIN,HIGH);
    for (int i = 0; i < steps; i++){
      adc_1_0 = ads1.readADC_SingleEnded(0) ;
      nueva = (adc_1_0 * 5)/65636;
      //Serial.println(nueva);
      delay(retardo);
    }

    digitalWrite(ledPIN,LOW);
    for (int i = 0; i <=steps; i++){
      adc_1_0 = ads1.readADC_SingleEnded(0) ;
      nueva = (adc_1_0 *  5)/65636;
      //Serial.println(nueva);
      delay(retardo);
    }
    Serial.println(repet);
  }
  
  // 2
}

void loop(void) 
{

  if (Serial.available()){
    Serial.println("Leyendo");
    teststr = Serial.readString();  //read until timeout
    Serial.println(teststr);
    Serial.println("##########");
    teststr.trim();                        // remove any \r \n whitespace at the end of the String
    for (int b ; b <10 ; b++){
      Serial.println(b);  
    }

  }
   
  Serial.println("HOLA ");
  // if (teststr == "adc_0") {
  // write_and_read(200);
  // teststr = "";
  // // LED APAGADO
  
  // }

  // else {
  //   //Serial.println(teststr);
  //   teststr = "";
  // }

}

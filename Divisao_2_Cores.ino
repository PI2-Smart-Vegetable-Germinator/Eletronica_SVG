#include "DHT.h"
#define DHTPIN 13  
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define SensorLaranja 12
#define SensorPrata 14
#define SensorRoxo 27
#define SensorRosaEscuro 26
#define SensorRosaClaro 33

#define Luximetro 32
#define Presenca 35

int dirPin1=2;
int stepPin1=4;
int dirPin2=25;
int stepPin2=16;

#define stepsPerRevolution 200
#define Velo 450

String recebido;

String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}

void setup() {
  
  pinMode(SensorLaranja, INPUT); 
  pinMode(SensorPrata, INPUT); 
  pinMode(SensorRoxo, INPUT); 
  pinMode(SensorRosaEscuro, INPUT); 
  pinMode(Presenca, INPUT); 
  pinMode(SensorRosaClaro, INPUT); 
  pinMode(Luximetro, INPUT); 
  dht.begin();
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0){
    // Lê toda string recebida
    recebido = leStringSerial();
      
  }
  if (recebido=="antihorario") {
    delay(500); 
    digitalWrite(dirPin1, HIGH);
  }else if(recebido=="horario"){
    delay(500);
    digitalWrite(dirPin1, LOW);
  }
   
 float h = dht.readHumidity();
 float t = dht.readTemperature();

  Serial.println("{");
   
    Serial.print("\"UmidadeAr\"");
    Serial.print(" : ");
    Serial.print("\"");
    Serial.print(h);
    Serial.println("\",");

    Serial.print("\"TemperaturaAr\"");
    Serial.print(" : ");
    Serial.print("\"");
    Serial.print(t);
    Serial.println("\",");
    
  Serial.print("\"SensorSolo1\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(SensorRosaEscuro));
  Serial.println("\",");

  Serial.print("\"SensorSolo2\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(SensorRosaClaro));
  Serial.println("\",");
  
  Serial.print("\"SensorSolo3\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(SensorPrata));
  Serial.println("\",");
 
  Serial.print("\"SensorSolo4\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(SensorLaranja));
  Serial.println("\",");
  
  Serial.print("\"SensorSolo5\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(SensorRoxo));
  Serial.println("\",");
  
  Serial.print("\"Presença\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(Presenca));
  Serial.println("\",");
  
  Serial.print("\"Luximetro\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print(analogRead(Luximetro));
  Serial.println("\"");
  Serial.println("}");
  Serial.println("");
  girar(dirPin1,stepPin1);
  delay(500);
}
void girar(int dirPin, int stepPin) {

  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(Velo);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(Velo);
  }

}

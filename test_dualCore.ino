TaskHandle_t Task1;
TaskHandle_t Task2;
// Motor pins
int dirPin1=2;
int stepPin1=15;
int dirPin2=4;
int stepPin2=16;

float UmidadeMedia=0;
String recebido;

int Cancela=0;
int Sensores=0;
int Plantar=0;

#define stepsPerRevolution 200
#define Velo 450

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
  Serial.begin(9600); 
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

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

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,3,&Task1,0);          /* pin task to core 0 */                  
  delay(500);
  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,2,&Task2,1);          /* pin task to core 0 */                  
  delay(500);  
}

void girar(int dirPin, int stepPin) {

  for (int i = 0; i < 5*10* stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(Velo);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(Velo);
    if(Cancela==true){
      break;
    }
  }
}

void loop() {}

void Task1code( void * pvParameters ){
for(;;){
  if (Serial.available() > 0){
    // Lê toda string recebida
    recebido = leStringSerial();    
  }
  if(recebido=="cancela"){
    Cancela=1;
    recebido=" ";
  } else if(recebido=="sensores"){
    Sensores=1;
    recebido=" ";
  } else if(recebido=="plantar"){
    Plantar=1;
    recebido=" ";
  }
  delay(100);
}
}

void Task2code( void * pvParameters ){
for(;;){
  delay(500);
  if (Plantar==1){
    Serial.println(analogRead(Presenca));
    if(analogRead(Presenca)<10){ 
      digitalWrite(dirPin2, LOW);
      girar(dirPin2,stepPin2);
      delay(400);
      digitalWrite(dirPin2, HIGH);
      girar(dirPin2,stepPin2);
    }else{
      Serial.println("falsapresenca");
    }
    Plantar=0;
    Cancela=0;
  }
  
  if (Sensores==1) {
    delay(100);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    UmidadeMedia=analogRead(SensorRosaEscuro)+analogRead(SensorRosaClaro)+analogRead(SensorPrata)+analogRead(SensorLaranja)+analogRead(SensorRoxo);
    UmidadeMedia=UmidadeMedia/5;
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
    
    Serial.print("\"UmidadeSolo\"");
    Serial.print(" : ");
    Serial.print("\"");
    Serial.print(UmidadeMedia);
    Serial.println("\",");
    
    Serial.print("\"Luximetro\"");
    Serial.print(" : ");
    Serial.print("\"");
    Serial.print(analogRead(Presenca));
    Serial.println("\"");
    Serial.println("}");
    Serial.println("");
    Sensores=0;
   }
} 
}

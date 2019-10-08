#include "DHT.h"
#define DHTPIN 4    
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
const int SRUS = 15;
const int LDR1 = 34;
const int LDR2 = 35;
const int Amostras = 500;
float umidade;
float temperatura_ar;
float umidade_ar;
float luminosidade;
float presenca_sementeira;
float A_umidade;
float A_temperatura_ar;
float A_umidade_ar;
float A_luminosidade;
float A_presenca_sementeira;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Inicializando monitoramento"));
  dht.begin();
}

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();

    umidade = 0;
    for (int i = 0; i <Amostras; i++)
    {
      umidade = umidade + analogRead(SRUS);
      delay(1);
    }
    umidade = umidade / Amostras;

    temperatura_ar = 0;
    for (int j = 0; j <Amostras; j++)
    {
      temperatura_ar = temperatura_ar + t;
      delay(1);
    }
    temperatura_ar = temperatura_ar / Amostras;
    
    umidade_ar = 0;
    for (int k = 0; k <Amostras; k++)
    {
      umidade_ar = umidade_ar + h;
      delay(1);
    }
    umidade_ar = umidade_ar / Amostras;
 
    luminosidade = 0;
    for (int l = 0; l <Amostras; l++)
    {
      luminosidade = luminosidade + analogRead(LDR1);
      delay(1);
    }
    luminosidade = luminosidade / Amostras;
    
    presenca_sementeira = 0;
    for (int m = 0; m <Amostras; m++)
    {
      presenca_sementeira = presenca_sementeira + analogRead(LDR2);
      delay(1);
    }
    presenca_sementeira = presenca_sementeira / Amostras;

    if(umidade!=A_umidade||temperatura_ar!=A_temperatura_ar||umidade_ar!=A_umidade_ar||luminosidade!=A_luminosidade||presenca_sementeira!=A_presenca_sementeira){
      A_umidade=umidade;
      A_temperatura_ar=temperatura_ar;
      A_umidade_ar=umidade_ar;
      A_luminosidade=int(luminosidade);
      A_presenca_sementeira=presenca_sementeira;
       // presenca_sementeira = (presenca_sementeira*0.1075268817204);
      Serial.print("Presença da sementeira: ");
      Serial.println(presenca_sementeira);
      // luminosidade = (luminosidade*0.1075268817204);
      Serial.print("Luminosidade: ");
      Serial.println(luminosidade);
      //umidade_ar = (umidade_ar*0.1075268817204);
      Serial.print("Umidade do ar: ");
      Serial.print(umidade_ar);
      Serial.println("%");
      // temperatura_ar = (temperatura_ar*0.1075268817204);
      Serial.print("Temperatura do Ar: ");
      Serial.print(temperatura_ar);
      Serial.println("°C");
      //   umidade = (umidade*0.1075268817204);
      Serial.print("Umidade do solo: ");
      Serial.println(umidade);
    }    
  }

TaskHandle_t Task1;
TaskHandle_t Task2;
// LED pins
int dirPin1=2;
int stepPin1=4;

String recebido;

#define stepsPerRevolution 200
#define Velo 450

const int SRUS1 = 12;
const int SRUS2 = 14;
const int SRUS3 = 27;
const int SRUS4 = 26;
const int SRUS5 = 33;
const int Amostras = 500;
const int Rele1 = 32;
int umidade1;
int UR1;
int umidade2;
int UR2;
int umidade3;
int UR3;
int umidade4;
int UR4;
int umidade5;
int UR5;
float media_SRUS;

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

  pinMode(Presenca, INPUT); 
  pinMode(Luximetro, INPUT);

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
  }
}

void loop() {}

void Task1code( void * pvParameters ){
for(;;){
    umidade1 = 0;

  for (int i = 0; i < Amostras; i++)
  {
    umidade1 =  analogRead(SRUS1);
    delay (1);
  }
  
  umidade2 = 0;
  for (int j = 0; j < Amostras; j++)
  {
    umidade2 =  analogRead(SRUS2);
    delay (1);
  }
  
  umidade3 = 0;
  for (int k = 0; k < Amostras; k++)
  {
    umidade3 =  analogRead(SRUS3);
    delay (1);
  }
  
  umidade4 = 0;
  for (int l = 0; l < Amostras; l++)
  {
    umidade4 =  analogRead(SRUS4);
    delay (1);
  }
  
  umidade5 = 0;
  for (int m = 0; m < Amostras; m++)
  {
    umidade5 =  analogRead(SRUS5);
    delay (1);
  }

  if ((umidade1 && umidade2 && umidade3 && umidade4 && umidade5) >3000 && (umidade1 && umidade2 && umidade3 && umidade4 && umidade5)<=4095)
  {
    Serial.println("Sementeira não encontrada");
  }
  else 
  {
  
  UR1 = map (umidade1, 3000, 900, 0, 100);
  UR2 = map (umidade2, 3000, 900, 0, 100);
  UR3 = map (umidade3, 3000, 900, 0, 100);
  UR4 = map (umidade4, 3000, 900, 0, 100);
  UR5 = map (umidade5, 3000, 900, 0, 100);
  
  int med [5] = {UR1, UR2, UR3, UR4, UR5};
  double favg = (med [0] + med [1] + med [2] + med [3] + med [4])/5;
  int acc = 0;
  int len = 0;
  for (int n=0; n <5; n++)
  {
    int dist = med [n] - favg;
    if (dist < 0)
    {
      dist *= -1;
    }

    if (dist <10)
    {
      len += 1;
      acc += med [n];
    }
  }
  int media_UR = (acc/(len+1));
  Serial.println("{");
  Serial.print("\"Media UR\"");
  Serial.print(" : ");
  Serial.print("\"");
  Serial.print (media_UR);
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
  delay(1000);  
  } 
}
}

void Task2code( void * pvParameters ){
for(;;){
  // Se receber algo pela serial
  if (Serial.available() > 0){
    // Lê toda string recebida
    recebido = leStringSerial(); 
  }
  delay(500);
  if (recebido=="Plantar") { 
    digitalWrite(dirPin1, LOW);
    girar(dirPin1,stepPin1);
    delay(400);
    digitalWrite(dirPin1, HIGH);
    girar(dirPin1,stepPin1);
    recebido=" ";
  }
  } 
}
}

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


void setup()
{		
  Serial.begin(9600);
  Serial.println(F("Inicializando monitoramento"));
  pinMode(Rele1, OUTPUT);
}

void loop()
{
  umidade1 = 0;

  for (int i = 0; i < Amostras; i++)
  {
    umidade1 +=  analogRead(SRUS1) ;
    delay (1);
  }
  umidade1 = umidade1 / Amostras;
  Serial.print ("Leitura1 ");
  Serial.println(umidade1);
  
  umidade2 = 0;
  for (int j = 0; j < Amostras; j++)
  {
    umidade2 +=  analogRead(SRUS2);
    delay (1);
  }
  umidade2 = umidade2 / Amostras;
  Serial.print ("Leitura2 ");
  Serial.println(umidade2);
  
  umidade3 = 0;
  for (int k = 0; k < Amostras; k++)
  {
    umidade3 +=  analogRead(SRUS3);
    delay (1);
  }
  umidade3 = umidade3 / Amostras;
  Serial.print ("Leitura3 ");
  Serial.println(umidade3);
  
  umidade4 = 0;
  for (int l = 0; l < Amostras; l++)
  {
    umidade4 +=  analogRead(SRUS4);
    delay (1);
  }
  umidade4 = umidade4 / Amostras;
  Serial.print ("Leitura4 ");
  Serial.println(umidade4);
  
  umidade5 = 0;
  for (int m = 0; m < Amostras; m++)
  {
    umidade5 +=  analogRead(SRUS5);
    delay (1);
  }
  umidade5 = umidade5 / Amostras;
  Serial.print ("Leitura5 ");
  Serial.println(umidade5);

  if ((umidade1 && umidade2 && umidade3 && umidade4 && umidade5) >3000)
  {
    Serial.println("Sementeira não encontrada")
  }

  else 
  {
    
  
  UR1 = map (umidade1, 3000, 900, 0, 100);
  UR2 = map (umidade2, 3000, 900, 0, 100);
  UR3 = map (umidade3, 3000, 900, 0, 100);
  UR4 = map (umidade4, 3000, 900, 0, 100);
  UR5 = map (umidade5, 3000, 900, 0, 100);
  Serial.print ("Mapeamento1 ");
  Serial.println(UR1);
  Serial.print ("Mapeamento2 ");
  Serial.println(UR2);
  Serial.print ("Mapeamento3 ");
  Serial.println(UR3);
  Serial.print ("Mapeamento4 ");
  Serial.println(UR4);
  Serial.print ("Mapeamento5 ");
  Serial.println(UR5); 
  
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
  Serial.print ("Media UR: ");
  Serial.print (media_UR); Serial.println("%");
    delay (2000);

  }
}

const int SRUS1 = 12;
const int SRUS2 = 14;
const int SRUS3 = 27;
const int SRUS4 = 26;
const int SRUS5 = 33;
const int Amostras = 500;
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

// calcula o tamanho de um vetor ignorando as posições com -1
int true_size(int a[5]) {
  int s = 0;
  for(int i=0; i<5; i++) {
    s += a[i] > 0 ? 1 : 0;
  }

  return s;
}

// calcula a média de 5 sensores recursivamente com base em um treshold inicial
int media_sensor(int sensor[5], int threshold){
  int attempt[5][5];
  int new_threshold = 0;
  int fl = 0;

  for (int i=0; i<5; i++){
    attempt[i][0] = sensor[i];
    attempt[i][1] = -1;
    attempt[i][2] = -1;
    attempt[i][3] = -1;
    attempt[i][4] = -1;
    
    for(int j=i+1; j<5; j++){
      int diff = sensor[j] - sensor[i];
      diff = diff < 0 ? diff * -1 : diff;

      if(diff <= threshold){
        attempt[i][j] = sensor[j];
	fl = 1;
      }else {
	new_threshold = new_threshold > 0 ? new_threshold : diff;
        new_threshold = diff < new_threshold ? diff : new_threshold;
      }
    }
  }
  
  int prev = 0;
  int greater = 0;

  for(int i=0; i<5; i++){
    int s = true_size(attempt[i]);

    if(s > prev) {
      prev = s;
      greater = i;
    }
  }
  
  int r = 0;
  int l = true_size(attempt[greater]);

  for(int i=0; i<5; i++) {
    r += attempt[greater][i] != -1 ? attempt[greater][i] : 0;
  }
  
  if(fl == 0) {
    return media_sensor(sensor, new_threshold);
  }

  return l > 0 ? r/l : 0;
}



void setup()
{		
  Serial.begin(9600);
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
  
  int sensor [5] = {UR1, UR2, UR3, UR4, UR5};
  int media_UR = media_sensor(sensor, 10);

  Serial.print ("Media UR: ");
  Serial.print (media_UR); Serial.println("%");
    delay (2000);

  }
}

   
int LED = 10; //Pino ligado ao anodo do led  
int LDR = 5;  //Pino ligado ao LDR  
int valor_LDR = 0; //Armazena valor lido do LDR, entre 0 e 1023  
double luminosidade = 0; //Valor de luminosidade do led     

void setup()  
{    
  Serial.begin(9600);    //Inicializa a serial    
  pinMode(LED, OUTPUT); //Define o pino do led como saída    
  pinMode(LDR, INPUT);  //Define o pino do LDR como entrada 
   
}     
  void loop()  
 {    
  valor_LDR = analogRead(LDR);  //Le o valor - analogico - do LDR  
  luminosidade = map(valor_LDR, 0, 255, 0, 1023); // Mapeia os valores de resistencia em relação a luminosidade   
  luminosidade = 255.84 * pow (valor_LDR, -10/9); // Equação da luminosidade
  Serial.print("Valor lido do LDR : ");     //Mostra o valor lido do LDR no monitor serial    
  Serial.print(valor_LDR);    
  Serial.print(" = Luminosidade : ");    //Mostra o valor da luminosidade no monitor serial    
  Serial.println(luminosidade);     //Acende o led com luminosidade variável  
  analogWrite(LED, luminosidade);   // PWM do LED, mas será substituido pelo relê
}

#define LDR_PIN                   0
#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           5.0
#define REF_RESISTANCE            5030  
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405

void setup(void) 
{
  Serial.begin(9600);
  //Serial.println(F("Luxímetro")); Serial.println("");
}


void loop(void) 
{  
  
  int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;
  
    
  ldrRawData = analogRead(LDR_PIN);


  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;

 
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage; 
  ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);

 
 Serial.print(ldrLux); 


  
  delay(1000);
}

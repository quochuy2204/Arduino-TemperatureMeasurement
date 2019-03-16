void setup() 
{
Serial.begin(9600); 

pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, INPUT);
pinMode(13, OUTPUT); //Arduino UNO pin 13 extra LED for ADC event

#define CS_HIGH digitalWrite(2, HIGH)
#define CS_LOW digitalWrite(2, LOW)

#define CLK_HIGH digitalWrite(3, HIGH)
#define CLK_LOW digitalWrite(3, LOW)

#define DIN_HIGH digitalWrite(4, HIGH)
#define DIN_LOW digitalWrite(4, LOW)

#define LED_ON digitalWrite(13, HIGH) //Arduino UNO pin 13 extra LED for ADC event
#define LED_OFF digitalWrite(13, LOW)

#define DOUT digitalRead(5)
}

void loop() 
{
// CLK_HIGH;
// CS_HIGH;
// delay(50);
  
int ADC_result;
  float temperature;
  ADC_result=get_AD_value();
  temperature=-(60.0/1023.0)*ADC_result+30.0;
  Serial.print("ADCC value ");
  Serial.print(ADC_result);
  Serial.println();
  Serial.print("Temperature ");
  Serial.print(temperature);
  Serial.println(); 
  ADC_result=0;
  temperature=0;
  LED_OFF;
  delay(50);
 

}


int get_AD_value()
  {
 int ADC_result;
 ADC_result=0;
  int mask=512;
  char pulse=0;
  char i=0;
  char k=0;
  CLK_LOW;
  CS_LOW;
  LED_ON; //extra LED on
  delay(10);
  DIN_HIGH;
  delay(10);
  
  for(i=0;i<5;i++)
    {
    CLK_HIGH;
    delay(10);
    CLK_LOW;
  
    if(pulse==3)
      {
      DIN_LOW;
      }
  
    delay(10);
    pulse++;
    }
  
  for(k=0;k<10;k++)
    {
    CLK_HIGH;

    
    
    if(DOUT==1)
      {
      ADC_result=(ADC_result|mask);
      }
      
    mask=mask>>1;

    
    delay(10);
    CLK_LOW;
    delay(10);
    }
  
  CS_HIGH;
  delay(20);

  return ADC_result;
  }
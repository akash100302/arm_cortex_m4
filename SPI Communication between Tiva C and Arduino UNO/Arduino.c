#include<SPI.h>
#define LEDpin 7
volatile boolean received;
char Slavereceived;
void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin,OUTPUT);                 
  SPCR |= (1<<SPE)| (1<<SPIE);            
  received = false;
  SPI.attachInterrupt();                  
  sei();
}

ISR (SPI_STC_vect)                         
{
  Slavereceived = SPDR;         
  received = true;                        
}

void loop()
{  
  if(received)  
   {
      if (Slavereceived=='A') 
      {
        digitalWrite(LEDpin,HIGH);         
        Serial.println("Slave LED ON");
        Serial.println(Slavereceived);
      }
       else
      {
        digitalWrite(LEDpin,LOW);          
        Serial.println("Slave LED OFF");
        Serial.println(Slavereceived);
      } 
   }
   delay(1000);
}

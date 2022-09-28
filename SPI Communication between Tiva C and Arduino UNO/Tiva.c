#include "TM4C123GH6PM.h"


void SPI1_init(void);
void SPI1_Write(unsigned char data);
void Delay_ms(int time_ms); 


int main(void)
{
    unsigned char val1 = 'A';
	  unsigned char val2 = 'B';

    SPI1_init();
    while(1)
		{              
    SPI1_Write(val1); 
    Delay_ms(1000);
		SPI1_Write(val2); 
    Delay_ms(1000);	
    }
}

void SPI1_Write(unsigned char data)
{
    GPIOF->DATA &= ~(1<<2);      
    while((SSI1->SR & 2) == 0); 
    SSI1->DR = data;            
    while(SSI1->SR & 0x10);     
    GPIOF->DATA |= 0x04;        
}

void SPI1_init(void)
{
    
	
   	SYSCTL->RCGCSSI |= (1<<1);   
    SYSCTL->RCGCGPIO |= (1<<3); 
    SYSCTL->RCGCGPIO |= (1<<5); 

   
	
    GPIOD->AMSEL &= ~0x09;      
    GPIOD->DEN |= 0x09;         
    GPIOD->AFSEL |= 0x09;      
    GPIOD->PCTL &= ~0x0000F00F; 
    GPIOD->PCTL |= 0x00002002;  
    
   
	
    GPIOF->DEN |= (1<<2);         
    GPIOF->DIR |= (1<<2);        
    GPIOF->DATA |= (1<<2);        

    
		
    SSI1->CR1 = 0;          
    SSI1->CPSR = 4;         
    SSI1->CR0 = 0x00007;    
    SSI1->CR1 |= 2;         
}




void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  
}

void SystemInit(void)
{
 
    SCB->CPACR |= 0x00f00000;
}

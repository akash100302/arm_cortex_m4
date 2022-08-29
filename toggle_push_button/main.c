#include "lm4f120h5qr.h"
#define GPIO_PORTF_DATA_RD (*((volatile unsigned long *)0x40025040))
#define GPIO_PORTF_DATA_WR (*((volatile unsigned long *)0x40025020))
#define GPIO_PORTF_PIN3_EN 0x08
#define GPIO_PORTF_PIN4_EN 0x10
#define SYSTEM_CLOCK_FREQ 16000000
#define DEBOUNCE SYSTEM_CLOCK_FREQ/1000
void Delay(unsigned long counter)
{
    unsigned long i;
    for(i=0;i<counter;i++);
}
int main() {  
    static char flag=0;
    SYSCTL_RCGCGPIO_R|=0x20;
    GPIO_PORTF_DEN_R|=GPIO_PORTF_PIN3_EN+GPIO_PORTF_PIN4_EN;
    GPIO_PORTF_DIR_R|=GPIO_PORTF_PIN3_EN;
    GPIO_PORTF_DIR_R&=(~GPIO_PORTF_PIN4_EN);
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    GPIO_PORTF_CR_R=0x01;
    GPIO_PORTF_PUR_R|=GPIO_PORTF_PIN4_EN;
    while(1) {
        if(GPIO_PORTF_DATA_RD==0)
        {       Delay(DEBOUNCE);
                if(flag==0 && GPIO_PORTF_DATA_RD==0)
                {    GPIO_PORTF_DATA_WR^=GPIO_PORTF_PIN3_EN;   
                     flag=1;
                }
            
            
        }
        else
        {
                flag=0;
        }
    }
}



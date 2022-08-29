#include "lm4f120h5qr.h"
int main() {
    unsigned int state;
    SYSCTL_RCGCGPIO_R|=0x20;
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    GPIO_PORTF_CR_R=0x01;
    GPIO_PORTF_PUR_R|=0x10;
    GPIO_PORTF_DIR_R|=0x02;
    GPIO_PORTF_DEN_R|=0x12;
    while(1) {
        state=GPIO_PORTF_DATA_R & 0x10;
        GPIO_PORTF_DATA_R=(~state>>3);
    }
    return 0;
    
}
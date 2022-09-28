#include "tm4c123gh6pm.h"


void SysTick_Init(void);                         
void SysTick_Wait(unsigned long delay1);
void SysTick_Wait10ms(unsigned long delay1);    
struct State{
	unsigned long TrafficLights_Cars; 
	unsigned long TrafficLights_Ped; s
	unsigned long Time;    
	unsigned long Next[8]; 
};
typedef const struct State STyp;
#define Go_West          0   
#define Wait_West        1
#define Go_South         2
#define Wait_South       3
#define Walk_Ped         4
#define Hurry_On_Ped1    5
#define Hurry_Off_Ped1   6
#define Hurry_On_Ped2    7
#define Hurry_Off_Ped2   8


STyp FSM[9]={
		{0x0C,0x04,100,{0,0,1,1,1,1,1,1}},       //state 1
	  {0x14,0x04,50 ,{2,2,2,2,4,4,4,2}},       //state 2
		{0x21,0x04,100,{2,3,2,3,3,3,3,3}},       //state 3
		{0x22,0x04,50 ,{0,0,0,0,4,4,4,4}},       //state 4
		{0x24,0x08,100,{4,5,5,5,4,5,5,5}},       //state 5
		{0x24,0x04,25 ,{6,6,6,6,4,6,6,6}},       //state 6
		{0x24,0x00,10 ,{7,7,7,7,4,7,7,7}},       //state 7
		{0x24,0x04,25 ,{8,8,8,8,4,8,8,8}},       //state 8
		{0x24,0x00,10 ,{0,0,2,0,4,0,2,0}}        //state 9

};
unsigned long S;  
unsigned long Input;


int main(void) {
	volatile unsigned long delay;
    SysTick_Init();
	SYSCTL_RCGC2_R=0x13;        
	delay=SYSCTL_RCGC2_R;      
	GPIO_PORTB_AMSEL_R=0x00;          
	GPIO_PORTE_AMSEL_R=0x00;          
	GPIO_PORTA_AMSEL_R=0x00;          
	GPIO_PORTB_PCTL_R=0x00000000;    
	GPIO_PORTE_PCTL_R=0x00000000;     
	GPIO_PORTA_PCTL_R=0x00000000;    
	GPIO_PORTB_DIR_R=0x3F;           
	GPIO_PORTE_DIR_R=0x00;            
	GPIO_PORTA_DIR_R=0x0C;            
	GPIO_PORTB_AFSEL_R=0x00;          
	GPIO_PORTE_AFSEL_R=0x00;          
	GPIO_PORTA_AFSEL_R=0x00;         
	GPIO_PORTB_DEN_R=0x3F;           
	GPIO_PORTE_DEN_R=0x07;            
	GPIO_PORTA_DEN_R=0x0C;            
	S=Go_West;
		while(1){
			GPIO_PORTB_DATA_R=FSM[S].TrafficLights_Cars;    
			GPIO_PORTA_DATA_R=FSM[S].TrafficLights_Ped;    
			SysTick_Wait10ms(FSM[S].Time);
			Input=GPIO_PORTE_DATA_R;                     
			S=FSM[S].Next[Input];
			}

}
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               
  NVIC_ST_CTRL_R = 0x00000005;      
}

void SysTick_Wait(unsigned long delay1){
  NVIC_ST_RELOAD_R = delay1-1;  
  NVIC_ST_CURRENT_R = 0;       
  while((NVIC_ST_CTRL_R&0x00010000)==0){ 
  }
}

void SysTick_Wait10ms(unsigned long delay1){
  unsigned long i;
  for(i=0; i<delay1; i++){
    SysTick_Wait(800000);  
  }
}

#include "delay.h"
void delay(int i){
  int volatile counter=0;
  while(counter<i){
    ++counter;
  }
}
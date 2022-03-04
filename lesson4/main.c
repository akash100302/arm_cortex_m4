int counter;
int main()
{ 
  int*ptr;
  
  ptr=&counter;
while(*ptr<21){    
  (*ptr)++;}
ptr=(int*)0x20000002u;
*ptr=0xDEADBEEF;
  return 0;
}

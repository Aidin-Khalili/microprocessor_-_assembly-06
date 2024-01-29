#include "LPC17xx.h"

int division_value;

void EINT0_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 20);     //To make pin2.10 as EINT0
	LPC_SC->EXTMODE|= 1;                      //To make edge sensetive
	LPC_SC->EXTPOLAR|= ~(1);                  //To make falling edge 
	NVIC_SetPriority (EINT1_IRQn,1);
	NVIC_EnableIRQ(EINT1_IRQn);
}

void EINT2_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 24);   //To make pin2.12 as EINT2
	LPC_SC->EXTMODE|= (1<<2);               //To make edge sensetive
	LPC_SC->EXTPOLAR|= (1<<2);              //To make rising edge 
	NVIC_SetPriority (EINT2_IRQn,1);
	NVIC_EnableIRQ(EINT2_IRQn);
}

int change_clk(int cpu_clk)
{
  if(cpu_clk == 2)  
		division_value=2;
	else 
		division_value=3;
	 LPC_SC->PCONP = (1<<22);                        //To power on(Timer2)
   LPC_PINCON->PINSEL0 |= (0x3<<16);						   	//To set pin as match out 2 pin0.8
   LPC_SC->PCLKSEL1 |= (division_value<<12);									//To set timer cpu clk           
}

void EINT2_IRQHandler(){
	change_clk(8);             //To make clock, 1/8 of cpu clk
	LPC_SC->EXTINT = (1<<2);    //To clear flag
	
}
void EINT0_IRQHandler(){
  change_clk(2);              //To make clock, 1/2 of cpu clk
	LPC_SC->EXTINT = (2);      //To clear flag
}

int main()
{
	EINT0_init();
	EINT2_init();
	while(1){}	
}
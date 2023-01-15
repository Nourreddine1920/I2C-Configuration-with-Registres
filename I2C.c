#include "I2C.h"
#include "RccConfig.h"

void I2C_Config (void){

    // Enable the I2C CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1<<21);  // enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1);  // Enable GPIOB CLOCK

    
}
#include "I2C.h"
#include "RccConfig.h"

void I2C_Config (void){

    // Enable the I2C CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1<<21);  // enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1);  // Enable GPIOB CLOCK


    // Configure the I2C PINs for ALternate Functions
	GPIOB->MODER |= (2<<12) | (2<<14);  // Bits (13:12)= 1:0 --> Alternate Function for Pin PB6; Bits (15:14)= 1:0 --> Alternate Function for Pin PB7
    GPIOB->OTYPER |= (1<<6) | (1<<7);  //  Bit6=1, Bit7=1  output open drain
    GPIOB->OSPEEDR |= (2<<12) | (2<<14);  // Bits (13:12)= 1:0 --> High Speed for PIN PB6; Bits (15:14)= 1:1 --> High Speed for PIN PB7
    GPIOB->PUPDR |= (1<<12) | (1<<14);  // Bits (13:12)= 0:1 --> Pull up for PIN PB6; Bits (15:14)= 0:1 --> pull up for PIN PB7
    GPIOB->AFR[0] |= (4<<24) | (4<<28);  // Bits (24:25:26:27) = 0:1:0:0 --> AF4 for pin PB6;  Bits (28:29:30:31) = 0:1:0:0 --> AF4 for pin PB7

    // Reset the I2C 
	I2C1->CR1 |= (1<<15);
	I2C1->CR1 &= ~(1<<15);



    
}
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

    // Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2C1->CR2 |= (45<<0);  // PCLK1 FREQUENCY in MHz
	
	// Configure the clock control registers
	I2C1->CCR = 225<<0;  // check calculation in PDF
	
	// Configure the rise time register
	I2C1->TRISE = 46;  // check PDF again
	
	// Program the I2C_CR1 register to enable the peripheral
	I2C1->CR1 |= (1<<0);  // Enable I2C



    
}

void I2C_Start (void)
{
/**** STEPS FOLLOWED  ************
1. Send the START condition 
2. Wait for the SB ( Bit 0 in SR1) to set. This indicates that the start condition is generated
*/	

	I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= (1<<8);  // Generate START
	while (!(I2C1->SR1 & (1<<0)));  // Wait fror SB bit to set
}

void I2C_Write (void){
	/**** STEPS FOLLOWED  ************
1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
2. Send the DATA to the DR Register
3. Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
*/	
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set
}


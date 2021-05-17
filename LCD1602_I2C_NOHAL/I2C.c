

/**
  ******************************************************************************

  I2C Setup For STM32F446RE
  Author:   ControllersTech
  Updated:  31st Jan 2020

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/


#include "I2C.h"
#include "RccConfig.h"

void I2C_Config (void)
{
/**** STEPS FOLLOWED  ************
1. Enable the I2C CLOCK and GPIO CLOCK
2. Configure the I2C PINs for ALternate Functions
	a) Select Alternate Function in MODER Register
	b) Select Open Drain Output 
	c) Select High SPEED for the PINs
	d) Select Pull-up for both the Pins
	e) Configure the Alternate Function in AFR Register
3. Reset the I2C 	
4. Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
5. Configure the clock control registers
6. Configure the rise time register
7. Program the I2C_CR1 register to enable the peripheral
*/
	
	// Enable the I2C CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1<<21);  // enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1);  // Enable GPIOB CLOCK
	
	
	// Configure the I2C PINs for ALternate Functions
	GPIOB->MODER |= (2<<16) | (2<<18);  // Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9
	GPIOB->OTYPER |= (1<<8) | (1<<9);  //  Bit8=1, Bit9=1  output open drain
	GPIOB->OSPEEDR |= (3<<16) | (3<<18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9
	GPIOB->PUPDR |= (1<<16) | (1<<18);  // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9
	GPIOB->AFR[1] |= (4<<0) | (4<<4);  // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9
	
	
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


void I2C_Write (uint8_t data)
{
/**** STEPS FOLLOWED  ************
1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
2. Send the DATA to the DR Register
3. Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
*/	
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set
}

void I2C_Address (uint8_t Address)
{
/**** STEPS FOLLOWED  ************
1. Send the Slave Address to the DR Register
2. Wait for the ADDR (bit 1 in SR1) to set. This indicates the end of address transmission
3. clear the ADDR by reading the SR1 and SR2
*/	
	I2C1->DR = Address;  //  send the address
	while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
	uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit
}
	
void I2C_Stop (void)
{
	I2C1->CR1 |= (1<<9);  // Stop I2C
}

void I2C_WriteMulti (uint8_t *data, uint8_t size)
{
/**** STEPS FOLLOWED  ************
1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
2. Keep Sending DATA to the DR Register after performing the check if the TXE bit is set
3. Once the DATA transfer is complete, Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
*/	
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set 
	while (size)
	{
		while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set 
		I2C1->DR = (uint32_t )*data++;  // send data
		size--;
	}
	
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF to set
}

void I2C_Read (uint8_t Address, uint8_t *buffer, uint8_t size)
{
/**** STEPS FOLLOWED  ************
1. If only 1 BYTE needs to be Read
	a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
	b) the Acknowledge disable is made during EV6 (before ADDR flag is cleared) and the STOP condition generation is made after EV6
	c) Wait for the RXNE (Receive Buffer not Empty) bit to set
	d) Read the data from the DR

2. If Multiple BYTES needs to be read
  a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
	b) Clear the ADDR bit by reading the SR1 and SR2 Registers
	c) Wait for the RXNE (Receive buffer not empty) bit to set
	d) Read the data from the DR 
	e) Generate the Acknowlegment by settint the ACK (bit 10 in SR1)
	f) To generate the nonacknowledge pulse after the last received data byte, the ACK bit must be cleared just after reading the 
		 second last data byte (after second last RxNE event)
	g) In order to generate the Stop/Restart condition, software must set the STOP/START bit 
	   after reading the second last data byte (after the second last RxNE event)
*/		
	
	int remaining = size;
	
/**** STEP 1 ****/	
	if (size == 1)
	{
		/**** STEP 1-a ****/	
		I2C1->DR = Address;  //  send the address
		while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
		
		/**** STEP 1-b ****/	
		I2C1->CR1 &= ~(1<<10);  // clear the ACK bit 
		uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit.... EV6 condition
		I2C1->CR1 |= (1<<9);  // Stop I2C

		/**** STEP 1-c ****/	
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
		
		/**** STEP 1-d ****/	
		buffer[size-remaining] = I2C1->DR;  // Read the data from the DATA REGISTER
		
	}

/**** STEP 2 ****/		
	else 
	{
		/**** STEP 2-a ****/
		I2C1->DR = Address;  //  send the address
		while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
		
		/**** STEP 2-b ****/
		uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit
		
		while (remaining>2)
		{
			/**** STEP 2-c ****/
			while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
			
			/**** STEP 2-d ****/
			buffer[size-remaining] = I2C1->DR;  // copy the data into the buffer			
			
			/**** STEP 2-e ****/
			I2C1->CR1 |= 1<<10;  // Set the ACK bit to Acknowledge the data received
			
			remaining--;
		}
		
		// Read the SECOND LAST BYTE
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = I2C1->DR;
		
		/**** STEP 2-f ****/
		I2C1->CR1 &= ~(1<<10);  // clear the ACK bit 
		
		/**** STEP 2-g ****/
		I2C1->CR1 |= (1<<9);  // Stop I2C
		
		remaining--;
		
		// Read the Last BYTE
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = I2C1->DR;  // copy the data into the buffer
	}	
	
}

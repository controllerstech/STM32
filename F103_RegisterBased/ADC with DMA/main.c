

#include "stm32f10x.h"                  // Device header
#include "Delay_F103.h"
#include "stdio.h"


void ADC_Init (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable ADC and GPIO clock
	2. Set the prescalar in the Clock configuration register (RCC_CFGR)
	3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)
	4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
	5. Set the Sampling Time for the channels in ADC_SMPRx
	6. Set the Regular channel sequence length in ADC_SQR1
	7. Set the Respective GPIO PINs in the Analog Mode
	************************************************/
	
//1. Enable ADC and GPIO clock
	RCC->APB2ENR |= 1<<9;  // enable ADC1 clock
	RCC->APB2ENR |= (1<<2);  // enable GPIOA clock
	
//2. Set the prescalar in the Clock configuration register (RCC_CFGR)	
	RCC->CFGR |= (2<<14);  // Prescaler 6, ADC Clock = 72/6 = 12 MHz  		 
	
//3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)	
	ADC1->CR1 = (1<<8);    // SCAN mode enabled
	// Resolution is 12 bit in F103
	
//4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
	ADC1->CR2 = (1<<1);     // enable continuous conversion mode
	// EOC after each conversion by default
	ADC1->CR2 |= (7<<17);  // External Event selection pointed to SWSTART bit
	ADC1->CR2 &= ~(1<<11);   // Data Alignment RIGHT
	
//5. Set the Sampling Time for the channels	
	ADC1->SMPR2 &= ~((7<<3) | (7<<12));  // Sampling time of 1.5 cycles for channel 1 and channel 4

//6. Set the Regular channel sequence length in ADC_SQR1
	ADC1->SQR1 |= (2<<20);   // SQR1_L =2 for 3 conversions
	
//7. Set the Respective GPIO PINs in the Analog Mode	
	GPIOA->CRL &= ~(0xf<<4);  // analog mode for PA 1
	GPIOA->CRL &= ~(0xf<<16); // analog mode for PA 4
	
	
	/**************************************************************************************************/
	
	
	// Sampling Freq for Temp Sensor 
	ADC1->SMPR1 |= (7<<18);  // Sampling time (71.5 cycles) of 7 us for channel 16.. It should be <17.1 us
	
	// Set the TSVREFE Bit to wake the sensor
	ADC1->CR2 |= (1<<23);
	
	// Enable DMA for ADC
	ADC1->CR2 |= (1<<8);
	
//	// Enable Continuous Request
//	ADC1->CR2 |= (1<<9);
	
	// Channel Sequence
	ADC1->SQR3 |= (1<<0);  // SEQ1 for Channel 1
	ADC1->SQR3 |= (4<<5);  // SEQ2 for CHannel 4
	ADC1->SQR3 |= (16<<10);  // SEQ3 for CHannel 16
}


void ADC_Enable (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable the ADC by setting ADON bit in CR2
	2. Wait for ADC to stabilize (approx 10us) 
	************************************************/
	ADC1->CR2 |= 1<<0;   // ADON =1 enable ADC1
	
	uint32_t delay = 10000;
	while (delay--);
}

void ADC_Start(void)
{	
	/************** STEPS TO FOLLOW *****************
	1. Clear the Status register
	2. Start the Conversion by Setting the SWSTART bit in CR2
	*************************************************/
	ADC1->SR = 0;                      // Clear Status register
	ADC1->CR2 |= (1<<20);              // Conversion on external event enabled
	ADC1->CR2 |= 1<<22;                // Start conversion
}

void DMA_Init (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable DMA clock
	2. Set the DATA Direction
	3. Enable/Disable the Circular Mode
	4. Enable/Disable the Memory Increment and Peripheral Increment
	5. Set the Data Size
	6. Select the channel for the Stream
	************************************************/
	
	// 1. Enable DMA1 Clock
	RCC->AHBENR |= 1<<0;
	
	// 2. Set the Data Direction
//	DMA1_Channel7->CCR |= (1<<4);   // Read From Memory
	DMA1_Channel1->CCR &= ~(1<<4);   // Read From Peripheral
	
	// 2. Enable the circular mode (CIRC)
	DMA1_Channel1->CCR |= 1<<5;
	
	// 3. Enable the Memory Increment (MINC)
	DMA1_Channel1->CCR |= 1<<7;
	
	// 4. Set the Peripheral data size (PSIZE)
	DMA1_Channel1->CCR |= (1<<8);  // 01 : 8 Bit Data
	
	// 5. Set the Memory data size (MSIZE)
	DMA1_Channel1->CCR |= (1<<10);  // 01 : 8 Bit Data
}


void DMA_Config (uint32_t srcAdd, uint32_t destAdd, uint16_t size)
{
	
	/************** STEPS TO FOLLOW *****************
	1. Set the Data Size in the CNDTR Register
	2. Set the Peripheral Address and the Memory Address
	3. Enable the DMA Stream
		 
		 Some peripherals don't need a start condition, like UART, So as soon as you enable the DMA, the transfer will begin
		 While Peripherals like ADC needs the Start condition, so Start the ADC later in the program, to enable the transfer
	************************************************/
	
	DMA1_Channel1->CNDTR = size;   // Set the size of the transfer
	
	DMA1_Channel1->CPAR = srcAdd;  // Source address is peripheral address
	
	DMA1_Channel1->CMAR = destAdd;  // Destination Address is memory address
	
	// Enable the DMA Stream
	DMA1_Channel1->CCR |= (1<<0);  // EN =1
}


uint16_t RxData[3];
float Temperature;

int main(void)
{
	SystemInit();
	TIM2_Config();
	
	ADC_Init ();
	ADC_Enable ();
	DMA_Init ();
	
	DMA_Config ((uint32_t ) &ADC1->DR, (uint32_t) RxData, 3);
	
	ADC_Start ();
	
	while (1)
	{
		
		Temperature = ((1.43 - ((float)(3.3*RxData[2]/(float)4095))) / 0.0043) + 25;
		
		Delay_ms (1000);
	}
	
}

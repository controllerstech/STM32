/*
 * uartRingBufDMA.c
 *
 *  Created on: Aug 12, 2021
 *      Author: controllerstech.com
 */


#include "stm32f4xx_hal.h"
#include "uartRingBufDMA.h"
#include "string.h"

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

#define UART huart1
#define DMA hdma_usart1_rx

/* Define the Size Here */
#define RxBuf_SIZE 512
#define MainBuf_SIZE 1024

uint8_t RxBuf[RxBuf_SIZE];
uint8_t MainBuf[MainBuf_SIZE];

uint16_t oldPos = 0;
uint16_t newPos = 0;

uint16_t Head, Tail;

int isDataAvailable = 0;

int isOK = 0;

/* Timeout is in milliseconds */
int32_t TIMEOUT = 0;

/* Initialize the Ring Buffer */
void Ringbuf_Init (void)
{
	memset(RxBuf, '\0', RxBuf_SIZE);
	memset(MainBuf, '\0', MainBuf_SIZE);

	Head = Tail = 0;
	oldPos = 0;
	newPos = 0;

  HAL_UARTEx_ReceiveToIdle_DMA(&UART, RxBuf, RxBuf_SIZE);
  __HAL_DMA_DISABLE_IT(&DMA, DMA_IT_HT);
}

/* Resets the Ring buffer */
void Ringbuf_Reset (void)
{
	memset(MainBuf,'\0', MainBuf_SIZE);
	memset(RxBuf, '\0', RxBuf_SIZE);
	Tail = 0;
	Head = 0;
	oldPos = 0;
	newPos = 0;
	isOK = 0;
}

/* checks, if the entered string is present in the given buffer ?
 * Returns 1 on Success
 * Returns 0 on Failure
 * */
uint8_t checkString (char *str, char *buffertolookinto)
{
	int stringlength = strlen (str);
	int bufferlength = strlen (buffertolookinto);
	int so_far = 0;
	int indx = 0;
repeat:
	while (str[so_far] != buffertolookinto[indx])
	{
		indx++;
		if (indx>bufferlength) return 0;
	}

	if (str[so_far] == buffertolookinto[indx])
	{
		while (str[so_far] == buffertolookinto[indx])
		{
			so_far++;
			indx++;
		}
	}

	if (so_far != stringlength)
	{
		so_far =0;
		if (indx >= bufferlength) return 0;
		goto repeat;
	}

	if (so_far == stringlength) return 1;
	else return 0;
}


/* waits for a particular string in the Rx Buffer
 * By Default it is set to wait for "OK", you can change the string in the HAL_UARTEx_RxEventCallback function
 * This function will wait in the blocking mode, so to avoid the halt, we will also include the timeout
 * The timeout is in milliseconds
 * returns 1 on success
 * returns 0 on failure
 * */
uint8_t isConfirmed (int32_t Timeout)
{
	TIMEOUT = Timeout;
	while ((!isOK)&&(TIMEOUT));
	isOK = 0;
	if (TIMEOUT <= 0) return 0;
	return 1;
}



/* Waits for a particular string to arrive in the incoming buffer... It also increments the tail
 * returns 1, if the string is detected
 * return 0, in case of the timeout
 */
int waitFor (char *string, uint32_t Timeout)
{
	int so_far =0;
	int len = strlen (string);

	TIMEOUT = Timeout;

	while ((Tail==Head)&&TIMEOUT);  // let's wait for the data to show up
	isDataAvailable = 0;

again:

	/* If the data doesn't show up, then return 0 */
	if (TIMEOUT <= 0) return 0;


	/* if the incoming data does not match with the string, we will simply increment the index
	 * And wait for the string to arrive in the incoming data
	 * */
	while (MainBuf[Tail] != string[so_far])  // peek in the rx_buffer to see if we get the string
	{
		if (TIMEOUT <= 0) return 0;


		if (Tail == Head) goto again;
		Tail++;

		if (Tail==MainBuf_SIZE) Tail = 0;
	}

	/* If the incoming data does match with the string, we will return 1 to indicate this */
	while (MainBuf[Tail] == string[so_far]) // if we got the first letter of the string
	{
		if (TIMEOUT <= 0) return 0;
		so_far++;

		if (Tail == Head) goto again;
		Tail++;
		if (Tail==MainBuf_SIZE) Tail = 0;
		if (so_far == len) return 1;
	}

//	if (so_far != len)
//	{
//		so_far = 0;
//		goto again;
//	}

	HAL_Delay (100);

	if ((so_far!=len)&&isDataAvailable)
	{
		isDataAvailable = 0;
//		so_far = 0;
		goto again;
	}
	else
	{
		so_far = 0;
		goto again;
	}


	return 0;
}


/* copies the data from the incoming buffer into our buffer
 * Must be used if you are sure that the data is being received
 * it will copy irrespective of, if the end string is there or not
 * if the end string gets copied, it returns 1 or else 0
 *
 */
int copyUpto (char *string, char *buffertocopyinto, uint32_t Timeout)
{
	int so_far =0;
	int len = strlen (string);
	int indx = 0;

	TIMEOUT = Timeout;
	while ((Tail==Head)&&TIMEOUT);
	isDataAvailable = 0;
again:

	if (TIMEOUT<=0) return 0;

	/* Keep copying data until the string is found in the incoming data */
	while (MainBuf[Tail] != string [so_far])
	{
		buffertocopyinto[indx] = MainBuf[Tail];

		if (Tail == Head) goto again;
		Tail++;
		indx++;
		if (Tail==MainBuf_SIZE) Tail = 0;
	}

/* If the string is found, copy it and return 1
 * or else goto again: and keep copying
 */
	while (MainBuf[Tail] == string [so_far])
	{
		so_far++;
		buffertocopyinto[indx++] = MainBuf[Tail++];
		if (Tail==MainBuf_SIZE) Tail = 0;
		if (so_far == len) return 1;
	}

	HAL_Delay (100);

	if ((so_far!=len)&&isDataAvailable)
	{
		isDataAvailable = 0;
//		so_far = 0;
		goto again;
	}
	else
	{
		so_far = 0;
		goto again;
	}
    return 0;
}



/* Copies the entered number of characters, after the entered string (from the incoming buffer), into the buffer
 * returns 1, if the string is copied
 * returns 0, in case of the timeout
 */
int getAfter (char *string, uint8_t numberofchars, char *buffertocopyinto, uint32_t Timeout)
{
	if ((waitFor(string, Timeout)) != 1) return 0;
//	TIMEOUT = Timeout/3;
//	while (TIMEOUT > 0);
	HAL_Delay (100);
	for (int indx=0; indx<numberofchars; indx++)
	{
		if (Tail==MainBuf_SIZE) Tail = 0;
		buffertocopyinto[indx] = MainBuf[Tail++];  // save the data into the buffer... increments the tail
	}
	return 1;
}


/* Copies the data between the 2 strings from the source buffer into the destination buffer
 * It does not copy the start string or the end string..
 */

void getDataFromBuffer (char *startString, char *endString, char *buffertocopyfrom, char *buffertocopyinto)
{
	int startStringLength = strlen (startString);
	int endStringLength   = strlen (endString);
	int so_far = 0;
	int indx = 0;
	int startposition = 0;
	int endposition = 0;

repeat1:

	while (startString[so_far] != buffertocopyfrom[indx]) indx++;
	if (startString[so_far] == buffertocopyfrom[indx])
	{
		while (startString[so_far] == buffertocopyfrom[indx])
		{
			so_far++;
			indx++;
		}
	}

	if (so_far == startStringLength) startposition = indx;
	else
	{
		so_far =0;
		goto repeat1;
	}

	so_far = 0;

repeat2:

	while (endString[so_far] != buffertocopyfrom[indx]) indx++;
	if (endString[so_far] == buffertocopyfrom[indx])
	{
		while (endString[so_far] == buffertocopyfrom[indx])
		{
			so_far++;
			indx++;
		}
	}

	if (so_far == endStringLength) endposition = indx-endStringLength;
	else
	{
		so_far =0;
		goto repeat2;
	}

	so_far = 0;
	indx=0;

	for (int i=startposition; i<endposition; i++)
	{
		buffertocopyinto[indx] = buffertocopyfrom[i];
		indx++;
	}
}




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
		isDataAvailable = 1;

		oldPos = newPos;  // Update the last position before copying new data

		/* If the data in large and it is about to exceed the buffer size, we have to route it to the start of the buffer
		 * This is to maintain the circular buffer
		 * The old data in the main buffer will be overlapped
		 */
		if (oldPos+Size > MainBuf_SIZE)  // If the current position + new data size is greater than the main buffer
		{
			uint16_t datatocopy = MainBuf_SIZE-oldPos;  // find out how much space is left in the main buffer
			memcpy ((uint8_t *)MainBuf+oldPos, (uint8_t *)RxBuf, datatocopy);  // copy data in that remaining space

			oldPos = 0;  // point to the start of the buffer
			memcpy ((uint8_t *)MainBuf, (uint8_t *)RxBuf+datatocopy, (Size-datatocopy));  // copy the remaining data
			newPos = (Size-datatocopy);  // update the position
		}

		/* if the current position + new data size is less than the main buffer
		 * we will simply copy the data into the buffer and update the position
		 */
		else
		{
			memcpy ((uint8_t *)MainBuf+oldPos, (uint8_t *)RxBuf, Size);
			newPos = Size+oldPos;
		}

		/* Update the position of the Head
		 * If the current position + new size is less then the buffer size, Head will update normally
		 * Or else the head will be at the new position from the beginning
		 */
		if (Head+Size < MainBuf_SIZE) Head = Head+Size;
		else Head = Head+Size - MainBuf_SIZE;

		/* start the DMA again */
		HAL_UARTEx_ReceiveToIdle_DMA(&UART, (uint8_t *) RxBuf, RxBuf_SIZE);
		__HAL_DMA_DISABLE_IT(&DMA, DMA_IT_HT);


	/****************** PROCESS (Little) THE DATA HERE *********************
	 * This is the PART OF  "isConfirmed" Function
	 */

	/* Let's say we want to check for the keyword "OK" within our incoming DATA */
	for (int i=0; i<Size; i++)
	{
		if ((RxBuf[i] == 'O') && (RxBuf[i+1] == 'K'))
		{
			isOK = 1;
		}
	}
}








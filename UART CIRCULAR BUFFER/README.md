## UART CIRCULAR BUFFER with DMA

1. In the CubeMX, enable the UART interrupt
2. In the DMA section, use the NORMAL mode.
3. Change the UART and the DMA in the ``uartRingBufDMA.c`` file
4. Define the RxBuf and MainBuf Sizes
5. check how the timeout is defined as the external variable in the STM32xxxxIT.c file. Also put the ```TIMEOUT--``` in the systick handler
6. The functions are commented as per their usage, you can read them.

### CORTEX M7 Users needs to be careful about memory management. You can check out the video series on the same below 
https://www.youtube.com/playlist?list=PLfIJKC1ud8gjoY2McCCqkxXWuwiC2iSap

## I will soon Release a Video on this Topic

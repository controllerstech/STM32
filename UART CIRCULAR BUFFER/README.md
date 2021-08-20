## UART CIRCULAR BUFFER with DMA

1. In the CubeMX, enable the UART interrupt
2. In the DMA section, use the NORMAL mode.
3. ``` IN the Generated code, make sure the DMA is initialized before the UART. CubeMX sometimes does the opposite and in that case, DMA won't work.```
4. Change the UART and the DMA in the ``uartRingBufDMA.c`` file
5. Define the RxBuf and MainBuf Sizes
6. check how the timeout is defined as the external variable in the STM32xxxxIT.c file. Also put the ```TIMEOUT--``` in the systick handler
7. check the main file to see the usage of the functions
8. The functions are commented as per their usage, you can read them.

### CORTEX M7 Users needs to be careful about memory management. You can check out the video series on the same below 
https://www.youtube.com/playlist?list=PLfIJKC1ud8gjoY2McCCqkxXWuwiC2iSap

## Check out the Video on Usage and application https://youtu.be/ly3_JEC_d9w

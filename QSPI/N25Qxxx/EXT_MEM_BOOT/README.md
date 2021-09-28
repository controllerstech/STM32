
# How to boot from external flash memory

## Following are the steps after creating a new project

1. Open the `system_stm32xxxx.c` file, goto System_Init, and add the following code to it.

   `RCC->CFGR = 0;   // Reset the configuration register`
   
   `SCB->VTOR = QSPI_BASE;   // 0x90000000`
 
2. Open the `Flash.ld` script file, and change the FLASH address to the QSPI FLASH. Also change the size 

   `FLASH    (rx)    : ORIGIN = 0x90000000,   LENGTH = 16M`
 
3. In the Debug configuration, goto debugger tab, and towards the bottom check the `external loader`. 

   Click scan, select the board, and click apply
   
4. The Application will run from the External memory now.   

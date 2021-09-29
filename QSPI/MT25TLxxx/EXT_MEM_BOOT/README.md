
# How to boot from external flash memory

## Following are the steps after creating a new project

1. If you are here, means you have already enabled the MEMORY MAPPED MODE. 
2. Now you have to create a new project, which will boot from the external Flash.
3. Open the `system_stm32xxxx.c` file, goto System_Init, and add the following code to it.

   `RCC->CFGR = 0;   // Reset the configuration register`
   
   `SCB->VTOR = QSPI_BASE;   // 0x90000000`
 
4. Open the `Flash.ld` script file, and change the FLASH address to the QSPI FLASH. Also change the size 

   `FLASH    (rx)    : ORIGIN = 0x90000000,   LENGTH = 16M`
 
5. In the Debug configuration, goto debugger tab, and towards the bottom check the `external loader`. 

   Click scan, select the board, and click apply
   
6. The Application will run from the External memory now.   


## Check out the Respective files if you don't understand the steps. Also check the .ioc file for the MPU Configuration

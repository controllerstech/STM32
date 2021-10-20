
# How to write and Read data to MT25 Flash memory using the QSPI

The steps are commented out in the main file itself

The code is written for the MT25TL01G. But This part works fine for the 512 Mb Flash memories too.

To make it work for 512 Mb Flash, follow the steps below

1. Change the FLASH SIZE in the MT25TL01G.h file.
2. Change the `MT25TL01G_DUMMY_CYCLES_READ_QUAD`, `MT25TL01G_DUMMY_CYCLES_READ`, `CONF_QSPI_DUMMY_CLOCK` to 10. These defines are in the beginning of the MT25TL01G.h 
3. That's it.


__________________________________________________________________________________________________________________


# How to configure MT25 in the memory mapped mode 

The steps are commented out in the main file itself

You have to also use the Folder `EXT_MEM_BOOT` to boot from the External flash.
Read the README File inside that folder for more details

This part only works with MT25TL01G with the `DUAL FLASH MODE ENABLED`.

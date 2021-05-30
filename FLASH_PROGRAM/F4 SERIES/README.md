# How to write data in the FLASH memory of ```F4 Series``` MCU


1. Rewrite the Sectors according to your reference manual
2. Do not program the initial addresses (around 0x08000000). This is where the program is stored.

## Always Refer to the manual, as some sectors are write protected.

To watch the video, goto https://youtu.be/dqfgxS3D1k0

To read the content, goto https://controllerstech.com/flash-programming-in-stm32/

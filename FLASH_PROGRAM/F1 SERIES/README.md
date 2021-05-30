# How to write data in the FLASH memory of ```F1 Series``` MCU


1. Rewrite the PAGES according to your reference manual
2. Do not program the initial addresses (around 0x08000000). This is where the program is stored.

## Always Refer to the manual, as some sectors are write protected.

To watch the video, goto https://youtu.be/BKgh896Bj8Q

To read the content, goto https://controllerstech.com/flash-programming-in-stm32/

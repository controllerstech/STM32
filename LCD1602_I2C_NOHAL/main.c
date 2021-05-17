

#include "RccConfig.h"
#include "Delay.h"
#include "I2C.h"
#include "i2c-lcd.h"


int main ()
{
	SysClockConfig ();
	TIM6Config ();
	I2C_Config ();	
	
	lcd_init ();
	lcd_put_cur (0,0);
	lcd_send_string ("hello");
	while (1)
	{
		
	}
}


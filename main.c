#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "stdint.h"

#define LCD_DATA GPIOB
#define LCD_CTRL GPIOA



#define RS 0x00 /* PORTA BIT5 mask */
#define RW 0x01 /* PORTA BIT6 mask */
#define EN 0x02 /* PORTA BIT7 mask */ 

void SystemInit(void)
{
}

void delayMs(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3180; j++)
		{
		} /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3; j++)
		{
		} /* do nothing for 1 us */
}


void LCD_command(unsigned char command)
{
	GPIO_PORTB_DATA_R = 0; /* RS = 0, R/W = 0 */
	GPIO_PORTA_DATA_R = command;
	GPIO_PORTB_DATA_R = EN; /* pulse E */
	delayUs(0);
	GPIO_PORTB_DATA_R = 0;
	if (command < 4)
		delayMs(2); /* command 1 and 2 needs up to 1.64ms */
	else
		delayUs(45); /* all others 40 us */
}


void LCD_Data(unsigned char data)
{
	GPIO_PORTB_DATA_R = RS;
	GPIO_PORTA_DATA_R = data;
	GPIO_PORTB_DATA_R |= EN;
	delayUs(0);
	GPIO_PORTB_DATA_R = 0;
	delayUs(45);

}


void init()
{
	uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x03;
	delay = 1;


	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R = 0xFF;
	GPIO_PORTA_DIR_R = 0xFF;
	GPIO_PORTA_DEN_R = 0xFF;
	GPIO_PORTA_AMSEL_R = 0;
	GPIO_PORTA_AFSEL_R = 0;
	GPIO_PORTA_PCTL_R = 0;

	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R = 0x07;
	GPIO_PORTB_DIR_R |= 0x07;
	GPIO_PORTB_DEN_R |= 0x07;
	GPIO_PORTB_AMSEL_R = 0;
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_PCTL_R = 0;


	delayMs(20); /* initialization sequence */
	LCD_command(0x30);
	delayMs(5);
	LCD_command(0x30);
	delayUs(100);
	LCD_command(0x30);
	LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
	LCD_command(0x06); /* move cursor right */
	LCD_command(0x01); /* clear screen, move cursor to home */
	LCD_command(0x0F); /* turn on display, cursor blinking */


}




int main()
{
	init();

	while (1)
	{

		LCD_command(1);	/* clear display */
		LCD_command(0x80); /* lcd cursor location  to write open at center of the screen*/
		delayMs(500);
		LCD_Data ('A');


	}

	return 0;
}

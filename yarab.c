#include "C:/Keil/EE319KwareSpring2020/inc/tm4c123gh6pm.h"
#include "stdint.h"

void keypad_init(void);
void PORTC_init (void); //KEYPAD_INPUT
void PORTD_init (void); //KEYPAD_OUTPUT
void PORTF_init (void);
int  key_pressed(void);
char get_char		(void);
void delayMs		(int n);
void delayUs		(int n);


char keys[4][4]=
{
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
	
void SystemInit(){}
int main()
{	char c = 0;
	PORTF_init();
	keypad_init();
	
	while(1)
	{
		if(key_pressed())
			c = get_char();
		
		if 		 (c == '1')
			GPIO_PORTF_DATA_R = 0x02;
		else if(c == '2')
			GPIO_PORTF_DATA_R = 0x04;
		else if(c == '3')
			GPIO_PORTF_DATA_R = 0x06;
		else if(c == '4')
			GPIO_PORTF_DATA_R = 0x08;
		else if(c == '5')
			GPIO_PORTF_DATA_R = 0x0A;
		else if(c == '6')
			GPIO_PORTF_DATA_R = 0x0C;
		else if(c == '7')
			GPIO_PORTF_DATA_R = 0x0E;
		
	}	
	
}
void PORTF_init(void)
{
	SYSCTL_RCGCGPIO_R |=(1<<5);//ENABLE CLOCK FOR PORT F
	delayUs(3);
	GPIO_PORTF_LOCK_R = 0x4C4F434B; 
	GPIO_PORTF_CR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_DIR_R |= 0x0E;
	
}
void PORTD_init(void)
{
	
	SYSCTL_RCGCGPIO_R |=(1<<3);//ENABLE CLOCK FOR PORT D
	delayUs(3);
	GPIO_PORTD_LOCK_R = 0x4C4F434B; 
	GPIO_PORTD_CR_R = 0x0F;
	GPIO_PORTD_AFSEL_R = 0;
	GPIO_PORTD_PCTL_R = 0;
	GPIO_PORTD_AMSEL_R = 0;
	GPIO_PORTD_DEN_R |= 0x0F;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_ODR_R |= 0x0F;
}
void PORTC_init(void)
{
	
	SYSCTL_RCGCGPIO_R |=(1<<2);
	delayUs(3);
	GPIO_PORTC_LOCK_R = 0x4C4F434B; 
	GPIO_PORTC_CR_R = 0xF0;
	GPIO_PORTC_AFSEL_R = 0;
	GPIO_PORTC_PCTL_R = 0;
	GPIO_PORTC_AMSEL_R = 0;
	GPIO_PORTC_DEN_R |= 0xF0;
	GPIO_PORTC_DIR_R &= 0x0F;
	GPIO_PORTC_PUR_R |= 0xF0;
}

void keypad_init(void)
{

		PORTD_init(); // ROWS
		PORTC_init(); // COLUMNS
	
	
}
int key_pressed(void)
{
		delayMs(30);
		GPIO_PORTD_DATA_R &=0xF0;
		delayUs(3);
		if ((GPIO_PORTC_DATA_R & 0xF0) == 0xF0)
			return 0;
		else
			return 1;
		
//				char key = get_char();
//		do{
//			while(key_pressed() != 0);
//			delayMs(30); /* wait to debounce */
//		}while(key_pressed() != 0);
//		
//		do{
//			key = key_pressed();
//			delayMs(30); /* wait to debounce */
//		}while(key_pressed() != key);
//		return 1;
}

char get_char(void)
{
	
	int row,col;
	while (1)
		
{
	row = 0;
	GPIO_PORTD_DATA_R |= 0x0E; /* enable row 0 */
	delayUs(3); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0) break;
	
	row = 1;
	GPIO_PORTD_DATA_R |= 0x0D; /* enable row 1 */
	delayUs(3); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0) break;
	
	
	row = 2;
	GPIO_PORTD_DATA_R |= 0x0B; /* enable row 2 */
	delayUs(3); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0) break;
	
	row = 3;
	GPIO_PORTD_DATA_R |= 0x07; /* enable row 3 */
	delayUs(3); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0) break;
}
if (col == 0xE0) return keys[row][0]; /* key in column 0 */
if (col == 0xD0) return keys[row][1]; /* key in column 1 */
if (col == 0xB0) return keys[row][2]; /* key in column 2 */
if (col == 0x70) return keys[row][3]; /* key in column 3 */

}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3180; j++)
{} /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} /* do nothing for 1 us */
}


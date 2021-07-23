#include <stdint.h>
#include "lcd.h"
#include "screen.h"

void main()
{
    dataUpdate Data,Data1;
    GPIO_LcdInit();
    LCD_init();
    LCD_clr();
    mainScreen(); 
    while(1)
    {          
        updateData(Data);
        delay(20000);
        updateData(Data1);
        delay(20000);
        updateData(Data);
        delay(20000);
        updateData(Data1);
        delay(5000);
    }
      
}
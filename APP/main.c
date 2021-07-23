#include <stdint.h>
#include "lcd.h"
#include "screen.h"

void main()
{
    dataUpdate Data,Data1;
    GPIO_LcdInit();
    lcd_init();
    lcd_clr();
    mainScreen(); 
    
    while(1)
    {          
        updateData(Data);
        delay(20000);
        updateData(Data1);
        delay(20000);
    }
      
}
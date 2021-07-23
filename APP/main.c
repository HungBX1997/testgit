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
    
    Data.DataCalo=10.7;
    Data.DataDistance=2.5;
    Data.DataSpeed=25.6;
    Data.DataTime.Second=2400;
    Data.Incline=9;   
    
    while(1)
    {          
        updateData(Data);
        delay(20000);
        updateData(Data1);
        delay(20000);
    }
      
}
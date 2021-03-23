#include <stdint.h>
#include "lcd.h"
#include "screen.h"

void main()
{
    dataUpdate data,data1;
    GPIO_LcdInit();
    lcd_init();
    lcd_clr();
    mainScreen();
    
    data.dataCalo=10.7;
    data.dataDistance=2.5;
    data.dataSpeed=25.6;
    data.dataTime.second=2400;
    data.incline=9;
    
    data1.dataCalo=70.1;
    data1.dataDistance=52.5;
    data1.dataSpeed=16.9;
    data1.dataTime.second=3500;
    data1.incline=14;
    
    while(1)
    {          
        updateData(data);
        delay(20000);
        updateData(data1);
        delay(20000);
    }
      
}
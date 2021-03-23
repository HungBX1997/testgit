#include <stdint.h>
#include "lcd.h"
#include "screen.h"

static void Screen_convertData(float dataIn, unsigned char* dataOut)
{
    int i;
    uint32_t ch[3];
    uint32_t b = (uint32_t)(dataIn * 10);
    ch[0]=b/100 ;
    ch[1]=(b-ch[0]*100)/10;
    ch[2]=(b-ch[0]*100-ch[1]*10);
    for(i=0;i<3;i++)
    {
        dataOut[i]=ch[i]+'0';
    }
}

static void timeScreenSecond(uint32_t second)
{
    unsigned char factorSecond[2]={'\0','\0'};
    factorSecond[0]=second%10+'0';
    factorSecond[1]=second/10+'0';
    lcd_send_data(&factorSecond[1],ADD_TIME_SECOND_1);
    lcd_send_data(&factorSecond[0],ADD_TIME_SECOND_0);
}

static void timeScreenMinute(uint32_t minute)
{
    unsigned char factorMinute[2]={'\0','\0'};
    factorMinute[0]=minute%10+'0';
    factorMinute[1]=minute/10+'0';
    lcd_send_data(&factorMinute[1],ADD_TIME_MINUTE_1);
    lcd_send_data(&factorMinute[0],ADD_TIME_MINUTE_0);
}

void updateTime(uint32_t time)
{
    uint32_t minute=time/60;
    uint32_t second= time-minute*60;
    timeScreenSecond(second);
    timeScreenMinute(minute);
}

void updateDistance(float dis)
{
    unsigned char dataConvert[3];
    Screen_convertData(dis,dataConvert);
    for(int i = 0; i <3 ; i++)
    {
        lcd_send_data(&dataConvert[i],ADD_DIS_0+2*i);
    }
}

void updateCalo(float cal)
{
    unsigned char dataConvert[3];
    Screen_convertData(cal,dataConvert);
    for(int i = 0; i <3 ; i++)
    {
        lcd_send_data(&dataConvert[i],ADD_CAL_0+2*i);
    }
}

void updateIncline(uint8_t incl)
{
    unsigned char factorIncline[2]={'\0','\0'};
    factorIncline[0]=incl%10+'0';
    factorIncline[1]=incl/10+'0';
    lcd_send_data(&factorIncline[1],ADD_INCL_0);
    lcd_send_data(&factorIncline[0],ADD_INCL_1);
}

void updateSpeed(float speed)
{
    unsigned char dataConvert[3];
    Screen_convertData(speed,dataConvert);
    for(int i = 0; i<3 ; i++)
    {
        lcd_send_data(&dataConvert[i],ADD_SPEED_2-2*i);
    }
}

void updateData(dataUpdate data)
{
    updateCalo(data.dataCalo);
    updateDistance(data.dataDistance);
    updateIncline(data.incline);
    updateTime(data.dataTime.second);
    updateSpeed(data.dataSpeed);
}

void mainScreen()
{
    int i=0;
    for(i = 0; i < 31; i+=2)
    {
         lcd_send_data("0",i);
         delay(1000);
    }
}
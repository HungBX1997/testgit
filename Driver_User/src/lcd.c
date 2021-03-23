#include <stdint.h>
#include "stm32f10x_usart.h"   
#include "stm32f10x_gpio.h" 
#include "lcd.h" 

#define HT1621_CS           GPIO_Pin_8   
#define HT1621_RD           GPIO_Pin_9   
#define HT1621_WR           GPIO_Pin_10   
#define HT1621_DAT          GPIO_Pin_11   
#define ENABLE_CLOCK_GPIOA  (RCC->APB2ENR|=(1<<2))   
   
#define  DAT   1    //����   
#define  COM   0    //����    
   
   
//һ��HT1621 4COM�ĳ��ñ���,��λ��COM0,��4bit��SEG0,��4bit��SEG1   
        //�ڰ���ʾλ      
//  _   
// |_|   ��Ե�8����ʾλ 1--f 2--e 3--d 4--c 5--g 6--b 7--a    
// |_|     
//     
//         
//unsigned char NUM[]={   
//  0x60,0x60,0x60,0xe0,0x60,0xe0,0x60,     // 0x60 -- 1   
//  0x3e,0xbe,0xbe,0x3e,0xbe,0xbe,0xbe,     // 0x3e -- 2   
//  0x7a,0x7a,0xfa,0xfa,0xfa,0xfa,0xfa,     // 0x7a -- 3   
//  0xe3,0x63,0x63,0xe3,0xe3,0xe3,0x63,     // 0x63 -- 4   
//  0xdb,0x5b,0xdb,0xdb,0xdb,0x5b,0xdb,     // 0x5b -- 5   
//  0xdf,0xdf,0xdf,0xdf,0xdf,0x5f,0xdf,     // 0x5f -- 6   
//  0x70,0x70,0x70,0xf0,0x70,0xf0,0xf0,     // 0x70 -- 7   
//  0xff,0xff,0xff,0xff,0xff,0xff,0xff,     // 0x7f -- 8   
//  0xfb,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,     // 0x7b -- 9   
//  0xfd,0xfd,0xfd,0xfd,0x7d,0xfd,0xfd,     // 0x7d -- 0   
//};   
   
/*  
* fq  
* LCD GPIO ��ʼ��  
* ���:void  
* ����:void  
* �õ� GPIOA 4,5,6,7 �ֱ��Ӧlcd CS RD(��ʱ����) WR DAT  
*/   
void GPIO_LcdInit(void)   
{
    ENABLE_CLOCK_GPIOA;
    
    GPIO_InitTypeDef GPIO_InitStruct_LCD;       //GIPOA4~7   
   
    GPIO_InitStruct_LCD.GPIO_Pin    = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;   
    GPIO_InitStruct_LCD.GPIO_Mode   = GPIO_Mode_Out_OD;   
    GPIO_InitStruct_LCD.GPIO_Speed  = GPIO_Speed_50MHz;   
    //GPIO_InitStruct_LCD.GPIO_PuPd   = GPIO_PuPd_UP;   
    //GPIO_InitStruct_LCD.GPIO_OType  = GPIO_OType_PP;   
    GPIO_Init(GPIOA,&GPIO_InitStruct_LCD);   
}   
   
/*  
* fq  
* LCD ģʽд��  
* ���:MODE :COM(����ģʽ) DAT(����ģʽ)  
* ����:void  
*  
*/   
   
void write_mode(unsigned char MODE) //д��ģʽ,����or����   
{   
    GPIO_ResetBits(GPIOA,HT1621_WR);                                //  RW = 0;   
    delay(10);   
    GPIO_SetBits(GPIOA,HT1621_DAT);                                 //  DA = 1;   
    GPIO_SetBits(GPIOA,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
       
    GPIO_ResetBits(GPIOA,HT1621_WR);                                //  RW = 0;   
    delay(10);   
    GPIO_ResetBits(GPIOA,HT1621_DAT);                               //  DA = 0;   
    GPIO_SetBits(GPIOA,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
       
    GPIO_ResetBits(GPIOA,HT1621_WR);                                //  RW = 0;   
    delay(10);   
   
    if(0==MODE)   
    {   
        GPIO_ResetBits(GPIOA,HT1621_DAT);                           //  DA = 0;   
    }   
    else   
    {   
        GPIO_SetBits(GPIOA,HT1621_DAT);                             //  DA = 1;   
    }   
    delay(10);   
    GPIO_SetBits(GPIOA,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
}   
   
/*  
* fq  
* LCD ����д�뺯��  
* ���:cbyte ,����������  
* ����:void  
*  
*/   
   
void write_command(unsigned char Cbyte)                             //д�������9bit,���1bitû��   
{   
    unsigned char i;   
    for(i=0;i<8;i++)   
    {   
        GPIO_ResetBits(GPIOA,HT1621_WR);                            //  RW = 0;   
        delay(10);   
   
        if((Cbyte>>(7-i)) & 0x01)   
        {   
            GPIO_SetBits(GPIOA,HT1621_DAT);                         //  DA = 1;   
        }   
        else   
        {   
            GPIO_ResetBits(GPIOA,HT1621_DAT);                       //  DA = 0;   
        }   
        delay(10);   
        GPIO_SetBits(GPIOA,HT1621_WR);                              //  RW = 1;   
        delay(10);   
    }   
    GPIO_ResetBits(GPIOA,HT1621_WR);                                //  RW = 0;   
    delay(10);   
    GPIO_ResetBits(GPIOA,HT1621_DAT);                               //  DA = 0; ��9bit,������,���Ǳ���д��   
    GPIO_SetBits(GPIOA,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
}   
   
/*  
* fq  
* LCD ��ַд�뺯��  
* ���:cbyte ,��ַ  
* ����:void  
*  
*/   
void write_address(unsigned char Abyte)                             //д��ַ6bit   
{   
    unsigned char i;   
    Abyte = Abyte<<2;   
    for(i=0;i<6;i++)   
    {   
        GPIO_ResetBits(GPIOA,HT1621_WR);                            //  RW = 0;   
        delay(10);   
   
        if((Abyte>>(7-i)) & 0x01)   
        {   
            GPIO_SetBits(GPIOA,HT1621_DAT);                         //  DA = 1;   
        }   
        else   
        {   
            GPIO_ResetBits(GPIOA,HT1621_DAT);                       //  DA = 0;   
        }   
        delay(10);   
        GPIO_SetBits(GPIOA,HT1621_WR);                              //  RW = 1;   
        delay(10);   
    }   
}   
/*  
* fq  
* LCD ����д�뺯��  
* ���:Dbyte ,����  
* ����:void  
*  
*/   
void write_data(unsigned char Dbyte)    //д����   
{   
    int i;   
    for(i=0;i<8;i++)   
    {   
        GPIO_ResetBits(GPIOA,HT1621_WR);                            //  RW = 0;   
        delay(10);   
   
        if((Dbyte>>(7-i)) & 0x01)   
        {   
            GPIO_SetBits(GPIOA,HT1621_DAT);                         //  DA = 1;   
        }   
        else   
        {   
            GPIO_ResetBits(GPIOA,HT1621_DAT);                       //  DA = 0;   
        }   
        delay(10);   
        GPIO_SetBits(GPIOA,HT1621_WR);                              //  RW = 1;   
        delay(10);   
    }   
}   
/*  
* fq  
* LCD ģ���ڲ�ר����ʱ����  
* ���:ms  
* ����:void  
*  
*/   
void delay(uint32_t MS)                                         //��ʱ   
{   
    unsigned char us,usn;   
    while(MS!=0)   
    {    
        usn = 2;   
        while(usn!=0)   
        {   
            us=0xf2;   
            while (us!=0){us--;};   
            usn--;   
        }   
        MS--;   
    }   
}   

/*  
* fq  
* LCD ��ʼ������lcd��������ʼ������  
* ���:void  
* ����:void  
*  
*/   
void lcd_init( void )                                               //��ʼ��   
{   
    GPIO_ResetBits(GPIOA,HT1621_CS);                                //CS = 0;   
    write_mode(COM);        //����ģʽ   
    write_command(0x01);    //Enable System   
    write_command(0x03);    //Enable Bias   
    write_command(0x04);    //Disable Timer   
    write_command(0x05);    //Disable WDT   
    write_command(0x08);    //Tone OFF   
    write_command(0x18);    //on-chip RC��   
    write_command(0x29);    //1/4Duty 1/3Bias   
    write_command(0x80);    //Disable IRQ   
    write_command(0x40);    //Tone Frequency 4kHZ   
    write_command(0xE3);    //Normal Mode   
    GPIO_SetBits(GPIOA,HT1621_CS);                                  //CS = 1;   
}   
/*  
* fq  
* LCD ������ʾ����  
* ���:��ʾ�������飬n ��ʾ��������  
* ����:void  
*  
*/   
void full_ram(unsigned char *puts,unsigned char n)   
{   
    unsigned char i;   
       
    GPIO_ResetBits(GPIOA,HT1621_CS);                                // CS = 0;   
    write_mode(DAT);   
    write_address(0);   
    for(i=0;i<15;i++)   
    {   
        write_data(puts[15*n+i]);   
        delay(4);   
    }      
    GPIO_SetBits(GPIOA,HT1621_CS);                                  //CS = 1;   
}   
/*  
* fq  
* LCD ����д�뺯��  
* ���:puts ����ʾ���ַ���,����Ϊ7���������������򳬳�������Ч��������������룬��: "12234567"  
* ����:void  
*  
*/   
   

void lcd_show_data(unsigned char *puts)   
{   
    unsigned char i ;   
       
    GPIO_ResetBits(GPIOA,HT1621_CS);                                // CS = 0;   
    write_mode(DAT);   
    write_address(0);   
       
    for(i=0;i<1;i++)   
    {   
        write_data(puts[i]);   
        delay(4);   
    }   
    GPIO_SetBits(GPIOA,HT1621_CS);                                  //CS = 1;   
}
/*  
* fq  
* LCD ����ʵ����ʱ����  
* ���:times  
* ����:void  
*  
*/   
void lcd_delay(int times)   
{   
    int i;   
    for(i=0;i<20*times;i++) ;   
}   
   
/*  
* fq  
* LCD ��������  
* ���:times  
* ����:void  
*  
*/   
   
void lcd_clr(void)   
{   
    unsigned char i;   
       
    GPIO_ResetBits(GPIOA,HT1621_CS);                                // CS = 0;   
    write_mode(DAT);   
    write_address(0);   
       
    for(i=0;i<16;i++)   
    {   
        write_data(0x00);   
    }      
    GPIO_SetBits(GPIOA,HT1621_CS);                                  //CS = 1;   
}   
   
/*  
* fq  
* ����ܱʶκ���  
* ���:void  
* ����:void  
*  
*/   
#if 1  
    unsigned char HT1621[]={   
       
        0x81,0x01,0x01,0x01,0x01,0x01,0x01,   
        0x02,0x02,0x02,0x02,0x82,0x02,0x02,   
        0x04,0x84,0x04,0x04,0x04,0x04,0x04,   
        0x08,0x08,0x88,0x08,0x08,0x08,0x08,   
        0x10,0x10,0x10,0x10,0x10,0x10,0x90,   
        0x20,0x20,0x20,0x20,0x20,0xa0,0x20,   
        0x40,0x40,0x40,0xc0,0x40,0x40,0x40,   
        };   
       
void test_line(void)   
{   
    int i ;   
    for(i=0;i<7;i++)   
    {   
        full_ram(HT1621,i);   
        lcd_delay(1000000);   
    }   
    GPIO_ResetBits(GPIOA,HT1621_CS);                                // CS = 0;   
   
    write_mode(COM);   
    GPIO_SetBits(GPIOA,HT1621_CS);                                  //CS = 1;   
}      
#endif   
   
/*  
* fq  
* LCD ����д�뺯��������ӿ�  
* ���:data ����ʾ���ַ���,����Ϊ7���������������򳬳�������Ч��������������룬��: "12234567"  
* ����:void  
*  
*/ 
void lcd_show_data1(unsigned char *puts,uint8_t address)   
{   
    unsigned char i ;   
       
    GPIO_ResetBits(GPIOA,HT1621_CS);                                // CS = 0;   
    write_mode(DAT);   
    write_address(address);   
       
    for(i=0;i<SIZE_BUFF;i++)   
    {   
        write_data(puts[i]);   
        delay(4);   
    }   
    GPIO_SetBits(GPIOA,HT1621_CS);                                  //CS = 1;   
}

void lcd_send_data(unsigned char *data,uint8_t address)   
{   
    char i = 0 ;   
    unsigned char show_buf[SIZE_BUFF]='\0';   
     
    while(data[i]!='\0')                                             //ȡǰ��λ��ʾ��   
    {   
        switch(data[i])   
        {   
            case '0':                    
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x7d|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0xd7;                   
                }                
                break;   
            case '1':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x60|DOT_SEG_1;        
                }
                else
                {
                    show_buf[i] = 0x06; 
                }              
                break;   
            case '2':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x3e|DOT_SEG_1; 
                }
                else
                {
                    show_buf[i] = 0xe3; 
                }                
                break;   
            case '3':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x7a|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0xa7; 
                }                 
                break;   
            case '4':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x63|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0x36; 
                }               
                break;   
            case '5':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x5b|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0xb5; 
                }              
                break;   
            case '6':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x5f|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0xf5; 
                }               
                break;   
            case '7':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x70|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0x07; 
                }                  
                break;   
            case '8':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x7f|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0xf7; 
                }                 
                break;   
            case '9':
                if(address==0||address==2||address==4||address==6)
                {
                    show_buf[i] = 0x7b|DOT_SEG_1;
                }
                else
                {
                    show_buf[i] = 0xb7; 
                }                 
                break;
            default:
                show_buf[i] = 0xff;
                break;
        }
        if(address==8||address==12||address==22||address==16          
           ||address==24)
        {
            show_buf[i] |= 0x08;
        }
        i++;       
    }
    lcd_show_data1(show_buf,address);  
}        
/***************************************************end file*************************************************/   
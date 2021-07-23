//LCD.h 
 
#ifndef	_LCD_H_ 
#define _LCD_H_ 
#define SIZE_BUFF (1U)
#define DOT_SEG_1   (0x80)
#define DOT_SEG_2   (0x08)

#define ADD_SPEED_0  (2U)
#define ADD_SPEED_1  (4U)
#define ADD_SPEED_2  (6U)

#define ADD_TIME_SECOND_0  (12U)
#define ADD_TIME_SECOND_1  (10U)
#define ADD_TIME_MINUTE_0  (8U)
#define ADD_TIME_MINUTE_1  (0U)

#define ADD_DIS_0  (14U)
#define ADD_DIS_1  (16U)
#define ADD_DIS_2  (18U)

#define ADD_CAL_0  (20U)
#define ADD_CAL_1  (22U)
#define ADD_CAL_2  (24U)

#define ADD_INCL_0  (28U)
#define ADD_INCL_1  (30U)

void GPIO_LcdInit(void);					// LCD gpio��ʼ�� 
void LCD_init(void);
void test_line(void);// LCD ģ���ʼ��	 
void LCD_show_data(unsigned char *puts);// LCD ��ʾ��������ϣ����ʾ��12345678�����ɴ��롰12345678����data�ĳ̶Ȳ���С��8 
void LCD_clr(void);	
void delay(uint32_t MS);// LCD �������� 
void LCD_test(void);						// LCD ���Ժ��� 

void LCD_show_data1(unsigned char *puts,uint8_t address)  ;
void LCD_send_data(unsigned char *data,uint8_t address) ;
#endif
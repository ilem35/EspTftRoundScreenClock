//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  3.3v��Դ
//              SCL  P10��SCLK��
//              SDA  P11��MOSI��
//              RES  P12
//              DC   P13
//              CS   P14 
//              BLK  P15
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/
#include "REG51.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"

int main(void)
{
	u8 i,j;
	float t=0;
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	while(1)
	{
		LCD_ShowChinese(30,40,"�о�԰����",RED,WHITE,32,0);
		LCD_ShowString(32,80,"LCD_Diameter:",RED,WHITE,16,0);
		LCD_ShowIntNum(134,80,LCD_W,3,RED,WHITE,16);
		LCD_ShowString(32,100,"Increaseing Nun:",RED,WHITE,16,0);
		LCD_ShowFloatNum1(160,100,t,4,RED,WHITE,16);
		t+=0.11;
		for(j=0;j<3;j++)
		{
			for(i=0;i<6;i++)
			{
				LCD_ShowPicture(40*i,120+j*40,40,40,gImage_1);
			}
		}
	}
}

	
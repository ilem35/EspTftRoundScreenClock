
/********************金逸晨**************************
*****************1.28’    7PIN SPI TFT FOR STM8S*************
***** PC3  SCK   ,  PC4  SDA   ,    PC5  DC   ,
      PC6   CS   ,    PC7   RST
***** BY: 
此模块可不接CS,RST引脚，板载硬件上电复位，和CS下拉电阻
控制器GC9A01圆屏

********************************************************/
#include "IOSTM8S003F3.h"

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 240


#define set_0   0x01
#define set_1   0x02
#define set_2   0x04
#define set_3   0x08    
#define set_4   0x10
#define set_5   0x20
#define set_6   0x40
#define set_7   0x80

#define clr_0   0xFE
#define clr_1   0xFD
#define clr_2   0xFB
#define clr_3   0xF7    
#define clr_4   0xEF
#define clr_5   0xDF
#define clr_6   0xBF
#define clr_7   0x7F

/**********SPI引脚分配，连接TFT屏，更具实际情况修改*********/

#define SPI_SCK_0  PC_ODR&=clr_3        //PC3       
#define SPI_SCK_1  PC_ODR|=set_3       
#define SPI_SDA_0  PC_ODR&=clr_4        //PC4        
#define SPI_SDA_1  PC_ODR|=set_4
#define SPI_DC_0  PC_ODR&=clr_5        //PC5        
#define SPI_DC_1  PC_ODR|=set_5
#define SPI_CS_0  PC_ODR&=clr_6           //PC6
#define SPI_CS_1  PC_ODR|=set_6
#define SPI_RST_0  PC_ODR&=clr_7          //PC7
#define SPI_RST_1  PC_ODR|=set_7


/*****************颜色数据**************************/
#define WHITE            0xFFFF
#define BLACK            0x0000   
#define BLUE             0x001F  
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define GREEN            0x07E0

//  const unsigned char  picture_tab[]={
// /*------------------------------------------------------------------------------
// ;  源文件 / 文字 : C:\Documents and Settings\Administrator\桌面\新建文件夹 (2)\logo.bmp字模
// ;  宽×高（像素）: 128×128
// ------------------------------------------------------------------------------*/
/* 0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X7F,0XFE,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XC0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X07,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0X0F,0XFF,0XFF,0XFE,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X0F,0XFF,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XFF,0XC3,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X88,0X0F,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X18,0X0F,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0X3C,0X0F,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0X7C,0X0F,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0XFC,0X0F,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF9,0XFC,0X0F,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFC,0X0F,0XFF,0XFF,0XFF,0XFF,0XCF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE3,0XFC,0X0F,0XFF,0XFF,0XF0,0X03,0XC7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE7,0XFC,0X0F,0XFF,0XFF,0XC0,0X00,0X63,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XC7,0XFC,0X0F,0XFF,0XFF,0X07,0XFC,0X03,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XCF,0XFC,0X0F,0XFF,0XFE,0X0F,0XFF,0X01,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X9F,0XFC,0X0F,0XFF,0XFC,0X3F,0XFF,0X81,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X9F,0XFC,0X0F,0XFF,0XF8,0X7F,0XFF,0XC1,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFC,0X0F,0XFF,0XF0,0X7F,0XFF,0XE4,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFC,0X0F,0XFF,0XE0,0XFF,0XFF,0XE4,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X3F,0XFC,0X00,0X0F,0XE0,0X00,0X0F,0XF6,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X00,0X3F,0XC0,0X00,0X3F,0XF6,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X00,0XFF,0XC1,0XF0,0X7F,0XFE,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X01,0XFF,0X83,0XF0,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X00,0XFF,0X83,0XF1,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0XFF,0XFC,0X00,0XFF,0X83,0XE3,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X00,0X7F,0X83,0XE3,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X00,0X7F,0X83,0XC7,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X00,0X3F,0X83,0X8F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X00,0X1F,0X87,0X8F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X00,0X1F,0X87,0X1F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X08,0X0F,0X87,0X1F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X08,0X07,0X82,0X3F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X0C,0X07,0X82,0X3F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFF,0XFC,0X0E,0X03,0X80,0X7F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0XFF,0XFC,0X0E,0X01,0X80,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X0F,0X01,0X80,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X0F,0X00,0XC1,0XFF,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X7F,0XFC,0X0F,0X80,0XC1,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X71,0XFC,0X1F,0XC0,0X41,0XFF,0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X20,0XFC,0X1F,0XC0,0X00,0XFF,0XFF,0XFA,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X20,0XFC,0X1F,0XE0,0X00,0X7F,0XFF,0XF4,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X20,0X7C,0X3F,0XF0,0X00,0X3F,0XFF,0XE4,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X78,0X3F,0XF0,0X08,0X3F,0XFF,0XCC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X90,0X38,0X7F,0XF8,0X1C,0X0F,0XFF,0X99,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X88,0X00,0XFF,0XF8,0X1E,0X07,0XFE,0X39,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XCE,0X03,0XFF,0XF8,0X1F,0X80,0X00,0XF3,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE7,0XFF,0XFF,0XF8,0X1F,0XE0,0X03,0XE3,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE7,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XE7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF3,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF1,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XF8,0X1F,0XFF,0XFF,0X1F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XF8,0X1F,0XFF,0XFF,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XF8,0X1F,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X1F,0XFF,0XF8,0X1F,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XF8,0X1F,0XFF,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XC7,0XFF,0XF8,0X1F,0XFF,0XE1,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XE1,0XFF,0XF8,0X1F,0XFF,0XC7,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0XFF,0XF8,0X1F,0XFF,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XF8,0X1F,0XFC,0X1F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,0XF0,0X0F,0XF0,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X81,0XE0,0X07,0X81,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X00,0X00,0X07,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X9F,0XFF,0XFF,0XFE,0XFF,0XFF,0XFF,0XF0,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0X3F,0XFF,0XFF,0XC0,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X8F,0XFF,0XFF,0XFF,0X1F,0XFF,0XFF,0XAF,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X0F,0XFF,0XFF,0XFE,0X0F,0XFF,0XFE,0XF3,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X03,0XFF,0XFF,0XFC,0X07,0XFF,0XFE,0X40,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X21,0XFF,0XFF,0XFC,0X47,0XFF,0XFF,0X26,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X78,0XFF,0XFE,0X3D,0X8F,0XFF,0XFF,0X28,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XFC,0X7F,0XFF,0X1F,0X13,0XFF,0XFF,0X00,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0XC6,0X1F,0XFE,0X5F,0X01,0XFF,0XFF,0X86,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF9,0X03,0X0F,0XFF,0XF6,0X19,0XFF,0XFF,0XF0,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X03,0X83,0XFF,0XF8,0X13,0XFF,0XFF,0X87,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF3,0X0F,0XC0,0XFC,0X79,0X83,0XFF,0XFC,0X18,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XE7,0X03,0XE0,0X3E,0X39,0X01,0XFF,0XFC,0X21,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XEE,0XC1,0XFF,0X3F,0X38,0X3F,0XFF,0XFF,0X32,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XCE,0X07,0XFF,0XFE,0X78,0X49,0XFF,0XFF,0X70,0X3F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X9C,0X0F,0XFF,0XFF,0X7C,0XC9,0XFF,0XFE,0X03,0X9F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X3E,0X4C,0XFF,0XFF,0X3C,0X91,0XFF,0XFE,0XCF,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X88,0XFF,0XFF,0XB9,0XBF,0XFF,0XFC,0XC0,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X01,0XFF,0XFF,0XB3,0X9E,0X7F,0XFD,0XC0,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X43,0XFF,0XFD,0X1F,0XC0,0X7F,0XF9,0X9F,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0XC7,0XFF,0XFE,0X00,0XFF,0XFF,0XFB,0X9C,0X83,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X80,0X3F,0XFF,0XFC,0X00,0X1F,0XF7,0X99,0XC0,0X7F,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFC,0X00,0X3F,0XFF,0XFF,0X80,0X0F,0XE7,0XD1,0XF0,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XFF,0XF8,0X7F,0XCF,0XC3,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFD,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X9F,0XE7,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
}; */

/*******时钟初始化******************/
void CLK_init(void)
{
  
  CLK_CKDIVR|= 0x00;       /*设置时钟为内部16M高速时钟*/ 
}
void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;
  }
}
void delay_ms(unsigned int _ms_time)
  {
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
  }
/*************SPI配置函数*******************
SSD1306，SCL空闲时低电平，第一个上升沿采样
模拟SPI
******************************************/

/**************************SPI模块发送函数************************************************

 *************************************************************************/
void SPI_SendByte(unsigned char byte)
{
  
  unsigned char counter;
   
  for(counter=0;counter<8;counter++)
  { 
    SPI_SCK_0;
    if((byte&0x80)==0)
    {
      SPI_SDA_0;
    }
    else SPI_SDA_1;
    byte=byte<<1;
    SPI_SCK_1;	     
  } 
}

void TFT_send_cmd(unsigned char o_command)
  {
    SPI_DC_0;
    SPI_CS_0;
    SPI_SendByte(o_command);
    SPI_CS_1;
    //SPI_DC_1;
  }
void TFT_send_data(unsigned char o_data)
  { 
    SPI_DC_1;
    SPI_CS_0;
    SPI_SendByte(o_data);
    SPI_CS_1;
   }
void TFT_init(void)	//GC9A01
  {
		SPI_RST_0;//复位 
	  delay_ms(100); 
	  SPI_RST_1; 
	  SPI_CS_0;
	  delay_ms(100); 
	  
	  TFT_send_cmd(0xEF); 		//使用指令2
	  TFT_send_cmd(0xEB); 		//
	  TFT_send_data(0x14);
	  
	  TFT_send_cmd(0xFE); 		//使用指令1
	  TFT_send_cmd(0xEF); 		//使用指令2  设置inter指令可用完成，复位之后才可关闭
	  
	  TFT_send_cmd(0xEB); 
	  TFT_send_data(0x14); 
	  
	  TFT_send_cmd(0x84); 
	  TFT_send_data(0x40); 
	  TFT_send_cmd(0x85); 
	  TFT_send_data(0xFF); 
	  TFT_send_cmd(0x86); 
	  TFT_send_data(0xFF); 
	  TFT_send_cmd(0x87); 
	  TFT_send_data(0xFF); 
	  TFT_send_cmd(0x88); 
	  TFT_send_data(0x0A); 
	  TFT_send_cmd(0x89); 
	  TFT_send_data(0x21);
	  
	  TFT_send_cmd(0x8A); 
	  TFT_send_data(0x00);
	  
	  TFT_send_cmd(0x8B); 
	  TFT_send_data(0x80);
	  
	  TFT_send_cmd(0x8C); 
	  TFT_send_data(0x01);
	  
	  TFT_send_cmd(0x8D); 
	  TFT_send_data(0x01);
	  
	  TFT_send_cmd(0x8E); 
	  TFT_send_data(0xFF);
	  
	  TFT_send_cmd(0x8F); 
	  TFT_send_data(0xFF);
	  
	  TFT_send_cmd(0xB6); 	//外部指令  显示功能控制
	  TFT_send_data(0x00); 		//扫描方向控制S1-S360 G1-32
	  TFT_send_data(0x20); 		
	  
	  TFT_send_cmd(0x36); 	//调整指令 存储控制 Memory Access Control
	  TFT_send_data(0x08); 		//MY MX MV ML BGR MH X X
	  
	  TFT_send_cmd(0x3A); 	//调整指令 	Pixel Format Set
	  TFT_send_data(0x05); 			//16bit MCU数据模式
	  
	  TFT_send_cmd(0x90); 	//xxx
	  TFT_send_data(0x08); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x08);
	  
	  TFT_send_cmd(0xBD); 	//XXX
	  TFT_send_data(0x06);
	  
	  TFT_send_cmd(0xBC); 	//XXX
	  TFT_send_data(0x00); 
	  
	  TFT_send_cmd(0xFF); 	//XXX	
	  TFT_send_data(0x60); 
	  TFT_send_data(0x01); 
	  TFT_send_data(0x04);
	  
	  TFT_send_cmd(0xC3); 	//	Vreg1a voltage Control
	  TFT_send_data(0x13);
	  
	  TFT_send_cmd(0xC4); 	// Vreg1b voltage Control
	  TFT_send_data(0x13);
	  
	  TFT_send_cmd(0xC9); 	//Vreg2a voltage Control
	  TFT_send_data(0x22);
	  
	  TFT_send_cmd(0xBE); 	//XXX
	  TFT_send_data(0x11); 
	  
	  TFT_send_cmd(0xE1); 	//XXX
	  TFT_send_data(0x10);
	  TFT_send_data(0x0E); 
	  
	  TFT_send_cmd(0xDF); 	//XXX
	  TFT_send_data(0x21); 
	  TFT_send_data(0x0c); 
	  TFT_send_data(0x02); 
	  
	  TFT_send_cmd(0xF0); 	//GAMMA1
	  TFT_send_data(0x45); 
	  TFT_send_data(0x09); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x26); 
	  TFT_send_data(0x2A); 
	  
	  TFT_send_cmd(0xF1); 	//GAMMA2
	  TFT_send_data(0x43); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x72); 
	  TFT_send_data(0x36); 
	  TFT_send_data(0x37); 
	  TFT_send_data(0x6F); 
	  
	  TFT_send_cmd(0xF2); 	//GAMMA3
	  TFT_send_data(0x45); 
	  TFT_send_data(0x09); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x26); 
	  TFT_send_data(0x2A); 
	  
	  TFT_send_cmd(0xF3); 	////GAMMA4
	  TFT_send_data(0x43); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x72); 
	  TFT_send_data(0x36); 
	  TFT_send_data(0x37); 
	  TFT_send_data(0x6F);
	  
	  TFT_send_cmd(0xED); 	//XXX
	  TFT_send_data(0x1B); 
	  TFT_send_data(0x0B);
	  
	  TFT_send_cmd(0xAE); 	//XXX
	  TFT_send_data(0x77);
	  
	  TFT_send_cmd(0xCD); 	//XXX
	  TFT_send_data(0x63);
	  
	  TFT_send_cmd(0x70); 
	  TFT_send_data(0x07); 
	  TFT_send_data(0x07); 
	  TFT_send_data(0x04); 
	  TFT_send_data(0x0E); 
	  TFT_send_data(0x0F); 
	  TFT_send_data(0x09); 
	  TFT_send_data(0x07); 
	  TFT_send_data(0x08); 
	  TFT_send_data(0x03); 
	  
	  TFT_send_cmd(0xE8); 	//Frame Rate
	  TFT_send_data(0x34);
	  
	  TFT_send_cmd(0x62); 	//XXX
	  TFT_send_data(0x18); 
	  TFT_send_data(0x0D); 
	  TFT_send_data(0x71); 
	  TFT_send_data(0xED); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x18); 
	  TFT_send_data(0x0F); 
	  TFT_send_data(0x71); 
	  TFT_send_data(0xEF); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x70); 
	  
	  TFT_send_cmd(0x63); 	//XXX
	  TFT_send_data(0x18); 
	  TFT_send_data(0x11); 
	  TFT_send_data(0x71); 
	  TFT_send_data(0xF1); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x18); 
	  TFT_send_data(0x13); 
	  TFT_send_data(0x71); 
	  TFT_send_data(0xF3); 
	  TFT_send_data(0x70); 
	  TFT_send_data(0x70); 
	  
	  TFT_send_cmd(0x64); 	//XXX
	  TFT_send_data(0x28); 
	  TFT_send_data(0x29); 
	  TFT_send_data(0xF1); 
	  TFT_send_data(0x01); 
	  TFT_send_data(0xF1); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x07);
	  
	  TFT_send_cmd(0x66); 	//XXX
	  TFT_send_data(0x3C); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0xCD); 
	  TFT_send_data(0x67); 
	  TFT_send_data(0x45); 
	  TFT_send_data(0x45); 
	  TFT_send_data(0x10); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x00); 
	  
	  TFT_send_cmd(0x67); 	//XXX
	  TFT_send_data(0x00); 
	  TFT_send_data(0x3C); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x01); 
	  TFT_send_data(0x54); 
	  TFT_send_data(0x10); 
	  TFT_send_data(0x32); 
	  TFT_send_data(0x98);
	  
	  TFT_send_cmd(0x74); 	//XXX
	  TFT_send_data(0x10); 
	  TFT_send_data(0x85); 
	  TFT_send_data(0x80); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x00); 
	  TFT_send_data(0x4E); 
	  TFT_send_data(0x00);
	  
	  TFT_send_cmd(0x98); 		//XXX
	  TFT_send_data(0x3e); 
	  TFT_send_data(0x07); 
	  
	  TFT_send_cmd(0x34); 	//Tearing Effect Line Off
	  TFT_send_cmd(0x21); 	//Display Inversion ON
	  TFT_send_cmd(0x11); 	//唤醒
	  //TFT_send_cmd(0x38);	//Idle Mode OFF
	  delay_ms(120); 
	  TFT_send_cmd(0x29); 	//显示开
	  delay_ms(20);
  }
void Add_set(unsigned char x_start,unsigned char y_start,unsigned char x_end,unsigned char y_end)
  {
	  TFT_send_cmd(0x2A);    //设置列地址
	  TFT_send_data(0);		//列地址起始 
	  TFT_send_data(x_start);
	  TFT_send_data(0);		//列地址结束
	  TFT_send_data(x_end);
	  TFT_send_cmd(0x2B);    //设置行地址
	  TFT_send_data(0);		//行地址起始 
	  TFT_send_data(y_start);
	  TFT_send_data(0);		//行地址结束
	  TFT_send_data(y_end);
	  TFT_send_cmd(0x2C);    //准备写入显示数据    	 
  }

void TFT_clear(void)
  {
    unsigned char Line,column;
	  Add_set(0,0,TFT_COLUMN_NUMBER-1,TFT_LINE_NUMBER-1);
    for(Line=0;Line<TFT_LINE_NUMBER;Line++)             //Line loop
      { 	  
          for(column=0;column<TFT_COLUMN_NUMBER;column++)	//column loop
            {
                TFT_send_data(0x00);
				TFT_send_data(0x00);
            }
      }
  }
void TFT_full(unsigned int color)
  {
    unsigned char Line,column;
	  Add_set(0,0,TFT_COLUMN_NUMBER-1,TFT_LINE_NUMBER-1);
    for(Line=0;Line<TFT_LINE_NUMBER;Line++)             //Line loop
      { 
		  
		for(column=0;column<TFT_COLUMN_NUMBER;column++)	//column loop
          {
              TFT_send_data(color>>8);
			  TFT_send_data(color);
          }
      }
  }
void TFT_dispoint(unsigned char x,unsigned char y,unsigned int color)
{
	Add_set(x,y,x,y);
	TFT_send_data(color>>8);
	TFT_send_data(color);
	
}


void Picture_display(unsigned int x,unsigned int y,unsigned int length,unsigned int width,const unsigned char *ptr_pic)
{
	unsigned int i,j;
	Add_set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{

            TFT_send_data(*ptr_pic++);
			TFT_send_data(*ptr_pic++);
		}
	}			
}
void Logo_display(const unsigned char *ptr_pic,unsigned int Bcolor,unsigned int Ccolor)
{
	unsigned int i,j,k;
	unsigned char x;
	Add_set(55,55,182,182);
	for(i=0;i<16;i++)
	{
		for(j=0;j<128;j++)
		{
			x = *ptr_pic++;
			for(k=0;k<8;k++)
			{
				if(x&0x80)
				{
					TFT_send_data(Bcolor>>8);
					TFT_send_data(Bcolor);
				}
				else 
				{
					TFT_send_data(Ccolor>>8);
					TFT_send_data(Ccolor);
				}
				x <<=1;
			}
		}
	}			
}
void IO_init(void)
{
  PC_DDR|=0xFF;                         //PC  06,07，03,04,07推挽输出模式
  PC_CR1|=0xFF;
  PC_CR2|=0xFF;
  PC_ODR=0XFF;
}
void main()
{ 
  IO_init();
  TFT_init();
	TFT_clear();
  
   
  while(1)
  {
	  TFT_full(GREEN);
  delay_ms(1000);
	TFT_full(RED);
  delay_ms(1000);
	TFT_full(BLUE);
  delay_ms(1000);
	TFT_full(WHITE);
  delay_ms(1000);
    TFT_clear();
	 // Logo_display(&picture_tab[0],RED,GREEN);
	delay_ms(200);
   /*  Picture_display(0,0,240,240,gImage_BP);
    delay_ms(10000); */
//    Picture_display(0,0,240,240,gImage_TKR);
//    delay_ms(10000);
	
    
  }
}

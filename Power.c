/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/6/18
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Power.h"

//后拨电源控制
#define READ PB_ODR_ODR1

static u8 batter_level = 0;

#define CLK_ADC1   0

#define BATTERY_EN PB_ODR_ODR4
#define COM_EN PB_ODR_ODR0
/**********************************************函数定义***************************************************** 
* 函数名称: void PowerInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/18
************************************************************************************************************/ 
void PowerInit(void) {
    //后拨电源使能
    PB_DDR_DDR1 = 1;
    PB_CR1_C11 = 1;
    PB_CR2_C21 = 0;
    //开机打开后拨电源
    PowerSet(1);
    
    //电压检测使能
    PB_DDR_DDR4 = 1;
    PB_CR1_C14 = 1;
    PB_CR2_C24 = 0;
    //电压检测PB3
    PB_DDR_DDR3 = 0;
    PB_CR1_C13 = 0;
    PB_CR2_C23 = 0;
    //考虑通讯功耗
    PB_DDR_DDR0 = 1;
    PB_CR1_C10 = 1;
    PB_CR2_C20 = 0;
    
    BATTERY_EN = 1;
    COM_EN = 1;
    
    CLK_PCKENR2 |= 1<<CLK_ADC1; //给ADC1喂时钟，否则ADC不工作。
    ADC1_CR1 = 0x01 ;//开启ADC电路 + 单次取样
    ADC1_CR2 = 0x82; //0..23通道，取样16分频 
    ADC1_CR3 = 0x40; //24,TS,Vref 通道，取样16分频
    
//    ADC1_SR &= ~BIT(6);
//	ADC1_SR &= ~BIT(4);
//	ADC1_CR1 |= BIT(1);
//	ADC1_CR2 |= BIT(1);
	//ADC1_TDRL = 0x01;
}
/**********************************************函数定义***************************************************** 
* 函数名称: void PowerSet(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能: 设置后拨电源  
* 作    者: by lhb_steven
* 日    期: 2016/6/18
************************************************************************************************************/ 
void PowerSet(u8 cmd) { 
    if(cmd == 0) {
        READ = 0;//0关闭 栅极电压 高于 源级电压
    } else {
        READ = 1;//3.3V打开 高于栅极电压
    }
}



float PowerGetVolate(u8 chx) {
    float volate = 0;
    u16 ad_value;
    u8 ad_h = 0;
    u8 ad_l = 0;
	u8 i;
	ADC1_SQR4 = ADC1_SQR3 = ADC1_SQR2 = ADC1_SQR1 = 0;
    if (chx<=7)
    ADC1_SQR4 |= (1<<chx);
    else if (chx<=15)
    ADC1_SQR3 |= (1<<(chx-8));
    else if (chx<=23)
    ADC1_SQR2 |= (1<<(chx-16));
    ADC1_CR1 |= (1<<1);
    for (i=0  ; i<100; i++); //简单延时下
    while ((ADC1_SR & (1<<0))==0); //等待取样结束
    ADC1_SR &= (~(1<<0));          //马上清标志位
    ad_h = ADC1_DRH;
    ad_l = ADC1_DRL;
	ad_value = (ad_h<<8) + ad_l;
    volate = (15.95*ad_value)/0xffff*10;
    return volate;
}


void PowerGet(void) {
    float bat = 0;
    bat = PowerGetVolate(15);
    if(bat > 8.2) {
    
            batter_level = 5;
   
    } else if(bat > 7.9) {
        
            batter_level = 4;
       
    } else if(bat > 7.6) {
        
            batter_level = 3;
       
    } else if(bat > 7.2) {
       
            batter_level = 2;
        
    } else if(bat > 6.8) {
        
            batter_level = 1;
     
    } else {
       
            batter_level = 0;
        
    }
}

u8 BattertGetLevel(void) {
    return batter_level;
}

/**********************************************函数定义***************************************************** 
* 函数名称: void PowerSetGet(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/18
************************************************************************************************************/ 
void PowerSetGet(u8 cmd) { 
    BATTERY_EN = cmd;
    if(cmd == 0) {
        //考虑通讯功耗
        PB_DDR_DDR0 = 1;
        PB_CR1_C10 = 1;
        COM_EN = 0;
        //为了低功耗 改成输出模式
        PB_DDR_DDR3 = 1;
        PB_CR1_C13 = 1;
        //测试
        PA_DDR = 0XFF;
        PA_CR1 = 0XFF;
        PB_DDR = 0XFF;
        PB_CR1 = 0XFF;
        PC_DDR = 0XFF;
        PC_CR1 = 0XFF;
        PD_DDR = 0XFF;
        PD_CR1 = 0XFF;
        
        PB_DDR_DDR7 = 0; //前拨减
        PB_CR1_C17 = 1;
        PB_CR2_C27 = 1;
        
        PB_DDR_DDR5 = 0;//前拨加
        PB_CR1_C15 = 1;
        PB_CR2_C25 = 1;
        
        //关闭ADC
        ADC1_CR1 = 0x00;//开启ADC电路 + 单次取样
        TIM4_CR1 = 0x00;
        USART1_CR2 = 0x00;
        CLK_PCKENR2 = 0X00; //给ADC1喂时钟，否则ADC不工作。
        CLK_PCKENR1 = 0X00;
    } else {
        //为了低功耗 改成输出模式
        PB_DDR_DDR3 = 0;
        PB_CR1_C13 = 0;
        
        //恢复二极管状态
        PA_DDR_DDR2 = 0;
        PA_CR1_C12 = 0;
        PA_CR2_C22 = 1;
        
        //打开ADC
        CLK_PCKENR1 = 0X04;
        CLK_PCKENR2 |= 1<<CLK_ADC1; //给ADC1喂时钟，否则ADC不工作。
        ADC1_CR1 = 0x01 ;//开启ADC电路 + 单次取样
        USART1_CR2 = 0x2c;
        TIM4_CR1 = 0x01;
        //考虑通讯功耗
        PB_DDR_DDR0 = 1;
        PB_CR1_C10 = 1;
        COM_EN = 1;
    }
} 




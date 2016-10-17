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
* 完成日期：2016/6/20
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Ant+.h"


/**********************************************函数定义***************************************************** 
* 函数名称: void AntInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/20
************************************************************************************************************/ 
void AntInit(void) { 
    PD_DDR &= ~BIT(6);//TX
    PD_CR1 |= BIT(6); 
    PD_CR2 &= ~BIT(6);

    PD_DDR |= BIT(5);//RX
    PD_CR1 |= BIT(5); 
    PD_CR2 |= BIT(5);
    
    USART1_CR1 = 0X00;
    USART1_CR2 = 0X00;
    USART1_CR3 = 0X00;
    USART1_BRR2 = 0x0a;
    USART1_BRR1 = 0x08;
    USART1_CR2 = 0x2c;
}
/**********************************************函数定义***************************************************** 
* 函数名称: void AntSend(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/23
************************************************************************************************************/ 
void AntSend(u8 cmd) {
    /*关闭ANT+*/
    u8 data[2] = {0x24,0x00};
    for(u8 i = 0;i < 1;i++) {
        while((USART1_SR & 0x80) == 0x00);
        USART1_DR = data[i];
    }
}





#pragma vector=30
__interrupt void UART1_RX_IRQHandler(void)
{
    u8 data;
    data = USART1_DR;
    /*等待数据接受完成*/
    while((USART1_SR & 0x80) == 0x00);
    
    return;
}

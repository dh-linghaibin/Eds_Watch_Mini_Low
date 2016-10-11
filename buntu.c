/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：buntu.h
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：v1.1
* 作    者：lhb Steven
* 完成日期：2016/3/14
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "buntu.h"
#include "Delay.h"
#include "Time.h"

#define BUNTU_REAR1     PB_IDR_IDR5
#define BUNTU_REAR2     PB_IDR_IDR4
#define BUNTU_BEHIND1   PB_IDR_IDR7
#define BUNTU_BEHIND2   PB_IDR_IDR6
#define BUNTU_MODE      PB_IDR_IDR0

#define Mountain_Bike   0x01 //山地车
#define Road_Bike       0x00//公路车 

#define BACK Road_Bike  //选择自行车版本

typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;

typedef enum
{
  EXTI_Pin_0 = (uint8_t)0x00, /*!< GPIO Pin 0 */
  EXTI_Pin_1 = (uint8_t)0x02, /*!< GPIO Pin 1 */
  EXTI_Pin_2 = (uint8_t)0x04, /*!< GPIO Pin 2 */
  EXTI_Pin_3 = (uint8_t)0x06, /*!< GPIO Pin 3 */
  EXTI_Pin_4 = (uint8_t)0x10, /*!< GPIO Pin 4 */
  EXTI_Pin_5 = (uint8_t)0x12, /*!< GPIO Pin 5 */
  EXTI_Pin_6 = (uint8_t)0x14, /*!< GPIO Pin 6 */
  EXTI_Pin_7 = (uint8_t)0x16  /*!< GPIO Pin 7 */
} EXTI_Pin_TypeDef;

typedef enum
{
  EXTI_Trigger_Falling_Low    = (uint8_t)0x00, /*!< Interrupt on Falling edge and Low level */
  EXTI_Trigger_Rising         = (uint8_t)0x01, /*!< Interrupt on Rising edge only */
  EXTI_Trigger_Falling        = (uint8_t)0x02, /*!< Interrupt on Falling edge only */
  EXTI_Trigger_Rising_Falling = (uint8_t)0x03  /*!< Interrupt on Rising and Falling edges */
} EXTI_Trigger_TypeDef;


void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin, EXTI_Trigger_TypeDef EXTI_Trigger)
{

  /* Check function parameters */
 // assert_param(IS_EXTI_PINNUM(EXTI_Pin));
  //assert_param(IS_EXTI_TRIGGER(EXTI_Trigger));

  /* Clear port sensitivity bits */
  switch (EXTI_Pin)
  {
    case EXTI_Pin_0:
      EXTI_CR1 &=  (uint8_t)(~0x03);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_1:
      EXTI_CR1 &=  (uint8_t)(~0x0C);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_2:
      EXTI_CR1 &=  (uint8_t)(~0x30);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_3:
      EXTI_CR1 &=  (uint8_t)(~0xC0);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_4:
      EXTI_CR2 &=  (uint8_t)(~0x03);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_5:
      EXTI_CR2 &=  (uint8_t)(~0x0C);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_6:
      EXTI_CR2 &=  (uint8_t)(~0x30);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_7:
      EXTI_CR2 &=  (uint8_t)(~0xC0);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    default:
      break;
  }
}
#define assert_param(expr) ((void)0)
typedef enum
{
  EXTI_IT_Pin0    = (uint16_t)0x0001, /*!< GPIO Pin pos 0 */
  EXTI_IT_Pin1    = (uint16_t)0x0002, /*!< GPIO Pin pos 1 */
  EXTI_IT_Pin2    = (uint16_t)0x0004, /*!< GPIO Pin pos 2 */
  EXTI_IT_Pin3    = (uint16_t)0x0008, /*!< GPIO Pin pos 3 */
  EXTI_IT_Pin4    = (uint16_t)0x0010, /*!< GPIO Pin pos 4 */
  EXTI_IT_Pin5    = (uint16_t)0x0020, /*!< GPIO Pin pos 5 */
  EXTI_IT_Pin6    = (uint16_t)0x0040, /*!< GPIO Pin pos 6 */
  EXTI_IT_Pin7    = (uint16_t)0x0080, /*!< GPIO Pin pos 7 */
  EXTI_IT_PortB   = (uint16_t)0x0101, /*!< GPIO Port B    */
  EXTI_IT_PortD   = (uint16_t)0x0102, /*!< GPIO Port D    */
  EXTI_IT_PortE   = (uint16_t)0x0104, /*!< GPIO Port E    */
  EXTI_IT_PortF   = (uint16_t)0x0108, /*!< GPIO Port F    */
  EXTI_IT_PortG   = (uint16_t)0x0110, /*!< GPIO Port G    */
  EXTI_IT_PortH   = (uint16_t)0x0120  /*!< GPIO Port H    */
} EXTI_IT_TypeDef;

void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT)
{
  uint16_t tempvalue = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  tempvalue = ((uint16_t)EXTI_IT & (uint16_t)0xFF00);

  if ( tempvalue == 0x0100)
  {
    EXTI_SR2 = (uint8_t)((uint16_t)EXTI_IT & (uint16_t)0x00FF);
  }
  else
  {
    EXTI_SR1 = (uint8_t) (EXTI_IT);
  }
}

/**********************************************函数定义***************************************************** 
* 函数名称: void BuntuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 按键初始化  
* 作    者: by lhb_steven
* 日    期: 2016/3/14
************************************************************************************************************/ 
void BuntuInit(void) { 
    PB_DDR_DDR4 = 0; //前拨减
    PB_CR1_C14 = 1;
    PB_CR2_C24 = 0;
    
    PB_DDR_DDR5 = 0;//前拨加
    PB_CR1_C15 = 1;
    PB_CR2_C25 = 0;
    
    PB_DDR_DDR6 = 0;//后拨减
    PB_CR1_C16 = 1;
    PB_CR2_C26 = 0;
    
    PB_DDR_DDR7 = 0;//后拨加
    PB_CR1_C17 = 1;
    PB_CR2_C27 = 0;
    
    PB_DDR_DDR0 = 0;//按键
    PB_CR1_C10 = 1;
    PB_CR2_C20 = 0;
    
    EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Falling); 
    EXTI_SetPinSensitivity(EXTI_Pin_4,EXTI_Trigger_Falling); 
    EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Falling); 
    EXTI_SetPinSensitivity(EXTI_Pin_6,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_7,EXTI_Trigger_Falling); 
    
    //这里是给通讯使用的 
    //EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Falling); //pa2
}


/**********************************************函数定义***************************************************** 
* 函数名称: u8 BuntuRead(void) 
* 输入参数: void 
* 返回参数: u8  
* 功    能: 读取按键状态  
* 作    者: by lhb_steven
* 日    期: 2016/3/14
************************************************************************************************************/ 
u8 BuntuRead(void) { 
    static u16 count1 = 0;
    static u16 count2 = 0;
    static u16 count3 = 0;
    static u16 count4 = 0;
    static u16 count5 = 0;
    static u8 count_small1 = 0;
    static u8 count_small2 = 0;
    static u8 count_small3 = 0;
    static u8 count_small4 = 0;
    static u8 count_small5 = 0;
    static u8 mode_count = 0;//模式
    static u8 teae_flag = 0;//后拨组合标志
    if(BUNTU_REAR1 == 0) {//后拨按钮1
        TimerSetSec(0);//清楚按键状态
        if(count_small1 < 30) {
            count_small1++;
        } else {
            count_small1 = 0;
            if(count1 < 3000) {
                count1++;
            }
            #if BACK
            if(count1 == 100) {//按键按下就触发
                if(count2 == 0) {//两颗按键要同时按下才有效
                   if(mode_count == 0) {//未进入一起按下的模式
                        teae_flag = 0;
                        return 0x11;
                    }
                }
            }
            #endif
            if(count1 == 2000) {
                //长按进入
                if(count2 > 1500) {//两颗按键要同时按下才有效
                    if(mode_count == 0) {//未进入一起按下的模式
                        teae_flag = 0;
                        return 0x01;
                    }
                }
            }
        }
    } else {
        if( (count1 > 50)&&(count1 < 1500) ) {
            //count1 = 0;
            //return 0x11;
        } else if(count1 > 1500) {//只要有一颗松开就结束
            count1 = 0;
            teae_flag = 0;//清楚标志
            return 0x21;
        }
        count_small1 = 0;
        count1 = 0;
    }
    
    if(BUNTU_REAR2 == 0) {//后拨按钮2   
        TimerSetSec(0);//清楚按键状态
        if(count_small2 < 30) {
            count_small2++;
        } else {
            count_small2 = 0;
            if(count2 < 3000) {
                count2++;
            }
            if(count2 == 100) {
                if(count1 == 0) {//小的按键不能按下
                    if(mode_count == 0) {//未进入一起按下的模式
                        teae_flag = 0;
                        return 0x12;    
                    }
                }   
                #if BACK
                
                #else
                else if(count1 > 100) {
                    if(mode_count == 0) {//未进入一起按下的模式
                        teae_flag = 0;
                        return 0x11;
                    }
                }
                #endif
            }
            if(count2 == 2000) {
                //长按进入
                if(count1 == 0) {//小的按键不能按下
                    if(mode_count == 0) {//未进入一起按下的模式
                        teae_flag = 0;
                        return 0x02;    
                    }
                }
            }
        }
    } else {
        //组合 后拨 按键 检测
        if(mode_count == 0) {
            if( ( ( (count1 > 50)&&(count1 < 3000) ) || (teae_flag == 1) ) && ( (count2 > 50)&&(count2 < 1500) ) ) {
                count1 = 0;
                count2 = 0;
                teae_flag = 0;
                //return 0x11;
            } else if( (count2 > 50)&&(count2 < 1500) ) {//后拨快速放开
                count2 = 0;
                teae_flag = 0;
                //return 0x12;
            } else if(count2 > 2000) {
                count2 = 0;
                teae_flag = 0;
                return 0x22;
            }
        }
        count_small2 = 0;
        count2 = 0;
    }
    
    if(BUNTU_BEHIND1 == 0) {//前拨按钮1
        TimerSetSec(0);//清楚按键状态
        if(count_small3 < 30) {
            count_small3++;
        } else {
            count_small3 = 0;
            if(count3 < 3000) {
                count3++;
            }
            if(count3 == 100) {
                return 0x13;
            }
            if(count3 == 2000) {
                //长按进入
                return 0x03;
            }
        }
    } else {
        if(mode_count == 0) {
            if( (count3 > 50)&&(count3 < 1500) ) {
                count3 = 0;
                //return 0x13;
            } else if(count3 > 1500) {
                count3 = 0;
                return 0x23;
            }
        }
        count_small3 = 0;
        count3 = 0;
    } 
    
    if(BUNTU_BEHIND2 == 0) {//前拨按钮2
        TimerSetSec(0);//清楚按键状态
        if(count_small4 < 30) {
            count_small4++;
        } else {
            count_small4 = 0;
            if(count4 < 3000) {
                count4++;
            }
            if(count4 == 2000) {
                //长按进入
                return 0x04;
            }
        }
    } else {
        count_small4 = 0;
        count4 = 0;
    }
    
    if(BUNTU_MODE == 0) {//模式按键
        TimerSetSec(0);//清楚按键状态
        if(count_small5 < 30) {
            count_small5++;
        } else {
            count_small5 = 0;
            if(count5 < 3000) {
                count5++;
            }
            if(count5 == 2000) {
                //长按进入
                //return 0x05;
                return 0x30;
            }
        }
    } else {
        if(count5 > 2000) {
            count_small5 = 0;
            count5 = 0;
            return 0x40;
        }
        count_small5 = 0;
        count5 = 0;
    }
    //组合按键
    if( (count3 > 1500) && (count2 > 1500) ) {//两颗按键同时按下
        if(mode_count < 200) {
            mode_count++;
            //TimerSetSec(0);//test
        } else {
            return 0x30;
        }
    } else {
        if(mode_count == 200) {
            mode_count = 0;
            return 0x40;
        }
    }
    return 0x00;
}
/**********************************************函数定义***************************************************** 
* 函数名称: void BuntuSleep(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 睡眠省电  
* 作    者: by lhb_steven
* 日    期: 2016/3/18
************************************************************************************************************/ 
void BuntuSleep(void) { 
    PB_CR2_C24 = 1;
    PB_CR2_C25 = 1;
    PB_CR2_C26 = 1;
    PB_CR2_C27 = 1;
    PB_CR2_C20 = 1;
    PA_CR2_C22 = 0;//关闭通讯中断 只接受按键
    DelayMs(100);
    MCUSLEEP
}
/**********************************************函数定义***************************************************** 
* 函数名称: void BuntuOpen(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 退出休眠状态  
* 作    者: by lhb_steven
* 日    期: 2016/3/18
************************************************************************************************************/ 
void BuntuOpen(void) { 
    PB_CR2_C24 = 0;
    PB_CR2_C25 = 0;
    PB_CR2_C26 = 0;
    PB_CR2_C27 = 0;
    PB_CR2_C20 = 0;
    EXTI_SR1 = 0xff;
    PA_CR2_C22 = 1;//打开通讯中断 只接受按键
}

#pragma vector=10
__interrupt void EXTI0_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin0);
    BuntuOpen();
    INTEN
    return;
}

#pragma vector=14
__interrupt void EXTI4_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin4);
    BuntuOpen();
    INTEN
    return;
}


#pragma vector=15
__interrupt void EXTI5_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin5);
    BuntuOpen();
    INTEN
    return;
}

#pragma vector=16
__interrupt void EXTI6_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin6);
    BuntuOpen();
    INTEN
    return;
}

#pragma vector=17
__interrupt void EXTI7_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin7);
    BuntuOpen();
    INTEN
    return;
}


//#pragma vector=8
//__interrupt void EXTIB6_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=13
//__interrupt void EXTIB1_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=14
//__interrupt void EXTIB2_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=15
//__interrupt void EXTIB3_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=16
//__interrupt void EXTIB4_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=17
//__interrupt void EXTIB5_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=9
//__interrupt void EXTIB7_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=10
//__interrupt void EXTIB8_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=11
//__interrupt void EXTIB9_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=18
//__interrupt void EXTIB10_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=19
//__interrupt void EXTIB11_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=20
//__interrupt void EXTIB12_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=21
//__interrupt void EXTIB13_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=22
//__interrupt void EXTIB14_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}


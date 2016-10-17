/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：main.c
*
* 文件标识：三色LED
* 摘    要：不带显示屏
* 当前版本：v1.0
* 作    者：lhb Steven
* 完成日期：2016/3/14
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
//PA2 通讯-后拨
//PA3 通讯-码表

//PB0 后拨电源使能

//PB3电源电压检测
//PB4电源电压检测使能

//PB5 按键2
//PB6 状态指示灯

//PB7 按键1

//PD0 上拉使能

//PC0 电源-R
//PC1 电源-G
//PC4 电量-B

//PC5 ANT+
//PC6 ANT-
*******************************************************************************/
#include "Eeprom.h"
#include "Com.h"
#include "Sys.h"
#include "buntu.h"
#include "Led.h"
#include "Menu.h"
#include "Time.h"
#include "Delay.h"
#include "Power.h"
#include "Ant+.h"

int main( void ) {
  
    SysInit();
    EeepromInit();
    BuntuInit();
    LedInit();
    MenuInit();
    ComInit();
    TimerInit();
    //PowerInit();
    /*Ant模块初始化*/
    //AntInit();
    /*关闭ANt+模块*/
   // AntSend(0);
    DelayMs(100);//等待系统上电稳定
    //while(1);
    INTEN
    while(1) {
        MenuModeSet( BuntuRead() );//按键和菜单服务
        LedTimeService();//led闪烁服务
        MenuServiceTime();//自动换档服务
        ComAskCmd();//回应
        if(ComGetFlag() == 0x80) {//通讯服务
            ComClearFlag();
            TimerSetSec(0);
            BuntuOpen();
            //LedSetModeFlicker(1);
            switch(ComGetData(0)) {
                case front:
                switch(ComGetData(1)) {
                    case dce_gear:
                        MenuSetBeind(ComGetData(2));
                    break;
                }
                break;
                case behind: 
                switch(ComGetData(1)) {
                    case dce_gear:
                        
                    break;
                }
                break;
                //已经没有电量了
                case dce_powe:
                    if(MenuGetMode() == 2) {
                    
                    } else if(MenuGetMode() == 3) {
                    
                    } else {
                        LedSetMode(ComGetData(1)+1);
                        LedSetPowerFlag(1);
                    }
                break;
            }
        } else { //只有在没数据的时候才可以休眠
            if(TimerGetSec() > 2) {
//                static u8 add_flag = 0;
//                static u8 add_num = 0;
                
                TimerSetSec(0);
//                if(add_flag == 0) {
//                    MenuModeSet(0x11);
//                } else {
//                    MenuModeSet(0x12);
//                }
//                if(add_num < 10) {
//                    add_num++;
//                } else {
//                    add_num = 0;
//                    if(add_flag == 0) {
//                        add_flag = 1;
//                    } else {
//                        add_flag = 0;
//                    }
//                }
                BuntuSleep();
            }
        }
    }
}

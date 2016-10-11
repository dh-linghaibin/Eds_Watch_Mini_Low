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
*******************************************************************************/
#include "Eeprom.h"
#include "Com.h"
#include "Sys.h"
#include "buntu.h"
#include "Led.h"
#include "Menu.h"
#include "Time.h"
#include "Delay.h"

int main( void ) {
    SysInit();
    EeepromInit();
    BuntuInit();
    LedInit();
    MenuInit();
    ComInit();
    TimerInit();
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
            if(TimerGetSec() > 60) {
                TimerSetSec(0);
                BuntuSleep();
            }
        }
    }
}

/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�main.c
*
* �ļ���ʶ����ɫLED
* ժ    Ҫ��������ʾ��
* ��ǰ�汾��v1.0
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/14
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
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
    DelayMs(100);//�ȴ�ϵͳ�ϵ��ȶ�
    //while(1);
    INTEN
    while(1) {
        MenuModeSet( BuntuRead() );//�����Ͳ˵�����
        LedTimeService();//led��˸����
        MenuServiceTime();//�Զ���������
        ComAskCmd();//��Ӧ
        if(ComGetFlag() == 0x80) {//ͨѶ����
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
        } else { //ֻ����û���ݵ�ʱ��ſ�������
            if(TimerGetSec() > 60) {
                TimerSetSec(0);
                BuntuSleep();
            }
        }
    }
}

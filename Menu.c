/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Menu.c
*
* 文件标识：V
* 摘    要：菜单内核
*
*
* 当前版本：V1.0
* 作    者：lhb Steven
* 完成日期：2016/3/17
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Menu.h"
#include "Led.h"
#include "Com.h"
#include "Power.h"//显示电压用

typedef struct DataNode
{
    u8 mode;
    u8 continuous;
    u8 behind_set_up;//加档标志位
    u8 behind_set_up_count;//加档标志位
    u8 beind_sta;//前拨档位
    
} tDataNode;
/***********************************************变量声明*****************************************************
* 功    能: caidan  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
static tDataNode menu;
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 菜单参数初始化  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
void MenuInit(void) { 
    menu.mode = 0x00;
    menu.continuous = 0x00;
    menu.behind_set_up = 0x00;
}
/**********************************************函数定义***************************************************** 
* 函数名称: u8 MenuGetMode(void) 
* 输入参数: void 
* 返回参数: u8  
* 功    能: 模式状态  
* 作    者: by lhb_steven
* 日    期: 2016/3/26
************************************************************************************************************/ 
u8 MenuGetMode(void) { 
    return menu.mode;
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuModeSet(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能: 更新相应模式进入相应功能  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
void MenuModeSet(u8 cmd) { 
    switch( cmd ) {
        case 0x01://后拨减档长按
        if(menu.mode == 0) {//连续换挡
            menu.continuous = 2;
            LedSetModeFlicker(11);//提示正在自动换档
        } else if(1 == menu.mode) {//进入后拨微调模式
            menu.mode = 2;
            LedSetPower(2);
        }
        break;
        case 0x02://后拨长按进入
        if(menu.mode == 0) {//连续换挡
            menu.continuous = 1;
            LedSetModeFlicker(11);//提示正在自动换档
        } else if(1 == menu.mode) {//进入后拨微调模式
            menu.mode = 2;
            LedSetPower(2);
        }
        break;
        case 0x03://前拨长按进入
        if(menu.mode == 0) {//连续换挡
         
        } else if(1 == menu.mode) {//进入前拨微调模式
            menu.mode = 3;
            LedSetPower(3);
        }
        break;
        case 0x04:
        break;
        case 0x05:
        break;
        case 0x06:
        break;
        case 0x11://后拨加
        LedSetModeFlicker(1);
        if(menu.mode == 0) {//加档
            ComSendCmdWatch(front,add_stal,0x00,0x00);//后拨加档
           // ComSendCmdWatch(add_stal,0x00,0x00,0x00);//直接控制后拨 不经过主控
        } else if(menu.mode == 2) {//后拨微调
            ComSendCmdWatch(front,add_setp,0x00,0x00);//后拨加档
           // ComSendCmdWatch(add_setp,0x00,0x00,0x00);
        } else if(menu.mode == 3) {//前拨微调
            ComSendCmdWatch(behind,add_setp,0x00,0x00);//后拨加档
        }
        //PowerGet();
       // LedSetMode(BattertGetLevel()+1);
       // LedSetPowerFlag(1);
        
        break;
        case 0x12://后拨减
        LedSetModeFlicker(1);
        if(menu.mode == 0) {//减档
            ComSendCmdWatch(front,sub_stal,0x00,0x00);//后拨减档
             //ComSendCmdWatch(sub_stal,0x00,0x00,0x00);//直接控制后拨 不经过主控
        } else if(menu.mode == 2) {//后拨微调
            ComSendCmdWatch(front,sub_setp,0x00,0x00);//后拨加档
            //ComSendCmdWatch(sub_setp,0x00,0x00,0x00);
        } else if(menu.mode == 3) {//前拨微调
            ComSendCmdWatch(behind,sub_setp,0x00,0x00);//后拨加档
        }
       // PowerGet();
       // LedSetMode(BattertGetLevel()+1);
       // LedSetPowerFlag(1);
        
        break;
        case 0x13://前拨按下
        LedSetModeFlicker(1);
        if(menu.mode == 0) {//只有在设置模式的时候才可以换挡
            menu.behind_set_up_count = 0;
            if(menu.behind_set_up == 0) {
                ComSendCmdWatch(behind,sub_exchange,0x00,0x00);//前拨换挡
                menu.behind_set_up = 1;
            } else if(menu.behind_set_up == 1) {
                if(menu.beind_sta == 0) {
                    ComSendCmdWatch(behind,set_down,0x00,0x00);//前拨换挡sub_exchange
                } else {
                    ComSendCmdWatch(behind,set_up,0x00,0x00);//前拨换挡sub_exchange 
                }
            } else if(menu.behind_set_up == 2) {
                ComSendCmdWatch(behind,set_down,0x00,0x00);//前拨换挡sub_exchange
            }
        }
        //ComSendCmdWatch(front,sub_stal,0x00,0x00);
        break;
        case 0x14:
        break;
        case 0x15:
        break;
        case 0x16:
        break;
        case 0x21://换挡自动退出
            menu.continuous = 0;//停止
            LedSetModeFlicker(0);//自动换档结束
        break;
        case 0x22://自动换挡退出
            menu.continuous = 0;//停止
            LedSetModeFlicker(0);//自动换档结束
        break;    
        case 0x23://自动换挡推出
        break;    
        case 0x24:
        break;    
        case 0x25:
        break;    
        case 0x26:
        break; 
        case 0x30://长按5s
        LedSetModeFlicker(100);
        break;
        case 0x40://长安5s放开
        if(menu.mode == 0) {
            menu.mode = 1;
            LedSetPower(1);
        } else if(menu.mode == 1) {//回到正常模式
            menu.mode = 0;
        } else if(menu.mode == 2) {//设置后拨微调档位值
            menu.mode = 0;
            LedSetPower(0);
            ComSendCmdWatch(set_inti,0x00,0x00,0x00);
        } else if(menu.mode == 3) {//设置前拨微调档位值
            menu.mode = 0;
            LedSetPower(0);
            ComSendCmdWatch(set_inti,0x00,0x00,0x00);
        }
        LedSetModeFlicker(1);
        break;
        default:
        break;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuServiceTime(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 菜单时间服务函数，主要用于后拨的自动换档  
* 作    者: by lhb_steven
* 日    期: 2016/3/18
************************************************************************************************************/ 
void MenuServiceTime(void) { 
    static u16 time_count = 0;
    if(time_count < 10000) {
        time_count++;
    } else {
        time_count = 0;
        if(menu.continuous == 1) {
            ComSendCmdWatch(sub_stal,0x00,0x00,0x00);//后拨加档
        } else if(menu.continuous == 2) {
            ComSendCmdWatch(add_stal,0x00,0x00,0x00);//后拨加档
        }
        if(menu.behind_set_up == 1) {
            if(menu.behind_set_up_count < 19) {
                menu.behind_set_up_count++;
            } else {
                menu.behind_set_up_count = 0;
                menu.behind_set_up = 0;
            }
        } else if(menu.behind_set_up == 2){
            
        }
    }
}


/**********************************************函数定义***************************************************** 
* 函数名称: void MenuSetBeind(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能: 设置前拨档位  
* 作    者: by lhb_steven
* 日    期: 2016/6/2
************************************************************************************************************/ 
void MenuSetBeind(u8 cmd) { 
    menu.beind_sta = cmd;
}







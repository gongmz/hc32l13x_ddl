/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2016-02-16  1.0  XYZ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lcd.h"
#include "lpm.h"
#include "gpio.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                            
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')                                         
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                             
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
void App_PortCfg(void);
void App_LcdCfg(void);
/**
 ******************************************************************************
 ** \brief  ?????????
 ** 
 ** @param  ???
 ** \retval ???
 **
 ******************************************************************************/ 
int32_t main(void)
{
    Sysctrl_ClkSourceEnable(SysctrlClkRCL,TRUE);            ///< ??????RCL??????
    Sysctrl_SetRCLTrim(SysctrlRclFreq32768);                ///< ?????????????????????????????????32.768kHz

    Sysctrl_SetPeripheralGate(SysctrlPeripheralLcd,TRUE);   ///< ??????LCD??????
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);  ///< ??????GPIO??????
    
    App_PortCfg();               ///< LCD????????????
    App_LcdCfg();                ///< LCD????????????

    Lcd_ClearDisp();             ///< ??????
    Lcd_WriteRam(0,0x0f0f0f0f);  ///< ???????????????LCDRAM0
    Lcd_WriteRam(1,0x0f0f0f0f);  ///< ???????????????LCDRAM1

    while(1)
    {
        ;
    }
}

/**
 ******************************************************************************
 ** \brief  ???????????????GPIO??????
 **
 ** \return ???
 ******************************************************************************/
void App_PortCfg(void)
{
    Gpio_SetAnalogMode(GpioPortA, GpioPin9);  //COM0
    Gpio_SetAnalogMode(GpioPortA, GpioPin10); //COM1
    Gpio_SetAnalogMode(GpioPortA, GpioPin11); //COM2
    Gpio_SetAnalogMode(GpioPortA, GpioPin12); //COM3   

    Gpio_SetAnalogMode(GpioPortA, GpioPin8);  //SEG0
    Gpio_SetAnalogMode(GpioPortC, GpioPin9);  //SEG1
    Gpio_SetAnalogMode(GpioPortC, GpioPin8);  //SEG2
    Gpio_SetAnalogMode(GpioPortC, GpioPin7);  //SEG3
    Gpio_SetAnalogMode(GpioPortC, GpioPin6);  //SEG4
    Gpio_SetAnalogMode(GpioPortB, GpioPin15); //SEG5
    Gpio_SetAnalogMode(GpioPortB, GpioPin14); //SEG6
    Gpio_SetAnalogMode(GpioPortB, GpioPin13); //SEG7
    Gpio_SetAnalogMode(GpioPortB, GpioPin3);  //VLCDH
    Gpio_SetAnalogMode(GpioPortB, GpioPin4);  //VLCD3
    Gpio_SetAnalogMode(GpioPortB, GpioPin5);  //VLCD2
    Gpio_SetAnalogMode(GpioPortB, GpioPin6);  //VLCD1
    
}

/**
 ******************************************************************************
 ** \brief  ??????LCD
 **
 ** \return ???
 ******************************************************************************/
void App_LcdCfg(void)
{
    stc_lcd_cfg_t LcdInitStruct;
    stc_lcd_segcom_t LcdSegCom;

    LcdSegCom.u32Seg0_31 = 0xffffff00;                              ///< ??????LCD_POEN0????????? ??????SEG0~SEG7
    LcdSegCom.stc_seg32_51_com0_8_t.seg32_51_com0_8 = 0xffffffff;   ///< ?????????LCD_POEN1????????? ????????????????????????
    LcdSegCom.stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = 0;          ///< ??????COM0~COM3
    LcdSegCom.stc_seg32_51_com0_8_t.segcom_bit.Mux = 0;             ///< Mux=0,Seg32_35=0,BSEL=1??????:???????????????????????????????????????????????????
    LcdSegCom.stc_seg32_51_com0_8_t.segcom_bit.Seg32_35 = 0;
    Lcd_SetSegCom(&LcdSegCom);                                      ///< LCD COMSEG????????????

    LcdInitStruct.LcdBiasSrc = LcdExtCap;                          ///< ?????????????????????????????????????????????
    LcdInitStruct.LcdDuty = LcdDuty4;                              ///< 1/4duty
    LcdInitStruct.LcdBias = LcdBias3;                              ///< 1/3 BIAS
    LcdInitStruct.LcdCpClk = LcdClk2k;                             ///< ???????????????????????????2kHz
    LcdInitStruct.LcdScanClk = LcdClk128hz;                        ///< LCD??????????????????128Hz
    LcdInitStruct.LcdMode = LcdMode0;                              ///< ????????????0
    LcdInitStruct.LcdClkSrc = LcdRCL;                              ///< LCD????????????RCL
    LcdInitStruct.LcdEn   = LcdEnable;                             ///< ??????LCD??????
    Lcd_Init(&LcdInitStruct);
}


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



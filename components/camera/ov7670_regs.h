/*
 * @file ov7670_regs.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * 
 * @brief
 * Registers for the OV7670 Camera.
 */

#ifndef __REG_REGS_H__
#define __REG_REGS_H__

#define VREF					0x03

#define COM3					0x0C /* Common Control 3			*/
#define COM3_DCW_EN				0x04 /* DCW Enable					*/

#define CLKRC					0x11 /* Internal Clock 				*/
#define CLKRC_NO_PRESCALE		0x40 /* Use external clock directly */
#define CLKRC_RES				0x80

#define COM8					0x13

#define REG_MIDH                0x1C /* Manufacturer ID Byte – High */
#define REG_MIDL                0x1D /* Manufacturer ID Byte – Low  */
#define REG_PID                 0x0A /* Product ID Number MSB 		*/
#define REG_VER                 0x0B /* Product ID Number LSB 		*/

#define MVFP					0x1E /* Mirror/VFlip enable			*/
#define MVFP_SET_MIRROR(r, x)	((r&0xDF)|((x&0x01)<<5))
#define MVFP_SET_FLIP(r, x)		((r&0xEF)|((x&0x01)<<4))

#define COM7                    0x12 /* Common Control 7         	*/
#define COM7_RESET              0x80 /* SCCB Register Reset      	*/
#define COM7_FMT_RGB            0x04 /* Output format RGB        	*/
#define COM7_FMT_YUV            0x00 /* Output format YUV422      	*/
#define COM7_RES_VGA            0x00 /* Resolution VGA           	*/
#define COM7_RES_CIF            0x20
#define COM7_RES_QVGA           0x10 /* Resolution QVGA          	*/
#define COM7_RES_QCIF           0x08
#define COM7_SET_FMT(r, x)      ((r&0xFA)|(x&0x05))
#define COM7_SET_RES(r, x)      ((r&0xC7)|(x&0x38))
#define COM7_SET_CBAR(r, x)     ((r&0xFE)|(x&0x01))

#define COM8					0x13
#define COM8_SET_AWB(r, x)		((r&0xFD)|((x&0x01)<<1))
#define COM8_SET_AGC(r, x)		((r&0xFB)|((x&0x01)<<2))
#define COM8_SET_AEC(r, x)      ((r&0xFE)|(x&0x01))

#define COM10					0x15

#define HSTART					0x17
#define VSTART					0x19
#define HSTOP					0x18
#define VSTOP					0x1A
#define HREF					0x32

#define TSLB					0x3A /* Line Buffer Test Option		*/
#define TSLB_SET_RESIZE(r, x)	((r&0xFE)|((x&0x01)<<0))

#define COM11					0x3B /* Common Control 11			*/
#define COM11_AUTO_HZ			0x10 /* Enable 50/60 Hz auto detect */
#define COM11_EXP_LESS			0x02 /* Exposure time can be less...*/

#define COM14					0x3E /* Common Control 14			*/
#define COM14_PCLK_DIV_4		0x02 /* PCLK Divider by 4			*/
#define COM14_SCALE_MAN			0x08 /* Manual scaling enabled		*/
#define COM14_SCALE_PCLK		0x10 /* DCW and scaling PCLK		*/
#define COM14_SET_SCALE(r, x)	((r&0xF7)|((x&0x01)<<3))

#define COM15					0x40 /* Common Control 15		 	*/
#define COM15_FMT_RGB565		0x10 /* RGB output format RGB565 	*/
#define COM15_FMT_YUV			0x00 /* Default output mode 	 	*/
#define COM15_SET_FMT(r, x)     ((r&0xCF)|(x&0x48))

#define COM17					0x42
#define COM17_SET_DSP_CBAR(r,x)	((r&0xF7)|(x&0x01)<<3)

#define AWBCTR0					0x6F

#define SCALING_XSC				0x70
#define SCALING_YSC				0x71
#define SCALING_DCWCTR			0x72
#define SCALING_PCLK_DIV		0x73

#define SCALING_PCLK_DELAY		0xA2

#define RSVD_COLOR				0xB0

#endif //__REG_REGS_H__

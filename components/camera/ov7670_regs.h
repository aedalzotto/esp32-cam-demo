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

#define COM15					0x40 /* Common Control 15		 	*/
#define COM15_FMT_RGB565		0x10 /* RGB output format RGB565 	*/
#define COM15_FMT_YUV			0x00 /* Default output mode 	 	*/
#define COM15_SET_FMT(r, x)     ((r&0xCF)|(x&0x48))

#define COM17					0x42
#define COM17_SET_DSP_CBAR(r,x)	((r&0xF7)|(x&0x01)<<3)


#endif //__REG_REGS_H__

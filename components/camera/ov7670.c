/*
 * @file ov7670.c
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * 
 * @copyright
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * @brief
 * OV7670 driver based on the OV7725 driver that is is part of the OpenMV project.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sccb.h"
#include "ov7670.h"
#include "ov7670_regs.h"
#include <stdio.h>

static int reset(sensor_t *sensor)
{
    // Reset all registers
    SCCB_Write(sensor->slv_addr, COM7, COM7_RESET);

    // Delay 10 ms
    systick_sleep(10);

    // no need to write default registers

    // Delay
    systick_sleep(30);

    return 0;
}

static int set_pixformat(sensor_t *sensor, pixformat_t pixformat)
{
    int ret=0;
    uint8_t reg7 = SCCB_Read(sensor->slv_addr, COM7);
    uint8_t reg15 = SCCB_Read(sensor->slv_addr, COM7);

    switch (pixformat) {
        case PIXFORMAT_RGB565:
            reg7 =  COM7_SET_FMT(reg7, COM7_FMT_RGB);
            reg15 = COM15_SET_FMT(reg15, COM15_FMT_RGB565);
            break;
        case PIXFORMAT_YUV422:
        case PIXFORMAT_GRAYSCALE:
            reg7 =  COM7_SET_FMT(reg7, COM7_FMT_YUV);
            reg15 = COM15_SET_FMT(reg15, COM15_FMT_YUV);
            break;
        default:
            return -1;
    }

    // Write back register COM7
    ret = SCCB_Write(sensor->slv_addr, COM7, reg7);
    ret |= SCCB_Write(sensor->slv_addr, COM15, reg15);

    // Delay
    systick_sleep(30);

    return ret;
}

static int set_framesize(sensor_t *sensor, framesize_t framesize)
{
    int ret=0;
    uint8_t reg7 = SCCB_Read(sensor->slv_addr, COM7);

    switch(framesize){
    case FRAMESIZE_VGA:
        reg7 = COM7_SET_RES(reg7, COM7_RES_VGA);
        break;
    case FRAMESIZE_QVGA:
        reg7 = COM7_SET_RES(reg7, COM7_RES_QVGA);
        break;
    case FRAMESIZE_CIF:
        reg7 = COM7_SET_RES(reg7, COM7_RES_CIF);
        break;
    case FRAMESIZE_QCIF:
        reg7 = COM7_SET_RES(reg7, COM7_RES_QCIF);
        break;
    default:
        return -1;
    }

    ret = SCCB_Write(sensor->slv_addr, COM7, reg7);

    // Delay
    systick_sleep(30);

    if (ret == 0) {
        sensor->framesize = framesize;
    }

    return ret;
}

static int set_colorbar(sensor_t *sensor, int enable)
{
    int ret=0;
    uint8_t reg = SCCB_Read(sensor->slv_addr, COM7);

    // Enable colorbar test pattern output
    reg = COM7_SET_CBAR(reg, enable);

    ret = SCCB_Write(sensor->slv_addr, COM7, reg);

    reg = SCCB_Read(sensor->slv_addr, COM17);
    // Enable DSP colorbar output
    reg = COM17_SET_DSP_CBAR(reg, enable);

    ret |= SCCB_Write(sensor->slv_addr, COM17, reg);

    return ret;
}

static int set_whitebal(sensor_t *sensor, int enable)
{
    // Read register COM8
    uint8_t reg = SCCB_Read(sensor->slv_addr, COM8);

    // Set white bal on/off
    reg = COM8_SET_AWB(reg, enable);

    // Write back register COM8
    return SCCB_Write(sensor->slv_addr, COM8, reg);
}

static int set_gain_ctrl(sensor_t *sensor, int enable)
{
    // Read register COM8
    uint8_t reg = SCCB_Read(sensor->slv_addr, COM8);

    // Set white bal on/off
    reg = COM8_SET_AGC(reg, enable);

    // Write back register COM8
    return SCCB_Write(sensor->slv_addr, COM8, reg);
}

static int set_exposure_ctrl(sensor_t *sensor, int enable)
{
    // Read register COM8
    uint8_t reg = SCCB_Read(sensor->slv_addr, COM8);

    // Set white bal on/off
    reg = COM8_SET_AEC(reg, enable);

    // Write back register COM8
    return SCCB_Write(sensor->slv_addr, COM8, reg);
}

static int set_hmirror(sensor_t *sensor, int enable)
{
    uint8_t reg = SCCB_Read(sensor->slv_addr, MVFP);

    // Set mirror on/off
    reg = MVFP_SET_MIRROR(reg, enable);

    return SCCB_Write(sensor->slv_addr, MVFP, reg);
}

static int set_vflip(sensor_t *sensor, int enable)
{
    uint8_t reg = SCCB_Read(sensor->slv_addr, MVFP);

    // Set mirror on/off
    reg = MVFP_SET_FLIP(reg, enable);

    return SCCB_Write(sensor->slv_addr, MVFP, reg);
}

int ov7670_init(sensor_t *sensor)
{
    // Set function pointers
    sensor->reset = reset;
    sensor->set_pixformat = set_pixformat;
    sensor->set_framesize = set_framesize;
    sensor->set_colorbar = set_colorbar;
    sensor->set_whitebal = set_whitebal;
    sensor->set_gain_ctrl = set_gain_ctrl;
    sensor->set_exposure_ctrl = set_exposure_ctrl;
    sensor->set_hmirror = set_hmirror;
    sensor->set_vflip = set_vflip;

    // Retrieve sensor's signature
    sensor->id.MIDH = SCCB_Read(sensor->slv_addr, REG_MIDH);
    sensor->id.MIDL = SCCB_Read(sensor->slv_addr, REG_MIDL);
    sensor->id.PID = SCCB_Read(sensor->slv_addr, REG_PID);
    sensor->id.VER = SCCB_Read(sensor->slv_addr, REG_VER);

    // Set sensor flags
    SENSOR_HW_FLAGS_SET(sensor, SENSOR_HW_FLAGS_VSYNC, 1);
    SENSOR_HW_FLAGS_SET(sensor, SENSOR_HW_FLAGS_HSYNC, 0);
    SENSOR_HW_FLAGS_SET(sensor, SENSOR_HW_FLAGS_PIXCK, 1);
    SENSOR_HW_FLAGS_SET(sensor, SENSOR_HW_FLAGS_FSYNC, 1);
    SENSOR_HW_FLAGS_SET(sensor, SENSOR_HW_FLAGS_JPEGE, 0);

    return 0;
}

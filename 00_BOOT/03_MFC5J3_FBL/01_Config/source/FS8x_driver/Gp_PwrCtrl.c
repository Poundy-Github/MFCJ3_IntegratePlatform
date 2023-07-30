/*
 * PwrCtrl.c
 *
 *  Created on: 2021
 *      Author: liuyang
 */

#include "sbc_fs8x.h"
#include "sbc_fs8x_assert.h"
#include "sbc_fs8x_common.h"
#include "sbc_fs8x_communication.h"
#include "sbc_fs8x_map.h"
#include "I2c.h"

static void reverseByteArray(uint8_t* start, uint32_t size)
{
    uint8_t* lo = start;
    uint8_t* hi = start + size - 1;
    uint8_t swap;
    while (lo < hi)
    {
        swap = *lo;
        *lo++ = *hi;
        *hi-- = swap;
    }
}

fs8x_status_t FS8x_MCU_I2C_SendData(uint8_t* txFrame, uint8_t frameSizeBytes, uint8_t i2cAddress)
{
	I2c_ErrorType status;
    uint16_t slaveAddress;
    uint16_t dataSize;
  //  DEV_ASSERT(txFrame != NULL);
    slaveAddress = (uint16_t)i2cAddress;
    reverseByteArray(txFrame, frameSizeBytes);
    dataSize = (uint16_t)frameSizeBytes;
    status = I2c_SyncWrite(0, txFrame, dataSize, slaveAddress);
    if (status != I2C_NO_ERR)
    {
        return fs8xStatusError;
    }
    return fs8xStatusOk;
}

fs8x_status_t FS8x_MCU_I2C_ReceiveData(uint8_t frameSizeBytes, uint8_t i2cAddress, uint8_t* rxFrame)
{
	I2c_ErrorType status;
    uint16_t slaveAddress;
    uint16_t dataSize;
    slaveAddress = (uint16_t)i2cAddress;
    dataSize = (uint16_t)frameSizeBytes;
    status = I2c_SyncRead(0,rxFrame, dataSize, slaveAddress);
    reverseByteArray(rxFrame, frameSizeBytes);
    if (status != I2C_NO_ERR)
    {
        return fs8xStatusError;
    }
    return fs8xStatusOk;
}

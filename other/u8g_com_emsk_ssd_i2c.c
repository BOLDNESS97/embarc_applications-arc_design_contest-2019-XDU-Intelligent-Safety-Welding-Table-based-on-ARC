/*

  u8g.h

  Universal 8bit Graphics Library

  Copyright (c) 2011, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
/*
 * Modified for port to ARC embARC platform
 * by Wayne Ren wei.ren@synopsys.com, Synopsys, Inc.
 */

#include "u8g.h"

#include "embARC.h"
#include "dev_iic.h"

#define I2C_SLA		0x3c
#define I2C_CMD_MODE	0x000
#define I2C_DATA_MODE	0x040
#define I2C_CONTINUE_BIT 0x080


static DEV_IIC *oled_ssd1306;
static uint8_t data_flag;


Inline int32_t oled_ssd1306_write(uint8_t *buf, uint32_t cnt)
{
	int32_t ercd;

	/** make sure set the temp sensor's slave address */
	oled_ssd1306->iic_control(IIC_CMD_MST_SET_TAR_ADDR, CONV2VOID(I2C_SLA));
	oled_ssd1306->iic_control(IIC_CMD_MST_SET_NEXT_COND, CONV2VOID(IIC_MODE_STOP));

	ercd = oled_ssd1306->iic_write(buf, cnt);

	return ercd;
}

Inline int32_t oled_ssd1306_write_cmd(uint8_t cmd)
{
	uint8_t cmd_data_pre[2];

	cmd_data_pre[0] = I2C_CMD_MODE;
	cmd_data_pre[1] = cmd;
	u8g_Delay(500);	// cmd needs some delay

	return oled_ssd1306_write(cmd_data_pre, 2);
}

Inline int32_t oled_ssd1306_write_data(uint8_t data)
{
	uint8_t cmd_data_pre[2];

	cmd_data_pre[0] = I2C_DATA_MODE;
	cmd_data_pre[1] = data;
	u8g_Delay(180);	// data also needs some delay

	return oled_ssd1306_write(cmd_data_pre, 2);
}

uint8_t u8g_com_emsk_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
	uint8_t *ptr;
	int32_t ercd;

	switch(msg) {
		case U8G_COM_MSG_INIT:
			oled_ssd1306 = iic_get_dev(arg_val);
			ercd = oled_ssd1306->iic_open(DEV_MASTER_MODE, IIC_SPEED_FAST);
			if ((ercd != E_OK) || (ercd != E_OPNED)) {
				return 0;
			}
			oled_ssd1306->iic_control(IIC_CMD_MST_SET_SPEED_MODE, CONV2VOID(IIC_SPEED_FAST));
			break;

		case U8G_COM_MSG_STOP:
			break;

		case U8G_COM_MSG_RESET:
			break;

		case U8G_COM_MSG_CHIP_SELECT:
			break;
		case U8G_COM_MSG_WRITE_BYTE:
			oled_ssd1306_write_cmd(arg_val);
			break;

		case U8G_COM_MSG_WRITE_SEQ:
			ptr = arg_ptr;
			while( arg_val--) {
				oled_ssd1306_write_data(*ptr);
				ptr++;
			}
			break;
		case U8G_COM_MSG_WRITE_SEQ_P:
			break;
		case U8G_COM_MSG_ADDRESS:
			data_flag = arg_val;/* define cmd (arg_val = 0) or data mode (arg_val = 1) */
			break;
	}
	return 1;
}


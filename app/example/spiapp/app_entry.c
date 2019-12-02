/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "aos/cli.h"
#include "aos/kernel.h"
#include "ulog/ulog.h"
#include "aos/yloop.h"

#include "netmgr.h"
#include "iot_export.h"
#include "iot_import.h"
#include "app_entry.h"

#include <k_api.h>
#include "aos/hal/spi.h"

#define SPI_TEST_LENGTH		512

static void handle_spi_test_cmd(char *pwbuf, int blen, int argc, char **argv)
{
	spi_dev_t spi_dev;
	uint16_t tx_len, rx_len;
	uint16_t i, ret;	

	
	uint8_t *write_data;
	uint8_t *receive_data; 
	
	spi_dev.port = 0;
	spi_dev.config.freq = 60;

    if(strcmp(argv[1], "master") == 0)
    {
		spi_dev.config.mode = HAL_SPI_MODE_MASTER;
    }
	else if(strcmp(argv[1], "slave") == 0)
	{
		spi_dev.config.mode = HAL_SPI_MODE_SLAVE;
	}
	else
	{
		aos_cli_printf("spi_test master/salve tx/rx len\r\n");
	}
	
	
	hal_spi_init(&spi_dev);

	if(strcmp(argv[2], "tx") == 0)
	{
		if(argc < 3)
		{
			tx_len = SPI_TEST_LENGTH;
		}
		else
		{
			tx_len = atoi(argv[3]);
		}
		aos_cli_printf("spi tx_len:%d\r\n", tx_len);
		
        write_data = (uint8_t *)aos_malloc(tx_len);
        if (!write_data) 
		{
           aos_cli_printf("send msg allocate fail\n");
           goto _exit;
        }

		for(i=0; i<tx_len; i++)
		{
			write_data[i] = 0x00 + i;
		}

		ret = hal_spi_send(&spi_dev, write_data, tx_len, AOS_WAIT_FOREVER );
		
		aos_cli_printf("ret = %d\r\n", ret);

		for(i=0; i<tx_len; i++)
		{
			aos_cli_printf("write_data[%d]=%x\r\n", i, write_data[i]);
		}
		
		aos_free(write_data);
	}

	else if(strcmp(argv[2], "rx") == 0)
	{
		if(argc < 3)
		{
			rx_len = SPI_TEST_LENGTH;
		}
		else
		{
			rx_len = atoi(argv[3]);
		}
		
		aos_cli_printf("spi rx_len:%d\r\n", rx_len);
		
        receive_data = (uint8_t *)aos_malloc(rx_len);
        if (!receive_data) 
		{
           aos_cli_printf("recev msg allocate fail\n");
           goto _exit;
        }

		ret = hal_spi_recv(&spi_dev, receive_data, rx_len, AOS_WAIT_FOREVER );

		aos_cli_printf("ret = %d\r\n", ret);
		
		for(i=0; i<rx_len; i++)
		{
			aos_cli_printf("receive_data[%d]=%x\r\n", i, receive_data[i]);
		}

		aos_free(receive_data);
	}
	
_exit:
	if(ret = 0)
	{
		hal_spi_finalize(&spi_dev);
		aos_cli_printf("\r\nspi test error\r\n");
	}

}

static struct cli_command spi_test_cmd = { .name     = "spi_test",
                                           .help     = "spi_test [start]",
                                           .function = handle_spi_test_cmd };

int application_start(int argc, char **argv)
{
    aos_set_log_level(AOS_LL_DEBUG);

    aos_cli_register_command(&spi_test_cmd);
    IOT_SetLogLevel(IOT_LOG_DEBUG);

    aos_loop_run();

    return 0;
}

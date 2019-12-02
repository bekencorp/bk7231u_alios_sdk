#ifndef _SPI_PUB_H_
#define _SPI_PUB_H_

#define SPI_FAILURE                (1)
#define SPI_SUCCESS                (0)

#define SPI_DEV_NAME                "spi"

#define SPI_CMD_MAGIC              (0xe250000)
enum
{
    CMD_SPI_UNIT_ENABLE = SPI_CMD_MAGIC + 1,
    CMD_SPI_SET_MSTEN,
    CMD_SPI_SET_CKPHA,
    CMD_SPI_SET_CKPOL,
    CMD_SPI_SET_BITWIDTH,
    CMD_SPI_SET_NSSID,
    CMD_SPI_SET_CKR,
    CMD_SPI_RXINT_EN,
    CMD_SPI_TXINT_EN,
    CMD_SPI_RXOVR_EN,
    CMD_SPI_TXOVR_EN,
    CMD_SPI_RXFIFO_CLR,
    CMD_SPI_RXINT_MODE,
    CMD_SPI_TXINT_MODE,
    CMD_SPI_INIT_MSTEN,
    CMD_SPI_GET_BUSY,
	CMD_SPI_SET_RX_CALLBACK,
	CMD_SPI_SET_TX_NEED_WRITE_CALLBACK,
	CMD_SPI_SET_TX_FINISH_CALLBACK,
    CMD_SPI_DEINIT_MSTEN
};

#define USE_SPI_GPIO_14_17          (0)
#define USE_SPI_GPIO_30_33          (1)

struct spi_message
{
    void *send_buf;
    UINT32 send_len;

    void *recv_buf;
    UINT32 recv_len;
};

/*******************************************************************************
* Function Declarations
*******************************************************************************/
void spi_init(void);
void spi_exit(void);
void spi_isr(void);
/*master api*/
int bk_spi_master_init(UINT32 rate, UINT8 port, UINT32 mode);
int bk_spi_master_xfer(struct spi_message *msg);
int bk_spi_master_deinit(void);
/*slave api*/
int bk_spi_slave_init(UINT32 rate, UINT8 port, UINT32 mode);
int bk_spi_slave_xfer(struct spi_message *msg);
int bk_spi_slave_deinit(void);
#endif //_SPI_PUB_H_

#include "hal/ble.h"
#include "hal/spi.h"
#include <stdlib.h>

/***********************************************************************************************/
/* Macro Definitions
/***********************************************************************************************/

#define SPI_PORT SPI_BUS0_CS0
#define SLAVE_ENABLE_CMD_LEN 3

/***********************************************************************************************/
/* private data fields
/***********************************************************************************************/

static int fd;

/***********************************************************************************************/
/* Implementation of User Functions
/***********************************************************************************************/

void ble_init(void)
{
	// Configure BBG as SPI Master
    fd = spi_init(SPI_PORT);

	// Slave enable command is }A, 0, 0
    spi_word* tx_buffer = calloc(SLAVE_ENABLE_CMD_LEN, sizeof(spi_word));
    tx_buffer[0] = ('}' << 8) | 'A';

	// Rx buffer should be the same size as tx
	spi_word* rx_buffer = malloc(SLAVE_ENABLE_CMD_LEN * sizeof(spi_word));

	// Send the command and collect the response
    spi_transaction(fd, tx_buffer, rx_buffer, SLAVE_ENABLE_CMD_LEN, 1);

	// TODO: Check response is AOK
	
	// cleanup
	free(tx_buffer);
	free(rx_buffer);
}

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/***********************************************************************************************/
/* BBG SPI Ports
/***********************************************************************************************/

#define SPI_BUS0_CS0 "/dev/spidev0.0"
#define SPI_BUS1_CS0 "/dev/spidev1.0"
#define SPI_BUS1_CS1 "/dev/spidev1.1"

/***********************************************************************************************/
/* SPI Data Type (Adjust to Word Size)
/***********************************************************************************************/

typedef uint16_t spi_word;

/***********************************************************************************************/
/* SPI User Functions
/***********************************************************************************************/

// spi port will be one of SPI_BUS0_CS0, SPI_BUS1_CS0, SPI_BUS1_CS1
int spi_init(char* spiPort);

// obtain file descriptor by calling spi_init
// the caller of this function is responsible for allocating and freeing tx and rx buffers
void spi_transaction(const int spiFileDesc, spi_word* tx_buffer, spi_word* rx_buffer, const int transactionLen, const int numTransactions);

#endif

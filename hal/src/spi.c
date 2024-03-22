#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "hal/system.h"
#include "hal/spi.h"

/***********************************************************************************************/
/* Macro Definitions
/***********************************************************************************************/

#define NUM_SPI_PORTS 3
// BBG supports up to 48 MHz but the clock speed will likely be dictated by peripherals
#define SPI_CLOCK_SPEED_HZ (4 * 1000000)
#define SPI_WORD_SIZE_BITS (sizeof(spi_word) * 8)

/***********************************************************************************************/
/* BBG SPI Pin Configuration Data Structures
/***********************************************************************************************/

typedef struct {
    char* cs;
    char* d0; // AKA miso
    char* d1; // AKA mosi
    char* sclk;
} spi_pins_t;

enum pinIndex {
    SPI0_CS0,
    SPI1_CS0,
    SPI1_CS1,
};

static const spi_pins_t SPI_PIN_INFO[NUM_SPI_PORTS] = {
    // SPI0_CS0
    { .cs = "p9_17", .d0 = "p9_21", .d1 = "p9_18", .sclk = "p9_22" },
    // SPI1_CS0
    { .cs = "p9_28", .d0 = "p9_29", .d1 = "p9_30", .sclk = "p9_31" },
    // SPI1_CS1
    { .cs = "p9_42", .d0 = "p9_29", .d1 = "p9_30", .sclk = "p9_31" },
};

enum cmdIndex {
    SPI_CS,
    SPI_CLK,
    SPI_DATA,
};

static const char* SPI_PIN_CFG_CMD[] = {
    // SPI_CS
    "config-pin %s spi_cs",
    // SPI_CLK
    "config-pin %s spi_sclk",
    // SPI_DATA
    "config-pin %s spi"
};

/***********************************************************************************************/
/* Helper Functions
/***********************************************************************************************/

static void runConfigPin(const char* pin, const int CMD_INDEX)
{
    const int MAX_CMD_LEN = 25;
    char command[MAX_CMD_LEN + 1];
    snprintf(command, MAX_CMD_LEN, SPI_PIN_CFG_CMD[CMD_INDEX], pin);
    command[MAX_CMD_LEN] = 0;
    system_exec(command);
}

static void configurePins(const char* spiPort)
{
    spi_pins_t pins;

    if (strncmp(spiPort, SPI_BUS0_CS0, strlen(spiPort)) == 0) {
        pins = SPI_PIN_INFO[SPI0_CS0];
    } else if (strncmp(spiPort, SPI_BUS1_CS0, strlen(spiPort)) == 0) {
        pins = SPI_PIN_INFO[SPI1_CS0];
    } else if (strncmp(spiPort, SPI_BUS1_CS1, strlen(spiPort)) == 0) {
        pins = SPI_PIN_INFO[SPI1_CS1];
    } else {
        printf("Error: invalid port, aborting pin configuration");
        exit(1);
    }

    runConfigPin(pins.cs, SPI_CS);
    runConfigPin(pins.sclk, SPI_CLK);
    runConfigPin(pins.d0, SPI_DATA);
    runConfigPin(pins.d1, SPI_DATA);
}

static int getFileDescriptor(char* file, int accessMode)
{
    int fileDescriptor = open(file, accessMode);
    if (fileDescriptor < 0) {
        printf("Error: Unable to open %s", file);
        exit(1);
    }
    return fileDescriptor;
}

static void setParameter(int fileDescriptor, unsigned long parameter, int value)
{
    int status = ioctl(fileDescriptor, parameter, &value);
    if (status < 0) {
        printf("Error: Unable to set parameter (fd=%d, param=%ld, value=%d)", fileDescriptor, parameter, value);
        exit(1);
    }
}

/***********************************************************************************************/
/* Implementation of User Functions
/***********************************************************************************************/

int spi_init(char* spiPort)
{
    configurePins(spiPort);
    int spiFileDesc = getFileDescriptor(spiPort, O_RDWR);
    setParameter(spiFileDesc, SPI_IOC_WR_MODE, SPI_MODE_0);
    setParameter(spiFileDesc, SPI_IOC_WR_MAX_SPEED_HZ, SPI_CLOCK_SPEED_HZ);
    // This does not need to be set if the default 8-bit data width will suffice
    setParameter(spiFileDesc, SPI_IOC_WR_BITS_PER_WORD, SPI_WORD_SIZE_BITS);
    return spiFileDesc;
}

void spi_transaction(const int spiFileDesc, spi_word* tx_buffer, spi_word* rx_buffer, const int transactionLen, const int numTransactions)
{
    struct spi_ioc_transfer handleSpi = { .tx_buf = (unsigned long)tx_buffer, .rx_buf = (unsigned long)rx_buffer, .len = transactionLen };
    int status = ioctl(spiFileDesc, SPI_IOC_MESSAGE(numTransactions), &handleSpi);
    if (status < 0) {
        printf("Error: Unable to complete SPI transaction");
    }
}

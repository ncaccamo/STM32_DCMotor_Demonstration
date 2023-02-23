/**
*******************************************************************************
 * @file           : spi.c
 * @author         : Nicholas Caccamo
 * @brief          : SPI initialization
 ******************************************************************************
 */
#include <stm32g431xx.h>
#include <gpio.h>
#include <spi.h>
#include <timer.h>

/************************************************************************************************/
/**
 * Function to initialize the SPI3 peripheral.
 * Parameters: none
 * Returns: none
 */
void SPI3Init(){
    //SPI3 clock enabled in clockconfig.c and GPIO configured in gpio.c
    //1-line bidrectional data mode
    //SPI3->CR1 |= (SPI_CR1_BIDIMODE);
    //transmit-only mode
    //SPI3->CR1 |= (SPI_CR1_BIDIOE);
    //Software slave management
    SPI3->CR1 |= (SPI_CR1_SSM);
    //Internal slave select bit
    SPI3->CR1 |= (SPI_CR1_SSI);
    //baud rate control, clock divider 128
    SPI3->CR1 |= (SPI_CR1_BR_2 | SPI_CR1_BR_1);
    //master configuration
    SPI3->CR1 |= (SPI_CR1_MSTR);
    //clock polarity 0 when idle
    SPI3->CR1 &= ~(SPI_CR1_CPOL);
    //clock phase
    SPI3->CR1 &= ~(SPI_CR1_CPHA);

    //SPI3->CR1 |= (SPI_CR1_CPOL);
    //SPI3->CR1 |= (SPI_CR1_CPHA);

    //Data size 8-bit
    //SPI3->CR2 |= (0x07 << SPI_CR2_DS_Pos);
    //SS output enabled in master mode
    //SPI3->CR2 |= (SPI_CR2_SSOE);

    //CS initialized high
    setPin(DIS_CS_PORT, DIS_CS_PIN, PIN_HIGH);
   }
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function that transfers one byte over SPI3.
 * Parameters: txData, one byte of data to send over SPI
 * Returns: none
 */
void transferSPIByte(uint8_t txData){
    //write data to be sent to data register
    *((volatile uint8_t *) &(SPI3->DR)) = txData;
    //wait until transmit buffer is empty
    while(!(SPI3->SR & SPI_SR_TXE));
    //while (SPI3->SR & SPI_SR_RXNE);
    delayMs(2);

}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to initiate transfer over SPI. Pulls CS low and then starts SPI3 peripheral.
 * Parameters: none
 * Returns: none
 */
void startTransferSPI(){
    setPin(DIS_CS_PORT, DIS_CS_PIN, PIN_LOW);
    delayMs(2);
    //enable SPI
    SPI3->CR1 |= (SPI_CR1_SPE);

}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to end transfer over SPI. Sets CS back to high and then disables SPI3.
 * Parameters: none
 * Returns: none
 */
void endTransferSPI(){
    //wait until SPI not busy
    while(SPI3->SR & SPI_SR_BSY);
    setPin(DIS_CS_PORT, DIS_CS_PIN, PIN_HIGH);
    delayMs(2);
    //disable SPI
    SPI3->CR1 &= ~(SPI_CR1_SPE);
}
/************************************************************************************************/



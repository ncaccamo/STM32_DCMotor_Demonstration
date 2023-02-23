/**
*******************************************************************************
 * @file           : spi.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for SPI initialization
 ******************************************************************************
 */
#ifndef SPI_H
#define SPI_H




//function prototypes
void SPI3Init();
void transferSPIByte(uint8_t txData);
void startTransferSPI();
void endTransferSPI();








#endif


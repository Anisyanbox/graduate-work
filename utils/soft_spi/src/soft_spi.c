#include "soft_spi.h"
#include "hal_1967VN034R1.h"

// PA19 - clk
// PA20 - cs
// PA22 - data
#define SPI_PORT        LX_GPIO_PA
#define SPI_CLK_PIN     GPIO_PIN_19
#define SPI_MOSI_PIN    GPIO_PIN_22
#define SPI_CS_PIN      GPIO_PIN_20

// delay = 72 = 100 KHz 
// -----------------------------------------------------------------------------
static void SoftSpiPeriodDelay(int delay) {
  for (volatile int i = 0; i < delay; i++) {
    asm("nop;;");
  }
}

// -----------------------------------------------------------------------------
static void SoftSpiClkPulse(void) {
  *(unsigned int *)(GPA_DR_SET_LOC)   = SPI_CLK_PIN;
  SoftSpiPeriodDelay(100);
  *(unsigned int *)(GPA_DR_CLEAR_LOC) = SPI_CLK_PIN;
}

// -----------------------------------------------------------------------------
void SoftSpiInit(void) {
  unsigned int temp32u;
  
  // Setup GPIO for soft SPI

  temp32u = (PF_ALT << 19) | (PF_ALT << 22);
  *(unsigned int *)(GPA_DR_CLEAR_LOC) = temp32u;	// clk,data = 0

  temp32u = (PF_ALT << 20);
  *(unsigned int *)(GPA_DR_SET_LOC) = temp32u;  // cs = 1

  temp32u = (PF_ALT << 19) | (PF_ALT << 20) | (PF_ALT << 22);
  *(unsigned int *)(GPA_ALT_CLEAR_LOC) = temp32u;
  *(unsigned int *)(GPA_DDR_SET_LOC) = temp32u;
}

// -----------------------------------------------------------------------------
void SoftSpiSend(uint8_t * tx_data, size_t n) {
  uint8_t tx_bit, temp_tx_byte;

  for (int j = 0; j < n; ++j) {
    temp_tx_byte = tx_data[j];
    for (int i = 0; i < 8; ++i) {
      tx_bit = temp_tx_byte & 0x80; 
      if (tx_bit == 0) {
        *(unsigned int *)(GPA_DR_CLEAR_LOC) = GPIO_PIN_22;
      } else {
        *(unsigned int *)(GPA_DR_SET_LOC) = GPIO_PIN_22;
      }
      SoftSpiPeriodDelay(100);
      SoftSpiClkPulse();
      SoftSpiPeriodDelay(10);
      temp_tx_byte <<= 1;
    }
  }
}

// -----------------------------------------------------------------------------
void SoftSpiSelect(void) {
  *(unsigned int *)(GPA_DR_CLEAR_LOC) = SPI_CS_PIN;
}

// -----------------------------------------------------------------------------
void SoftSpiUnselect(void) {
  *(unsigned int *)(GPA_DR_SET_LOC) = SPI_CS_PIN;
}

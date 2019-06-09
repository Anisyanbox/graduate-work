/*
 *
 *  hal_audio.h
 *  HAL  AC97/I2S
 *
 *				21-Mar-2017 Dmitry Sharavev
 *
 */
#ifndef __HAL_AUDIO_H__
#define __HAL_AUDIO_H__

#include "def1967VN034R1.h"
#include <stdint.h>

typedef union {
  uint32_t word;
  struct {
    uint32_t ENB    :1; 
    uint32_t AC97DIS  :1; 
    uint32_t MODEN    :1;
    uint32_t AMCCH    :1;
    uint32_t RST    :1;
    uint32_t LPBK    :1;
    uint32_t BCKD    :1;
    uint32_t MONO_DA  :1;
    uint32_t BIT8_DA  :1;
    uint32_t MONO_AD  :1;
    uint32_t BIT8_AD  :1;
    uint32_t TO_EN    :1;
    uint32_t DIV_EN    :1;
  } b;
} Audio_SICR0_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t EREC    :1;
    uint32_t ERPL    :1;
    uint32_t EINC    :1;
    uint32_t EOUT    :1;
    uint32_t EGPIO    :1;
    uint32_t WKUP    :1;
    uint32_t DRSTO    :1;
    uint32_t REQLP    :16;
  } b;
} Audio_SICR2_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t COMSEL    :1;
    uint32_t C2ID    :2;
  } b;
} Audio_SICR3_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t DTD    :1;
    uint32_t RDD    :1;
    uint32_t GTD    :1;
    uint32_t RES    :1;
    uint32_t BSY    :1; 
    uint32_t ATNE    :1;
    uint32_t ATNF    :1;
    uint32_t ARNE    :1;
    uint32_t ATFS    :1;
    uint32_t ARFS    :1;
    uint32_t ATUR    :1;
    uint32_t AROR    :1;
    uint32_t MTNF    :1;
    uint32_t MRNE    :1;
    uint32_t MTFS    :1;
    uint32_t MRFS    :1;
    uint32_t MTUR    :1;
    uint32_t MROR    :1; 
    uint32_t RSTO    :1;
    uint32_t CLPM    :1;
    uint32_t CRDYPR    :1;
    uint32_t CRDYSC    :1;
    uint32_t RESU    :1;
    uint32_t GINT    :1;
    uint32_t RS3V    :1;  
    uint32_t RS4V    :1;
    uint32_t RS5V    :1;
    uint32_t RS12V    :1; 
  } b;
} Audio_SISR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t DTD    :1;
    uint32_t RDD    :1;
    uint32_t GTD    :1;
    uint32_t RES0    :5;
    uint32_t ATFS    :1;
    uint32_t ARFS    :1; 
    uint32_t ATUR    :1;
    uint32_t AROR    :1;
    uint32_t RES1    :2;
    uint32_t MTFS    :1;
    uint32_t MRFS    :1; 
    uint32_t MTUR    :1;
    uint32_t MROR    :1;
    uint32_t RSTO    :1;
    uint32_t RES2    :3;
    uint32_t RESU    :1;
    uint32_t GINT    :1;
  } b;
} Audio_SIIERD_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t DTD    :1;
    uint32_t RDD    :1;
    uint32_t GTD    :1; 
    uint32_t RES0    :7;
    uint32_t ATUR    :1;
    uint32_t AROR    :1;
    uint32_t RES1    :4;
    uint32_t MTUR    :1;
    uint32_t MROR    :1;
    uint32_t RSTO    :1;
    uint32_t RES2    :3;
    uint32_t RESU    :1;
    uint32_t GINT    :1;
  } b;
} Audio_SIICR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t RES    :12;
    uint32_t IX      :7;
    uint32_t RW      :1;
  } b;
} Audio_ACCAR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t RES    :4;
    uint32_t CDR    :16;
  } b;
} Audio_ACCDR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t RES    :12;
    uint32_t SAR    :7;
  } b;
} Audio_ACSAR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t RES    :4;
    uint32_t SDR    :16;
  } b;
} Audio_ACSDR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t RES    :4;
    uint32_t GDAT    :16; 
  } b;
} Audio_ACGDR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t RES    :4;
    uint32_t SDR    :16; 
  } b;
} Audio_ACGSR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t TEN    :1;
    uint32_t MODE    :1;
    uint32_t SONY    :1;
    uint32_t MS      :1;
    uint32_t DSS    :6; 
    uint32_t PNIS    :1;
    uint32_t PNOS    :1; 
    uint32_t SWHW    :1;
    uint32_t PACKH    :1;
    uint32_t LRSP    :1;
  } b;
} Audio_I2S_T_CR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t REN    :1;
    uint32_t MODE    :1;
    uint32_t SONY    :1;
    uint32_t MS      :1;
    uint32_t DSS    :6;
    uint32_t PNIS    :1;
    uint32_t PNOS    :1;
    uint32_t SWHW    :1;
    uint32_t R_INIT    :1;
    uint32_t LRSP    :1;
    uint32_t SEXT    :1;
  } b;
} Audio_I2S_R_CR_type;

typedef volatile struct {
  Audio_SICR0_type     SICR0;
  uint32_t             SINT;
  Audio_SICR2_type     SICR2;
  Audio_SISR_type      SISR;
  Audio_SISR_type      SIRSR;
  Audio_SIIERD_type   SIIER;
  Audio_SIIERD_type    SIIDR;
  Audio_SIICR_type     SIICR;
  uint32_t            SIADR;
  uint32_t            SIMDR;
  Audio_ACCAR_type     ACCAR;
  Audio_ACCDR_type     ACCDR;
  Audio_ACSAR_type     ACSAR;
  Audio_ACSDR_type     ACSDR;
  Audio_ACGDR_type     ACGDR;
  Audio_ACGSR_type     ACGSR;
  Audio_I2S_T_CR_type I2S_T_CR;
  Audio_I2S_R_CR_type I2S_R_CR;
  uint32_t       RES[ 10 ];
  Audio_SICR3_type     SICR3;
} AUDIO_type;

#define LX_AUDIO0       ( ( AUDIO_type * ) base_I2S0 )
#define LX_AUDIO1       ( ( AUDIO_type * ) base_I2S1 )

#define ROLE_SLAVE      0
#define ROLE_MASTER      1
#define MODE_I2S      0
#define MODE_DSP      1
#define STANDART_PHILLIPS  0
#define STANDART_SONY    1

typedef struct {
  uint8_t Role;
  uint8_t Mode;
  uint8_t Standart;
  uint8_t TfsPos;
  uint8_t SwapLR;
  uint16_t DataLen;
  uint32_t AudioFreq;
} AUDIO_I2S_type;

#ifdef __cplusplus
extern "C" {
#endif
  void HAL_AUDIO_I2SInit(AUDIO_type* const AudioX, AUDIO_I2S_type* I2sConf);
  void HAL_AUDIO_StartDMA(uint32_t channel, AUDIO_type* const AudioX, void *pvDataBuf, uint16_t usSize, void* pvDmaIsrHandler);
  void HAL_AUDIO_StopDMA(AUDIO_type* const AudioX);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __HAL_AUDIO_H__ */

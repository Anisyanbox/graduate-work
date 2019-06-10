#include "aic23b.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

/* Codec TLV320AIC23 */
#define TLV320AIC23_LINVOL      0x00
#define TLV320AIC23_RINVOL      0x01
#define TLV320AIC23_LCHNVOL     0x02
#define TLV320AIC23_RCHNVOL     0x03
#define TLV320AIC23_ANLG        0x04
#define TLV320AIC23_DIGT        0x05
#define TLV320AIC23_PWR         0x06
#define TLV320AIC23_DIGT_FMT    0x07
#define TLV320AIC23_SRATE       0x08
#define TLV320AIC23_ACTIVE      0x09
#define TLV320AIC23_RESET       0x0F

/* Left (right) line input volume control register */
#define TLV320AIC23_LRS_ENABLED 0x0100
#define TLV320AIC23_LIM_MUTED   0x0080
#define TLV320AIC23_LIV_DEFAULT 0x0017
#define TLV320AIC23_LIV_MAX     0x001f
#define TLV320AIC23_LIV_MIN     0x0000

/* Left (right) channel headphone volume control register */
#define TLV320AIC23_LZC_ON      0x0080
#define TLV320AIC23_LHV_DEFAULT 0x0079
#define TLV320AIC23_LHV_MAX     0x007f
#define TLV320AIC23_LHV_MIN     0x0000

/* Analog audio path control register */
#define TLV320AIC23_STA_REG(x)    ((x) << 6)
#define TLV320AIC23_STE_ENABLED   0x0020
#define TLV320AIC23_DAC_SELECTED  0x0010
#define TLV320AIC23_BYPASS_ON     0x0008
#define TLV320AIC23_INSEL_MIC     0x0004
#define TLV320AIC23_MICM_MUTED    0x0002
#define TLV320AIC23_MICB_20DB     0x0001

/* Digital audio path control register */
#define TLV320AIC23_DACM_MUTE    0x0008
#define TLV320AIC23_DEEMP_32K    0x0002
#define TLV320AIC23_DEEMP_44K    0x0004
#define TLV320AIC23_DEEMP_48K    0x0006
#define TLV320AIC23_ADCHP_ON     0x0001

/* Power control down register */
#define TLV320AIC23_DEVICE_PWR_OFF  0x0080
#define TLV320AIC23_CLK_OFF         0x0040
#define TLV320AIC23_OSC_OFF         0x0020
#define TLV320AIC23_OUT_OFF         0x0010
#define TLV320AIC23_DAC_OFF         0x0008
#define TLV320AIC23_ADC_OFF         0x0004
#define TLV320AIC23_MIC_OFF         0x0002
#define TLV320AIC23_LINE_OFF        0x0001

/* Digital audio interface register */
#define TLV320AIC23_MS_MASTER    0x0040
#define TLV320AIC23_LRSWAP_ON    0x0020
#define TLV320AIC23_LRP_ON       0x0010
#define TLV320AIC23_IWL_16       0x0000
#define TLV320AIC23_IWL_20       0x0004
#define TLV320AIC23_IWL_24       0x0008
#define TLV320AIC23_IWL_32       0x000C
#define TLV320AIC23_FOR_I2S      0x0002
#define TLV320AIC23_FOR_DSP      0x0003
#define TLV320AIC23_FOR_LJUST    0x0001

/* Sample rate control register */
#define TLV320AIC23_CLKOUT_HALF  0x0080
#define TLV320AIC23_CLKIN_HALF   0x0040
#define TLV320AIC23_BOSR_384fs   0x0002  /* BOSR_272fs in USB mode */
#define TLV320AIC23_USB_CLK_ON   0x0001
#define TLV320AIC23_SR_MASK      0xf
#define TLV320AIC23_CLKOUT_SHIFT 7
#define TLV320AIC23_CLKIN_SHIFT  6
#define TLV320AIC23_SR_SHIFT     2
#define TLV320AIC23_BOSR_SHIFT   1

/* Digital interface register */
#define TLV320AIC23_ACT_ON  0x0001

/*
 * AUDIO related MACROS
 */
#define TLV320AIC23_DEFAULT_OUT_VOL  0x70
#define TLV320AIC23_DEFAULT_IN_VOLUME  0x10

#define TLV320AIC23_OUT_VOL_MIN    TLV320AIC23_LHV_MIN
#define TLV320AIC23_OUT_VOL_MAX    TLV320AIC23_LHV_MAX
#define TLV320AIC23_OUT_VO_RANGE  (TLV320AIC23_OUT_VOL_MAX - \
          TLV320AIC23_OUT_VOL_MIN)
#define TLV320AIC23_OUT_VOL_MASK  TLV320AIC23_OUT_VOL_MAX

#define TLV320AIC23_IN_VOL_MIN    TLV320AIC23_LIV_MIN
#define TLV320AIC23_IN_VOL_MAX    TLV320AIC23_LIV_MAX
#define TLV320AIC23_IN_VOL_RANGE  (TLV320AIC23_IN_VOL_MAX - \
          TLV320AIC23_IN_VOL_MIN)
#define TLV320AIC23_IN_VOL_MASK    TLV320AIC23_IN_VOL_MAX

#define TLV320AIC23_SIDETONE_MASK  0x1c0
#define TLV320AIC23_SIDETONE_0     0x100
#define TLV320AIC23_SIDETONE_6     0x000
#define TLV320AIC23_SIDETONE_9     0x040
#define TLV320AIC23_SIDETONE_12    0x080
#define TLV320AIC23_SIDETONE_18    0x0c0

#define SND_SOC_BIAS_ON          0x1
#define SND_SOC_BIAS_PREPARE     0x2
#define SND_SOC_BIAS_STANDBY     0x3
#define SND_SOC_BIAS_OFF         0x4

#define SR_MULT         (11*12)
#define MCLK            12e+6 //Hz
#define ADC_SRATE       22050 //Hz
#define DAC_SRATE       22050 //Hz

#define LOWER_GROUP ((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<6) | (1<<7))
#define UPPER_GROUP ((1<<8) | (1<<9) | (1<<10) | (1<<11)        | (1<<15))

/*
 * AIC23 register cache
 */
static unsigned short tlv320aic23_reg[16] = { 0 };
static long bosr_usb_divisor_table[4];
static unsigned short sr_valid_mask[4];
static unsigned char sr_adc_mult_table[16];
static unsigned char sr_dac_mult_table[16];

/*
250  * Common Crystals used
251  * 11.2896 Mhz /128 = *88.2k  /192 = 58.8k
252  * 12.0000 Mhz /125 = *96k    /136 = 88.235K
253  * 12.2880 Mhz /128 = *96k    /192 = 64k
254  * 16.9344 Mhz /128 = 132.3k /192 = *88.2k
255  * 18.4320 Mhz /128 = 144k   /192 = *96k
*/

/*
 * Hw func pointers
 */
static Aic23bHwDependFuncs_t hw_funcs = { 0 };

// -----------------------------------------------------------------------------
static unsigned long get_score(long adc, 
                               long adc_l, 
                               long adc_h, 
                               long need_adc,
                               long dac, 
                               long dac_l, 
                               long dac_h, 
                               long need_dac) {
  long diff_adc;
  long diff_dac;

  if ((adc >= adc_l) && (adc <= adc_h) && (dac >= dac_l) && (dac <= dac_h)) {
    diff_adc = need_adc - adc;
    diff_dac = need_dac - dac;
    return abs(diff_adc) + abs(diff_dac);
  }
  return UINT32_MAX;
}

// -----------------------------------------------------------------------------
static void Aic23bInitRegCache(void) {
  tlv320aic23_reg[TLV320AIC23_LINVOL]     = 0x0097;
  tlv320aic23_reg[TLV320AIC23_RINVOL]     = 0x0097;
  tlv320aic23_reg[TLV320AIC23_LCHNVOL]    = 0x00F9;
  tlv320aic23_reg[TLV320AIC23_RCHNVOL]    = 0x00F9;
  tlv320aic23_reg[TLV320AIC23_ANLG]       = 0x001A;
  tlv320aic23_reg[TLV320AIC23_DIGT]       = 0x0004;
  tlv320aic23_reg[TLV320AIC23_PWR]        = 0x0007;
  tlv320aic23_reg[TLV320AIC23_DIGT_FMT]   = 0x0001;
  tlv320aic23_reg[TLV320AIC23_SRATE]      = 0x0020;
  tlv320aic23_reg[TLV320AIC23_ACTIVE]     = 0x0000;
  tlv320aic23_reg[TLV320AIC23_RESET]      = 0x0000;

  bosr_usb_divisor_table[0]               = 93750; 
  bosr_usb_divisor_table[1]               = 96000; 
  bosr_usb_divisor_table[2]               = 62500; 
  bosr_usb_divisor_table[3]               = 88235;

  sr_valid_mask[0] = LOWER_GROUP|UPPER_GROUP;
  sr_valid_mask[1] = LOWER_GROUP;
  sr_valid_mask[2] = LOWER_GROUP|UPPER_GROUP;
  sr_valid_mask[3] = UPPER_GROUP;

  sr_adc_mult_table[0]=66;
  sr_adc_mult_table[1]=66;
  sr_adc_mult_table[2]=11;
  sr_adc_mult_table[3]=11;
  sr_adc_mult_table[4]=0;
  sr_adc_mult_table[5]=0;
  sr_adc_mult_table[6]=44;
  sr_adc_mult_table[7]=132;
  sr_adc_mult_table[8]=66;
  sr_adc_mult_table[9]=66;
  sr_adc_mult_table[10]=12;
  sr_adc_mult_table[11]=12;
  sr_adc_mult_table[12]=0;
  sr_adc_mult_table[13]=0;
  sr_adc_mult_table[14]=0;
  sr_adc_mult_table[15]=132;
  
  sr_dac_mult_table[0]=66;
  sr_dac_mult_table[1]=11;
  sr_dac_mult_table[2]=66;
  sr_dac_mult_table[3]=11;
  sr_dac_mult_table[4]=0;
  sr_dac_mult_table[5]=0;
  sr_dac_mult_table[6]=44;
  sr_dac_mult_table[7]=132;
  sr_dac_mult_table[8]=66;
  sr_dac_mult_table[9]=12;
  sr_dac_mult_table[10]=66;
  sr_dac_mult_table[11]=12;
  sr_dac_mult_table[12]=0;
  sr_dac_mult_table[13]=0;
  sr_dac_mult_table[14]=0;
  sr_dac_mult_table[15]=132;
}

// -----------------------------------------------------------------------------
static unsigned short Aic23ReadRegCache(unsigned short reg) {
  return tlv320aic23_reg[reg];
}

// -----------------------------------------------------------------------------
static void Aic23WriteRegCache(unsigned short reg, unsigned short value) {
  tlv320aic23_reg[reg] = value;
}

// -----------------------------------------------------------------------------
static void Aic23Select(void) {
  if (hw_funcs.select != NULL) {
    hw_funcs.select();
  }
}

// -----------------------------------------------------------------------------
static void Aic23Unselect(void) {
  if (hw_funcs.unselect != NULL) {
    hw_funcs.unselect();
  }
}

// -----------------------------------------------------------------------------
static void Aic23WriteReg(unsigned short reg, unsigned short value) {
  uint8_t data[2] = { 0 };

  /* TLV320AIC23 has 7 bit address and 9 bits of data
   * so we need to switch one data bit into reg and rest
   * of data into val
   */
  data[0] = (reg << 1) | (value >> 8 & 0x01);
  data[1] = value & 0xff;

  Aic23Select();
  hw_funcs.send(data, 2);
  Aic23Unselect();
}

// -----------------------------------------------------------------------------
static void Aic23SetBiasLevel(unsigned short level) {
  unsigned short reg = Aic23ReadRegCache(TLV320AIC23_PWR) & 0xff7f;

  switch (level) {
    case SND_SOC_BIAS_ON:
    /* vref/mid, osc on, dac unmute */
    reg &= ~(TLV320AIC23_DEVICE_PWR_OFF | TLV320AIC23_OSC_OFF | TLV320AIC23_DAC_OFF);
    reg &= ~(TLV320AIC23_ADC_OFF | TLV320AIC23_MIC_OFF);
    Aic23WriteReg(TLV320AIC23_PWR, reg);
    break;

    case SND_SOC_BIAS_PREPARE:
    break;

    case SND_SOC_BIAS_STANDBY:
    /* everything off except vref/vmid, */
    Aic23WriteReg(TLV320AIC23_PWR, reg | TLV320AIC23_CLK_OFF);
    break;

    case SND_SOC_BIAS_OFF:
    /* everything off, dac mute, inactive */
    Aic23WriteReg(TLV320AIC23_ACTIVE, 0x0);
    Aic23WriteReg(TLV320AIC23_PWR, 0xffff);
    break;
    
    default:
    break;
  }
}

// -----------------------------------------------------------------------------
static void Aic23SetDaiFmt(void) {
  unsigned short iface_reg;
  iface_reg = Aic23ReadRegCache(TLV320AIC23_DIGT_FMT) & (~0x03);

  /* set master/slave audio interface */
  iface_reg |= TLV320AIC23_MS_MASTER;
  
  /* interface format */
  #if 1
    iface_reg |= TLV320AIC23_FOR_I2S; //I2S
  #else
    //iface_reg |= TLV320AIC23_LRP_ON;
    iface_reg |= TLV320AIC23_FOR_DSP | TLV320AIC23_LRP_ON;/* | TLV320AIC23_IWL_32;*/
  #endif
  Aic23WriteReg(TLV320AIC23_DIGT_FMT, iface_reg);
}

// -----------------------------------------------------------------------------
static long FindRate(unsigned short mclk, 
                     unsigned long need_adc, 
                     unsigned long need_dac) {
  long i, j;
  long best_i;
  long best_j;
  long best_div = 0;
  unsigned long best_score;
  long adc_l, adc_h, dac_l, dac_h;
  long base;
  long mask;
  long adc;
  long dac;
  long score;

  best_i = -1;
  best_j = -1;
  best_score = UINT32_MAX;
  adc=0x0000;
  dac=0x0000;

  need_adc *= SR_MULT;
  need_dac *= SR_MULT;

  /*
  311          * rates given are +/- 1/32
  312          */
  adc_l = need_adc - (need_adc >> 5);
  adc_h = need_adc + (need_adc >> 5);
  dac_l = need_dac - (need_dac >> 5);
  dac_h = need_dac + (need_dac >> 5);

  for (i = 0; i < sizeof(bosr_usb_divisor_table); i++) {
    base = bosr_usb_divisor_table[i];
    mask = sr_valid_mask[i];
    for (j = 0; j < sizeof(sr_adc_mult_table); j++, mask >>= 1)  {    
      if ((mask & 1) == 0) {
        continue;
      }
      adc = base * sr_adc_mult_table[j];
      dac = base * sr_dac_mult_table[j];      
      
      score = get_score(adc, adc_l, adc_h, need_adc,dac, dac_l, dac_h, need_dac);
      if (best_score > score)  {
        best_score = score;
        best_i = i;
        best_j = j;
        best_div = 0;
      }
      
      score = get_score((adc >> 1), adc_l, adc_h, need_adc,(dac >> 1), dac_l, dac_h, need_dac);
      /* prefer to have a /2 */
      if ((score != UINT32_MAX) && (best_score >= score))  {
        best_score = score;
        best_i = i;
        best_j = j;
        best_div = 1;
      }
    }
  }
  return (best_j << 2) | best_i | (best_div << TLV320AIC23_CLKIN_SHIFT);
}

// -----------------------------------------------------------------------------
static void Aic23SetSampleRateControl(unsigned long mclk,
                                                unsigned long sample_rate_adc, 
                                                unsigned long sample_rate_dac) {
  /* Search for the right sample rate */
  long data = FindRate(mclk, sample_rate_adc, sample_rate_dac);
  Aic23WriteReg(TLV320AIC23_SRATE, data);
}

// -----------------------------------------------------------------------------
int Aic23bInit(Aic23bHwDependFuncs_t * hw_depend_funcs) {
  unsigned short reg;

  if ((hw_depend_funcs->hw_init == NULL) || \
      (hw_depend_funcs->send == NULL) || \
      (hw_depend_funcs->delay == NULL)) {
    return 1;
  }
  memcpy((void*)&hw_funcs, (const void*)hw_depend_funcs, sizeof(hw_funcs));
  hw_funcs.hw_init();
  
  Aic23bInitRegCache();
  Aic23WriteReg(TLV320AIC23_ACTIVE, 0x0);
  hw_funcs.delay(100);

  /* Reset codec */
  Aic23WriteReg(TLV320AIC23_RESET, 0);
  hw_funcs.delay(100);

  /* power on device */
  Aic23SetBiasLevel(SND_SOC_BIAS_ON);
  hw_funcs.delay(100);
  Aic23WriteReg(TLV320AIC23_DIGT, TLV320AIC23_ADCHP_ON);
  hw_funcs.delay(100);

  /* Unmute input */
  reg = Aic23ReadRegCache(TLV320AIC23_LINVOL);
  Aic23WriteReg(TLV320AIC23_LINVOL,(reg & (~TLV320AIC23_LIM_MUTED)) |(TLV320AIC23_LRS_ENABLED));
  hw_funcs.delay(100);

  reg = Aic23ReadRegCache(TLV320AIC23_RINVOL);
  Aic23WriteReg(TLV320AIC23_RINVOL, (reg & (~TLV320AIC23_LIM_MUTED)) | TLV320AIC23_LRS_ENABLED);
  hw_funcs.delay(100);

  reg = Aic23ReadRegCache(TLV320AIC23_ANLG);
  Aic23WriteReg(TLV320AIC23_ANLG, ((reg) /*& (~TLV320AIC23_BYPASS_ON)*/ & (~TLV320AIC23_MICM_MUTED)) |
  TLV320AIC23_INSEL_MIC /*| TLV320AIC23_MICB_20DB*/);
  hw_funcs.delay(100);

  /* Default output volume */
  Aic23WriteReg(TLV320AIC23_LCHNVOL, 0x080 + 121);
  hw_funcs.delay(100);

  Aic23WriteReg(TLV320AIC23_RCHNVOL, 0x080 + 121);
  hw_funcs.delay(100);

  /* audio */
  Aic23SetDaiFmt();
  hw_funcs.delay(100);

  /* sample rate playback */
  Aic23SetSampleRateControl(MCLK, 44100, 44100);
  hw_funcs.delay(100);

  Aic23WriteReg(TLV320AIC23_ACTIVE, 0x1);
  hw_funcs.delay(100);
  return 0;
}

// -----------------------------------------------------------------------------  
void Aic23bSetVolume(unsigned short val) {
  Aic23WriteReg(TLV320AIC23_LCHNVOL, 0x080 + val);
  hw_funcs.delay(100);
  Aic23WriteReg(TLV320AIC23_RCHNVOL, 0x080 + val);
  hw_funcs.delay(100);
}

// -----------------------------------------------------------------------------  
void Aic23bSetRate(unsigned short sample_rate) {
  Aic23SetSampleRateControl(MCLK, sample_rate, sample_rate);
  hw_funcs.delay(100);
}

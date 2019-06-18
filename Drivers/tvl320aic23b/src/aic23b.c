#include "aic23b.h"
#include <string.h>

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
#define MCLK            12500000 //Hz

#define LOWER_GROUP ((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<6) | (1<<7))
#define UPPER_GROUP ((1<<8) | (1<<9) | (1<<10) | (1<<11)        | (1<<15))

/*
 * AIC23 register cache
 */
static unsigned short tlv320aic23_reg[16] = { 0 };

/*
 * Resolutions
*/
static unsigned int adc_res = 65535;
static unsigned int dac_res = 65535;

/*
 * Hw func pointers
 */
static Aic23bHwDependFuncs_t hw_funcs = { 0 };

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
    reg &= ~(TLV320AIC23_ADC_OFF | TLV320AIC23_MIC_OFF | TLV320AIC23_CLK_OFF);
    reg &= ~(TLV320AIC23_OUT_OFF | TLV320AIC23_LINE_OFF);
    Aic23WriteReg(TLV320AIC23_PWR, reg);
    Aic23WriteRegCache(TLV320AIC23_PWR, reg);
    break;

    case SND_SOC_BIAS_PREPARE:
    break;

    case SND_SOC_BIAS_STANDBY:
    /* everything off except vref/vmid, */
    Aic23WriteReg(TLV320AIC23_PWR, reg | TLV320AIC23_CLK_OFF);
    Aic23WriteRegCache(TLV320AIC23_PWR, reg | TLV320AIC23_CLK_OFF);
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
static void Aic23SetI2SMasterFmt(void) {
  unsigned short iface_reg;
  iface_reg = Aic23ReadRegCache(TLV320AIC23_DIGT_FMT) & (~0x03);

  /* set master/slave audio interface */
  iface_reg |= TLV320AIC23_MS_MASTER;
  iface_reg |= TLV320AIC23_FOR_I2S;
  Aic23WriteReg(TLV320AIC23_DIGT_FMT, iface_reg);
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
  hw_funcs.delay(1000);

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
  Aic23bSetOutVolume(50);

  /* audio */
  Aic23SetI2SMasterFmt();
  hw_funcs.delay(100);

  /* sample rate playback */
  Aic23WriteReg(TLV320AIC23_SRATE, (0 << 7) | (0 << 6));
  hw_funcs.delay(100);

  Aic23WriteReg(TLV320AIC23_ACTIVE, TLV320AIC23_ACT_ON);
  hw_funcs.delay(100);
  return 0;
}

// -----------------------------------------------------------------------------  
void Aic23bSetOutVolume(unsigned short percent) {
  unsigned short reg_data = 0;

  reg_data = (unsigned short)(((float)(TLV320AIC23_LHV_MAX - TLV320AIC23_LHV_MIN) * \
                              (float)percent) / 100.0);

  reg_data &= TLV320AIC23_LHV_MAX;
  reg_data |= TLV320AIC23_LZC_ON;
  Aic23WriteReg(TLV320AIC23_LCHNVOL, reg_data);
  Aic23WriteReg(TLV320AIC23_RCHNVOL, reg_data);
  Aic23WriteRegCache(TLV320AIC23_LCHNVOL, reg_data);
  Aic23WriteRegCache(TLV320AIC23_RCHNVOL, reg_data);
}

// ----------------------------------------------------------------------------- 
void Aic23bSetInputVolume(unsigned short percent) {
  unsigned short reg_data = 0;

  reg_data = (unsigned short)(((float)(TLV320AIC23_LIV_MAX - TLV320AIC23_LIV_MIN) * \
                              (float)percent) / 100.0);
  reg_data &= TLV320AIC23_LIV_MAX;
  reg_data &= (~TLV320AIC23_LIM_MUTED);

  Aic23WriteReg(TLV320AIC23_LINVOL, reg_data);
  Aic23WriteReg(TLV320AIC23_RINVOL, reg_data);
  Aic23WriteRegCache(TLV320AIC23_LINVOL, reg_data);
  Aic23WriteRegCache(TLV320AIC23_RINVOL, reg_data);
}

// -----------------------------------------------------------------------------  
void Aic23bSetRate(Aic23bSamples_t srate) {
  unsigned short data;

  switch (srate) {
    case AIC23B_ADC_96_DAC_96:
      data = 0x1C;
      break;

    case AIC23B_ADC_48_DAC_48:
      data = 0x00;
      break;

    case AIC23B_ADC_32_DAC_32:
      data = 0x18;
      break;

    case AIC23B_ADC_8_DAC_8:
      data = 0x0C;
      break;

    case AIC23B_ADC_48_DAC_8:
      data = 0x04;
      break;

    case AIC23B_ADC_8_DAC_48:
      data = 0x08;
      break;

    default:
      return;
  }

  Aic23WriteReg(TLV320AIC23_SRATE, data);
  Aic23WriteRegCache(TLV320AIC23_SRATE, data);
}

// -----------------------------------------------------------------------------  
void Aic23bSetAdcDacResolution(Aic23bSoundDepth_t depth) {
  unsigned short iface_reg = Aic23ReadRegCache(TLV320AIC23_DIGT_FMT);

  iface_reg &= (~0x0c);
  switch (depth) {
    case AIC23B_16BIT_SOUNND:
      iface_reg |= TLV320AIC23_IWL_16;
      adc_res = 65535;
      dac_res = 65535;
      break;

    case AIC23B_20BIT_SOUNND:
      iface_reg |= TLV320AIC23_IWL_20;
      adc_res = 1048575;
      dac_res = 1048575;
      break;

    case AIC23B_24BIT_SOUNND:
      iface_reg |= TLV320AIC23_IWL_24;
      adc_res = 16777215;
      dac_res = 16777215;
      break;

    case AIC23B_32BIT_SOUNND:
      iface_reg |= TLV320AIC23_IWL_32;
      adc_res = 4294967295;
      dac_res = 4294967295;
      break;

    default:
      return;
  }
  Aic23WriteReg(TLV320AIC23_DIGT_FMT, iface_reg);
  Aic23WriteRegCache(TLV320AIC23_SRATE, iface_reg);
}

// -----------------------------------------------------------------------------  
unsigned int Aic23bGetAdcRes(void) {
  return adc_res;
}

// -----------------------------------------------------------------------------  
unsigned int Aic23bGetDacRes(void) {
  return dac_res;
}

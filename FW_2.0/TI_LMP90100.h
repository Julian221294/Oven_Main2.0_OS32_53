#ifndef _TI_LMP90100_H_
#define _TI_LMP90100_H_

/************************************************************
* TI LMP90100 REGISTER SET ADDRESSES
************************************************************/
#define TI_LMP90100_RESETCN_REG                        (0x00)             /* Reset Control */

#define TI_LMP90100_SPI_HANDSHAKECN_REG                (0x01)             /* SPI Handshake Control */
#define TI_LMP90100_SPI_RESET_REG                      (0x02)             /* SPI Reset Control */
#define TI_LMP90100_SPI_STREAMCN_REG                   (0x03)             /* SPI Stream Control*/

#define TI_LMP90100_PWRCN_REG                          (0x08)             /* Power Mode Control and Status */
#define TI_LMP90100_DATA_ONLY_1_REG                    (0x09)             /* Data Only Read Control 1 */
#define TI_LMP90100_DATA_ONLY_2_REG                    (0x0A)             /* Data Only Read Control 2 */
#define TI_LMP90100_ADC_RESTART_REG                    (0x0B)             /* ADC Restart Conversion */

#define TI_LMP90100_GPIO_DIRCN_REG                     (0x0E)             /* GPIO Direction Control */
#define TI_LMP90100_GPIO_DAT_REG                       (0x0F)             /* GPIO Data */

#define TI_LMP90100_BGCALCN_REG                        (0x10)             /* Background Calibration Control */

#define TI_LMP90100_SPI_DRDYBCN_REG                    (0x11)             /* SPI Data Ready Bar Control */


#define TI_LMP90100_ADC_AUXCN_REG                      (0x12)             /* ADC Auxillary Control */
#define TI_LMP90100_SPI_CRC_CN_REG                     (0x13)             /* CRC Control */
#define TI_LMP90100_SENDIAG_THLDH_REG                  (0x14)             /* Sensor Diagnostic Threshold High */
#define TI_LMP90100_SENDIAG_THLDL_REG                  (0x15)             /* Sensor Diagnostic Threshold Low */

#define TI_LMP90100_SCALCN_REG                         (0x17)             /* System Calibration Control */
#define TI_LMP90100_ADC_DONE_REG                       (0x18)             /* ADC Data Available */
#define TI_LMP90100_SENDIAG_FLAGS_REG                  (0x19)             /* Sensor Diagnostic Flags */
#define TI_LMP90100_ADC_DOUT2_REG                      (0x1A)             /* ADC Conversion Data 2 */
#define TI_LMP90100_ADC_DOUT1_REG                      (0x1B)             /* ADC Conversion Data 1 */
#define TI_LMP90100_ADC_DOUT0_REG                      (0x1C)             /* ADC Conversion Data 0 */
#define TI_LMP90100_SPI_CRC_DAT_REG                    (0x1D)             /* CRC Data */

#define TI_LMP90100_CH_STS_REG                         (0x1E)             /* Channel Status */
#define TI_LMP90100_CH_SCAN_NRDY                       (0x02)             /* Channel Scan Not Ready Bit */

#define TI_LMP90100_CH_SCAN_REG                        (0x1F)             /* Channel Scan Mode */
#define TI_LMP90100_CH0_INPUTCN_REG                    (0x20)             /* CH0 Input Control */
#define TI_LMP90100_CH0_CONFIG_REG                     (0x21)             /* CH0 Configuration */
#define TI_LMP90100_CH1_INPUTCN_REG                    (0x22)             /* CH1 Input Control */
#define TI_LMP90100_CH1_CONFIG_REG                     (0x23)             /* CH1 Configuration */
#define TI_LMP90100_CH2_INPUTCN_REG                    (0x24)             /* CH2 Input Control */
#define TI_LMP90100_CH2_CONFIG_REG                     (0x25)             /* CH2 Configuration */
#define TI_LMP90100_CH3_INPUTCN_REG                    (0x26)             /* CH3 Input Control */
#define TI_LMP90100_CH3_CONFIG_REG                     (0x27)             /* CH3 Configuration */
#define TI_LMP90100_CH4_INPUTCN_REG                    (0x28)             /* CH4 Input Control */
#define TI_LMP90100_CH4_CONFIG_REG                     (0x29)             /* CH4 Configuration */
#define TI_LMP90100_CH5_INPUTCN_REG                    (0x2A)             /* CH5 Input Control */
#define TI_LMP90100_CH5_CONFIG_REG                     (0x2B)             /* CH5 Configuration */
#define TI_LMP90100_CH6_INPUTCN_REG                    (0x2C)             /* CH6 Input Control */
#define TI_LMP90100_CH6_CONFIG_REG                     (0x2D)             /* CH6 Configuration */

#define TI_LMP90100_CH0_SCAL_OFFSET2_REG               (0x30)             /* CH0 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH0_SCAL_OFFSET1_REG               (0x31)             /* CH0 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH0_SCAL_OFFSET0_REG               (0x32)             /* CH0 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH0_SCAL_GAIN2_REG                 (0x33)             /* CH0 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH0_SCAL_GAIN1_REG                 (0x34)             /* CH0 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH0_SCAL_GAIN0_REG                 (0x35)             /* CH0 System Calibration Gain Coefficient [7:0]  */ 
#define TI_LMP90100_CH0_SCAL_SCALING_REG               (0x36)             /* CH0 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH0_SCAL_BITS_SELECTOR_REG         (0x37)             /* CH0 System Calibration Bits Selector */

#define TI_LMP90100_CH1_SCAL_OFFSET2_REG               (0x38)             /* CH1 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH1_SCAL_OFFSET1_REG               (0x39)             /* CH1 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH1_SCAL_OFFSET0_REG               (0x3A)             /* CH1 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH1_SCAL_GAIN2_REG                 (0x3B)             /* CH1 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH1_SCAL_GAIN1_REG                 (0x3C)             /* CH1 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH1_SCAL_GAIN0_REG                 (0x3D)             /* CH1 System Calibration Gain Coefficient [7:0]  */ 
#define TI_LMP90100_CH1_SCAL_SCALING_REG               (0x3E)             /* CH1 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH1_SCAL_BITS_SELECTOR_REG         (0x3F)             /* CH1 System Calibration Bits Selector */

#define TI_LMP90100_CH2_SCAL_OFFSET2_REG               (0x40)             /* CH2 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH2_SCAL_OFFSET1_REG               (0x41)             /* CH2 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH2_SCAL_OFFSET0_REG               (0x42)             /* CH2 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH2_SCAL_GAIN2_REG                 (0x43)             /* CH2 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH2_SCAL_GAIN1_REG                 (0x44)             /* CH2 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH2_SCAL_GAIN0_REG                 (0x45)             /* CH2 System Calibration Gain Coefficient [7:0]  */
#define TI_LMP90100_CH2_SCAL_SCALING_REG               (0x46)             /* CH2 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH2_SCAL_BITS_SELECTOR_REG         (0x47)             /* CH2 System Calibration Bits Selector */

#define TI_LMP90100_CH3_SCAL_OFFSET2_REG               (0x48)             /* CH3 System Calibration Offset Coefficient [23:16] */
#define TI_LMP90100_CH3_SCAL_OFFSET1_REG               (0x49)             /* CH3 System Calibration Offset Coefficient [15:8] */
#define TI_LMP90100_CH3_SCAL_OFFSET0_REG               (0x4A)             /* CH3 System Calibration Offset Coefficient [7:0] */
#define TI_LMP90100_CH3_SCAL_GAIN2_REG                 (0x4B)             /* CH3 System Calibration Gain Coefficient [23:16]  */
#define TI_LMP90100_CH3_SCAL_GAIN1_REG                 (0x4C)             /* CH3 System Calibration Gain Coefficient [15:8]  */
#define TI_LMP90100_CH3_SCAL_GAIN0_REG                 (0x4D)             /* CH3 System Calibration Gain Coefficient [7:0]  */ 
#define TI_LMP90100_CH3_SCAL_SCALING_REG               (0x4E)             /* CH3 System Calibration Scaling Coefficient */
#define TI_LMP90100_CH3_SCAL_BITS_SELECTOR_REG         (0x4F)             /* CH3 System Calibration Bits Selector */

// Data output rate, Gain, buffer:
#define LMP90100_ODR_1SPS                            (0x00)
#define LMP90100_ODR_3SPS                            (0x10)
#define LMP90100_ODR_7SPS                            (0x20)
#define LMP90100_ODR_13SPS                           (0x30)
#define LMP90100_ODR_27SPS                           (0x40)
#define LMP90100_ODR_54SPS                           (0x50)
#define LMP90100_ODR_107SPS                            (0x60)
#define LMP90100_ODR_214SPS                            (0x70)

#define LMP90100_PGA_1                                 (0x00)
#define LMP90100_PGA_2                                 (0x02)
#define LMP90100_PGA_4                                 (0x04)
#define LMP90100_PGA_8                                 (0x06)
#define LMP90100_PGA_16                                (0x08)
#define LMP90100_PGA_32                                (0x0A)
#define LMP90100_PGA_64                                (0x0C)
#define LMP90100_PGA_128                               (0x0E)
#define LMP90100_BUF_DIS                               (0x01)




// Useful definitions
#define LMP90100_URA_END                               (0xFF)
#define LMP90100_URA_MASK                              (0x70)
#define LMP90100_LRA_MASK                              (0x0F)
#define LMP90100_READ_BIT                              (0x80)
#define LMP90100_WRITE_BIT                             (0x00)
#define LMP90100_SIZE_1B                               (0x00)
#define LMP90100_SIZE_2B                               (0x20)
#define LMP90100_SIZE_3B                               (0x40)
#define LMP90100_SIZE_STREAM                           (0x60)
#define LMP90100_CH_NUM_MASK                           (0x07)

#define LMP90100_INSTRUCTION_BYTE1_WRITE               (0x10)
#define LMP90100_DATA_FIRST_MODE_INSTRUCTION_ENABLE    (0xFA)
#define LMP90100_DATA_FIRST_MODE_INSTRUCTION_DISABLE   (0xFB)
#define LMP90100_DATA_FIRST_MODE_INSTRUCTION_READ_MODE_STATUS    (0x9F)
#define LMP90100_DATA_FIRST_MODE_STATUS_FLAG           (0x80)

enum crc_check { CRC_PASS, CRC_FAIL, CRC_NOT_USED};


#endif                                                        // _TI_LMP90100_H_


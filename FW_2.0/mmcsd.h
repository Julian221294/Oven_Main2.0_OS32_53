#ifndef _MMCSD_H_
#define _MMCSD_H_

#include "stdint.h"

//meda library, a compatable media library is required for FAT.
#use fast_io(C)
#use fast_io(B)
#use fast_io(D)

#define MMCSD_PIN_SCL     PIN_C3
#define MMCSD_PIN_SDI     PIN_C4
#define MMCSD_PIN_SDO     PIN_C5
#define MMCSD_PIN_SELECT  PIN_B0

enum MMCSD_err
{
   MMCSD_GOODEC = 0,
   MMCSD_IDLE = 0x01,
   MMCSD_ERASE_RESET = 0x02,
   MMCSD_ILLEGAL_CMD = 0x04,
   MMCSD_CRC_ERR = 0x08,
   MMCSD_ERASE_SEQ_ERR = 0x10,
   MMCSD_ADDR_ERR = 0x20,
   MMCSD_PARAM_ERR = 0x40,
   RESP_TIMEOUT = 0x80
};

#define GO_IDLE_STATE         0
#define SEND_OP_COND          1
#define SEND_IF_COND          8
#define SEND_CSD              9
#define SEND_CID              10
#define STOP_TRANSMISSION     12
#define SEND_STATUS           13
#define SET_BLOCKLEN          16
#define READ_SINGLE_BLOCK     17
#define READ_MULTIPLE_BLOCK   18
#define WRITE_SINGLE_BLOCK    24
#define WRITE_MULTIPLE_BLOCK  25
#define PROGRAM_CSD           27
#define SET_WRITE_PROT        28
#define CLR_WRITE_PROT        29
#define SEN_WRITE_PROT        30
#define TAG_SECTOR_START      32
#define TAG_SECTOR_END        33
#define UNTAG_SECTOR          34
#define TAG_ERASE_GROUP_START 35
#define TAG_ERASE_GROUP_END   36
#define UNTAG_ERASE_GROUP     37
#define ERASE                 38
#define SD_SEND_OP_COND       41
#define APP_CMD               55
#define READ_OCR              58
#define CRC_ON_OFF            59

#define IDLE_TOKEN 0x01
#define DATA_START_TOKEN 0xFE

#define MMCSD_MAX_BLOCK_SIZE 512

////////////////////////
///                  ///
/// Global Variables ///
///                  ///
////////////////////////

uint8_t g_mmcsd_buffer[MMCSD_MAX_BLOCK_SIZE];

/////////////////////////////
////                     ////
//// Function Prototypes ////
////                     ////
/////////////////////////////

MMCSD_err mmcsd_software_reset();
MMCSD_err mmcsd_initialize();
MMCSD_err mmcsd_init();
MMCSD_err mmcsd_read_data(uint32_t address, uint16_t size, uint8_t* ptr);
MMCSD_err mmcsd_read_block(uint32_t address, uint16_t size, uint8_t* ptr);
MMCSD_err mmcsd_write_data(uint32_t address, uint16_t size, uint8_t* ptr);
MMCSD_err mmcsd_write_block(uint32_t address, uint16_t size, uint8_t* ptr);
MMCSD_err mmcsd_go_idle_state(void);
MMCSD_err mmcsd_print_csd();
MMCSD_err mmcsd_print_cid();
MMCSD_err mmcsd_sd_status(uint8_t r2[]);
MMCSD_err mmcsd_send_status(uint8_t r2[]);
MMCSD_err mmcsd_set_blocklen(uint32_t blocklen);
MMCSD_err mmcsd_read_single_block(uint32_t address);
MMCSD_err mmcsd_read_sector(uint32_t address);
MMCSD_err mmcsd_write_single_block(uint32_t address);
MMCSD_err mmcsd_sd_send_op_cond(void);
MMCSD_err mmcsd_app_cmd(void);
MMCSD_err mmcsd_read_ocr(uint8_t* r1);
MMCSD_err mmcsd_crc_on_off(int1 crc_enabled);
void mmcsd_send_cmd(uint8_t cmd, uint32_t arg);
uint8_t mmcsd_get_r1(void);
void mmcsd_get_r2(void);
void mmcsd_get_r3(void);
void mmcsd_get_r7(void);
MMCSD_err mmcsd_wait_for_token(uint8_t token);
uint8_t mmcsd_crc7(char *data, uint8_t length);
uint16_t mmcsd_crc16(char *data, uint8_t length);
void mmcsd_select();
void mmcsd_deselect();

/// Fast Functions ! ///

MMCSD_err mmcsd_load_buffer(void);
MMCSD_err mmcsd_flush_buffer(void);
MMCSD_err mmcsd_move_buffer(uint32_t new_addr);
MMCSD_err mmcsd_read_byte(uint32_t addr, char* data);
MMCSD_err mmcsd_write_byte(uint32_t addr, char data);

uint8_t g_cr[8];
int8 card_type;

//////////////////////////////////
////                          ////
//// Function Implementations ////
////                          ////
//////////////////////////////////

void mmcsd_send_cmd(uint8_t cmd, uint32_t arg)
{   
   uint8_t packet[6]; // the entire command, argument, and crc in one variable
   uint8_t  timeout = 8; // maximum amount loops to wait for idle before getting impatient and leaving the function with an error code
   
   mmcsd_select();
   spi_read(0xFF);spi_read(0xFF);spi_read(0xFF);      //Send buffer clock to remove any trailing data.
   // construct the packet
   // every command on an SD card is or'ed with 0x40
   packet[0] = cmd | 0x40;
   packet[1] = make8(arg, 3);
   packet[2] = make8(arg, 2);
   packet[3] = make8(arg, 1);
   packet[4] = make8(arg, 0);
   packet[5] = mmcsd_crc7(packet, 5);
   spi_read(packet[0]);
   spi_read(packet[1]);
   spi_read(packet[2]);
   spi_read(packet[3]);
   spi_read(packet[4]);
   spi_read(packet[5]);
   while(timeout)
   {
      g_cr[1] = spi_read(0xFF);
      if(g_cr[1] != 0xFF)
         break;
      timeout--;
   }
   if((cmd == 58)||(cmd == 8))  //checking response of CMD58
   {
      g_cr[2] = spi_read(0xFF);
      g_cr[3] = spi_read(0xFF);
      g_cr[4] = spi_read(0xFF);
      g_cr[5] = spi_read(0xFF); 
   }
   //spi_read(0xFF); //extra 8 CLK
   //mmcsd_deselect();
}

uint8_t mmcsd_get_r1(void)
{
   uint8_t r1;
   uint8_t  timeout = 8; // maximum amount loops to wait for idle before getting impatient and leaving the function with an error code
    
   // loop until timeout == 0
   while(timeout)
   {
      r1 = spi_read(0xFF);
      if(r1 != 0xFF)
         break;
      timeout--;
   }
   return r1;
}

void mmcsd_get_r2(void)
{
   mmcsd_get_r1();
   g_cr[2] = spi_read(0xFF);
}

void mmcsd_get_r3(void)
{
   mmcsd_get_r1();
   g_cr[2] = spi_read(0xFF);
   g_cr[3] = spi_read(0xFF);
   g_cr[4] = spi_read(0xFF);
   g_cr[5] = spi_read(0xFF);
}

void mmcsd_get_r7(void)
{
   mmcsd_get_r1();
   g_cr[2] = spi_read(0xFF);
   g_cr[3] = spi_read(0xFF);
   g_cr[4] = spi_read(0xFF);
   g_cr[5] = spi_read(0xFF);
}

MMCSD_err mmcsd_software_reset()
{
   uint8_t  r1;
   uint16_t i;
   mmcsd_deselect();
   // Clock out 80 clks (more than 74) with CS and DO high.
   for (i = 0; i < 10; i++)
      r1 = spi_read(0xFF);
   //=========Send 'reset & go idle' command
   card_type = 0;
   i = 1000;      // 1 second
   do {
      delay_ms(1);
      mmcsd_send_cmd(GO_IDLE_STATE, 0);
      //mmcsd_send_cmd(0, 0);
   } while((g_cr[1] != 0x01)&& (--i));
   if (!i) {
      return RESP_TIMEOUT;
   } else {
      return g_cr[1];
   }
}

MMCSD_err mmcsd_init()
{
   uint8_t  r1;
   uint16_t i;
   r1 = mmcsd_software_reset();
   if (r1 == 1) {
      mmcsd_send_cmd(SEND_IF_COND,0x000001AA);
      if(g_cr[1] != 1) {
         return g_cr[1];
      } else {
         if ((g_cr[5] == 0xAA)&&((g_cr[4]&0x0F)==1)) {
            card_type = 2;
            i = 1000;
            while (i) {
               mmcsd_send_cmd(APP_CMD,0);
               mmcsd_send_cmd(SD_SEND_OP_COND,0x40000000);
               if(g_cr[1] == 0) 
                  break;
            }
            if (i == 0)
               return RESP_TIMEOUT;
            //mmcsd_send_cmd(SET_BLOCKLEN,0x00000200);  //Force block mode 512
            return g_cr[1];
         }
      }
   }
   return r1;
}

MMCSD_err mmcsd_read_sector(uint32_t address)
{
   uint8_t data_token;
   uint16_t count;
   mmcsd_send_cmd(READ_SINGLE_BLOCK,address);
   count = 0xFFFF;
   do {
      data_token = spi_read(0xFF); 
   } while ((data_token != 0xFE) && (count--));
   for (count = 0; count < MMCSD_MAX_BLOCK_SIZE; count++)
   {
      g_mmcsd_buffer[count] = spi_read(0xFF);
   }
   data_token = spi_read(0xFF); data_token = spi_read(0xFF); // Flushing in the don't care 2 CRC bytes
   mmcsd_deselect();
   return 0;
}

MMCSD_err mmcsd_write_sector(uint32_t address)
{
   uint8_t data_token;
   uint16_t count;
   mmcsd_send_cmd(WRITE_SINGLE_BLOCK,address);
   spi_read(0xFE);   // Send data token
   for (count = 0; count < MMCSD_MAX_BLOCK_SIZE; count++)
   {
      spi_read(g_mmcsd_buffer[count]);
   }
   data_token = spi_read(0xFF); data_token = spi_read(0xFF); // Flushing out the 2 dummy CRC bytes
   count = 0xFFFF;
   do {
      data_token = spi_read(0xFF); 
   } while ((data_token == 0xFF) && (count--));
   data_token = spi_read(0xFF);
   mmcsd_deselect();
   data_token = spi_read(0xFF);
   return 0;
}

MMCSD_err mmcsd_read_data(uint32_t address, uint16_t size, uint8_t* ptr)
{
   MMCSD_err r1;
   uint16_t i;  // counter for loops

   for(i = 0; i < size; i++)
   {
      r1 = mmcsd_read_byte(address++, ptr++);
      if(r1 != MMCSD_GOODEC)
         return r1;
   }
   
   return MMCSD_GOODEC;
}

MMCSD_err mmcsd_write_data(uint32_t address, uint16_t size, uint8_t* ptr)
{
   MMCSD_err ec;
   uint16_t i;  // counter for loops
  
   for(i = 0; i < size; i++)
   {
      ec = mmcsd_write_byte(address++, *ptr++);
      if(ec != MMCSD_GOODEC)
         return ec;
   }
   
   return MMCSD_GOODEC;
}

MMCSD_err mmcsd_print_csd()
{  
   uint8_t  buf[16], i, r1;

   mmcsd_send_cmd(SEND_CSD, 0);
   if(g_cr[1] != MMCSD_GOODEC) {
      return g_cr[1];
   }
   i = 32;
   while (1) {
      r1 = spi_read(0xFF);
      if (r1 == 0xFE)   // The data token
         break;
   }
   if (i == 0)
      return RESP_TIMEOUT;
   for(i = 0; i < 16; i++) // Read the 16 bytes of CSD
      buf[i] = spi_read(0xFF);
   
   r1 = spi_read(0xFF); r1 = spi_read(0xFF); // Flushing out the 2 CRC bytes
   mmcsd_deselect();

   printf("\r\nCSD_STRUCTURE: %X", (buf[0] & 0x0C) >> 2);
   printf("\r\nTAAC: %X", buf[1]);
   printf("\r\nNSAC: %X", buf[2]);
   printf("\r\nTRAN_SPEED: %X", buf[3]);
   printf("\r\nCCC: %lX", (make16(buf[4], buf[5]) & 0xFFF0) >> 4);
   printf("\r\nREAD_BL_LEN: %X", buf[5] & 0x0F);   
   printf("\r\nREAD_BL_PARTIAL: %X", (buf[6] & 0x80) >> 7);
   printf("\r\nWRITE_BLK_MISALIGN: %X", (buf[6] & 0x40) >> 6);
   printf("\r\nREAD_BLK_MISALIGN: %X", (buf[6] & 0x20) >> 5);
   printf("\r\nDSR_IMP: %X", (buf[6] & 0x10) >> 4);
   printf("\r\nC_SIZE: %lX", (((buf[6] & 0x03) << 10) | (buf[7] << 2) | ((buf[8] & 0xC0) >> 6)));
   printf("\r\nVDD_R_CURR_MIN: %X", (buf[8] & 0x38) >> 3);
   printf("\r\nVDD_R_CURR_MAX: %X", buf[8] & 0x07);
   printf("\r\nVDD_W_CURR_MIN: %X", (buf[9] & 0xE0) >> 5);
   printf("\r\nVDD_W_CURR_MAX: %X", (buf[9] & 0x1C) >> 2);
   printf("\r\nC_SIZE_MULT: %X", ((buf[9] & 0x03) << 1) | ((buf[10] & 0x80) >> 7));
   printf("\r\nERASE_BLK_EN: %X", (buf[10] & 0x40) >> 6);
   printf("\r\nSECTOR_SIZE: %X", ((buf[10] & 0x3F) << 1) | ((buf[11] & 0x80) >> 7));
   printf("\r\nWP_GRP_SIZE: %X", buf[11] & 0x7F);
   printf("\r\nWP_GRP_ENABLE: %X", (buf[12] & 0x80) >> 7);
   printf("\r\nR2W_FACTOR: %X", (buf[12] & 0x1C) >> 2);
   printf("\r\nWRITE_BL_LEN: %X", ((buf[12] & 0x03) << 2) | ((buf[13] & 0xC0) >> 6));
   printf("\r\nWRITE_BL_PARTIAL: %X", (buf[13] & 0x20) >> 5);
   printf("\r\nFILE_FORMAT_GRP: %X", (buf[14] & 0x80) >> 7);
   printf("\r\nCOPY: %X", (buf[14] & 0x40) >> 6);
   printf("\r\nPERM_WRITE_PROTECT: %X", (buf[14] & 0x20) >> 5);
   printf("\r\nTMP_WRITE_PROTECT: %X", (buf[14] & 0x10) >> 4);
   printf("\r\nFILE_FORMAT: %X", (buf[14] & 0x0C) >> 2);
   printf("\r\nCRC: %X", buf[15]);

   return r1;
}

MMCSD_err mmcsd_print_cid()
{
   uint8_t  buf[16], i, r1;

   mmcsd_send_cmd(SEND_CID, 0);
   if(g_cr[1] != MMCSD_GOODEC) {
      return g_cr[1];
   }
   while (1) {
      r1 = spi_read(0xFF);
      if (r1 == 0xFE)   // The data token
         break;
   }
   if (i == 0)
      return RESP_TIMEOUT;
   for(i = 0; i < 16; i++) // Read the 16 bytes of CSD
      buf[i] = spi_read(0xFF);
   
   r1 = spi_read(0xFF); r1 = spi_read(0xFF); // Flushing out the 2 CRC bytes
   mmcsd_deselect();
   
   printf("\r\nManufacturer ID: %X", buf[0]);
   printf("\r\nOEM/Application ID: %c%c", buf[1], buf[2]);
   printf("\r\nOEM/Application ID: %c%c%c%c%c", buf[3], buf[4], buf[5], buf[6], buf[7]);
   printf("\r\nProduct Revision: %X", buf[8]);
   printf("\r\nSerial Number: %X%X%X%X", buf[9], buf[10], buf[11], buf[12]);
   printf("\r\nManufacturer Date Code: %X%X", buf[13] & 0x0F, buf[14]);
   printf("\r\nCRC-7 Checksum: %X", buf[15]);

   return r1;
}

MMCSD_err mmcsd_sd_status(uint8_t r2[])
{
   uint8_t i;

   mmcsd_select();
   mmcsd_send_cmd(APP_CMD, 0);
   mmcsd_get_r1();
   mmcsd_deselect();

   mmcsd_select();
   mmcsd_send_cmd(SEND_STATUS, 0);

   for(i = 0; i < 64; i++)
      spi_read(0xFF);      

   mmcsd_deselect();

   mmcsd_get_r2();
   return g_cr[2];
}

MMCSD_err mmcsd_wait_for_token(uint8_t token)
{
   // get a token
   mmcsd_get_r1();
   
   // check to see if the token we recieved was the one that we were looking for
   if(g_cr[1] == token)
      return MMCSD_GOODEC;
   
   // if that wasn't right, return the error
   return g_cr[1];   
}

unsigned int8 mmcsd_crc7(char *data,uint8_t length)
{
   uint8_t i, ibit, c, crc;
    
   crc = 0x00;                                                                // Set initial value

   for (i = 0; i < length; i++, data++)
   {
      c = *data;

      for (ibit = 0; ibit < 8; ibit++)
      {
         crc = crc << 1;
         if ((c ^ crc) & 0x80) crc = crc ^ 0x09;                              // ^ is XOR
         c = c << 1;
      }

       crc = crc & 0x7F;
   }

   shift_left(&crc, 1, 1);                                                    // MMC card stores the result in the top 7 bits so shift them left 1
                                                                              // Should shift in a 1 not a 0 as one of the cards I have won't work otherwise
   return crc;
}

uint16_t mmcsd_crc16(char *data, uint8_t length)
{
   uint8_t i, ibit, c;

   uint16_t crc;

   crc = 0x0000;                                                                // Set initial value

   for (i = 0; i < length; i++, data++)
   {
      c = *data;

      for (ibit = 0; ibit < 8; ibit++)
      {
         crc = crc << 1;
         if ((c ^ crc) & 0x8000) crc = crc ^ 0x1021;                              // ^ is XOR
         c = c << 1;
      }

       crc = crc & 0x7FFF;
   }

   shift_left(&crc, 2, 1);                                                    // MMC card stores the result in the top 7 bits so shift them left 1
                                                                              // Should shift in a 1 not a 0 as one of the cards I have won't work otherwise
   return crc;
}

void mmcsd_select()
{
   //delay_ms(1);
   output_high(PIN_A0); //Disable the AFE
   output_low(MMCSD_PIN_SELECT);
   //delay_ms(1);
}

void mmcsd_deselect()
{
   //spi_read(0xFF);
   //delay_ms(1);
   output_high(MMCSD_PIN_SELECT);
   //delay_ms(1);
}

#endif //_MMCSD_H_



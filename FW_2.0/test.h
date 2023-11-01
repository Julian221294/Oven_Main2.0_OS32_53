#ifndef _TEST_H_
#define _TEST_H_

char ch, cmd;
uint8_t i;
BYTE value;
int32 address = 0;
uint8_t ds1307_guard;
uint8_t mon_data_curr, mon_data_prev;
uint32_t page_ptr;
uint16_t byte_ptr;
unsigned char sec, min, hour, day, date, month, year;
unsigned char last_min, curr_min;
unsigned int16 half_second_count = HALF_SECOND;
unsigned int8 tick;
unsigned int8 time_update_index = 0;

uint16_t is_sector_used(uint32_t sector)
{
   int16 tmp;
   mmcsd_read_sector(sector);
   if ( (g_mmcsd_buffer[0] == make8(sector, 3))&&
         (g_mmcsd_buffer[1] == make8(sector, 2))&&
         (g_mmcsd_buffer[2] == make8(sector, 1))&&
         (g_mmcsd_buffer[3] == make8(sector, 0))&&
         (g_mmcsd_buffer[4] == 0x55)&&
         (g_mmcsd_buffer[5] == 0xAA) ) {
      tmp = make16(g_mmcsd_buffer[6], g_mmcsd_buffer[7]);
      return tmp;
   }
   return 0;
}

void get_ptr(void)
{
   int16 tmp;
   page_ptr = 0;
   byte_ptr = 8;
   while(page_ptr < 1000) {
      tmp = is_sector_used(page_ptr);
      if (tmp > 0) {
         if (tmp == 512) {
            page_ptr += 1;
         } else {
            byte_ptr = tmp;
            break;
         }
      } else {
         g_mmcsd_buffer[0] = make8(page_ptr,3);
         g_mmcsd_buffer[1] = make8(page_ptr,2);
         g_mmcsd_buffer[2] = make8(page_ptr,1);
         g_mmcsd_buffer[3] = make8(page_ptr,0);
         g_mmcsd_buffer[4] = 0x55;
         g_mmcsd_buffer[5] = 0xAA;
         g_mmcsd_buffer[6] = 0;
         g_mmcsd_buffer[7] = 8;
         for(tmp = 8; tmp < 512; tmp++)
            g_mmcsd_buffer[tmp] = 0;
         mmcsd_write_sector(page_ptr);
         break;
      }
      printf("\r\nChecking page %Lu...", page_ptr);
   }
}

void init_mmcsd(void)
{
   char str[] = "Hello World!\n";
   rtcc_init();
   //SPI settings:
   output_drive(MMCSD_PIN_SCL);
   output_drive(MMCSD_PIN_SDO);
   output_drive(MMCSD_PIN_SELECT);
   output_float(MMCSD_PIN_SDI);
   delay_ms(100);
   delay_ms(100);
   // TODO: USER CODE!!
   delay_ms(1000);
   printf("Hello World!\n");
   
   i = mmcsd_init();
   delay_ms(100);
   
   if (i == 0) {
      printf("Card Init Successful!\n\r");
      switch (card_type)
      {
         case 1:
            printf("Standard Capacity Card (Ver 1.x) Detected!\n\r");
            break;
         case 2:
            printf("High Capacity Card Detected!\n\r");
            break;
         case 3:
            printf("Standard Capacity Card (Ver 2.x) Detected!\n\r");
            break;
         default:
            printf("Unknown SD Card Detected!\n\r");
            break; 
      }
   } else {
      printf("Card Init Failure! Code: %u\n\r", i);
   }
   get_ptr();
   delay_ms(100);
   printf("Current page ptr %Lu\n\r", page_ptr);
   printf("Current byte ptr %Lu\n\r", byte_ptr);
   delay_ms(100);
   
}

void process_remote_command(char rm_cmd)
{
   int32 read_page_ptr;
   switch(rm_cmd) {
      case 'p':
         printf("%Lu\n", page_ptr);
         break;
      case 'l':
         read_page_ptr = make32(getc()-0x30, getc()-0x30, getc()-0x30, getc()-0x30);
         mmcsd_read_sector(read_page_ptr);
         for (read_page_ptr = 0; read_page_ptr < 512; read_page_ptr++)
         {
            printf("%u:", g_mmcsd_buffer[read_page_ptr]);
         }
         printf("\n");
         
   }
}
void process_kbhit(void)
{
   char rcmd;
   if (kbhit())
   {
      ch = getc();
      switch (ch)
      {
         case 'g':
            get_ptr();
            printf("Current page ptr %Lu\n\r", page_ptr);
            printf("Current byte ptr %Lu\n\r", byte_ptr);
            break;
         case '1':
            i = mmcsd_software_reset();
            if (i == 1){
               printf ("MMC/SD card software reset successfull!\n\r");
            }else {
               printf ("MMC/SD card software reset error! code: %u\n\r", i);
            }
            break;
         case '2':
            mmcsd_send_cmd(SEND_OP_COND,0);
            printf("%u\n\r", g_cr[1]);
            break;
         case '3':
            mmcsd_send_cmd(READ_OCR,0);
            printf("%u:%u:%u:%u:%u\n\r", g_cr[1], g_cr[2], g_cr[3], g_cr[4], g_cr[5]);
            break;
         case '4':
            mmcsd_send_cmd(SEND_IF_COND,0x000001AA);
            printf("%u:%u:%u:%u:%u\n\r", g_cr[1], g_cr[2], g_cr[3], g_cr[4], g_cr[5]);
            break;
         case '5':
            mmcsd_send_cmd(APP_CMD,0);
            mmcsd_send_cmd(SD_SEND_OP_COND,0x40000000);
            printf("%u\n\r", g_cr[1]);
            break;
         case 'I':
         case 'i':
            i = mmcsd_init();
            switch (card_type)
            {
               case 1:
                  printf("Standard Capacity Card (Ver 1.x) Detected!\n\r");
                  break;
               case 2:
                  printf("High Capacity Card Detected!\n\r");
                  break;
               case 3:
                  printf("Standard Capacity Card (Ver 2.x) Detected!\n\r");
                  break;
               default:
                  printf("Unknown SD Card Detected!\n\r");
                  break; 
            }
            break;
         case 'C':
         case 'c':
            //printf("===============CSD===============\r\n");
            mmcsd_print_csd();
            printf("===============CID===============\r\n");
            mmcsd_print_cid();
            break;
         case 'd':
            printf("Current page ptr %Lu\n\r", page_ptr);
            printf("Current byte ptr %Lu\n\r", byte_ptr);
            break;
         case 'R':
         case 'r':
            printf("Address?\n\r");
            address = make32(getc()-0x30, getc()-0x30, getc()-0x30, getc()-0x30);
            mmcsd_read_sector(address);
            for (address = 0; address < 512; address++)
            {
               printf("%u:", g_mmcsd_buffer[address]);
            }
            printf("\n\r");
            break;
         case 'W':
         case 'w':
            printf("Address?\n\r");
            address = make32(getc()-0x30, getc()-0x30, getc()-0x30, getc()-0x30);
            printf("Value?\n\r");
            value = getc();
            for (index = 0; index < 512; index++)
            {
               g_mmcsd_buffer[index] = value;
            }
            mmcsd_write_sector(address);
            printf("%d is written to @%ld\n\r", value, address);
            break;
         case 'S':
            address = 1000;
            for (index = 0; index < 512; index++)
            {
               g_mmcsd_buffer[index] = 0xFF;
            }
            for (index = 1; index < address; index++) {
               mmcsd_write_sector(index);
               printf("Blanking out Page %Lu ...\n\r", index);
            }
            break;
         case 's':
            printf("Page ptr?\n\r");
            address = getc() - '0';
            for (index = 0; index < 512; index++)
            {
               g_mmcsd_buffer[index] = 0xFF;
            }
            for (index = 1; index < address; index++) {
               mmcsd_write_sector(index);
               printf("Blanking out Page %Lu ...\n\r", index);
            }
            break;
         case 'b':
            printf("Page ptr?\n\r");
            address = getc() - '0';
            for (index = 0; index < 512; index++)
            {
               g_mmcsd_buffer[index] = 0xFF;
            }
            mmcsd_write_sector(address);
            printf("Blanking out Page %Lu ...\n\r", address);
            break;
         case 'p':
            value = input_d();
            printf("PortD: %u\n\r", value);
            break;
         case 'l':
            break;
         case ':':
            rcmd = getc();
            process_remote_command(rcmd);
            break;
      }
   }
}


void log_state(void)
{
   if (mon_data_curr != mon_data_prev) {
      mon_data_prev = mon_data_curr;
      g_mmcsd_buffer[byte_ptr] = ':';
      g_mmcsd_buffer[byte_ptr+1] = year;
      g_mmcsd_buffer[byte_ptr+2] = month;
      g_mmcsd_buffer[byte_ptr+3] = date;
      g_mmcsd_buffer[byte_ptr+4] = hour;
      g_mmcsd_buffer[byte_ptr+5] = min;
      g_mmcsd_buffer[byte_ptr+6] = sec;
      g_mmcsd_buffer[byte_ptr+7] = mon_data_curr;
      byte_ptr += 8;
      g_mmcsd_buffer[6] = make8(byte_ptr,1);
      g_mmcsd_buffer[7] = make8(byte_ptr,0);
      mmcsd_write_sector(page_ptr);
      //printf("Current page ptr %Lu\n\r", page_ptr);
      //printf("Current byte ptr %Lu\n\r", byte_ptr);
      print_time();
      //printf("Data %u\n\r", mon_data_curr);
      if (byte_ptr >= 512) {
         byte_ptr = 8;
         page_ptr += 1;
         for (index = 8; index < 512; index++) {
            g_mmcsd_buffer[index] = 0x00;
         }
         g_mmcsd_buffer[0] = make8(page_ptr,3);
         g_mmcsd_buffer[1] = make8(page_ptr,2);
         g_mmcsd_buffer[2] = make8(page_ptr,1);
         g_mmcsd_buffer[3] = make8(page_ptr,0);
         g_mmcsd_buffer[4] = 0x55;
         g_mmcsd_buffer[5] = 0xAA;
         g_mmcsd_buffer[6] = 0;
         g_mmcsd_buffer[7] = 8;
         mmcsd_write_sector(page_ptr);
      }
   }
}

void main_guard(void)
{
   if (half_second_count == 0) {
      //disable_interrupts(GLOBAL);
      half_second_count = HALF_SECOND;
      if(tick == 0) {
         tick = 1;
         sec = read_DS1307(0);
         mon_data_curr = input_b()&0x80;  //bit 7 of PortB
         mon_data_curr |= (input_a()&0x78)<<1;  //bit 3, 4, 5, 6 of PortA
         mon_data_curr |= input_e()&0x07;  //bit 0, 1, 2 of PortE
         put_state(mon_data_curr);
         //if(sec == 0) {
            min = read_DS1307(1);
            hour = read_DS1307(2);
            day = read_DS1307(3);
            date = read_DS1307(4);
            month = read_DS1307(5);
            year = read_DS1307(6);
            log_state();
         //}
      } else {
         tick = 0;
      }
      //enable_interrupts(GLOBAL);
   }
}

#endif

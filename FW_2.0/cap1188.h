#ifndef _CAP1188_H_
#define _CAP1188_H_

#include "globals.h"

#use fast_io(C)

#define CAP_RESET    PIN_C0
#define CAP_CS1      PIN_D4
#define CAP_CS2      PIN_D5
#define CAP_CLK      PIN_C3
#define CAP_MOSI     PIN_C4
#define CAP_MISO     PIN_C5

#inline
void cap1188_reset(void)
{
   output_low(CAP_CS1);
   output_low(CAP_RESET);
   delay_ms(10);
   output_high(CAP_RESET);
   delay_ms(100);
   output_low(CAP_RESET);
   delay_ms(1);
   output_high(CAP_CS1);
   delay_ms(1);
   //
   output_low(CAP_CS2);
   output_low(CAP_RESET);
   delay_ms(10);
   output_high(CAP_RESET);
   delay_ms(100);
   output_low(CAP_RESET);
   delay_ms(1);
   output_high(CAP_CS2);
}
/*
void cap1188_clr_int(void)
{
   
}

void cap1188_reset_interface(void)
{   
   output_low(CAP_CS1);
   delay_ms(1);
   spi_write(0x7A);
   spi_write(0x7A);
   delay_ms(1);
   output_high(CAP_CS1);
   delay_ms(1);
   output_low(CAP_CS2);
   delay_ms(1);
   spi_write(0x7A);
   spi_write(0x7A);
   delay_ms(1);
   output_high(CAP_CS2);
}

void cap1188_set_address_ptr1(int8 adr)
{
   output_low(CAP_CS1);
   delay_us(1);
   spi_write(0x7D);
   spi_write(adr);
   delay_us(1);
   output_high(CAP_CS1);
}

void cap1188_set_address_ptr2(int8 adr)
{
   output_low(CAP_CS2);
   delay_us(1);
   spi_write(0x7D);
   spi_write(adr);
   delay_us(1);
   output_high(CAP_CS2);
}
*/
void cap1188_write_data1(int8 addr, int8 data)
{
   output_low(CAP_CS1);
   delay_us(10);
   spi_write(0x7D);
   spi_write(addr);
   delay_us(10);
   spi_write(0x7E);
   spi_write(data);
   delay_us(10);
   output_high(CAP_CS1);
}

void cap1188_write_data2(int8 addr, int8 data)
{
   output_low(CAP_CS2);
   delay_us(10);
   spi_write(0x7D);
   spi_write(addr);
   delay_us(10);
   spi_write(0x7E);
   spi_write(data);
   delay_us(10);
   output_high(CAP_CS2);
}

int8 cap1188_read_data1(int8 addr)
{
   int8 data;
   output_low(CAP_CS1);
   delay_us(10);
   spi_write(0x7D);
   spi_write(addr);
   delay_us(10);
   spi_write(0x7F);
   data = spi_read(0x7F);
   delay_us(10);
   output_high(CAP_CS1);
   return data;
}

int8 cap1188_read_data2(int8 addr)
{
   int8 data;
   output_low(CAP_CS2);
   delay_us(10);
   spi_write(0x7D);
   spi_write(addr);
   delay_us(10);
   spi_write(0x7F);
   data = spi_read(0x7F);
   delay_us(10);
   output_high(CAP_CS2);
   return data;
}
/*
void cap1188_disable_int(void)
{
   cap1188_write_data1(0x27, 0x00);
   cap1188_write_data2(0x27,0x00);
}

void cap1188_disable_ret(void)
{
   cap1188_write_data1(0x28, 0x00);
   cap1188_write_data2(0x28, 0x00);
}
*/
void cap1188_init(void)
{
   delay_ms(100);
   cap1188_reset();
   delay_ms(100);
}

/*void cap1188_clr_int1(void)
{
   cap1188_write_data1(0, 0);
}

void cap1188_clr_int2(void)
{
   cap1188_write_data2(0, 0);
}*/

#endif   // #define _CAP1188_H_


//
// FILE 
// spif.c
//
// DESCRIPTION
// spi-flash support
//
#include "config.h"
#include "regmap.h"
#include "types.h"

#include "spif.h"

// System used GPIO
#define GPIO_IRIN       20
#define GPIO_VFDCLK     21
#define GPIO_VFDSTB     22
#define GPIO_VFDDAT     23

// GPIO assumption of spi-flash interface
#define GPIO_SPI_CLK    GPIO_VFDCLK         // CLK: spi-flash required clock
#define GPIO_SPI_CS     GPIO_VFDSTB         // CS: spi-flash chip-select
#define GPIO_SPI_DI     GPIO_VFDDAT         // DI: input of spi-flash
#define GPIO_SPI_DO     GPIO_IRIN           // DO: output of spi-flash

// assume all GPIO in the the same gpio_*[] register
#define GPIO_OUT        regs0->gpio_out[GPIO_SPI_DI/16]     
#define GPIO_IN         regs0->gpio_in[GPIO_SPI_DO/16]

#define CLK1            (1<<(GPIO_SPI_CLK%16))
#define DO1             (1<<(GPIO_SPI_DI%16))
#define CS1             (1<<(GPIO_SPI_CS%16))

#define DIB             (GPIO_SPI_DO%16)
#define DI1             (1<<DIB)


static void
spiflash_write_byte(unsigned v)
{
    int i;
    unsigned gpioc0d0;
    unsigned gpioc0d1;

    gpioc0d0  = GPIO_OUT & ~(CLK1|DO1);
    gpioc0d1  = gpioc0d0 | DO1;

    for (i=0;i<8;i++) {
        unsigned gpioc0;
        if (v&(1<<7))
            gpioc0 = gpioc0d1;
        else 
            gpioc0 = gpioc0d0;
        GPIO_OUT = gpioc0;          // clk-0
        GPIO_OUT = gpioc0|CLK1;     // clk-1
        v<<=1;
    }
}


void
spiflash_assert_cs(void)
{
    GPIO_OUT |= CS1;
    GPIO_OUT &= ~CS1;
}


void
spiflash_deassert_cs(void)
{
    GPIO_OUT |= CS1;
}


static unsigned
spiflash_read_byte(void)
{
    int i __attribute__((unused));
    unsigned gpioc0, gpioc1, gi;
    unsigned v;

    gpioc0  = GPIO_OUT & ~(CLK1|DO1);
    gpioc1  = gpioc0 | CLK1;
    v = 0;
#if 0
    for (i=7;i>=0;i--) {
        GPIO_OUT = gpioc0;
        GPIO_OUT = gpioc1;
        if (GPIO_IN & DI1) v |= (1<<i);
    }
#else
        GPIO_OUT = gpioc0;
        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<7;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<6;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<5;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<4;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<3;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<2;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<1;

        GPIO_OUT = gpioc1;
        gi = GPIO_IN;
        GPIO_OUT = gpioc0;
        v |= ((gi>>DIB) & 0x01) <<0;

#endif

    return v;
}


static void
spiflash_read_bytes(UINT8 *target, unsigned len)
{
    while (len--) {
        *target++ = spiflash_read_byte();
    }
}




unsigned
spiflash_read_id(void)
{
    unsigned v=0;
    spiflash_assert_cs();
    spiflash_write_byte(0x90);
    spiflash_write_byte(0x0);
    spiflash_write_byte(0x0);
    spiflash_write_byte(0x0);
    v = (v<<8) |spiflash_read_byte();
    v = (v<<8) |spiflash_read_byte();
    return v;
}

void
spiflash_write_enable(void)
{
    spiflash_assert_cs();
    spiflash_write_byte(0x06);
    spiflash_deassert_cs();
}


void
spiflash_write_disable(void)
{
    spiflash_assert_cs();
    spiflash_write_byte(0x04);
    spiflash_deassert_cs();
}


void
spiflash_write_status(unsigned status)
{
    spiflash_assert_cs();
    spiflash_write_byte(0x01);
    spiflash_write_byte(status);
}


unsigned
spiflash_read_status(void)
{
    unsigned v;
    spiflash_assert_cs();
    spiflash_write_byte(0x05);
    v = spiflash_read_byte();
    return v;
}


void
spiflash_program(UINT8 *src, unsigned address, unsigned len)
{
    spiflash_assert_cs();
    spiflash_write_byte(0x02);
    spiflash_write_byte(address>>16);       // 23:16
    spiflash_write_byte(address>>8);        // 15:8
    spiflash_write_byte(address>>0);        // 7:0

    while (len--) {
        spiflash_write_byte(*src++);
    }
    spiflash_deassert_cs();
}



void
spiflash_fast_read(UINT8 *target, unsigned address, unsigned len)
{
    spiflash_assert_cs();
    spiflash_write_byte(0x0B);
    spiflash_write_byte(address>>16);       // 23:16
    spiflash_write_byte(address>>8);        // 15:8
    spiflash_write_byte(address>>0);        // 7:0

    spiflash_read_byte();
    spiflash_read_bytes(target, len);
}



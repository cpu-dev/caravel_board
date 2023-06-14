#include "../defs.h"
#include "../gpio_config/gpio_config_io.c"

#define BASE_ADDR 0x30000000
#define IMEM_WRITE BASE_ADDR
#define UART_CLK_FREQ BASE_ADDR + 0x4

static void
write(uint32_t addr, uint32_t val)
{
    *(volatile uint32_t *)addr = val;
}

void
reset()
{
    reg_wb_enable = 1;
    reg_mprj_io_35 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_USER_STD_OUTPUT;

    reg_mprj_io_37 = GPIO_MODE_USER_STD_OUTPUT;
    reg_la0_iena = 0;
    reg_la0_oenb = 0;

    reg_la0_data = 0;
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void
main()
{
    #include "instr.c"

    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    gpio_config_io();
    reg_gpio_out = 1;

    reset();

    // set reset to high
	reg_la0_data = 1;

    // set uart clk frequency
    write(UART_CLK_FREQ, 10000000);

    for(int i = 0; i < 10; ++i) {
        write(IMEM_WRITE, i << 8 | mem[i]);
    }

//    reg_la0_data = 1 << 16 | 0x00 << 8 | 0b11000000; // ldih 0  0xC0
//    reg_la0_data = 1 << 16 | 0x01 << 8 | 0b11010000; // ldil 0  0xD0
//    reg_la0_data = 1 << 16 | 0x02 << 8 | 0b10110011; // jmp r3  0xB3

    reg_la0_data = 0;
    reg_gpio_out = 0x0;

    while(1) {
        reg_gpio_out = 0x0;
        delay(100000);
        reg_gpio_out = 0x1;
        delay(100000);
    }
}


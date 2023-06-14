# jacaranda-8_test

.
├── gpio_config_io.py
├── instr.c instructions that is loaded to Jacaranda-8's Imem.
├── instr_gpio.c contains gpio test instructions
├── instr_uart.c contains uart test instructions
├── jacaranda-8_test.c test firmware
├── jacaranda-8_test_gpio.c test firmware for gpio
├── jacaranda-8_test_uart.c test firmware for uart
├── Makefile
└── xclk_by_nucleo.py using external clock by nucleo board

## To use external clock
move to `../nucleo`, then run `make repl`

```
cd ../nucleo
make repl
```

then copy the lines of `xclk_by_nucleo.py` to micropython console.


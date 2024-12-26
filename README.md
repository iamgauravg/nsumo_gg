
install GCM https://github.com/git-ecosystem/git-credential-manager/releases
tar -xvzf gcm-linux_amd64.2.6.0.tar.gz
./git-credential-manager configure
./git-credential-manager --version
git config --global credential.credentialStore secretservice

sudo apt install git
git init
git config --local user.email "iamgauravg@gmail.com"
git config --local user.name "Gaurav Gupta"
git add .
git status
git commit
git log
git remote add origin git@github.com:iamgauravg/nsumo_gg.git
git remote set-url origin https://github.com/iamgauravg/nsumo_gg.git

git config credential.helper store
git push -u origin main


git submodule add https://github.com/mpaland/printf.git external/printf

sudo apt install cppcheck

-----------------------------------------
msp430-elf-gcc -c -mmcu=msp430fr2355 -I /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/ blink.c

msp430-elf-objdump --syms blink.o

------------------------------------------

msp430-elf-gcc -I /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/ -L /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/ -T /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/msp430fr2355.ld blink.c

-I to include msp430.h
-T to point to msp43fr2344.ld linker file
-L to point to the supporting/helper linker file like _symbols.ld

------------------------------------------

If we again have a look in the well-written MSP430 GCC User's Guide, we find the flag "-mmcu", which does three things:

Defines the symbol __MSP430XXXX__
Selects the ISA (430 or 430X)
Selects the MCU-specific linker script

Therefore, if we add this flag, we no longer need to define __MSP430XXXX__ at the top of blink.c (make sure you remove it) or provide the "-Wl,-T" flag. Our command instead becomes

msp430-elf-gcc -mmcu=msp430fr2355 -I /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/ -L /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/  blink.c

------------------------------------------
------------------------------------------
------------------------------------------
------------------------------------------
------------------------------------------

LD_LIBRARY_PATH=/home/gauravgupta/ti/ccs1281/ccs/ccs_base/DebugServer/drivers /home/gauravgupta/ti/ccs1281/ccs/ccs_base/DebugServer/bin/mspdebug tilib "prog a.out"

------------------------------------------
Understanding the original code from tutorial

        io_configure(io, &io_initial_configs[io]);

static const struct io_config io_initial_configs[IO_PORT_CNT * IO_PIN_CNT_PER_PORT] = 
{
    // Output
    [IO_TEST_LED] = { IO_SELECT_GPIO, IO_RESISTOR_DISABLED, IO_DIR_OUTPUT, IO_OUT_LOW },
    [IO_UART_RXD] = { IO_SELECT_ALT3, IO_RESISTOR_DISABLED, IO_DIR_OUTPUT, IO_OUT_LOW },
    [IO_UART_TXD] = { IO_SELECT_ALT3, IO_RESISTOR_DISABLED, IO_DIR_OUTPUT, IO_OUT_LOW },
};

void io_configure(io_e io, const struct io_config *config)
{
    io_set_select(io, config->select);
    io_set_direction(io, config->dir);
    io_set_out(io, config->out);
    io_set_resistor(io, config->resistor);
}

void io_set_select(io_e io, io_select_e select)
{
    const uint8_t port = io_port(io);
    const uint8_t pin = io_pin_bit(io);
    switch (select) {
    case IO_SELECT_GPIO:
        *port_sel1_regs[port] &= ~pin;
        *port_sel2_regs[port] &= ~pin;
        break;
    case IO_SELECT_ALT1:
        *port_sel1_regs[port] |= pin;
        *port_sel2_regs[port] &= ~pin;
        break;
    case IO_SELECT_ALT2:
        *port_sel1_regs[port] &= ~pin;
        *port_sel2_regs[port] |= pin;
        break;
    case IO_SELECT_ALT3:
        *port_sel1_regs[port] |= pin;
        *port_sel2_regs[port] |= pin;
        break;
    }
}

static volatile uint8_t *const port_sel1_regs[IO_PORT_CNT] = { &P1SEL, &P2SEL };
static volatile uint8_t *const port_sel2_regs[IO_PORT_CNT] = { &P1SEL2, &P2SEL2 };

----------------------------------------------------
Debugging

Get /home/gauravgupta/tools/msp430-gcc/bin/msp430-elf-gdb working
ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/libtinfo.so.5 

ls -l /usr/lib/libtinfo.so.5 
lrwxrwxrwx 1 root root 39 Dec 24 11:53 /usr/lib/libtinfo.so.5 -> /usr/lib/x86_64-linux-gnu/libtinfo.so.6
ls -l /lib/x86_64-linux-gnu/libncursesw.so.5
lrwxrwxrwx 1 root root 42 Dec 23 10:45 /lib/x86_64-linux-gnu/libncursesw.so.5 -> /usr/lib/x86_64-linux-gnu/libncursesw.so.6
idea from: https://stackoverflow.com/questions/48674104/clang-error-while-loading-shared-libraries-libtinfo-so-5-cannot-open-shared-o

gauravgupta@gauravgupta-ThinkPad-P1-Gen-3:~/tools/msp430-gcc$ bin/gdb_agent_console msp430.dat 
gauravgupta@gauravgupta-ThinkPad-P1-Gen-3:~/tempworkspace/nsumo_gg$ /home/gauravgupta/tools/msp430-gcc/bin/msp430-elf-gdb blink

(gdb) target remote :55000
Remote debugging using :55000
0x00008000 in __crt0_start ()
(gdb) b 44
Breakpoint 1 at 0x8082: file src/blink.c, line 44.
(gdb) b 47
Breakpoint 2 at 0x8098: file src/blink.c, line 47.
(gdb) lay split
(gdb) c
Continuing.
^C
Program stopped.
0x00008094 in main () at src/blink.c:44
44			switch1_pushed = ( (P4IN & 0x02) == 0x00);
(gdb) b 44
Breakpoint 1 at 0x8082: file src/blink.c, line 44.
(gdb) b 47
Breakpoint 2 at 0x8098: file src/blink.c, line 47.


Resource
http://www.simplyembedded.org/archives/debugging-with-gdb-mspdebug-and-ti-msp430-gcc/
https://github.com/dlbeer/mspdebug
Programming the MSP430 on debian linux tutorial
https://www.youtube.com/watch?v=1aSsr7nUfpk&t=20s
Debugging Embedded Systems With GDB?
https://www.youtube.com/watch?v=m4agpY_w2y8

/*
* Ping Pong OS
* main.c
* Projeto da disciplina Sistemas Operacionais - UTFPR - 2016.02
* Professor: Copetti
* Alunos: Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
*         Lucas Zimmermann Cordeiro ()
*/

#include <config/includes.h>

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

task_t Pang, Peng, Ping, Pong, Pung;

int flag;
int memPC = 0;

void Body (void * arg)
{
   int i ;

   for (i=0; i<4; i++)
   {
      printf ("%s %d\n", (char *) arg, i) ;
      task_yield ();
   }
   printf ("%s FIM\n", (char *) arg) ;
   task_exit (0) ;
}

//------------------------------------------------------------------------------

int main(void)
{
    uint32_t uartSourceClock = 0;
    UART_Type * baseAddr     = BOARD_DEBUG_UART_BASEADDR;

    // Enable clock for PORTs, setup board clock source, config pin
    hardware_init();
    dbg_uart_init();


    // Initialize the uart module with base address and config structure
    CLOCK_SYS_EnableUartClock(BOARD_DEBUG_UART_INSTANCE);

    // Get working uart clock
    uartSourceClock = CLOCK_SYS_GetUartFreq(BOARD_DEBUG_UART_INSTANCE);

    // Initialize UART baud rate, bit count, parity and stop bit
    UART_HAL_SetBaudRate(baseAddr, uartSourceClock, BOARD_DEBUG_UART_BAUD);
    UART_HAL_SetBitCountPerChar(baseAddr, kUart8BitsPerChar);
    UART_HAL_SetParityMode(baseAddr, kUartParityDisabled);
#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    UART_HAL_SetStopBitCount(baseAddr, kUartOneStopBit);
#endif

    // Enable the UART transmitter and receiver
    UART_HAL_EnableTransmitter(baseAddr);
    UART_HAL_EnableReceiver(baseAddr);

    // Inform to start polling example

    // Inform user of what to do

    printf("PING PONG OS\n");
    printf("Leonardo Winter Pereira\n");
    printf("Lucas Zimmermann Cordeiro\n");

    printf ("Main INICIO\n");

    task_init();

    task_create (&Pang, Body, "    Pang") ;
	//task_setprio (&Pang, 0);

	task_create (&Peng, Body, "        Peng");
	//task_setprio (&Peng, 2);

	task_create (&Ping, Body, "            Ping");
	//task_setprio (&Ping, 4);

	task_create (&Pong, Body, "                Pong");
	//task_setprio (&Pong, 6);

	task_create (&Pung, Body, "                    Pung");
	//task_setprio (&Pung, 8);

	task_yield ();

    printf ("Main FIM\n");

    exit (0);
}





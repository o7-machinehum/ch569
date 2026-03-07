#include "ch56x_common.h"

#define UART1_BAUD 115200

void DebugInit(uint32_t baudrate)
{
	uint32_t x;
	uint32_t t = FREQ_SYS;
	x = 10 * t * 2 / 16 / baudrate;
	x = (x + 5) / 10;
	R8_UART1_DIV = 1;
	R16_UART1_DL = x;
	R8_UART1_FCR = RB_FCR_FIFO_TRIG | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN;
	R8_UART1_LCR = RB_LCR_WORD_SZ;
	R8_UART1_IER = RB_IER_TXD_EN;
	R32_PA_SMT |= (1 << 8) | (1 << 7);
	R32_PA_DIR |= (1 << 8);
}

static void uart_putc(char c)
{
	while (R8_UART1_TFC == UART_FIFO_SIZE);
	R8_UART1_THR = c;
}

static void uart_puts(const char *s)
{
	while (*s) uart_putc(*s++);
}

int main(void)
{
	SystemInit(FREQ_SYS);
	Delay_Init(FREQ_SYS);

	/* LED on PA9 */
	R32_PA_DIR |= (1 << 9);
	R32_PA_OUT &= ~(1 << 9);

	/* UART1 init */
	DebugInit(UART1_BAUD);

	uart_puts("Hello from CH569\r\n");

	while (1)
	{
		R32_PA_OUT ^= (1 << 9);
		mDelaymS(500);
		uart_puts("tick\r\n");
	}
}

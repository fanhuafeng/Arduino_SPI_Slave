/*
 * SPI_Slave_LEDx8.c
 *
 * Created: 2017/08/26 9:16:53
 * Author : gizmo
 */ 

#define F_CPU	(8000000UL)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t sdata = 0;

ISR (SPI_STC_vect)
{
	// ��M�f�[�^��LED�ɏo��
	PORTD = SPDR;
	
	// ���ɑ��M����f�[�^���Z�b�g
	SPDR = sdata;
	sdata++;
}

int main(void)
{
	// LEDs output
	DDRD = 0xFF;
	PORTD = 0xFF;
	_delay_ms(100);

	// LEDs check
	for (int i = 0; i < 8; i++) {
		PORTD = 1 << i;
		_delay_ms(100);
	}
	PORTD = 0x00;

	// SPI slave
	DDRB = 0x10;  // MISO(PB4)��output�ɐݒ�

	// SPCR�̃r�b�g�ݒ�
	// SPI�L��:1 | SPI���荞�ݗL��:1 | MSB���瑗�M:0 | �X���[�u:0
	// �N���b�N�ɐ�:0 | �N���b�N�ʑ�:0 | SPR1:0 | SPR0:0
	SPCR = (1 << SPIE) | (1 << SPE);

	sei();	// ���荞�݋���
	
	while (1)
	{
	}
}




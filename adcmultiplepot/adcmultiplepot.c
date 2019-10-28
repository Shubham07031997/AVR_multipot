#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>
#include<lcdavr.h>
#include<stdio.h>

void adc_init1()
{
	ADMUX = 0B01000000;//for vcc +5v aNd vref =5v| ADC0 is selected for displaying
	ADCSRA = ((1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0));
	}

  void adc_init2()
{
	ADMUX = 0B01000001;//for vcc +5v aNd vref =5v| ADC1 is selected for displaying
	ADCSRA = ((1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0));
	}

   
	unsigned int adc_read(unsigned char channel)
{	
	
	ADMUX=0x40|channel;
	ADCSRA |= (1<<ADSC);//for starting the conversion
	while(!(ADCSRA & (1<<ADIF)));//for progress report //for converting the data

	ADCSRA |= (1<<ADIF);//for updating the data the data and previous task is done
	
	return ADC;
}





int main()
{

	unsigned char i[5],j[5];
	unsigned int value1,value2;
	DDRB = 0XFF;
	
	lcd_init();

	adc_init1();//calling user defined function adc
	adc_init2();
	
while(1)
{ //adc_init1();
  value1=adc_read(0);//0th pin is used 0f adc channel
	lcd_clear();
	lcd_command(0x80);
	sprintf(i,"%d",value1);//convrets adc value to i's data type
	lcd_string("adc value:     ");
	lcd_command(0x8b);
	lcd_string(i);
    _delay_ms(100);
//	adc_init2();
    value2=adc_read(1);//1th pin is used 0f adc channel
	lcd_clear();
	lcd_command(0xc0);
	sprintf(j,"%d",value2);//convrets adc value to i's data type
	lcd_string("adc value:     ");
	lcd_command(0xcb);
	lcd_string(j);
      _delay_ms(100);
	
}
	return 0;
}


#include "ADC.h"

void init_ADC(int referencia,int justificacion,int preescaler){
	ADMUX=0;
	ADCSRA=0;
	//Definimos la referencia que va a tener el ADC
	if (referencia==0){
			//Voltaje de referencia interna de 5V.
			ADMUX |= (1<<REFS0);
	} else if (referencia==1){
		//Voltaje de referencia interna de 1.1V.
		ADMUX |= (1<<REFS0)|(1<<REFS1);
	}
	
	//Escogemos la justificación (IZQUIERDA O DERECHA)
	if (justificacion==0){
		//Justificación izquierda
		ADMUX |= (1<<ADLAR);
	} else if (justificacion==1){
		//Justificación derecha
		ADMUX &= ~(1<<ADLAR);
	}
	
	//Escogemos el preescaler
	if (preescaler==2){
			//Preescaler 2 -> frecuencia del adc = Foscilador/2
			ADCSRA |= (1<<ADPS0);
	} else if (preescaler==4){
		//Preescaler 2 -> frecuencia del adc = Foscilador/2
		ADCSRA |=(1<<ADPS1);
	}else if (preescaler==8){
		//Preescaler 2 -> frecuencia del adc = Foscilador/8
		ADCSRA |=(1<<ADPS1) | (1<<ADPS0);
	}else if (preescaler==16){
		//Preescaler 2 -> frecuencia del adc = Foscilador/16
		ADCSRA |= (1<<ADPS2);
	}else if (preescaler==32){
		//Preescaler 2 -> frecuencia del adc = Foscilador/32
		ADCSRA |= (1<<ADPS2)|(1<<ADPS0);
	}else if (preescaler==64){
		//Preescaler 2 -> frecuencia del adc = Foscilador/64
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1);
	} else if (preescaler==128){
		//Preescaler 2 -> frecuencia del adc = Foscilador/128
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	}
	
	//Habilitando la interrupción del ADC
	//ADCSRA |= (1<<ADIE);
	
	//Enciendo el ADC
	ADCSRA |= (1 << ADEN);

}

uint8_t readADC(int canal){
	//Borramos el MUX DEL ADC
	ADMUX &= ~(1<<MUX3)& ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
	
	//Encendemos el puerto deseado
	if (canal==0){
		//Seleccionar puerto (ADC0 - A0)
		ADMUX &= ~(1<<MUX3)& ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
	}else if (canal==1){
		// Seleccionar puerto (ADC1 - A1)
		ADMUX |= (1<<MUX0);
	}else if (canal==2){
		// Seleccionar puerto (ADC2 - A2)
		ADMUX |= (1<<MUX1);
	}else if (canal==3){
		// Seleccionar puerto (ADC3 - A3)
		ADMUX |= (1<<MUX1)|(1<<MUX0);
	}else if (canal==4){
		//Seleccionar puerto (ADC4 - A4)
		ADMUX |= (1<<MUX2);
	} else if (canal==5){
		//Seleccionar puerto (ADC5 - A5)
		ADMUX |= (1<<MUX2)|(1<<MUX0);
	} else if (canal==6){
		//Seleccionar puerto (ADC6 - A6)
		ADMUX |= (1<<MUX2)|(1<<MUX1);
	} else {
		//Seleccionar puerto (ADC7 - A7)
		ADMUX |= (1<<MUX2)|(1<<MUX1) |(1<<MUX0);
	}
	
	//INICIAMOS LECTURA
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1 << ADSC)) {
		// Esperar
	}
	//uint8_t valor = ADCH;
	ADCSRA |= (1<<ADIF);

	return ADCH;
}
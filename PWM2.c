/*
 * PWM2.c
 *
 * Created: 17/04/2024 16:56:29
 *  Author: luisd
 */ 

#include "PWM2.h" 

void init_PWM2A(int orientacion,int modo, int preescaler){
	//Definimos el puerto de salida
	DDRB |= (1<<PINB3);
	TCCR2A=0;
	TCCR2B=0;
	
	//Definimos la orientación
	if (orientacion==0){
		//No invertido
		TCCR2A |= (1<<COM2A1);
		}else{
		//invertido
		TCCR2A |= (1<<COM2A1) | (1<<COM2A0);
	}
	
	//Definimos modo de operación FAST O PhaseCorrect
		if(modo==1){
		//Fast con 9 bits
		TCCR2A |= (1<<WGM20);
		}else if(modo==2){
		//FAST con 10 bits
		TCCR2A |= (1<<WGM21);
		}else if(modo==3){
		//PhaseCorrect con 8 bits
		TCCR2A |= (1<<WGM21) | (1<<WGM20);
		}else if(modo==4){
		//PhaseCorrect con 9 bits
		TCCR2B |= (1<<WGM22);
		}else if(modo==5){
		//PhaseCorrect con 10 bits
		TCCR2A |= (1<<WGM20);
		TCCR2B |= (1<<WGM22);
		}else if (modo==6){
		//FAST con ICR1 TOP
		TCCR2A |= (1<<WGM21);
		TCCR2B |= (1<<WGM22);
		}else if (modo==7){
		//PhaseCorrect con ICR1 TOP
		TCCR2A |= (1<<WGM21)|(1<<WGM20);
		TCCR2B |= (1<<WGM22);
	}
	
	//Definimos el preescaler
	switch(preescaler){
		case 0:
		TCCR2B |= (1<<CS20);
		break;
		case 8:
		TCCR2B |= (1<<CS21);
		break;
		case 64:
		TCCR2B |= (1<<CS21)|(1<<CS20);
		break;
		case 256:
		TCCR2B |= (1<<CS22);
		break;
		case 1024:
		TCCR2B |= (1<<CS22) |(1<<CS21) | (1<<CS20);
		break;
	}
	//Definimos la frecuencia (unicamente funciona en modo donde el top es ICR1)
	//Fpwm=(fosc)/(preescaler*(1+TOP)
	//ICR1 = frecuency;
}

void init_PWM2B(int orientacion){
	//Definimos el puerto de salida
	DDRD |= (1<<PIND3);
	
	//Definimos la orientación
	if (orientacion==0){
		//No invertido
		TCCR2A |= (1<<COM2B1);
		}else{
		//invertido
		TCCR2A |= (1<<COM2B1) | (1<<COM2B0);
	}
}

void duty_cycle2A(uint8_t duty){
	OCR2A = duty;
}

void duty_cycle2B(uint16_t duty){
	OCR2B = duty;
}
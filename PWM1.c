#include "PWM1.h" 

void init_PWM1A(int orientacion,int modo, int preescaler,uint16_t frecuency ){
	//Definimos el puerto de salida
	DDRB |= (1<<PINB1);
	TCCR1A=0;
	TCCR1B=0;
	
	//Definimos la orientación
	if (orientacion==0){
		//No invertido
		TCCR1A |= (1<<COM1A1);
		}else{
		//invertido
		TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
	}
	
	//Definimos modo de operación FAST O PhaseCorrect
	if (modo==0){
		//FAST con 8 bits
		TCCR1A |= (1<<WGM10);
		TCCR1B |= (1<<WGM12);
		}else if(modo==1){
		//Fast con 9 bits
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM12);
		}else if(modo==2){
		//FAST con 10 bits
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		TCCR1B |= (1<<WGM12);
		}else if(modo==3){
		//PhaseCorrect con 8 bits
		TCCR1A |= (1<<WGM10);
		}else if(modo==4){
		//PhaseCorrect con 9 bits
		TCCR1A |= (1<<WGM11);
		}else if(modo==5){
		//PhaseCorrect con 10 bits
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		}else if (modo==6){
		//FAST con ICR1 TOP
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM12)|(1<<WGM13);
		}else if (modo==7){
		//PhaseCorrect con ICR1 TOP
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM13);
	}
	
	//Definimos el preescaler
	switch(preescaler){
		case 0:
		TCCR1B |= (1<<CS10);
		break;
		case 8:
		TCCR1B |= (1<<CS11);
		break;
		case 64:
		TCCR1B |= (1<<CS11)|(1<<CS10);
		break;
		case 256:
		TCCR1B |= (1<<CS12);
		break;
		case 1024:
		TCCR1B |= (1<<CS12)|(1<<CS10);
		break;
	}
	//Definimos la frecuencia (unicamente funciona en modo donde el top es ICR1)
	//Fpwm=(fosc)/(preescaler*(1+TOP)
	ICR1 = frecuency;
}

void init_PWM1B(int orientacion){
	//Definimos el puerto de salida
	DDRB |= (1<<PINB2);
	
	//Definimos la orientación
	if (orientacion==0){
		//No invertido
		TCCR1A |= (1<<COM1B1);
		}else{
		//invertido
		TCCR1A |= (1<<COM1B1) | (1<<COM1B0);
	}
}

void duty_cycle1A(uint16_t duty){
	OCR1A = duty;
}

void duty_cycle1B(uint16_t duty){
	OCR1B = duty;
}
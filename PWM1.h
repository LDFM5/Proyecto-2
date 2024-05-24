#ifndef PWM1_H_
#define PWM1_H_
#include <stdint.h>
#include <avr/io.h>

void init_PWM1A(int orientacion,int modo, int preescaler,uint16_t frecuency);
void init_PWM1B(int orientacion);
void duty_cycle1A(uint16_t duty);
void duty_cycle1B(uint16_t duty);


#endif /* PWM1_H_ */
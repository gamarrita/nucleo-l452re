#ifndef _TUNE_TIMER_H_
#define _TUNE_TIMER_H_

#define PERIOD_MAX 65536u
#define PRESCALER_MAX 65536u
#define FREQ_UP_LIMIT  100000u // Frecuencia maxima
#define FREQ_LOW_LIMIT  1u // Frecuencia maxima


double tune_timer(unsigned gen_freq, const unsigned TIM_FREQ, unsigned *const prescaler, unsigned *const period);

#endif

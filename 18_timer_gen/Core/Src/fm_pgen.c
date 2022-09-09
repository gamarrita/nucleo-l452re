#include <math.h>
#include <stdint.h>
#include "fm_pgen.h"

double tune_timer(unsigned gen_freq, const unsigned TIM_FREQ,
                    unsigned *const prescaler, unsigned *const period)
{
    double real_freq;
    double freq_min;
    double delta_min = gen_freq;
    double delta_now;
    double delta_before;
    unsigned tune_prescaler;
    unsigned tune_period;

    freq_min = TIM_FREQ;
    freq_min /= PERIOD_MAX;
    freq_min /= PRESCALER_MAX;

    if(gen_freq < FREQ_LOW_LIMIT)
    {
        gen_freq = FREQ_LOW_LIMIT;
    }

    if(gen_freq > FREQ_UP_LIMIT)
    {
        gen_freq = FREQ_UP_LIMIT;
    }

    // Calculo en menor valor posible de PRESCALER que me permita llegar a
    // la recuencia de generacion, se debe usar el PERIDO mas grande posible
    tune_period = PERIOD_MAX;
    tune_prescaler = TIM_FREQ;
    tune_prescaler = tune_prescaler / (PERIOD_MAX * gen_freq);
    if(!tune_prescaler)
    {
        tune_prescaler = 1;
    }

    for(;tune_prescaler <= tune_period; tune_prescaler++)
    {
        real_freq = TIM_FREQ;
        real_freq /= (tune_period * tune_prescaler);
        delta_now = fabs(real_freq - gen_freq);

        do
        {
            delta_before = delta_now;
            tune_period--;
            real_freq = TIM_FREQ;
            real_freq /= (tune_period * tune_prescaler);
            delta_now = fabs(real_freq - gen_freq);
        }
        while(delta_now<delta_before);

        if(delta_before < delta_min)
        {
            delta_min = delta_before;
            *prescaler = tune_prescaler;
            *period = tune_period + 1;
        }
        if(delta_min == 0) break;
    }
    real_freq = TIM_FREQ;
    real_freq /= (*period) * (*prescaler);
    return real_freq;
}


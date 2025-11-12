

#ifndef TIM_H_
#define TIM_H_


void tim2_1hz_init(void);
void tim2_PA5_output_compare(void);
void tim3_input_capture(void);

#define TIM2_SR_UIF		(1U<<0)
#define TIM3_SR_CC1IF	(1U<<1)



#endif


//Port A clock
void GPIOA_enable_clock(void){
	//GPIO clock enable register
	unsigned int* RCC_AHB2ENR = (unsigned int*) 0x4002104c;

	//Set bit 0 for port A
	*RCC_AHB2ENR |= 0b1;

	return;
}

//Port B clock
void GPIOB_enable_clock(void){
	//GPIO clock enable register
	unsigned int* RCC_AHB2ENR = (unsigned int*) 0x4002104c;

	//Set bit 0 for port B
	*RCC_AHB2ENR |= 0b10;

	return;
}

//Port C clock
void GPIOC_enable_clock(void){
	//GPIO clock enable register
	unsigned int* RCC_AHB2ENR = (unsigned int*) 0x4002104c;

	//Set bit 0 for port C
	*RCC_AHB2ENR |= 0b100;

	return;
}

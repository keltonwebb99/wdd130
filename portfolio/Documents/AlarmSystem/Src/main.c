/* This program uses inputs from buttons and reed switch sensors
* and outputs to status and alarm LEDs to create an home
* security system.
*/


// GPIO Port struct

typedef struct{
unsigned int MODER; // offset: 0x00
unsigned int OTYPER; // offset: 0x04
unsigned int OSPEEDR; // offset: 0x08
unsigned int PUPDR; // offset: 0x0C
unsigned int IDR; // offset: 0x10
unsigned int ODR; // offset: 0x14
} Port;

// Address of the Advanced High-performance Bus 2 Enable Register
unsigned int* AHB2ENR = (unsigned int*) 0x4002104c;

// Base addresses of the GPIO Port control registers (SFRs)
Port* GPIOA = (Port*) 0x48000000; // base address of GPIOA
Port* GPIOB = (Port*) 0x48000400; // base address of GPIOB
Port* GPIOC = (Port*) 0x48000800; // base address of GPIOC


// input pins
#define ArmButtonPin 13 // PC13
#define DisarmButtonPin 9 // PA9
#define FrontSensorPin 0 // PA0
#define BackSensorPin 1 // PA1
#define WindowSensorPin 4 // PA4

// output pins
#define ArmStatusPin 5 // PA5
#define FrontAlarmPin 6 // PA6
#define BackAlarmPin 7 // PA7
#define WindowAlarmPin 8 // PA8

int main(void)
{
// Turn on GPIO clocks (Ports A, B, and C)
 *AHB2ENR |= 0b111;


 	 
 	 // Configure button pin as inputs
 	 GPIOC->MODER &= ~(0b11 << (ArmButtonPin*2)); // configure ArmButtonPin as input
 	 GPIOA->MODER &= ~(0b11 << (DisarmButtonPin*2)); // configure DisarmButtonPin as input

 	 // Configure reed switch pins as inputs
 	 GPIOA->MODER &= ~(0b11 << (FrontSensorPin*2)); // configure FrontSensorPin as input
	 GPIOA->MODER &= ~(0b11 << (BackSensorPin*2)); // configure BackSensorPin as input
	 GPIOA->MODER &= ~(0b11 << (WindowSensorPin*2)); // configure WindowSensorPin as input


	 
	 // Enable pull resistors
	 GPIOA->PUPDR |= (0b01 << (DisarmButtonPin*2));
 	 GPIOA->PUPDR |= (0b01 << (FrontSensorPin*2));
 	 GPIOA->PUPDR |= (0b01 << (BackSensorPin*2));
 	 GPIOA->PUPDR |= (0b01 << (WindowSensorPin*2));


 	 
 	 // Configure LED pins as outputs
 	 GPIOA->MODER &= ~(0b10 << (ArmStatusPin*2)); // configure ArmStatusPin as output
 	 GPIOA->MODER &= ~(0b10 << (FrontAlarmPin*2)); // configure FrontAlarmPin as output
 	 GPIOA->MODER &= ~(0b10 << (BackAlarmPin*2));// configure BackAlarmPin as output
 	 GPIOA->MODER &= ~(0b10 << (WindowAlarmPin*2)); // configure WindowAlarmPin as output

 	 // Initialize Alarm Status (turn off all LEDs)
 	 GPIOA->ODR &= ~(1 << ArmStatusPin);
 	 GPIOA->ODR &= ~(1 << FrontAlarmPin);
 	 GPIOA->ODR &= ~(1 << BackAlarmPin);
 	 GPIOA->ODR &= ~(1 << WindowAlarmPin);

 	 //This lab material is provided for students in ECEN 260 during the Spring 2023 semester.
 	 //Use of this material by students in other semesters is not allowed and is academic dishonesty.

 	 // armed state (initialize to disarm)
 	 int armed = 0;
 	 // infinite loop


 	 while(1){
 		 

 		 // check if ArmButton is pressed
 		 if ((GPIOC->IDR & (0b1 << ArmButtonPin)) == 0){
 			 // arm system
 			 armed = 1; // set arm state
 			 GPIOA->ODR |= (1 << ArmStatusPin); // turn on ArmStatus LED
 		 }

 		 // check if DisarmButton is pressed
 		 if ((GPIOA->IDR & (0b1 << DisarmButtonPin)) == 0){
 			 // disarm system
 			armed = 0; // reset arm state
 			GPIOA->ODR &= ~(1 << ArmStatusPin); // turn off ArmStatus LED
 			GPIOA->ODR &= ~(1 << FrontAlarmPin); // turn off FrontAlarm LED
 			GPIOA->ODR &= ~(1 << BackAlarmPin); // turn off BackAlarm LED
 			GPIOA->ODR &= ~(1 << WindowAlarmPin); // turn off WindowAlarm LED
 		 }


 		
 		// if system is armed, check sensors
 		if (armed){
 			 // check the FrontSensor
 			 if ((GPIOA->IDR & (1 << FrontSensorPin)) != 0){
 				 // system armed & front door is open:
 				 GPIOA->ODR |= (1 << FrontAlarmPin); // turn on FrontAlarm LED
 			 }

 			 // check the BackSensor
 			 if ((GPIOA->IDR & (1 << BackSensorPin)) != 0){
 				 // system armed & front door is open:
 				 GPIOA->ODR |= (1 << BackAlarmPin); // turn on BackAlarm LED
 			 }

 			 // check the WindowSensor
 			 if ((GPIOA->IDR & (1 << WindowSensorPin)) != 0){
 			 	 // system armed & front door is open:
 			 	 GPIOA->ODR |= (1 << WindowAlarmPin); // turn on WindowAlarm LED
 			 }
 		 }
 	 }
}

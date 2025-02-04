// Water Level Detector Code for PIC16F877A in MikroC

// Define the connections for the LEDs and Sensors
#define LOW_SENSOR PORTC.F1   // RC1 -> Low-level sensor (Pin 16)
#define MID_SENSOR PORTC.F2   // RC2 -> Mid-level sensor (Pin 17)
#define HIGH_SENSOR PORTC.F3  // RC3 -> High-level sensor (Pin 18)

// Define seven-segment display pins (connected to PORTD)
#define SEGMENT PORTD

#define GREEN_LED PORTB.F0    // RB0 -> Green LED (Pin 33)
#define YELLOW_LED PORTB.F1   // RB1 -> Yellow LED (Pin 34)
#define RED_LED PORTB.F2      // RB2 -> Red LED (Pin 35)
#define MOTOR PORTB.F3       // RB3 -> Motor (Pin 36)
#define BUZZER PORTB.F4       // RB4 -> Buzzer (Pin 37)

void display_number(unsigned char number) {
    switch (number) {
        case 1:
            SEGMENT = 0b00000110; // Display '1'
            break;
        case 2:
            SEGMENT = 0b01011011; // Display '2'
            break;
        case 3:
            SEGMENT = 0b01001111; // Display '3'
            break;
        case 0:
            SEGMENT = 0b00111111; // Display '0'
            break;
    }
}

void main() {
    // Configure Ports of Sensor
    TRISC.F0 = 1;  // Set RC1 as input (Low-level sensor)
    TRISC.F1 = 1;  // Set RC2 as input (Mid-level sensor)
    TRISC.F2 = 1;  // Set RC3 as input (High-level sensor)

	// Configure Ports of LED,Buzzer and Motor

    TRISB.F0 = 0;  // Set RB0 as output (Green LED)
    TRISB.F1 = 0;  // Set RB1 as output (Yellow LED)
    TRISB.F2 = 0;  // Set RB2 as output (Red LED)
    TRISB.F3 = 0;  // Set RB2 as output (Motor)
    TRISB.F4 = 0;  // Set RB2 as output (Buzzer)

// Configure ports
    TRISD.F0 = 0;  // Set RD0 as output (for seven-segment display bit 0)
    TRISD.F1 = 0;  // Set RD1 as output (for seven-segment display bit 1)
    TRISD.F2 = 0;  // Set RD2 as output (for seven-segment display bit 2)
    TRISD.F3 = 0;  // Set RD3 as output (for seven-segment display bit 3)
    TRISD.F4 = 0;  // Set RD4 as output (for seven-segment display bit 4)
    TRISD.F5 = 0;  // Set RD5 as output (for seven-segment display bit 5)
    TRISD.F6 = 0;  // Set RD6 as output (for seven-segment display bit 6)
    TRISD.F7 = 0;  // Set RD7 as output (for seven-segment display bit 7)


    // Initialize LEDs to OFF
    GREEN_LED = 0;
    YELLOW_LED = 0;
    RED_LED = 0;
    MOTOR =0;
    BUZZER =0;
SEGMENT = 0x00; // Initialize seven-segment display to off

    while (1) {
        if (LOW_SENSOR == 1 && MID_SENSOR == 0 && HIGH_SENSOR == 0) {
            // Low-level detected
            GREEN_LED = 1;
            YELLOW_LED = 0;
            RED_LED = 0;
            MOTOR  =1;
            BUZZER =0;
		 display_number(1);
        } else if (LOW_SENSOR == 1 && MID_SENSOR == 1 && HIGH_SENSOR == 0) {
            // Mid-level detected
            GREEN_LED = 0;
            YELLOW_LED = 1;
            RED_LED = 0;
            MOTOR =1;
            BUZZER =0;
		            display_number(2);
        } else if (LOW_SENSOR == 1 && MID_SENSOR == 1 && HIGH_SENSOR == 1) {
            // High-level detected
            GREEN_LED = 0;
            YELLOW_LED = 0;
            RED_LED = 1;
            MOTOR =0;
             BUZZER =0;
	            display_number(3);
        } else {
            // No water or invalid state
            GREEN_LED = 1;
            YELLOW_LED = 0;
            RED_LED = 0;
            MOTOR =1;
             BUZZER =1;
	            display_number(0);
        }
    }
}
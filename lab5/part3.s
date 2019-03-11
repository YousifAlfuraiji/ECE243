.global _start
_start:
	
        	MOV 	R4, #0				// First digit of counter
        	MOV 	R5, #0				// Second digit of counter
		MOV	R0, #1				// Boolean for checking button press
        	
            LDR		R3, =0xFFFEC600		// Timer initialization
            LDR		R12, =200000000
            STR		R12, [R3]
            MOV		R12, #0b011
            STR		R12, [R3, #8]
            
WHILE:		MOV 	R6, #NUM_CODES		// Points to the number codes for the hexes
			LDR 	R10, =0xFF200020     // R4 points to HEX3-0
			
			LDRB	R7, [R6, R4]		// Hex value of first digit
            LDRB	R8, [R6, R5]		// Hex value of second digit
            LSL		R8, #8
			
		    ORR		R11, R7, R8			// Hex3-0 bit value loaded
			STR		R11, [R10]
      
      
            ADD		R4, #1				// Increment counter
            CMP		R4, #9
            MOVGT	R4, #0
            ADDGT	R5, #1
            
            MOV		R0, #10 			//Check if 99 is reached
            MLA		R1, R5, R0, R4
            CMP		R1, #100
            MOVEQ	R4, #0
            MOVEQ	R5, #0
            
WAIT:       //LDR		R2, =0xFF200050			// Wait after a key until next key press
			LDR		R2, [R10, #0x3C]
            ANDS	R1,	R2, #0b1111
            BEQ		CONTROL
            
            CMP		R0, #0
            MOVNE	R0, #0
            MOVEQ	R0, #1
            STR		R2, [R10, #0x3C]
            
CONTROL:	CMP		R0, #0
			BEQ		WAIT
            
DELAY:		LDR		R12, [R3, #0xC]				// Check if timer reached 0
			CMP		R12, #0
            BEQ		DELAY
            STR		R12, [R3, #0xC]
            B		WHILE

		
NUM_CODES:  .byte   0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
            .byte   0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111
            .skip   2      // pad with 2 bytes to maintain word alignment
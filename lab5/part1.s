.global _start
_start:
	
		MOV 	R6, #0				// Counter for pointing to the hex number
        
        
WHILE: 	LDR 	R4, =0xFF200020     // R4 points to HEX3-0
		MOV 	R5, #NUM_CODES		// Points to the number codes for the hexes
		MOV		R9, #0				// Initalize a register that holds the saved value of the keys

		LDRB 	R5, [R5, R6]
        STR		R5, [R4]			// Initialize hex with a 0 
    
WAIT:	LDR 	R7, =0xFF200050		// Load the value of the keys
		LDR 	R7, [R7]
        CMP		R7, #0
        MOVNE	R9, R7				
        CMP		R7, #0
        BNE		WAIT
		
        CMP 	R9, #1				// Compare to key 0
        MOVEQ	R6, #0
        
        CMP		R9, #2				// Compare to key 1
        ADDEQ	R6, #1
        CMP		R6, #9					// Check if > 9
        MOVGT	R6, #0
        
        CMP		R9, #4				// Compare to key 2
        SUBEQ	R6, #1
        CMP		R6, #0				// Check if < 0
       	MOVLT	R6, #9
        
        CMP		R9, #8
        BLT		WHILE
        
        CMP		R9, #8				// Compare to key 3
        MOV		R8, #0
        STREQ	R8, [R4]
        
BLANKED:	// Stay blanked while no other key is pressed
        LDR 	R7, =0xFF200050		// Load the value of the keys
        LDR		R7, [R7]
        CMP		R7, #0
        BEQ		BLANKED
        
WAIT_AGAIN:		// If any other key is pressed wait until unpress and set hex to 0
		LDR 	R7, =0xFF200050		// Load the value of the keys
        LDR		R7, [R7]
        MOV		R6, #0
        CMP		R7, #0
        BNE		WAIT_AGAIN
        
		B 		WHILE
		
		
		
		
		
		
NUM_CODES:  .byte   0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
            .byte   0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111
            .skip   2      // pad with 2 bytes to maintain word alignment
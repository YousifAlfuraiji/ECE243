.global _start
_start:
	
	LDR R0, =0xFF200020	//R0 points to HEX3-0
    	   //0xFF20005C
    MOV R1, #0			//R1 points to BIT_CODES
    MOV R3, #0			//R3 holds full bit_code to write to HEX3 - HEX0
    MOV R5, #0			//R5 holds bit_codes to be stored into R3
    
    MOV R9, #0			//R9 holds thousands
    MOV R7, #0			//R7 holds hundreds
    MOV R4, #0	 		//R4 holds tens
    MOV R2, #0			//R2 holds ones
    LDR R10, =0xFFFFFFFF
    
	
MAIN:		LDR R10, =0xFFFFFFFF
            LDR R1, =0xFF20005C
			STR R10, [R1]
            
            
            
            ///////////////////////
DIVIDE:    
		
		
COMP10: 	CMP    R2, #10
			BLT    COMP100 
            SUB    R2, #10
            ADD    R4, #1	//Tens
            
              B      COMP10
			//R2 has ones now
            
            COMP100:	CMP    R4, #10
			BLT    COMP1000  //Branch to the next cmpr
            SUB    R4, #10
            ADD    R7, #1	//hundreds
			B	COMP100		
            
            COMP1000:   CMP    R7, #10
            BLT    DIV_END  //Branch to the next cmpr
            SUB    R7, #10
            ADD    R9, #1		//thousands
			B	COMP1000

DIV_END:    			//R2 holds ones

			//STRB   R9, [R0, #3] // Thousands digit is now in R1
	    	//STRB   R7, [R0, #2] // Hundreds digit is now in R1
            //STRB   R4, [R0, #1] // Tens digit is now in R1
            //STRB   R2, [R0]     // Ones digit is in R0
            
			MOV     R1, #BIT_CODES  
            ADD     R1, R9        // index into the BIT_CODES "array"
            LDRB    R3, [R1]       // load the bit pattern (to be returned)
            
            MOV     R1, #BIT_CODES  
            ADD     R1, R7         // index into the BIT_CODES "array"
            LSL		R3, #8
            LDRB    R5, [R1]       // R3 now has full code to display

			ORR		R3, R5
            
            MOV     R1, #BIT_CODES  
            ADD     R1, R4         // index into the BIT_CODES "array"
            LSL		R3, #8
            LDRB    R5, [R1]       // R3 now has full code to display
            
            ORR		R3, R5
            
            MOV     R1, #BIT_CODES  
            ADD     R1, R2         // index into the BIT_CODES "array"
            LSL		R3, #8
            LDRB    R5, [R1]       // R3 now has full code to display
            
            ORR		R3, R5
    
			STR R3, [R0]
    
    
DO_DELAY: 	PUSH {R0, R2}
			LDR R1, =200000000 // delay counter
			LDR R0, =0xFFFEC600
            
            STR R1, [R0]
            MOV R1, #1
            STR R1, [R0, #0x8]
            
            MOV R1, #1

LOOP_INT:   LDR R2, [R0, #0xC]
            
   			CMP R2, R1
            BNE LOOP_INT
            
            STR R1, [R0, #0xC]
            
            POP {R0, R2}
            
//SUB_LOOP: SUBS R1, R1, #1
//		  BNE SUB_LOOP
          
          
          
    	//check for button pressed
    	
    	LDR R1, =0xFF20005C	//Edgecapture register
		//STR R9, [R1]
        LDR R1, [R1]
		CMP R1, #0x0
    	BLNE WAIT
    	
    
          //R1 holds holds 9+9 = 18
          LDR R1, =0x6d676767
          CMP R3, R1
          ADDNE R2, #1
          MOVEQ R2, #0
          MOVEQ R4, #0
          MOVEQ R7, #0
          MOVEQ R9, #0
          
          
	B MAIN
    
    
    
WAIT:
	LDR R1, =0xFF20005C
	STR R10, [R1]
WAIT1:
	//LDRB R1, [R0, #0x3C]
	//CMP R5, #0b0000
    //B WAIT1
	LDR R1, =0xFF20005C 	//Edgecapture register
    LDR R1, [R1]
	CMP R1, #0x0
    BEQ WAIT1
    MOV PC, LR
     /*   
WAIT:
    LDR R5, [R0, #0x30]
	CMP R5, #0b0000
    BEQ WAIT
    STR R10, [R11]
    B MAIN*/


BIT_CODES:  .byte   0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110
            .byte   0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111
            .skip   2      // pad with 2 bytes to maintain word alignment
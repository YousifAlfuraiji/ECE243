.define LED_ADDRESS 0x1000
.define HEX_ADDRESS 0x2000
.define SW_ADDRESS 0x3000
.define STACK 256

			mvi 	r6, #STACK			// r6 points to stack 
			mvi 	r1, #1				// r1 holds increment 1
			mvi 	r3, #0 				// r3 holds value to be displayed on HEX
			mvi 	r4, #HEX_ADDRESS	// r4 points to the HEX address

// Main's job is to increment the LEDR display by one
MAIN: 		sub	    r6, r1				// store variables on a stack
			st 	    r3, [r6]
			sub 	r6, r1
			st 	    r4, [r6]
			
			mv 	    r2, r7				// r2 holds return address
			mvi 	r7, #DELAY			// go to delay subroutine 

			ld	    r4, [r6] 			// retrieve variables from stack
			add	    r6, r1
			ld 	    r3, [r6]
			add 	r6, r1

			add 	r3, r1				// increment value on HEX by 1
			mv 	    r2, r7				// r2 holds return address
			mvi 	r7, #LOAD_HEX		// go to LOAD_HEX subroutine 

			mvi 	r7, #MAIN			// execute main again

LOAD_HEX: 	sub	    r6, r1				// store r2 (return) on a stack
			st 	    r2, [r6]
			sub	    r6, r1				// store r3 (current value) on a stack
			st 	    r3, [r6]

			mv 	    r0, r3

			// HEX0
			mv 	    r5, r7				// r5 holds the next instruction
			mvi 	r7, #DIV10			// divide by 10
			mvi 	r3, #DATA
			add 	r3, r0
			ld	    r3, [r3]
			st 	    r3, [r4]
			add 	r4, r1				// increment the hex address counter 
			mv 	    r0, r2 				// load r2 into r0

			// HEX1
			mv 	    r5, r7				// r5 holds the next instruction
			mvi 	r7, #DIV10			// divide by 10
			mvi 	r3, #DATA
			add 	r3, r0
			ld	    r3, [r3]
			st 	    r3, [r4]
			add 	r4, r1				// increment the hex address counter 
			mv 	    r0, r2 				// load r2 into r0

			// HEX2
			mv 	    r5, r7				// r5 holds the next instruction
			mvi 	r7, #DIV10			// divide by 10
			mvi 	r3, #DATA
			add 	r3, r0
			ld	    r3, [r3]
			st 	    r3, [r4]
			add 	r4, r1				// increment the hex address counter 
			mv 	    r0, r2 				// load r2 into r0

			// HEX3
			mv 	    r5, r7				// r5 holds the next instruction
			mvi 	r7, #DIV10			// divide by 10
			mvi 	r3, #DATA
			add 	r3, r0
			ld	    r3, [r3]
			st 	    r3, [r4]
			add 	r4, r1				// increment the hex address counter 
			mv 	    r0, r2 				// load r2 into r0

			// HEX4
			mv 	    r5, r7				// r5 holds the next instruction
			mvi 	r7, #DIV10			// divide by 10
			mvi 	r3, #DATA
			add 	r3, r0
			ld	    r3, [r3]
			st 	    r3, [r4]
			add 	r4, r1				// increment the hex address counter 
			mv 	    r0, r2 				// load r2 into r0

			// HEX5
			mv 	    r5, r7				// r5 holds the next instruction
			mvi 	r7, #DIV10			// divide by 10
			mvi 	r3, #DATA
			add 	r3, r0
			ld	    r3, [r3]
			st 	    r3, [r4]
			add 	r4, r1				// increment the hex address counter 
			mv 	    r0, r2 				// load r2 into r0

			sub 	r4, r1
			sub 	r4, r1
			sub 	r4, r1
			sub 	r4, r1
			sub 	r4, r1
			sub 	r4, r1

			ld 	    r3, [r6]
			add 	r6, r1
			ld 	    r2, [r6] 			// retrieve r2 on stack
			add 	r6, r1	

			add 	r2, r1 
			add 	r2, r1
			mv	    r7, r2

// Delay's job is to count down
DELAY: 		sub 	r6, r1
			st 	    r2, [r6]

			mvi	r3, #5000			// r3 is the delay counter
			mv 	    r5, r7				// save address of next instruction
			mvi 	r0, #SW_ADDRESS			// point to SW port
			ld	    r4, [r0]			// r4 is the inner loop counter
			add 	r4, r1				// in case 0 is read 
			mv 	    r2, r7 				// save address of next instruction
			sub 	r4, r1				// decrement inner loop counter
			mvnz 	r7, r2				// continue inner loop 
			sub	    r3, r1				// decrement outer loop counter
			mvnz 	r7, r5				// continue outer loop

			ld	    r2, [r6] 			// retrieve variables from stack
			add	    r6, r1
			
			add 	r2, r1 
			add 	r2, r1			

			mv 	    r7, r2				// after delay, go back to main

// returns quotient Q in r2, remainder R in r0

DIV10:		sub 	r6, r1 		// save registers that are modified
			st 	    r3, [r6]
			sub 	r6, r1
			st 	    r4, [r6] 	// end of register saving
			mvi 	r2, #0		// init Q
			mvi 	r3, RETDIV 	// for branching
DLOOP: 		mvi 	r4, #9 		// check if r0 is < 10 yet
			sub 	r4, r0
			mvnc 	r7, r3 		// if so, then return
INC: 		add 	r2, r1 		// but if not, then increment Q
			mvi 	r4, #10
			sub 	r0, r4 		// r0 -= 10
			mvi 	r7, DLOOP 	// continue loop
RETDIV:		ld 	    r4, [r6] 	// restore saved regs
			add 	r6, r1
			ld 	    r3, [r6] 	// restore the return address
			add 	r6, r1
			add 	r5, r1 		// adjust the return address by 2
			add 	r5, r1
			mv 	    r7, r5 		// return results
			
DATA:		.word 0b00111111			// '0'
			.word 0b00000110			// '1'
			.word 0b01011011			// '2' 	 
			.word 0b01001111			// '3'
			.word 0b01100110			// '4'  
			.word 0b01101101			// '5'
			.word 0b01111101			// '6'
			.word 0b00000111			// '7'
			.word 0b01111111			// '8' 
			.word 0b01101111			// '9' 
				 			

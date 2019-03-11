.define LED_ADDRESS 0x1000
.define HEX_ADDRESS 0x2000
.define SW_ADDRESS 0x3000
.define STACK 256

			mvi 	r6, #STACK			// r6 points to stack 
			mvi 	r1, #1				// r1 holds increment 1
			mvi 	r3, #0 				// r3 holds value to be displayed on HEX
			mvi 	r4, #LED_ADDRESS	// r4 points to the LED address

MAIN:       sub     r6, r1              //store values in the stack
            st      r3, [r6]
            sub     r6, r1
            st      r4, [r6]

            mv      r2, r7              //holds the return address
            mvi     r7, #DELAY          //moves to DELAY subroutine

            ld      r4, [r6]            //loads back values into registers
            add     r6, r1
            ld      r3, [r6]
            add     r6, r1

            add     r3, r1              //increments the value by 1
            st      r3, [r4]            //loads value to LEDs

            mvi     r7, #MAIN           //cycles to beginning of main

DELAY:      sub     r6, r1              //stores value into stack
            st      r2, [r6]

            mvi     r3, #5000
            mv      r5, r7

            mvi     r0, #SW_ADDRESS     //Obtains addressof switches
            ld      r4, [r0]            //Holds the value of the switches into r4
            add     r4, r1
            mv      r2, r7              //Holds value of instructions
            sub     r4, r1              //Subtracts by 1
            mvnz    r7, r2              //Only moves past once the inner loop has finished

            sub     r3, r1              //Subtracts by 1
            mvnz    r7, r5              //Only moves past once outer loop has finished

            ld      r2, [r6]            //Obtains data back from the stack
            add     r6, r1

            add     r2, r1
            add     r2, r1

            mv      r7, r2              //Returns to instruction in main

/* Program that finds the largest number in a list of integers	*/

            .text                   // executable code follows
            .global _start                  
_start:                             
            MOV     R4, #RESULT     // R4 points to result location
            LDR     R0, [R4, #4]    // R0 holds the number of elements in the list
            MOV     R1, #NUMBERS    // R1 points to the start of the list
            BL      LARGE           
DONE:		STR     R0, [R4]        // R0 holds the subroutine return value

END:        B       END             

/* Subroutine to find the largest integer in a list
 * Parameters: R0 has the number of elements in the lisst
 *             R1 has the address of the start of the list
 * Returns: R0 returns the largest item in the list
 */
LARGE:      SUBS    R0, #1	    // decrement the loop counter
			BEQ	    DONE		    // if the result is equal to 0, branch (MOVEQ pc, LR)
			ADD     R1, #4
			LDR	    R5, [R1]	    // R5 holds the next number in the list
			LDR     R6, [R4]		// R6 holds the largest number so far
			CMP     R6, R5        // check if larger number is found
			BGE     LARGE
			MOV     R4, R1
			MOV		R0, R1
			B       LARGE

RESULT:     .word   0           
N:          .word   7           // number of entries in the list
NUMBERS:    .word   4, 5, 3, 6  // the data
            .word   1, 8, 2                 

            .end                            


/* Program that counts consecutive 1's, 0's and alternating 1/0's with subroutines */

          .text                   // executable code follows
          .global _start                  
_start:                             
          MOV     R4, #TEST_NUM   // R4 has address of data
	  MOV     R5, #0	  // R5 will hold the 1s result
	  MOV	  R0, #0
	  MOV	  R6, #0	  // R6 holds the 0s result
	  MOV	  R7, #0	  // R7 holds alternate results
	  MOV	  R9, #ALT
	  LDR	  R9, [R9]
	  MOV	  R10, #0
	  MOV	  R11, #BITS
	  LDR	  R11, [R11]
	 


MAIN:	  LDR	  R1, [R4], #4	  //R1 gets the next data word
	  CMP     R1, #0          //Checks for the last item in TEST_NUM
          BEQ     END       

	  //ONES
	  MOV	  R0, #0    
	  MOV	  R8, R1 
          BL	  ONES		  //Parameter passed in 
	  CMP	  R5, R0	  //Result returned in 
	  MOVLT	  R5, R0 	  //New best result?
	  
	  //ZEROS 
	  MOV	  R0, #0
	  MVN	  R8, R1
          BL	  ONES  	  //Parameter passed in 
	  CMP	  R6, R0	  //Result returned in 
	  MOVLT	  R6, R0 	  //New best result?
	  
	  //ALTERNATE  
	  MOV	  R0, #0
          BL	  ALTERNATE	  //Parameter passed in 	  
	  CMP	  R7, R0	  //Result returned in 
	  MOVLT	  R7, R0 	  //New best result?
	  
	  B	  MAIN
END:      B       END     

ONES:	  CMP	  R8, #0
	  BEQ	  END_ONES
	  LSR     R2, R8, #1      // perform SHIFT, followed by AND
          AND     R8, R8, R2   
	  ADD	  R0, #1
	  B	  ONES       
END_ONES: MOV	  PC, LR        


ALTERNATE:EOR	  R8, R1, R9
	  MOV	  R0, #0
	  MOV	  R10, #0
	  	  
	  PUSH	  {LR}
	  BL	  ONES
	  POP	  {LR}
	  MOV 	  R10, R0

	  MOV	  R0, #0
	  EOR	  R8, R1, R9
	  MVN	  R8, R8

	  PUSH	  {LR}
	  BL	  ONES
	  POP	  {LR}
	  
	  CMP	  R0, R10
	  MOVLT   R0, R10

	  MOV	  PC, LR   

TEST_NUM: .word   0x103fe00f
	  .word	  0x1545cdcd
	  .word	  0x10e30e30
	  .word	  0x0001fffe
	  .word	  0x0001ffff
	  .word	  0x01aaaaaa
	  .word	  0x11000000
	  .word	  0x55555500
	  .word	  0xfffffff0
	  .word	  0x000000ff
	  .word	  0x00000000

ALT:	  .word	  0x55555555                         

BITS:	  .word	  32

	  .end
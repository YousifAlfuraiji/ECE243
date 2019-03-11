/* Program that counts consecutive 1's */

          .text                   // executable code follows
          .global _start                  
_start:                             
          MOV     R6, #TEST_NUM   // load the data word ...

WORDSLOOP:LDR     R1, [R6]        // R1 points to the indexed word
          ADD     R6, #4          // Post increment
          CMP     R5, R0          // Decide if should update final result
          MOVLE   R5, R0
          CMP     R1, #0          // Decide if at the final word
          BNE     ONES
          B       END

ONES:     MOV     R0, #0          // R0 will hold the result
LOOP:     CMP     R1, #0          // loop until the data contains no more 1's
          BEQ     WORDSLOOP             
          LSR     R2, R1, #1      // perform SHIFT, followed by AND
          AND     R1, R1, R2      
          ADD     R0, #1          // count the string length so far
          B       LOOP            

END:      B       END             

TEST_NUM: .word   0x01010101      // 1 consecutive 1's
          .word   0x00100100      // 1
          .word   0x03030303      // 2
          .word   0x70707070      // 3
          .word   0xf0f0f0f0      // 4
          .word   0x103fe00f      // 9
          .word   0x103fe000      // 9
          .word   0xffffffff      // 32
          .word   0x11111111      // 1
          .word   0x00000000
          .end                            

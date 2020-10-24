		.cpu cortex-m0
		.text
		.align 2
		.global txt
        .global application
        .global print_asciz

application:
	push {lr}
	ldr r0, =txt
	bl decode
	ldr r0, =buf
	bl print_asciz
	pop {pc}




//print_asciz function to print all characters of string
print_asciz:
	push {r5, lr}
	mov r5, r0			

loop:
	ldrb r0, [r5]		// load first character in r0	
	add r0, r0, #0		// add 0 to check in branh if its the end
	beq done			// branch to done if its the end
	bl uart_put_char	// print the char
	add r5, r5, #1		// go to next address
	b loop				// go to beginning

done:
	pop {r5, pc}		// pop out of function


// decode function to remove markers and replace them with original text
// r0 = character
// r1 = offset
// r4 = buffer
// r5 = buffer location
decode:
	push {r4, r5, lr}
	ldr r4, =buf
	mov r1, r0			// save location of first character
	mov r5, r4			// save location of buffer in r5

decode_loop:
	ldrb r0, [r1]		// load character from address of r1 in r0			
	add r0, #0			// check if its the end of string
	beq end				// branch to done if its the end
	cmp r0, #'@'		// check if character is a marker
	beq match			// branch to marker if its a marker
	strb r0, [r5]		// store character from r0 in address of r4
	add r5, #1			// go to next position of buffer
	add r1, #1			// increase loop with 1 for the next character
	b decode_loop		// go back to beginning		

// r1 is the loop counter and at first the offset location
// r2 is the match start location of compressed text
// r0 is offset location
// r3 is the length of the match
match:
	add r1, r1, #1		// next character is offset
	ldrb r2, [r1]		// load offset in r2
	sub r2, #47			// substract 48 (0) to correct the value
	sub r2, r5, r2		// go to location in buffer of the match
	add r1, r1, #1		// next character is match length 
	ldrb r3, [r1]		// load this value ( amount to go forward ) in r3
	sub r3, #48			// substract 48 (0) to correct the value
	add r1, #1			// 
		
// r0 is the match character to write to buffer
// r2 is the location of the match in the buffer
// r3 is the length of the match
// r5 is the last location in buffer
match_loop:
	cmp r3, #0			// check if match length is 0				
	beq decode_loop		// if its the end go back to beginning						
	ldrb r0, [r2]		// load character of match in buffer in r0
	strb r0, [r5]		// store character of match in buffer 
	add r5, #1			// go to next position of buffer			
	add r2, #1			// go to next position of match
	sub r3, #1			// decrease the length of the match with 0
	b match_loop		// repeat loop

end:
	pop {r4, r5, pc}

//Buffer
.bss					
buf:
.skip 4000

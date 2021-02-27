#BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
#ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
#ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
#OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
#IT IS NOT MACHINE GENERATED OR TAKEN FROM MACHINE GENERATED CODE

#Name: Noah Hufnagel
.file "count.s"
.section	.rodata

#Table Array, this is the 2D array of ranges
Table:
.byte 0x30, 0x39 #0-9
.byte 0x41, 0x5a #A-Z
.byte 0x61, 0x7a #a-z

.data

.globl count
	.type count, @function

.align 8

.text
count:					#param 1 = char pointer string input, param 2= long range number (0-2) 
	pushq %rbp			#save old base pointer
	movq %rsp, %rbp			#set new base pointer
	
	movq $Table, %rdx		#Set up the range table
	imulq $2, %rsi			#multiply range number by 2 to account for 2d array
	movb (%rdx, %rsi), %cl		#save first bound of the range
	movb 1(%rdx, %rsi), %r8b	#save second bound of the range
					#We no longer need Table or the range number saved

	xorq %rax, %rax			#Zero Count
	movq $-1, %rdx			#Set index to -1 since array will increment to 0 at start
	movb $0x00, %r9b		#save a null character for comparison


char_loop_start:
	movq $1, %rsi			#holds 0 if previous char is in range, 1 if not.
					#rsi will be refered to as current state
char_loop_in_word:
	incq %rdx			#increment index

	cmpb (%rdi, %rdx), %r9b		#Compare current character to Null Byte
	je done				#jump to end once we reach null byte

					#these lines jump back to the top, ensuring that 
					#current state is set to 1. so that once we are in
					#range that word is counted
	cmpb %cl, (%rdi, %rdx)		#Compare current character to lower bound  
	jl char_loop_start		#Jump back to start of loop if character below the range
	cmpb %r8b, (%rdi, %rdx)		#Compare current character to upper bound  
	jg char_loop_start		#Jump back to start of loop if character above the range

					#if we get here then we know that our character is in the range
	addq %rsi, %rax			#if we are in a word this adds 0, if not this adds 1 (meaning its new word)
	xorq %rsi, %rsi			#Zero current state (because we are in a word) so we shouldnt count
					#any other characters in the range until we leave this word
					#and we know that we have left this word when we find a
					#character that is not inside the range

	jmp char_loop_in_word		#jump to the loop break inside the word. 
					#we don't jump back to the line that sets current state(rsi)
					#since we are in a word so we want to keep adding 0 to rax until
					#this word is over.
done:
	leave				#Tear down stack frame
	ret				#return to call

	.size count, .-count		#reqired directive

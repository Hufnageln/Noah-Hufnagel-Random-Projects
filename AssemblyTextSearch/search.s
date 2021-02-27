#BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
#ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
#ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
#OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
#IT IS NOT MACHINE GENERATED OR TAKEN FROM MACHINE GENERATED CODE

#Name: Noah Hufnagel
.file "search.s"
.section	.rodata
	searchPrint: .string "search: \"%s\" has the most words using range %d with %d found.\n"
.data
.globl search
	.type search, @function

.align 8

.text
search:						#param1= pointer to pointer to strings, param2= int size, param3= long range
	pushq %rbp				#save old base pointer
	movq %rsp, %rbp				#set new base pointer

	pushq %r12				#set up a place to hold the range
	pushq %r13				#set up a place to hold the best count
	pushq %r14				#set up a place to hold the best pointer
	pushq %r15				#set up a place to hold the array

	movq %rdx, %r12				#store range
	movq $-1, %r13				#set best count to negative 1
	xorq %r14, %r14				#zero best pointer
	movq %rdi, %r15				#set the array pointer

loop_start:
	movq (%r15), %rdi			#put the current element of the string pointer into the first param
	movq %r12, %rsi				#put the range into second parameter
	call evaluate				#evaluate the string with the given range

	cmpq %r13, %rax				#compare output of evaluate to the best count
	jl next_index				#if this has less words then we dont change our best registers
	
						#only fall through if our new count is better
						#if this count is better we change our best registers
	movq %rax, %r13				#set best count to output from evaluate
	movq (%r15), %r14			#set best string pointer to the current string

next_index:
	addq $8, %r15				#go to next index
	movq $0 , %rsi				#set a null for comparison. this trashes rsi, we dont care
	cmpq (%r15), %rsi			#check if the new index is null
	jnz loop_start				#if its not null then loop

						#we fall through the jump above if
						#we have reached the null. so we know that
						#when we get here our work is done
done:
	movq $searchPrint, %rdi			#set printed line as first parameter
	movq %r14, %rsi				#set best string as second parameter for print
	movq %r12, %rdx				#set range as third parameter for print
	movq %r13, %rcx				#set best count as fourth parameter for print
	movq %rax, %rax				#zero output for print
	call print				#print(searchPrint, str, range, count)

	movq %r14, %rax				#set output to best string pointer

	popq %r15				#tear down array
	popq %r14				#tear down best ptr
	popq %r13				#tear down best count
	popq %r12				#Tear down range number

	leave					#tear down stack frame
	ret					#return to call

	.size search, .-search			#reqired directive

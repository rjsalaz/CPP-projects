# Who:  Randy Salazar
# What: Fibonacci_Calculator.asm
# Why:  Program to find the Nth fibonacci number based upon user input 
# When: created on 3/17/2019. Due on 3/17/2019
# How:  # $t0 holds n
        # $t1 holds address of array space
        # $t2 holds initial 0 value and is used fib calculation and is later used to hold values for output 
        # $t3 holds initial 1 value  and is used fib calculation
        # $t4 is used a counter in for loops 
        # $t5 is temp value holder used in  fib calculation
        

.data

user_prompt: 		    .asciiz  "Please Enter a Integer Value from  0 <= N <= 47 For N to Find the Nth Fibonacci number: "
output_of_fib_value: 	    .asciiz  "This is your Nth Fibonacci number: "
output_of_fib_array: 	    .asciiz  "This is the whole Fibonacci sequence: "
user_prompt_Error: 	    .asciiz  "Invalid input Exiting program . . . "

.align 2

                         
fib_space: 		    .space 188   # arrays max size is 47

.text
.globl main

main:	                                 # program entry

    la $t1, fib_space

    la $a0, user_prompt                  # sends prompt to user and takes in user input 
    li $v0, 51                           # syscall 51 returns int value into $a0, and a status code into $a1
    syscall
    
   
    
 ################## Check user input  ###########################
    bne $a1, $0, invalid          	 # if status code returns a value other than zero jump to invalid label
    
    slti $t0, $a0, 48			 # if n > 47 jumps to invalid label
    beq  $t0, $0, invalid 
      
    bltz $a0,  invalid			 # if n < 0 jumps to invalid label
    
 ###############################################################
 
    move $t0, $a0                        # input is valid  store in $t0 
    
    
               	     
    li $a0, '\n'	                 # write new line
    li $v0, 11	
    syscall           	  
    
    

 ##################  Fibonacci calculator  #####################
    li $t2, 0                            # holds  0 ( a = 0)
    li $t3, 1                            # holds  1 (b = 1) 

    addi $t4, $t4, 0                     # declare counter for loop 

    fib_loop:

        bgt  $t4, $t0, exit_fib_loop     # runs as long as counter <= user input 

            sw $t2, 0($t1)               # array [i] = a 
            
            move $t5, $t3                # temp =  b 
            addu $t3, $t3, $t2           #  b = b + a 

            move $t2, $t5                # a = temp

            addu $t1, $t1, 4             # increase position in array
            addu $t4, $t4, 1		 # increase counter 
            
    j fib_loop
 
exit_fib_loop: 

 ##############################################################




 ################## Print output of fib(n)  ###########################
   la $a0, output_of_fib_value           # print output 
   li $v0, 4                            
   syscall
   
   		
   lw $t2, -4($t1)                       # prints out the desired Fib(n) numbers
   move $a0, $t2
   li $v0, 36                           
   syscall
               

   li $a0, '\n'	                	 # write new line
   li $v0, 11	
   syscall		
 #####################################################################


 ################## Print output of array  ###########################   
   la $a0, output_of_fib_array           	# print output 
   li $v0, 4                            
   syscall
   
    
   la $t1, fib_space			 	# load beginning of fib_space( array) 	
   move $t4, $0 			 	# restart counter 

   print_fib_array: 
              
        bgt  $t4, $t0 exit_print_fib_array      # counter <= user input 

            lw $t2, 0($t1)			# grabs value from array 
            
            move $a0, $t2                	# print value from array 
            li $v0, 36
            syscall 

            li $a0, ' '	                 	# write space
            li $v0, 11	
            syscall	

            addu $t1, $t1, 4             	# increase position in array
            addu $t4, $t4, 1 		 	# increase counter

        j print_fib_array

    exit_print_fib_array:


 ###############################################################
 
    li $v0, 10		                  	# terminate the program
    syscall
    
    
    
    
invalid: 				 	# jumps here if user input is invalid 
	la $t0, user_prompt_Error

	move $a0, $t0			 	# print output 
	li $v0, 4 
	syscall 
	
	li $v0, 10		         	# terminate the program
    	syscall

# Who:  Randy Salazar
# What: project4.asm
# Why:  program reads in a source and destination file, then ask for a passphrase and stores it, next it encrypts the source file with passphrase and stores it into the desintation file
# When: Created 5/5/2019, Due 5/5/2019
# How:  $a0 used for prompts, and as arguments for syscalls 
#	$a1 used as arguments for syscall 
#	$a2 used as arguments for syscall and used as a counter 
#	$a3 used for passing PASS_BUFFER to subroutines 
#	$v0 used for syscalls and file descriptors 
#	$s0 holds file descriptor
#	$s1 holds file descriptor 
#	$t0 used in calculations for storing source and destination paths, removing null characters, getting passphrase, and encryption
#	$t1 used in calculations for storing source and destination paths, removing null characters, getting passphrase, and encryption

.data

    .eqv	NEW_LINE		0xA  # holds \n
    .eqv	PRINT_CHAR		0xB  # holds 11
    .eqv    	STAR            	0x2A # holds * 
    ###################### used for polling ###################### 
    .eqv	CONSOLE_RECEIVER_CONTROL            0xffff0000
    .eqv	CONSOLE_RECEIVER_READY_MASK         0x00000001
    .eqv	CONSOLE_RECEIVER_DATA               0xffff0004
    ##############################################################
    .eqv    	BUFFER_SZ                           256
    .eqv 	PASS_BUFFER_SZ			    257	
    .eqv 	FILE_BUFFER_SZ		            1024
    .eqv    	FILE_OPEN_CODE                      13
    .eqv    	FILE_CLOSE_CODE                     16
    .eqv    	FILE_READ_CODE                      14
    .eqv    	FILE_WRITE_CODE                     15   
            	SRC_DEST_BUFFER:        .space      BUFFER_SZ
            	PASS_BUFFER:            .space      PASS_BUFFER_SZ
            	FILE_BUFFER:		.space	    FILE_BUFFER_SZ 
    		prompt:        		.asciiz     "Enter Source path: "
    		prompt1:       		.asciiz     "Enter Destination path: "  
    		prompt2:       		.asciiz     "***************Enter your passphrase***************"
            
.text
.globl main

main:	# program entry
   la $a1, SRC_DEST_BUFFER	# pass SRC_DEST_BUFFER by reference 
   jal GET_SRC_DST		# get source and destination path from user
   
   la $a3, PASS_BUFFER  	# pass PASS_BUFFER by reference 
   jal GET_PASS			# gets pass phrase from the user 

   la $a0, SRC_DEST_BUFFER	# pass SRC_DEST_BUFFER by reference to ENCRY_FILE
   la $a3, PASS_BUFFER  	# pass PASS_BUFFER by reference to ENCRY_FILE
   jal ENCRY_FILE		# encryptes source file and stores it into the destination file

li $v0, 10			# terminate the program
syscall


##########################################################

#GET_SRC_DST - subroutine will get source file and the destination of soon to be encrypted file from user 
#args
    # no arguments will be passed to subroutine 
#return 
    # nothing is returned, source and destination paths will be stored into SRC_DEST_BUFFER
    
GET_SRC_DST:
    la $a0, prompt                           # prompt for source path 
    li $v0, 4
    syscall
    
    move $a0, $a1			     # move buffer to $a0
    li $a1, BUFFER_SZ
    li $v0, 8 
    syscall

    # look for newline character and replace with null
    push_null_src: 
    
        lb $t0, 0($a0)                       # load first char from SRC string int $t0 
        beq $t0, 0xA, exit_push_null_loop    # if $t0 == /n exit loop 

            addu $a0,$a0, 1		     # increase position in buffer 

       j push_null_src

    exit_push_null_loop: 
    
    sb $0, 0($a0) 			     # replace \n with null 
    addu $t0,$a0, 1                          # set $t0 to location in buffer after null
    
    la $a0, prompt1                          # prompt for Destination path 
    li $v0, 4
    syscall
    
    la $a0, 0($t0)	     		     # get Destination path and store in buffer 
    li $a1, BUFFER_SZ
    li $v0, 8 
    syscall
    

    # look for newline character and replace with null 
    push_null_DST: 
    
        lb $t0, 0($a0)                       # load first char from DST string into $t0 
        beq $t0, 0xA, exit_push_null         # if $t0 = /n exit loop 

            addu $a0,$a0, 1		     # increase position in buffer 

        j push_null_DST

   exit_push_null: 
    
   sb $0, 0($a0)			     # replace \n with null 

   jr $ra 				     # return to main 	     



 ##########################################################
 
# GET_PASS - Will get password from user using the keyboard and Display MMIO simulator 
# args
    # $a3 which will hold the address of the PASS_BUFFER
#return 
    # nothing is returned, password will be stored into the PASS_BUFFER
    
 GET_PASS:
 	
    la $a0, prompt2                                       # prompt for passphrase 
    li $v0, 4
    syscall
       
    li $a0, NEW_LINE                                      # load NEWLINE character and print 
    li $v0, PRINT_CHAR
    syscall
    
    li $t1, 0						  # set counter 
    pass_wait:                                            # Spin-wait for key to be pressed
	    # if $t1 = 257 then exit
	    beq $t1, 257, exit 				  # prevent user from entering more characters than the buffer can hold   
	    
	    lw   $t0, CONSOLE_RECEIVER_CONTROL
	    andi $t0, $t0, CONSOLE_RECEIVER_READY_MASK    # Isolate ready bit
	    beqz $t0, pass_wait

	    lbu $a0, CONSOLE_RECEIVER_DATA                # Read in new character from keyboard to low byte of $a0
	    beq $a0, 10, exit                             # and clear other 3 bytes of $a0
        
            sb $a0, 0($a3)                                # store char into buffer 
            addu $a3,$a3, 1 				  # increase place in buffer 
	    	    
	    li $a0, STAR                                  # load star and print 
	    li $v0, PRINT_CHAR
	    syscall
	    
	    addu $t1, $t1, 1				  # increase counter 

	    j pass_wait	    

    exit: 

    li $t0, 0x0						  # replace newline character with null character in buffer 
    sb $t0, 0($a3) 
	
    li $a0, NEW_LINE                             	  # load \n character and print 
    li $v0, PRINT_CHAR
    syscall

    jr $ra 

##########################################################

# ENCRY_FILE - Will open the files from the SRC_DEST_BUFFER, then read a buffer load of data from source file 
# and that buffer will be encrypted using the provided passphrase from the PASS_BUFER. Next the buffer 
# will be written to the destination file. This continues until all data has been copied from the source file     
# args
    # $a3 which will hold the address of the PASS_BUFFER
# return 
    # nothing is returned, source file is now encrypted into the destination file
    
ENCRY_FILE: 
	# open source file
        li $a1, 0 
        li $a2, 0 
        li $v0, 13
        syscall

        # test the descripter for fault 
        move $s0, $v0 
        slt $t0, $s0, $0 
        bne $t0, $0, EXIT
	
	# look for null caracter in SRC_DEST_BUFFER
	search_for_null:
	
		lb $t0, 0($a0) 			# load byte from buffer	
		beq $t0, $0, end_search 	# if $t0 = null then exit 
		
			addu $a0,$a0, 1		# increase position in buffer 
			
		j search_for_null
			
		
	end_search: 
	
	addu $a0,$a0, 1				# set $a0 to starting position of DEST path 
	
        # open Dest file
        la $a0, 0($a0)				# load address of DEST using $a0 as offset,
        li $a1, 1
        li $a2, 0 
        li $v0, 13
        syscall

        # test the descripter for fault 
        move $s1, $v0 
        slt $t0, $s1, $0 
        bne $t0, $0, EXIT


COPY_LOOP:

        # read Buffer load from file 
        li $v0, FILE_READ_CODE
        move $a0, $s0 
        la $a1, FILE_BUFFER
        li $a2, FILE_BUFFER_SZ
        syscall
        
 	# if $v0 = 0 then close files 
        beq $v0,$0,CLOSE_RESOURCES 
               
	#xor buffer here before writing 
            
	ENCRYPT: 
            li $a2, 0                               	# set counter 
            encrypt_loop: 
        
                lb $t0, 0($a3)				# load byte from PASS_BUFFER
                lb $t1, 0($a1)				# load byte from FILE_BUFFER
                
		# if counter equals $v0 then exit loop
                bgt $a2, $v0, exit_encrypt_loop    	
                
                # if $t0 = null then reset pass_buffer 
                bne $t0, 0, continue		        
                    
                	la $a3, PASS_BUFFER		# reset PASS_BUFFER 
                	lb $t0, 0($a3)                  # load byte from PASS_BUFFER
                
                continue:
                    
                xor $t0, $t0, $t1 			# xor byte from pass_buffer with byte file_buffer 
                
                sb $t0, 0($a1) 				# store xord byte back into buffer
                
                # increase position of pass_buffer, file_buffer, and counter
                addu $a1, $a1, 1
                addu $a2, $a2, 1			 
                addu $a3, $a3, 1
                 
                
            j encrypt_loop
            
        exit_encrypt_loop:
 
	
        # write to file from buffer 
        move $a0, $s1
        la $a1, FILE_BUFFER
        move $a2, $v0 					# write to the file with size of $v0 
        li $v0, FILE_WRITE_CODE
        syscall
        
     
 j COPY_LOOP

CLOSE_RESOURCES:
	# close both files that were opened 
        li $v0, FILE_CLOSE_CODE
        move $a0, $s0 
        syscall

        li $v0, FILE_CLOSE_CODE
        move $a0, $s1 
        syscall


EXIT: 

jr $ra 

##########################################################

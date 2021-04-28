from sys import exit as exit_program


def encrypt(message, password):

    encrypted_message = "0x"
    password_length = len(password) - 1
    password_counter = 0

    for message_letter in message: 
    
        encrypted_text = ord(message_letter) ^ ord(password[password_counter])
        hex_value_of_encrypted_text = hex(encrypted_text)

        if(password_counter == password_length):
            
            password_counter = 0

        else:

            password_counter += 1

        if (len(hex_value_of_encrypted_text) < 4): 

            hex_value_of_encrypted_text = "0x0" + hex_value_of_encrypted_text[2]

        encrypted_message += hex_value_of_encrypted_text[2:]

    return encrypted_message


def decrypt(ciphertext, password):

    decrypted_message = ""
    ciphertext = ciphertext[2:]
    password_length = len(password) - 1
    password_counter = 0

    for ciphertext_letter in range(0, len(ciphertext), 2): 
        
        hex_to_be_converted = ciphertext[ciphertext_letter] + ciphertext[ciphertext_letter + 1]
        
        if (hex_to_be_converted[0] == "0"):

            hex_to_be_converted = hex_to_be_converted[1]
    
        ascii_rep_of_hex = int(hex_to_be_converted, 16)
    
        decrypted_text = ascii_rep_of_hex ^ ord(password[password_counter])
        decrypted_message += chr(decrypted_text)

        if (password_counter == password_length):

            password_counter = 0

        else:

            password_counter += 1

    return  decrypted_message 


def verify_password_length(user_password):

    if (len(user_password) > 15):
        
        return True

    else: 

        return False 


def get_user_password():

    is_password_valid = False 

    while True: 
   
        user_password = input("Input password (must be greater than 15 characters) :")
        is_password_valid = verify_password_length(user_password)

        if is_password_valid: 

            return user_password
    
        print("Invalid password length. Please try again or press ctrl->c to quit.")


######## MAIN ###########

is_valid_input = False
valid_choices = ['a','b','c']

menu_prompt = """
Welcome to My Encryption/Decryption Program
Please enter the letter of your chosen operation:
\ta) Encrypt a message
\tb) Decrypt a message
\tc) Exit 
"""

while (not(is_valid_input)) : 

    print(menu_prompt)
    user_operation_choice = input("Enter option:").lower() 

    if (user_operation_choice in valid_choices):

        is_valid_input = True
    
    else:

        print("Invalid choice, please try again")

if (user_operation_choice == "a"): 

    message = input("Input your message:") 
    password = get_user_password()       
    result = encrypt(message, password)

elif (user_operation_choice == "b"):  

    ciphertext = input("Input the ciphertext in hexadecimal form (0x…) :")
    password = get_user_password()
    result = decrypt(ciphertext, password)

else:
    print("Exiting Program ....")
    exit_program(0)

print("Result: " + result)
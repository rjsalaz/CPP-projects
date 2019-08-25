#/!bin/bash

clear
x=0
counter=0

while [ $x -eq 0 ]
do
    echo "*** Welcome to Cal Poly's ATM ****"
    echo ""
    echo ""
    echo ""
    echo ""
    echo ""
    echo -n  "Please enter your PIN: "
    read pin

    if [ $pin -eq 111 ]
    then

        x=1

    elif [ $counter -eq 2 ]
    then

        echo "Too many illegal PINs. Try later again."
        exit 0

    else

         counter=`expr $counter + 1`

    fi

    clear

done

x=0
savings=1000
checkings=1000

clear_screen() {



        sleep 4
        clear

}

display () {

    echo "*** Welcome to Cal Poly's ATM ****"
    echo "(1) Transfer funds from checking account to savings account"
    echo "(2) Transfer funds from savings account to checking account"
    echo "(3) Savings account balance"
    echo "(4) Checking account balance"
    echo "(5) Withdraw Cash from either account"
    echo "(6) Exit"
    echo -n "==> Please select option (1-6): "
    read userinput


}

checkings_balance() {

    echo "Your checking account balance is \$$checkings"
    clear_screen
}

savings_balance() {

    echo "Your savings account balance is \$$savings"
    clear_screen
}

# transfer funds from checkings to savings
checkings_to_savings() {

    local check=0

    echo -n "How much would you like to transer to your savings: "
    read transfer_amount


    check=`expr $checkings - $transfer_amount`

    if [ $check -lt 0 ]
    then
        echo "Transaction not completed"
        echo "Your checking account balance is \$$checkings"

    else
        checkings=$check
        savings=`expr $savings + $transfer_amount`
        echo "Your savings account balance is \$$savings"
    fi

    clear_screen
}

# transfer funds from savings to checkings
savings_to_checkings() {

    local check

    echo -n "How much would you like to transer to your checkings: "
    read transfer_amount

    check=`expr $savings - $transfer_amount`

    if [ $check -lt 0 ]
    then
        echo "Transaction not completed"
        echo "Your savings account balance is \$$savings"

    else
        savings=$check
        checkings=`expr $checkings + $transfer_amount`
        echo "Your checking account balance is \$$checkings"
    fi

    clear_screen

}

# withdraw fund from either savings or checkings
withdraw_cash() {

    local check=0

    echo -n "How much cash would you like to withdraw: "
    read cash

    echo "(1) Withdraw Cash from Checking Account"
    echo "(2) Withdraw Cash from Savings Account"
    read input


    if [ $input -eq 1 ]
    then

        check=`expr $checkings - $cash`

        if [ $check -lt 0 ]
        then

            echo "Transaction not completed"
            echo "Your checking account balance is \$$checkings"

        else

            checkings=$check
            echo "Your checking account balance is \$$checkings"

        fi

    elif [ $input -eq 2 ]
    then

        check=`expr $savings - $cash`

        if [ $check -lt 0 ]
        then

            echo "Transaction not completed"
            echo "Your savings account balance is \$$savings"

        else

            savings=$check
            echo "Your savings account balance is \$$savings"

        fi

    else

        echo "Invalid Input"

    fi

    clear_screen


}


exit_script() {


    clear
    echo "Thank you for using the ATM system."
    exit 0

}


while [ $x -eq 0 ]
do


    display

    if [ $userinput -eq 1 ]
    then

        checkings_to_savings


    elif [ $userinput -eq 2 ]
    then

        savings_to_checkings


    elif [ $userinput -eq 3 ]
    then

        savings_balance


    elif [ $userinput -eq 4 ]
    then


        checkings_balance


    elif [ $userinput -eq 5 ]
    then

        withdraw_cash

    elif [ $userinput -eq 6 ]
    then

        exit_script


    else

        echo "Invalid Input"

    fi



done

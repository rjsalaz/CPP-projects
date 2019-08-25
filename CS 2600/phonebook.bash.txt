#!/bin/bash

clear

# get user input
echo -n "Enter name of input file: "
read FILE


# remove new line character
FILE=${FILE//$'\n'/}


# check if file exist
if [ ! -f $FILE ]
then
        # if file dose exit exit program
        echo "$FILE dose not exist.. Exiting";

        sleep 5

        exit 0
fi

clear
# display menu for program
menu(){

        echo "*********************** Menu ***********************"
        echo "(1) List the recods in alphabetical order of first name or last name"
        echo "(2) Listing of records in reverse alphabetical order of first name or last name"
        echo "(3) Search for a record by Last Name and print out the result"
        echo "(4) Search for a record by birthday in a given year or month"
        echo "(5) Exit Program"
        echo -n "Enter input: "

}


# list records in order of first name or last name
list_by_first_or_last(){


        clear

        local selection=0

        # get userinput
        echo "(1) Sort by First Name"
        echo "(2) Sort by last Name "
        echo -n "Enter input: "
        read selection

        if [ $selection -eq 1 ]
        then
                # sort by first name
                sort $FILE


        elif [ $selection -eq 2 ]
        then
                # sort by last name
                sort  -k 2  $FILE

        else


                echo "invalid input"
        fi


}


reverse_list_by_first_or_last(){

        clear

        local selection=0

          # get userinput
        echo "(1) Sort by First Name"
        echo "(2) Sort by last Name "
        echo -n "Enter input: "
        read selection

        if [ $selection -eq 1 ]
        then
                 # sort by first name in reverse order
                 sort -r $FILE


        elif [ $selection -eq 2 ]
        then
                 # sort by last name in reverse order
                  sort -r  -k 2  $FILE

        else


                  echo "invalid input"
        fi

}



search_by_lastname(){

        clear

        local selection

        echo "If nothing is returned no record was matched"

        # get lastname of person to search for
        echo -n "Enter the last name of the desired person to search for: "
        read selection

        # search file for last name using awk
        awk "/ $selection/ {print }" $FILE


}


search_by_birthday_or_birthmonth(){

        clear

        local selection

        echo "If nothing is returned no record was matched"

        # get user inout
        echo "(1) Search by Birt Year"
        echo "(2) search by Birth Month"
        echo -n "Enter input: "
        read selection


        if [ $selection -eq 1 ]
        then
                # search by birth year using awk
                echo -n "What is the birth year(ex. 89,01,09)"
                read selection

                awk   "/\/$selection:/{print}" $FILE

        elif [ $selection -eq 2 ]
        then

                # search by birth month using awk
                echo -n "What is the birth month"
                read selection

                awk  "/:$selection\//{print}" $FILE

        else
                echo "Invalid Input "
        fi

}


x=0

while [ $x -eq 0 ]
do

        menu

        read input

        if [ $input -eq 1 ]
        then


                list_by_first_or_last


        elif [ $input -eq 2 ]
        then
                reverse_list_by_first_or_last

        elif [ $input -eq 3 ]
        then

                search_by_lastname

        elif [ $input -eq 4 ]
        then

                 search_by_birthday_or_birthmonth

        elif [ $input -eq 5 ]
        then

                clear

                 # exit program
                exit 0


        else
                echo "Invalid input"

        fi

done

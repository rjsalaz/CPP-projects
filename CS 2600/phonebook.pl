#!/usr/bin/perl

system ("clear");

#get file for input
print "Enter name of input file: ";
my $file = <STDIN>;

#erase new line
chomp($file);

open FILE,$file or die "Can't open $file...$!\n";
close FILE;




my $x=0;

while ( $x == 0 )
{

        menu();
        my $input = <STDIN>;

        if ( $input == 1 )
        {


                list_by_first_or_last();

        }
        elsif ( $input == 2 )
        {
                reverse_list_by_first_or_last();


        }
        elsif ( $input == 3 )
        {

                search_by_lastname();

        }
        elsif ( $input == 4 )
        {

                 search_by_birthday_or_birthmonth();

        }
        elsif ( $input == 5 )
        {

                system("clear");
                # exit program
                exit 0;

        }
        else
        {
                print "Invalid input\n";
        }


}

# display menu for program
sub menu(){

       print "*********************** Menu ***********************\n";
       print "(1) List the recods in alphabetical order of first name or last name\n";
       print "(2) Listing of records in reverse alphabetical order of first name or last name\n";
       print "(3) Search for a record by Last Name and print out the result\n";
       print "(4) Search for a record by birthday in a given year or month\n";
       print "(5) Exit Program\n";
       print  "Enter input: ";

}


sub list_by_first_or_last(){

        system ("clear");

        local $selection;

        # get userinput
        print "(1) Sort by First Name\n";
        print "(2) Sort by last Name\n";
        print "Enter input: ";
        $selection = <STDIN>;

        chomp($selection);

        if ( $selection == 1 )
        {
                # sort by first name

               system("sort $file");

        }
        elsif ( $selection == 2 )
        {
                # sort by last name
               system ("sort -k 2 $file");
        }
        else
        {
                print "Invalid Input\n";

        }

        print "\n";
}

sub reverse_list_by_first_or_last(){

        system("clear");

        local $selection;

        # get userinput
        print "(1) Sort by First Name\n";
        print "(2) Sort by last Name\n";
        print "Enter input: ";
        $selection = <STDIN>;

        chomp($selection);

        if ( $selection == 1 )
        {
                 # sort by first name in reverse order
                system(" sort -r $file");

        }
        elsif ( $selection == 2 )
        {
                 # sort by last name in reverse order
                  system("sort -r -k 2 $file");

        }
        else
        {


                  print "Invalid Input\n"
        }


        print "\n";

}




sub search_by_lastname(){

        system ("clear");

        local $selection;

        print "******* If Nothing is Returned No Record Was Matched ******\n";

        # get lastname of person to search for
        print "Enter the last name of the desired person to search for: ";
         $selection = <STDIN>;
        chomp($selection);

        # open file and search file for last name
        open FILE,$file or die "Can't open $file...$!\n";
        while ($line=<FILE>)
        {
                  if( $line=~/ $selection:/)
                  {
                        print $line;
                  }

        }

        close FILE;
        print "\n";
}




sub search_by_birthday_or_birthmonth(){

        system ("clear");

        local $selection;

        print "If nothing is returned no record was matched\n";

        print "(1) Search by Birt Year\n";
        print "(2) search by Birth Month\n";
        print "Enter input: ";
        $selection = <STDIN>;

        chomp($selection);

        if ( $selection == 1 )
        {

                print "What is the birth year(ex. 89,01,09): ";
                $selection = <STDIN>;
                chomp($selection);

                # open file and search for birth year
                open FILE,$file or die "Can't open $file...$!\n";
                while ($line=<FILE>)
                {
                        # if birth year is found print line
                        if( $line=~/\/$selection:/)
                        {
                                print $line;
                        }


                }

                close FILE;




        }
        elsif ( $selection == 2 )
        {


                print "What is the birth month: ";
                $selection = <STDIN>;
                chomp($selection);

                # open file and search for birth month
                open FILE,$file or die "Can't open $file ... $!\n";
                while( $line=<FILE> )
                {
                        # if birth month is found print that line
                        if ( $line=~/:$selection\// )
                        {
                                print $line;

                        }
                }


                close FILE;

        }
        else
        {
                print "Invalid Input \n";
        }

        print "\n";

}

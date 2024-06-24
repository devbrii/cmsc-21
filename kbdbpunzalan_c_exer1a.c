// Punzalan, Kurt Brian Daine B.
// CMSC 21 - ST-2L

#include <stdio.h>

void main()
{
    int input;

    printf("Enter a number (1-12): ");
    scanf("%d", &input);
    
    if(input <= 12 && input > 0) // makes sure that the input is from 1 to 12 only
    {
        int total = 0, increment, remainder, counter = 1;
        char *day, *month; // declaration of strings in C
        
        // number of days each month
        while (counter <= input)
        {
            switch(counter)
            {
                case(2):
                    increment = 28;
                    break;
                case(4):
                case(6):
                case(9):
                case(11):
                    increment = 30;
                    break;
                default:
                    increment = 31;
            }
            
            total += increment; // increment number of days and put into total
            counter++;
        }

        total -= increment; // subtract from total the latest number of days in the month (in the increment variable)
        remainder = (total+5)%7; // 5 was added so that every sunday, the remainder is 0. see code below.

        // for the respective month of the year
        if(input == 1) month = "January";
        else if(input == 2) month = "February";
        else if(input == 3) month = "March";
        else if(input == 4) month = "April";
        else if(input == 5) month = "May";
        else if(input == 6) month = "June";
        else if(input == 7) month = "July";
        else if(input == 8) month = "August";
        else if(input == 9) month = "September";
        else if(input == 10) month = "October";
        else if(input == 11) month = "November";
        else if(input == 12) month = "December";

        // choices for the day -- remainder as the basis
        if(remainder == 5) day = "Friday";
        else if(remainder == 6) day = "Saturday";
        else if(remainder == 0) day = "Sunday";
        else if(remainder == 1) day = "Monday";
        else if(remainder == 2) day = "Tuesday";
        else if(remainder == 3) day = "Wednesday";
        else if(remainder == 4) day = "Thursday";

        printf("1 %s 2021 is %s.\n", month, day); // prints the day based from the remainder

    }

    else printf("Invalid input\n");
    

}

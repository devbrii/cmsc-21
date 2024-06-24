#include <stdio.h>

void main()
{
    int input, total = 0, increment, remainder, counter = 1;
    char *month; // declaration of strings in C

    printf("Enter a number (1-12): ");
    scanf("%d", &input);

    if(input <= 12 && input > 0) // makes sure that the input is from 1 to 12 only
    {
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
        
        while (counter <= input)
        {
            // number of days each month
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
        remainder = (total+5)%7; // 5 was added so that every sunday, the remainder is 0.

        printf("\n%s 2021 Calendar\n\n", month);
        printf("SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n");
        int space_count = 0, day_count = 1, remainder_break = 1;
        while(day_count <= increment) // all days up until increment will surely be printed
        {   
            // this indicates the number of spaces (\t) allotted before printing the numbers 
            // which is why we set the remainder 0 every sunday
                // if it is sunday, then there are no spaces in the calendar
                // if the remainder is 6, then there are also 6 spaces (numbers will start from Friday of the first week)
            if(space_count < remainder) 
            {
                printf("\t"); // spaces will be printed if while space_count < remainder
                space_count++; // increment
            }

            else // after the spaces, the numbers will be printed
            {
                printf("%d\t", day_count);
                day_count++;
            }

            if(remainder_break % 7 == 0) printf("\n"); // enters new line after every week

            remainder_break++;
        }

        printf("\n");
    }

    else printf("Invalid input\n");

}
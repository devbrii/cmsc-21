#include <stdio.h>

// Function Prototypes
int daysOfMonth(int);
void printCalendaOfMonth2021(int, int, char*);
void firstDayOfMonth2021(int, char*, char*);

void main()
{
    int input;
    
    printf("Enter a number (1-12): ");
    scanf("%d", &input);

    if(input <= 12 && input > 0) // makes sure that the input is from 1 to 12 only
    {
        int total = 0, increment, remainder, counter = 1;
        char *day, *month; // declaration of strings in C

        while (counter <= input)
        {
            increment = daysOfMonth(counter);
            
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

        firstDayOfMonth2021(remainder, month, day); // prints the first day of the month
        printCalendaOfMonth2021(increment, remainder, month); // function for printing the calendar
    }

    else printf("Invalid input\n");
    
}


int daysOfMonth(int counter) // function for getting days of each month
{
    int increment;

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

    return increment;
}


void printCalendaOfMonth2021(int increment, int remainder, char *month) // function for printing calendar
{
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

        else
        {
            printf("%d\t", day_count); // after the spaces, the numbers will be printed
            day_count++;
        }

        if(remainder_break % 7 == 0) printf("\n"); // enters new line after every week

        remainder_break++;
    }

    printf("\n");
}


void firstDayOfMonth2021(int remainder, char *month, char *day)
{
    // choices for the day -- remainder as the basis
    if(remainder == 5) day = "Friday";
    else if(remainder == 6) day = "Saturday";
    else if(remainder == 0) day = "Sunday";
    else if(remainder == 1) day = "Monday";
    else if(remainder == 2) day = "Tuesday";
    else if(remainder == 3) day = "Wednesday";
    else if(remainder == 4) day = "Thursday";

    printf("\n1 %s 2021 is %s.\n", month, day);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function prototypes
int is_palindrome(char*);
void upper_case_change(char*);
void print_palindrome(char**, int);


int main()
{
    // variable declaration
    int value, palindrome_count = 0;
    char *user_input, **append_palindrome;

    // Initialize dynamic array
    user_input = (char*) malloc(sizeof(char) * 100); 


    // 2D Dynamic array for printing all palindromes
    append_palindrome = (char**) malloc(sizeof(char*) * 30); // Initialize 30 rows (user can input upto 30 palindromes)

    for (int i = 0; i < 30; i++)
    {
        append_palindrome[i] = (char*) malloc(sizeof(char) * 50); // user can input upto 50 characters per string
    }

    do
    {

        printf("Enter string: ");
        scanf("%s", user_input);

        upper_case_change(user_input); // change all characters to uppercase so that comparison will be easy

        if (strcmp("EXIT", user_input) == 0) // if user chose to terminate (EXIT)
        {
            printf("Detected terminate keyword. Goodbye!\n\n");

            print_palindrome(append_palindrome, palindrome_count);

            free(user_input); // before terminating the program
        
            for(int x = 0; x < 30; x++)
            {
                free(append_palindrome[x]);
            }

            free(append_palindrome);

            break;
        }

        value = is_palindrome(user_input); // value = 1 if palindrome

        if (value == 1) // it is a palindrome
        {
            printf("%s is a palindrome!\n\n", user_input);
            strcpy(append_palindrome[palindrome_count], user_input); // Appends every string depending on the palindrome_count
            palindrome_count++; // serves as the index. Is 
        }
        
        else
            printf("%s is not a palindrome!\n\n", user_input);

    } while (1);



    // // just to check if the arrays were properly freed (by turning the free() functions from line 44 as comments
    //     // and uncommenting the following)
    // printf("\n\nSTRING: %s\n\n", user_input);
    // print_palindrome(append_palindrome, palindrome_count);

    return 0;
}


int is_palindrome(char *user_input) // function for palindrome checking
{
    int value = 0;
    for (int i = 0; i < strlen(user_input)/2; i++)
    {
        if (user_input[i] == user_input[strlen(user_input) - (i+1)])
            value = 1;
        else
        {
            value = 0;
            break;
        }
    }

    return value;

    /*
    code above:
        NOTE: all characters were already changed into upper case
        if current character is equal to the last character per iteration (i.e NOON --> N & N, O & O)
            based on the ASCII chart, it will have a value of 1
        else:
            value of 0, then immediately terminates the program since it cannot be a palindrome anymore

        Even if the length of user_input is odd, it will not affect the code because of the integer division by 2
    */
}


void upper_case_change(char *user_input)
{
    for (int j = 0; j < strlen(user_input); j++)
    {
        user_input[j] = toupper(user_input[j]); // converts any character into upper case
    }
}


void print_palindrome(char **array, int counter)
{
    printf("Here are all your palindromes: \n");
    printf("===========================\n");
    for (int i = 0; i < counter; i++)
    {
        printf("[%d] %s\n", i+1, array[i]);
    }
    printf("===========================\n");

    // Prints all strings that are put in the arrays from index 1 up to counter (which represents the number of palindromes in our array)
}
// Punzalan, Kurt Brian Daine B.
// CMSC 21 - ST-2L
// Exercise 2

// Prime numbers are numbers whose factors are 1 and the number itself.

#include <stdio.h>

int prime_checker(int i, int j) // Checks if the value is prime or not
{
    if (j==1) return 1; // Meaning, the number is only divisible with j, which is 1.
    else if(i%j==0) return 0; // if the number i is divisible by j, return 0 (False) --> It is not prime
    else prime_checker(i, j-=1); // calls the function back until it reached one of the base cases. 

    // decrement the number being checked
        // Kumbaga, if i is 5, program will check if i is divisible by 1 to 5, but in decreasing manner.
}


int main() // Main function
{
    int n, j; // initializing variables

    do
    {   
        printf("Enter a positive number: "); // user input
        scanf("%d", &n);

        if (n < 2) printf("Invalid range.\n\n");

        else
        {
        printf("The prime numbers from 1 to %d are: ", n);
        for(int i=2; i<=n; i++) // iterating every numebr from 2 to n. (printing all prime numbers in the range)
        { // i is the current number being checked (if prime or not)
            if (prime_checker(i, i-1)) printf("%d ", i); // if the return value of the prime checker function is 1, meaing it is prime, then print it.
        }

        printf("\n");
        }
    }
    while(n < 2);




    return 0;
}

// We start off by setting i = 1 and j = i - 1 = 2.
    // then, the prime_checker() function checks if it is prime
        // Since j = 1, we return 1 and the recursive function terminates. 2 is prime.

// Then, i is incremented by 1, i = 3, and j = 2.
    // prime_checker()
        // first base case: j is not equal to 1
        // second base case: (i%j == 0) ? (3%2==0) ? False --> goes to else block
        // j is decremented by 1. j now is 1
        // function is called again
    // prime_checker()
        // first base case: j == 1 --> True
        // return 1
        // terminate
    // print i. 3 is prime

// i is then incremented by 1, i = 4, j = 3
    // prime_checker()
        // first base case: j is not equal to 1
        // second base case: (i % j == 0) ? (4 % 3 == 0) ? False --> goes to else block
        // j is decremented by 1. j now is 2
        // function is called again
    // prime_checker()
        // first base case: j is not equal to 1
        // second base case: (i % j == 0) ? (4 % 2 == 0) ? True --> terminate
            // return 0 (i is not a prime number)
    // does not print i because 4 is not a prime number

// this happens iteratively up to the user input n.
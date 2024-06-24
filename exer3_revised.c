#include <stdio.h>

// Function Prototpyes
void user_input(int*, int*);
void swap(int*, int*);
int prime_calc(int, int);
void get_largest(int*, int, int, int*, int*, int*);
void print_largest(int, int, int, int);


int main()
{
    int x, y, counter, a, b, c;

    user_input(&x, &y); // since the formal parameters are integer pointers, we must put &, referring to the memory locations of both x and y

    if ((x < 2) && (y < 2)) printf("Invalid range!\n"); // checks if the numbers input by the user is from 2 to any number greater than 2.
    else
    {
        if (x > y) swap(&x, &y); // formal parameters are also integer pointers.

        get_largest(&counter, x, y, &a, &b, &c);  // value of counter must be updated, otherwise it will still be 0 regardless of its value inside the function

        print_largest(a, b, c, counter); // print all prime numbers in the range

    }

    return 0;
}


void user_input(int *x, int *y)
{
    // since x and y are already pointers, we do not need to put & since both x and y int this function already point to the address of the variables.
    printf("Enter x: ");
    scanf("%d", x);

    printf("Enter y: ");
    scanf("%d", y);
}


void swap(int *x, int *y)
{
    // updates the values of x and y using pointers
    int swapper = *x;
    *x = *y;
    *y = swapper;
}


int prime_calc(int y, int w)
{
    // For cases of [ (x, y): (1, 2), (1, 3) and (1, 4) ] and [ (x, y): (2, 0), (2, -1), (2, -2) ...] --> There will come a time that (y, y-1) from line 70 will be (1, 0) or (2, 0).
    if (w <= 0) return 0; // updated from --> if (w == 0) return 0;

    else if (w == 1) return 1; // Meaning, the number is only divisible with j, which is 1.
    else if(y % w == 0) return 0; // if the number i is divisible by j, return 0 (False) --> It is not prime
    else prime_calc(y, w -= 1); // calls the function back until it reaches one of the base cases. 
}


void get_largest(int *counter, int x, int y, int *a, int *b, int *c)
{
    *counter = 0;

    while (y >= x)
    {   
        if (prime_calc(y, y-1)) // checks if the number is prime
        {              
            *counter += 1; 
            
            // all values of y that are prime (at most three) will be held by a pointer
            if(*counter == 1) *a = y; // this holds the largest prime number in the range
            else if (*counter == 2) *b = y; // 2nd largest
            else if (*counter == 3)
            {
                *c = y; // 3rd largest
                break;
            }
        }

        y--;
    }
}


void print_largest(int a, int b, int c, int counter)
{
    // print all prime numbers depending on the value of prime counter
    if (counter == 1) printf("There is one prime number: %d\n", a);
    else if (counter == 2) printf("There are two prime numbers: %d %d\n", a, b);
    else if (counter == 3) printf("The three largest prime numbers are: %d %d %d\n", a, b, c);
    else printf("There are no prime numbers in the given range\n");
}



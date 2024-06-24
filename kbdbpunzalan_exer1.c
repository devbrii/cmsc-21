// Punzalan, Kurt Brian Daine B.
//CMSC 21 - ST-2L
// EXER 1

#include <stdio.h>

int main() {
    
    // initializing variables
    int unit_choice = 0;
    float weight_kg, height_cm, weight_lbs, height_ft;

    printf("\n\nBMI CALCULATOR\n\n");


    while(unit_choice != 3) {
        float bmi = 0;

        printf("=====MENU=====\n");
        printf("[1] Kilograms & Centimeter\n");
        printf("[2] Pounds & Feet\n");
        printf("[3] Exit\n\n");
        printf("Enter choice: ");
        scanf("%d", &unit_choice); // user choice for the units
        printf("\n");

        switch(unit_choice) {
            case(1): // user chose kilograms and centimeters
                printf("Enter weight in kg: ");
                scanf("%f", &weight_kg);
                printf("Enter height in centimeters: ");
                scanf("%f", &height_cm);
                printf("\n");
                bmi = weight_kg/((height_cm*0.01)*(height_cm*0.01)); // BMI = kg/m^2 --> height is converted to meters 
                printf("Your BMI is %f.\n", bmi);
                break;

            case(2): // user chose punds and feet
                printf("Enter weight in lbs: ");
                scanf("%f", &weight_lbs);
                printf("Enter height in ft: ");
                scanf("%f", &height_ft);
                printf("\n");
                bmi = (weight_lbs/((height_ft*12)*(height_ft*12)))*703; // BMI = (lbs/in^2)*703 --> feet is converted into inches
                printf("Your BMI is %f.\n", bmi);
                break;
            
            case(3):
                printf("Goodbye!\n");
                bmi = 0;
                break;
             
            default: // invalid user choice
                printf("Wrong input!\nTry again!\n\n");
        }

        // interprets the calculated BMI
        if (bmi > 0 && bmi < 18.5) printf("You are underweight.\n\n");
        else if (bmi >= 18.5 && bmi < 25) printf("You are normal.\n\n");
        else if (bmi >= 25 && bmi < 30) printf("You are overweight.\n\n");
        else if (bmi >= 30) printf("You are obese.\n\n");
        else (bmi == 0);
    }

    return 0;
}

/*

1.) unit_choice is initialized to 0.
    > If not initialized and the garbage value of unit_choice = 3, then the program will not run properly

2.) bmi is initialized to 0 every iteration
    > If unit_choice != 1, 2, or 3, then it will go to the default, which is printing "invalid output"
    > the value of bmi is then checked. bmi is still 0.
        > first IF: bmi > 0 && bmi < 18.5 ? FALSE
        > else bmi == 0
            > does not print bmi category hehe

    > reason why bmi is in the loop:
        > we must make sure that at the start of every loop, bmi is 0. Why?

        > If user input 1 or 2, then bmi will surely have a value. For instance, bmi = 19. It is under normal range
            > bmi is updated to 19.
            > prints "You are normal."
        > In the second iteration, if user input != 1, 2, or 3, since bmi is stil 19:
            > It will print invalid input
            > At the same time, "You are normal." will also be printed (category for bmi = 19)

*/
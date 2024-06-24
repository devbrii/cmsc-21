#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Anagram Function
int areAnagrams(char str1[100], char str2[100])
{

    //initialize variables
    int length1 = strlen(str1);
    int length2 = strlen(str2);
    int result;

    //if length is not equal, it automatically reads the input NOT anagram
    if (length1 != length2)
    {
        result = 0;
    }
    else
    // if it is equal, each letter of str1 will be compared to str2
    {
        for (int i = 0; i < length1; i++)    //loops each letter of str1
        {
            for (int j = 0; j < length2; j++) //loop each letter of str2
            {
                char letter1 = str1[i], letter2 = str2[j]; //initialize variables

                if (letter1 == letter2) //if letter has a match
                {
                    result = 1;
                    str2[j] = '*'; //The letter will be replaced by * to avoid repetition
                    break;
                }
                else if (letter1 != letter2 && j == (length2 - 1)) //if there's no letter match then it is not an anagram 
                {

                    result = 0;
                    break;
                }
            }if (result==0) break; //end of loop for second word
        }
    }
    return result; //end of loop for first word
}

//makes the input lowercase
void toLower(char *string) // changes all input into lowercase (per character)
{
    for (int x = 0; x < strlen(string); x++)
    {
        string[x] = tolower(string[x]);
    }
}

int main(){
    char str1[100], str2[100], a[100], b[100]; // variable declarations

    do
    {
        printf("Enter two strings: ");
        scanf("%s %s", str1, str2);

        //case sensitive
        toLower(str1);
        toLower(str2);
        
        strcpy(a, str1);
        strcpy(b, str2);

        if ((strcmp(str1, "exit") == 0) && (strcmp(str2, "now") == 0)) // if 'EXIT NOW' is entered by the user, terminate the loop then exit)
        {
            printf("Good bye!\n");
            break;
        }

        if (areAnagrams(str1, str2) == 1) // they are anagrams
        {
            printf("%s and %s are Anagrams!\n\n", a, b);
        }
        else
        {
            printf("%s and %s are NOT Anagrams!\n\n", a, b);
        }

    } while (1);

    return 0;
}

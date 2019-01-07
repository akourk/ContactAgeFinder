// Author       :   Alex Kourkoumelis
// Date         :   2/17/2018
// Title        :   Contact Age Finder
// Description  :   Reads a .txt file in the format FNAME LNAME 00-00-0000
//              :   Stores the information into 2 structs, date, and contact
//              :   Then compares the current date to the date of each contact
//              :   Lists all contacts between the ages of 18 and 25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct to keep track of birth dates
typedef struct {
    int day;
    int month;
    int year;
} date;

//struct to keep track of firstname and lastname
typedef struct {
    char fname[16];
    char lname[16];
} contact;

//array of contact and birthdate structs
contact contacts[100];
date dates[100];

//Loads all the contacts into the struct arrays
void loadContact() {
    printf("Hello, World!\n");

    //prompts for filename
    char filename[16];
    printf("Enter the filename to open \n");
    scanf("%s", filename);

    //opens the file
    FILE *file;
    file = fopen(filename, "r");
    char fullfile [100][43];
    int i = 0;
    int total = 0;

    //finds how many lines there are
    while(fgets(fullfile[i], sizeof(file[i]), file)){
        i++;
    }

    //keeps track of how many lines there are
    total = i;

    //prints contents of the file
//    for(i = 0; i < total; ++i){
//        printf("%s", fullfile[i]);
//    }

    //to break apart character arrays
    char *breaker;
    char *strArray[16];
    for(i = 0; i < total; i++){
        breaker = strtok(fullfile[i], " ,.-");
        int j = 0;

        //adds first name into first contact before breaker is activated again
        strcpy(contacts[i].fname, breaker);

        //adds the rest of the elements to the array of contacts and phone numbers
        while(breaker != NULL) {
            j++;
            strArray[i] = strdup(breaker);
            breaker = strtok(NULL, " ,.-");
            if (j == 1) {
                strcpy(contacts[i].lname, breaker);
            } else if (j == 2) {

                //atoi converts char string to int
                int temp = atoi(breaker);
                dates[i].day = temp;
            } else if (j == 3) {
                int temp = atoi(breaker);
                dates[i].month = temp;
            } else if (j == 4) {
                int temp = atoi(breaker);
                dates[i].year = temp;
            }
        }
    }
}

int main() {

    //to load contacts
    loadContact();

    //uncomment to print out the list of all loaded contacts and their corresponding info
//    for(int i = 0; i < 101; ++i){
//        printf("\n");
//        printf("\n\tContact #%d:", i);
//        printf("\nFirst Name is:\t%s", contacts[i].fname);
//        printf("\nLast Name is:\t%s", contacts[i].lname);
//        printf("\nDay is:\t\t\t%d", dates[i].day);
//        printf("\nMonth is:\t\t%d", dates[i].month);
//        printf("\nYear is:\t\t%d", dates[i].year);
//    }

    //current year, month, and day
    int currentYear = 2018;
    int currentMonth = 2;
    int currentDay = 17;
    printf("\n\nCurrent year is: \t%d", currentYear);
    printf("\nCurrent month is: \t%d", currentMonth);
    printf("\nCurrent day is: \t%d\n", currentDay);
    printf("\nList of people who are between 18 and 25 years old:");

    //one metric shitload of edge cases all taken care of!
    //for loop iterates through each contact
    for(int i = 0; i < 101; i++){

        //edge case 1.a: current year - birth year = 18, but the contact isn't 18 yet
        if(currentYear - dates[i].year == 18){

            //so we check for month, but that leads to
            //edge case 1.b: month is after current, but day isn't
            if(currentMonth >= dates[i].month){

                //so we check for day as well
                //edge case 1.c: month and day are after current, so age defaults to 18
                if(currentDay >= dates[i].day){
                    printf("\n%c. %s, 18", contacts[i].fname[0], contacts[i].lname);
                }
            }
        }

        //simple stuff, but we still have edge cases
        //checks for all middle cases (ages 19 through 24)
        if(currentYear - dates[i].year > 18 && currentYear - dates[i].year < 25){

            //calculate current year - birth year
            //but this doesn't cover for months before or after
            int age = currentYear - dates[i].year;

            //thus we have edge case 2:
            //current month is the same as birth month, so we check for day
            if(currentMonth == dates[i].month){

                //if day is past, contact hasn't yet had their birthday, so we decrement age
                if(currentDay < dates[i].day){
                    age--;
                }
            }

            //edge case 2.b: month has passed, so we don't need to check day, and we decrement age
            if(currentMonth < dates[i].month){
                age--;
            }

            //prints age
            printf("\n%c. %s, %d", contacts[i].fname[0], contacts[i].lname, age);
        }
        //edge case 3.a: current year - birth year = 25, but contact isn't 25 yet
        if(currentYear - dates[i].year == 25){

            //edge case 3.b: month is after current or equal to, but day needs to be checked
            if(currentMonth <= dates[i].month){

                //edge case 3.c: birthday hasn't happened yet, so contact is still 24
                if(currentDay < dates[i].day){

                    //and age defaults to 24
                    printf("\n%c. %s, 24", contacts[i].fname[0], contacts[i].lname);                }
            }
        }
    }

    //edge case 4: Doesn't matter how old the contact is, everyone deserves a birthday celebration!
    for(int i = 0; i < 101; i++){
        if(currentMonth == dates[i].month && currentDay == dates[i].day){

            // !!! :)
            printf("\n\nHappy Birthday, %s %s!!!", contacts[i].fname, contacts[i].lname);
        }
    }
    return 0;
}
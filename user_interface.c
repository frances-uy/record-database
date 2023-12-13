/*****************************************************************
//
//  NAME:        Frances Michelle Uy
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 22, 2023
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   Contains the functions to accept user input through a
//   user-friendly interface,  based on options
//   to add, find, print, or delete new or current records.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "database.h"

void getaddress (char [], int);

int debugmode = 0;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Prints an introductory message and record
//                 manipulation options, for the user to select.
//                 May prompt for more information, otherwise
//                 will call corresponding database function.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : The user-chosen menu option was carried out.
//                 1 : The user-chosen menu option was not carried out.
//
****************************************************************/

int main(int argc, char* argv[])
{
    /*Initialize the database*/
    struct record * start = NULL;

    /*Tracker to control termination of program*/
    int quit;
    int validInput;
    int accountNumber;
    int i;
    int foundTracker;
    int deletedTracker;
    int quitTracker;
    char input[50];
    char name[100];
    char address[100];

    quit = 0;

    /*Check for command-line arguments*/
    /*Whether or not debugmode will be activated*/
    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = 1;
    } 
    else if (argc > 1) 
        {
        printf("Error: Invalid arguments\n");
        return 1;
    }


    if (readfile(&start, "writefile.txt") == -1)
    {     
        if (debugmode == 1)
        {
     	    printf ("===================|DEBUG INFORMATION|=========================\n");
            printf ("* Debug: File to read from does not exists yet.\n");
            printf ("===============================================================\n");
        }
    }

    /*Introductory Message*/
    printf("Aloha, Welcome to the Banking Database Program\n");

    while (!quit)
    {
        printf("********************************[PLEASE SELECT A MENU OPTION]*********************************\n");
        printf("add: Add a new record in the database\n");
        printf("printall: Print all records in the database\n");
        printf("find: Find one or more records with a specified account number\n");
        printf("delete: Delete one or more existing records with a specified account number\n");
        printf("quit: Quit the program\n"); 
        printf("**********************************************************************************************\n");

        /*Prompt the user for menu option*/
        printf("\nEnter a menu option: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        /*Converting the input to lowercase to prevent case-sensitivity*/
        for (i = 0; input[i]; i++)
        {
            input[i] = tolower(input[i]);
        }

        if (strcmp(input, "add") == 0 || strncmp(input, "ad", 2) == 0 || strncmp(input, "a", 1) == 0)
        {
        
            /*Additional prompt for account number*/
             while (!validInput)
             {
                 printf("Enter account number: ");
                 if (scanf("%d", &accountNumber) == 1 && accountNumber > 0)
                 {
                     validInput = 1;
                 }
                 else
                 {
                 printf("Invalid input. Please enter a positive integer.\n");
                 while (getchar() != '\n');
                 }
            }
            getchar();

            printf("Enter name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            getaddress(address, sizeof(address));

            addRecord(&start, accountNumber, name, address);
            validInput = 0;
        }
        else if (strncmp(input, "printall", strlen(input)) == 0)
        {
            printAllRecords(start);
        }
        else if (strcmp(input, "find") == 0 || strncmp(input, "fin", 3) == 0 || strncmp(input, "fi", 2) == 0 || strncmp(input, "f", 1) == 0)
        {
            /*Additional prompt for account number*/
             while (!validInput)
             {
              	 printf ("Enter account number: ");
                 if (scanf("%d", &accountNumber) == 1 && accountNumber > 0)
                 {
                     validInput = 1;
                 }
                 else
                 {
                 printf ("Invalid input. Please enter a positive integer.\n");
                 while (getchar() != '\n');
                 }
            }
            getchar();

            foundTracker = findRecord(start, accountNumber);
            
            if (foundTracker == 0)
            {
                printf("Record found!\n");
            }
            else
            {
                printf("Sorry, record not found with given number for account.\n");
            }
            validInput = 0;
        }                        
        else if (strncmp(input, "delete", strlen(input)) == 0)
        {
 
            /*Additional prompt for account number*/
             while (!validInput)
             {
              	 printf("Enter account number: ");
                 if (scanf("%d", &accountNumber) == 1 && accountNumber > 0)
                 {
                     validInput = 1;
                 }
                 else
                 {
                 printf("Invalid input. Please enter a positive integer.\n");
                 while (getchar() != '\n');
                 }
            }
            getchar();
  
            deletedTracker = deleteRecord(&start, accountNumber);
            
            if (deletedTracker  == 0)
            {
                printf("Record deleted.\n");
            }
            else
            {
                printf("Record not found for deletion.\n");
            }
            validInput = 0;
        }    
        else if (strncmp(input, "quit", strlen(input)) == 0)
        {
            quitTracker = writefile (start, "writefile.txt");
        
            if (quitTracker == 0)
            {
                printf ("Data saved successfully.\n");
            }
            else
            {
                printf ("There was an issue saving the data.\n");
            }
            
            printf("Exiting the program. Mahalo!\n");
            cleanup(&start);
            quit = 1;
        }
        else
        {
            printf("Invalid menu option. Please try again.\n");
        }
    }
    return 0;

}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   Collects the information of the given address
//                 by user.
//
//  Parameters:    char address[] : Character array to collect and
//                                  store lines of user-provided
//                                  addresses.
//
//                 maxLength (int): The maximum length in characters
//                                  the address array can hold.
//
//  Return values: void
//
****************************************************************/

void getaddress (char address[], int maxLength)
{
    int lengthInput = 0;
    char line[100];
    /*Tracker variable determining whether user input is terminated or not*/
    int userWantsToContinue;
    userWantsToContinue = 1;

    /*Initializing address to an empty string*/
    address[0] = '\0';

    printf("Enter address line (Enter just '.' to finish):\n");

    while (userWantsToContinue)
    {
        fgets (line, sizeof(line), stdin);

        if (strcmp(line, ".\n") == 0 || strcmp(line, ".") == 0)
        {
            userWantsToContinue = 0;
        }
        else
        {
            if (lengthInput + strlen(line) >= maxLength)
            {
                line[maxLength - lengthInput - 1] = '\0';
                userWantsToContinue = 0;
            }
            strcat (address, line);
            lengthInput += strlen(line);
        }
    /*    strcat (address, line);
        lengthInput += strlen(line); */
    }

    if (debugmode == 1)
    {
     	printf ("===================|DEBUG INFORMATION|=========================\n");
        printf ("* Debug: Entering getaddress function\n");
        printf ("* Debug: Parameters - maxLength: %d\n", maxLength);
        printf ("* Debug: Address: %s\n", address);
        printf ("===============================================================\n");
    }
}

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
//  FILE:        database.c
//
//  DESCRIPTION:
//   Depending on input from user interface, either of these
//   functions will be called to manipulate the database by
//   adding, printing, finding, or deleting records.
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "string.h"

extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Allows a user to add a new record to the
//                 databse linked list.
//
//  Parameters:    struct record ** : A pointer to a pointer to a struct record. 
//                                    Used to modify the linked list of records
//                                    by adding a new record to it.
//                 int : The account number of a new record.
//                                  
//                 char [] : Array of characters specifying the
//                           name of the new record.
//
//                 char[] : Array of characters specifying the
//                          address of the new record.
//
//  Return values: void
//                 
//
****************************************************************/

int addRecord (struct record **start, int uaccountno, char uname[], char uaddress[])
{
    int result;
    struct record* current = *start;
    struct record* previous = NULL;
    int foundPosition = 0;
    struct record* newRecord;

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Entering addRecord function\n");
        printf("* Debug: Parameters - struct record **, int, char [], char []\n");
        printf("* Debug: uaccountno: %d\n", uaccountno);
        printf("* Debug: uname: %s\n", uname);
        printf("* Debug: uaddress: %s\n", uaddress);
        printf("===============================================================\n");
    }

    while (current != NULL && !foundPosition)
    {
        if (uaccountno == current->accountno)
        {
            printf("Adding failed: An account with number %d already exists!\n", uaccountno);
            result = -1; /* duplicate account number */
            return result;
        }
        else if (uaccountno < current->accountno)
        {
            foundPosition = 1;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    /* Create the new record */
    newRecord = (struct record*)malloc(sizeof(struct record));
    if (newRecord == NULL)
    {
        printf("Memory allocation failed!\n");
        result = -2; /* Memory allocation error */
        return result;
    }

    newRecord->accountno = uaccountno;
    strcpy(newRecord->name, uname);
    strcpy(newRecord->address, uaddress);
    newRecord->next = current;

    if (previous == NULL) /* Inserting at the start */
    {
        *start = newRecord;
        printf("Successfully Added Account: %d\n", uaccountno);
    }
    else /* Inserting somewhere in the middle or at the end */
    {
        previous->next = newRecord;
        printf("Successfully Added Account: %d\n", uaccountno);
    }

    result = 0;
    return result;
}


/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints and displays the entire database.
//
//  Parameters:    struct record * : The head of the linked list.
//
//  Return values: void
//
****************************************************************/

void printAllRecords (struct record *start)
{
    struct record* temp;
    int count = 0;
    temp = start;    

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Entering printAllRecords function\n");
        printf("* Debug: Parameters - Starting address of the linked list: %p\n", (void *)start);
        printf("===============================================================\n");
    }

    if (temp == NULL)
    {
        printf("No records to print. The list is empty. Please select another option.\n");
    }

    while (temp != NULL)
    {
        printf ("Account Number: %d\nName: %s\nAddress: %s\n\n", temp->accountno, temp->name, temp->address);

        if (debugmode == 1)
        {
            printf("===================|DEBUG INFORMATION|=========================\n");
            printf("* Debug: Processing record at address %p with account number %d\n", (void *)temp, temp->accountno);
            printf("===============================================================\n");
        }

        count++;
        temp = temp->next;
    }

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Total records processed: %d\n", count);
        printf("* Debug: Exiting printAllRecords function\n");
        printf("===============================================================\n");
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Searches for a record with the specified account
//                 number in the linked list.
//
//  Parameters:    struct record * : The head of the linked list.
//                 int : The account number to search for.
//
//  Return values: void
//
****************************************************************/

int findRecord (struct record *start, int uaccountno)
{
    struct record* current;
    int result;
    current = start;
    result = -1;

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Entering findRecord function\n");
        printf("* Debug: Parameters - struct record * start, int accountNumber: %d\n", uaccountno);
        printf("===============================================================\n");
    }

    while (current != NULL) 
    {
        if (current->accountno == uaccountno) 
        {
            if (debugmode == 1)
            {
                printf("===================|DEBUG INFORMATION|=========================\n");
                printf("* Debug: Found record at address %p with account number %d\n", (void *)current, current->accountno);
                printf("===============================================================\n");
            }
            printf ("Account Number: %d\nName: %s\nAddress: %s\n\n", current->accountno, current->name, current->address);
            result = 0;
            return result; /* Found the record */
        }
        current = current->next;
    }

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: No record found with account number %d\n", uaccountno);
        printf("===============================================================\n");
    }
    result = -1;
    return result; /* Record not found */
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Searches for a record with the specified account
//                 number in the linked list and deletes it if found.
//
//  Parameters:    struct record ** : A pointer to a pointer to
//                                    the head of the linked list.
//                 int : The account number to search for and delete.
//
//  Return values: void
//
****************************************************************/

int deleteRecord(struct record **start, int uaccountno)
{
    int result;
    struct record* current = *start;
    struct record* previous = NULL;
 
    result = -1;

    if (debugmode == 1)
    {
     	printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Entering deleteRecord function\n");
        printf("* Debug: Parameters - struct record ** start, int uaccountno\n");
        printf("* Debug: start's address: %p\n", (void *)start);
        printf("* Debug: start points to address: %p\n", (void *)*start);
        printf("* Debug: uaccountno: %d\n", uaccountno);
        printf("===============================================================\n");
    }

 
    while (current != NULL) {
        if (current->accountno == uaccountno) {
            if (previous != NULL)
            {
                previous->next = current->next;
                free(current);
                current = previous->next; /* Continue from the next record */
                result = 0;
            }
            else
            {
                *start = current->next;
                free(current);
                current = *start; /* Reset to the new start */
                result = 0;
            }
        }
        else 
        {
            previous = current;
            current = current->next;
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Saves the records from the linked list into a file.
//
//  Parameters:    struct record * : The head of the linked list.
//                 char filename[] : The name of the file to save the records to.
//
//  Return values: int: 0 for success, -1 for failure
//
****************************************************************/

int writefile(struct record *start, char filename[])
{
    FILE *fp;
    struct record *current = start;

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Entering writefile function\n");
        printf("* Debug: Parameters - struct record * start, char filename[]: %s\n", filename);
        printf("===============================================================\n");
    }

    fp = fopen(filename, "w");
    
    if (fp == NULL)
    {
        if (debugmode == 1)
        {
            printf("===================|DEBUG INFORMATION|=========================\n");
            printf("* Debug: Failed to open file: %s\n", filename);
            printf("===============================================================\n");
        }

        perror("Error opening file");
        return -1;  /* Return failure if unable to open file */
    }

    while(current != NULL)
    {
        fprintf(fp, "%d\n%s\n%s.\n", current->accountno, current->name, current->address);

        if (debugmode == 1)
        {
            printf("===================|DEBUG INFORMATION|=========================\n");
            printf("* Debug: Writing record with account number %d to file\n", current->accountno);
            printf("===============================================================\n");
        }   

        current = current->next;
    }

    fclose(fp);

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Exiting writefile function\n");
        printf("===============================================================\n");
    }

    return 0;  /* Return success */
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Retrieves records from a saved file.
//
//  Parameters:    struct start ** : Pointer to the start of the record.
//                 char filename[] : The filename the records were saved to.
//
//  Return values: int : 0 if successful, -1 if an error occurred or unsuccessful.
//
****************************************************************/

int readfile(struct record **start, char filename[])
{
    FILE *fp;
    char line[200];
    struct record *current;
    int result;
    int eofReached = 0; 

    if (debugmode == 1)
    {
        printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Entering readfile function\n");
     	printf("* Debug: Parameters - struct record ** start, char filename[]: %s\n", filename);
        printf("===============================================================\n");
    }


    fp = fopen(filename, "r");
    if (fp == NULL)
    {
       if (debugmode == 1)
        {
            printf("===================|DEBUG INFORMATION|=========================\n");
            printf("* Debug: Failed to open file: %s\n", filename);
            printf("===============================================================\n");
	}

        printf("No previous records were found.\n");
        return -1; 
    }

    while (!eofReached)
    {
        struct record *newRec = malloc(sizeof(struct record));
        if (newRec == NULL)
        {
            fclose(fp);
            
            if (debugmode == 1)
            {
                printf("===================|DEBUG INFORMATION|=========================\n");
                printf("* Debug: malloc failed to allocate memory for the new record.\n");
                printf("===============================================================\n");
            }

            return -1; 
        }

        result = fscanf(fp, "%d\n", &newRec->accountno);
        if (result != 1)
        {
            free(newRec);
            if (result == EOF)
            {
                eofReached = 1;
            }
            else
            {
                fclose(fp);

                if (debugmode == 1)
                {
                    printf("===================|DEBUG INFORMATION|=========================\n");
                    printf("* Debug: fscanf failed to read account number.\n");
                    printf("===============================================================\n");
       	        }

                return -1;
            }
        }
        else
        {

            fgets(newRec->name, sizeof(newRec->name), fp);
            newRec->name[strcspn(newRec->name, "\n")] = '\0';

           
            newRec->address[0] = '\0';
            while (fgets(line, sizeof(line), fp) && strcmp(line, ".\n") != 0)
            {
                if (line[strlen(line) - 1] == '\n')
                    line[strlen(line) - 1] = '\0'; 

                strncat(newRec->address, line, sizeof(newRec->address) - strlen(newRec->address) - 1);
                strncat(newRec->address, "\n", sizeof(newRec->address) - strlen(newRec->address) - 1); /* re-add newline */
            }

            newRec->next = NULL;

            if (*start == NULL)
            {
                *start = newRec; /* if this is the first record, it becomes the start of the list */

                if (debugmode == 1)
                {
                    printf("===================|DEBUG INFORMATION|=========================\n");
                    printf("* Debug: First record with account number %d read from file.\n", newRec->accountno);
                    printf("===============================================================\n");
                }
            }
            else
            {
                current = *start;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newRec; /* append the new record to the end of the list */
               
                if (debugmode == 1)
                {
                printf("===================|DEBUG INFORMATION|=========================\n");
                printf("* Debug: Appended record with account number %d.\n", newRec->accountno);
                printf("===============================================================\n");
                }
            }
        }
    }

    fclose(fp);

    if (debugmode == 1)
    {
     	printf("===================|DEBUG INFORMATION|=========================\n");
        printf("* Debug: Exiting readfile function\n");
        printf("===============================================================\n");
    }

    return 0;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Frees all the nodes in the linked list.
//
//  Parameters:    struct record **start : Pointer to the head of the linked list.
//
//  Return values: None
//
****************************************************************/

void cleanup(struct record **start)
{
    struct record *current = *start;
    struct record *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *start = NULL;
}


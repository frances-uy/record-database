/*****************************************************************
//
//  NAME:        Frances Michelle Uy
//
//  HOMEWORK:    3b
//
//  CLASS:	 ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 22, 2023
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   This header file declares the methods for the
//   Bank Database Application database.
//
******************************************************************/
#include "record.h"

int addRecord (struct record **, int, char[], char[]);
void printAllRecords (struct record *);
int findRecord (struct record *, int);
int deleteRecord (struct record **, int);
int writefile (struct record *, char []);
int readfile (struct record **, char []);
void cleanup (struct record **);

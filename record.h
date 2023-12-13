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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This header file defines the parts of a record for the
//   Bank Database Application user-interface and database
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};


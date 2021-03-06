
Conversation opened. 1 unread message.

Skip to content
Using Gmail with screen readers

  More 
1 of 2,566
 
C Assignment 
Inbox
x 

Nettle
Attachments23:35 (2 minutes ago)
to me 
Try and change up the code as much as you can so we don't get done for plagiarism!
also it's quite complicated but i tried to simplify it as much as I could and commented as much as made sense! let me know if you can't figure something out! 
Attachments area
	
Click here to Reply or Forward
0.63 GB (4%) of 15 GB used
Manage
Terms - Privacy
Last account activity: 39 minutes ago
Details

// Week 21 Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct date {
	int dd;
	int mm;
	int yyyy;
}date;
typedef struct time {
	int hour;
	int minute;
}time;
typedef struct work {
	int employeeID;
	date date;
	time startTime;
	time endTime;
}work;

void handleArgs(int argc, char *argv[]); // handles arg inputs and converts from string and stores in structs
int convert(char *argv[], int i); //converts string to int
void send(FILE *fptr); //refactoring parts of handleArgs to simplify
void append(int argc, char *argv[], char *directory); // if append was chosen
int handleStrings(int argc, char *argv[], int i); //determines what to do based on arg inputs
void search(char *directory, char *argv[]); //searches for records from Employee ID and prints records if found
void print(char *directory);	// prints an entire file based on dir input 
FILE *openFile(char *dir, char *mode);

work *store;

int main(int argc, char *argv[])
{	
	if (argc > 1) {
		handleArgs(argc, argv);
	}
	
	
    return 0;
}
void handleArgs(int argc, char *argv[]) {

	store = (work*)malloc(sizeof(work)); 

	char *mode[] = { "\\a", "\\s","\\p" }; //append, search, print
	char customDir[80]; // this is recieved from arg[1]
	strcpy(customDir, argv[1] );

	const int baseArg = 3;
	
	if ((argc - baseArg) % 4 == 0 && strcmp(argv[2], mode[0])==0) //deals with 3 base args and then any multiple of 4inputs
	{
		//printf("Base 3 + multiple of 4 args have been entered.\n");
		append(argc, argv, customDir); //runs append function and sends data to file
	}
	else if (argc == 4)
	{
		if (strcmp(argv[2],mode[0])==0) { // if next arg is equal to \a (append)
			//puts("debug. Entered append if statement");
			puts("Not enough parameters, try again. Exiting...");
			exit(1);
		}
		if (strcmp(argv[2], mode[1]) == 0) { // if next arg is equal to \s (search)
			//puts("debug. Entered search if statement");
			search(customDir, argv);
		}
		else if (strcmp(argv[2], mode[2])==0) { // if next arg is equal to \p (print)
			//puts("debug. Entered print if statement");
			printf("Too many arguments to print file.Try: \ndir \p ");
		}
	}
	else if (argc == 3)
	{
		if (strcmp(argv[2], mode[2]) == 0) {
			print(customDir);
		}
	}
	else {
		printf("Invalid input or incorrect number of args entered.\n");
		printf("Enter data in the form:\nworklog.txt \\a 1234 01/01/2018 12:34 12:34\n");
		printf("Multiples of 4 are allowed after \\a therefore incomplete records are not allowed.\n");
		printf("or\nworklog.txt \\p 1234\n");
		printf("or\nworklog.txt \\s 1234\n\n");
	}
}

FILE *openFile(char *dir, char *mode) {
	FILE *fptr;
	fptr = fopen(dir, mode);
	if (fptr == NULL) {
		printf("Could not open file or directory. ing.\n");
		exit(1);
	}
	else {
		return fptr;
	}
		
}
void append(int argc, char *argv[], char *directory) {

	FILE *fptr = NULL;
	char *mode[] = { "\\a", "\\s","\\p" }; //append, search, print

		if (argc > 1) {
			strcpy(directory, argv[1]);
			fptr = openFile(directory, "a");
			//puts("debug. Entered dir if statement");
		}
		for (int i = 3; i < argc; i++) // we know that argc is 3 + 4x so we can loop over last 4
		{
			if ((i % 4) == 3 && strlen(argv[i]) == 4) {
				store->employeeID = convert(argv, i); // converts employee ID to int and stores in struct
				printf("Employee ID is: %d\n", store->employeeID);
			}
			else if (i % 4 == 0 && strlen(argv[i]) <= 10) { // if next arg is less than 10 chars long
					 //puts("debug. Entered date if statement");
				int index = 1; // determines if handleStrings uses NULL or Array as part of strtok				
				store->date.dd = handleStrings(index, argv, i);
				index++;
				store->date.mm = handleStrings(index, argv, i);
				store->date.yyyy = handleStrings(index, argv, i);

				printf("%02d/%02d/%04d\n", store->date.dd, store->date.mm, store->date.yyyy);
			}
			else if (i % 4 == 1 && strlen(argv[i]) <= 5) { // if next arg is <= 5 chars long
				//puts("debug. Entered start time if statement");
				int index = 1;
				store->startTime.hour = handleStrings(index, argv, i);
				index++;
				store->startTime.minute = handleStrings(index, argv, i);

				printf("%02d:%02d\n", store->startTime.hour, store->startTime.minute);
			}
			else if (i % 4 == 2 && strlen(argv[i]) <= 5) { // if next arg is <= 5 chars long
				//puts("debug. Entered start time if statement");
				int index = 1;
				store->endTime.hour = handleStrings(index, argv, i);
				index++;
				store->endTime.minute = handleStrings(index, argv, i);

				printf("%02d:%02d\n", store->endTime.hour, store->endTime.minute);
				if (fptr != NULL) {
					send(fptr); //write all data from this loop to file
				}
			}
			else
				puts("Error in append function.\n");
			
		}
		fclose(fptr);
}
void search(char *directory, char *argv[]) {
	FILE *fptr;
	fptr = openFile(directory, "r");
	char *delim = { " \"," };
	char fileLine[100];
	char *token;
	char *months[] = { "", "January", "February", "March", "April",
		"May", "June", "July", "August", "September",
		"November", "December" };
	char day[4];
	char month[10];
	char intMonth;
	char year[5];
	char ID[5];
	char start[6];
	char end[6];
	int matchFound = 0;

	// date, ID, start time, endtime
	while (!feof(fptr)) {
	
		fgets(fileLine, 100, fptr);
		token = strtok(fileLine, delim);
		strcpy(day, token);


		while (token != NULL) {
			token = strtok(NULL, delim);
			if (token == NULL) continue;
			strcpy(month, token);
			for (int i = 1; i < 14; i++)
			{
				if (strcmp(month, months[i]) == 0) {
					intMonth = i;
					break;
				}
			}
			token = strtok(NULL, delim);
			strcpy(year, token);
			token = strtok(NULL, delim);
			strcpy(ID, token);
			if (strcmp(token, argv[3]) == 0) {
				//match found print whole line.
				matchFound++;
				if (matchFound == 1) {
					printf("Match found. Printing all records for ID %s\n", argv[3]);
					token = strtok(NULL, delim);
					strcpy(start, token);
					token = strtok(NULL, delim);
					strcpy(end, token);
				}
				printf("Date: %s/%02d/%s, Employee: %s, Started at: %s, Finished at: %s\n",
					day, intMonth, year, ID, start, end);
			}
			token = NULL;
		}
	}
	if (feof(fptr) && matchFound == 0) {
		printf("Sorry, no match was found.\n");
	}
	//printf("Matches found: %d\n", matchFound);
}
void print(char *direcotry) {
	FILE *fptr; 
	fptr = openFile(direcotry, "r");
	char fileLine[100];
	char *delim = { " \"," };
	char *token;
	char *months[] = { "", "January", "February", "March", "April",
		"May", "June", "July", "August", "September",
		"November", "December" };
	char day[4];
	char month[10];
	char intMonth;
	char year[5];
	char ID[5];
	char start[6];
	char end[6];

	while (!feof(fptr)) {

		fgets(fileLine, 100, fptr);
		token = strtok(fileLine, delim);
		strcpy(day, token);


		while (token != NULL) {
			token = strtok(NULL, delim);
			if (token == NULL)continue;
			strcpy(month, token);
			for (int i = 1; i < 14; i++)
			{
				if (strcmp(month, months[i]) == 0) {
					intMonth = i;
					break;
				}
			}
			token = strtok(NULL, delim);
			strcpy(year, token);
			token = strtok(NULL, delim);
			strcpy(ID, token);
			token = strtok(NULL, delim);
			strcpy(start, token);
			token = strtok(NULL, delim);
			strcpy(end, token);
			
			printf("Date: %s/%02d/%s, Employee: %s, Started at: %s, Finished at: %s\n",
				day, intMonth, year, ID, start, end);
			token = NULL;
		}
	}	
}
int convert(char *argv[], int i) {
	
	int convert;
	convert = strtol(argv[i], NULL, 10);
	return convert;
}
void send(FILE *fptr) {
	char *months[] = { "", "January", "February", "March", "April",
					"May", "June", "July", "August", "September",
					"November", "December" };
	char string[13];

	for (int i = 1; i < 13; i++)
	{
		if (store->date.mm == i)
		{
			strcpy(string, months[i]);
		}
	}
	fprintf(fptr, "\"%02d %s %04d\",\"%04d\",\"%02d:%02d\",\"%02d:%02d\"\n",
	store->date.dd, string, store->date.yyyy, store->employeeID,
	store->startTime.hour, store->startTime.minute,
	store->endTime.hour,store->endTime.minute);
}
int handleStrings(int index, char *argv[], int i) {
	char dateArr[11];
	char *token;
	char delim[] = { "/:" };

	if (index == 1) {
		strcpy(dateArr, argv[i]);
		token = strtok(dateArr, delim);
		return strtol(token, NULL, 10);
	}
	else {
		strcpy(dateArr, argv[i]);
		token = strtok(NULL, delim);
		return strtol(token, NULL, 10);
	}
}
Week 21 Assignment.cpp
Displaying Week 21 Assignment.cpp.
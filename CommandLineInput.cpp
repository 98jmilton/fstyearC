// CommandLineInput.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 4474)




typedef struct worktime
{
	int employeeID;
	date date;
	time startTime;
	time endTime;
} work;

typedef struct date {
	int dd;
	int mm;
	int yyyy;
}date;
typedef struct time {
	int hour;
	int minute;
}time;

FILE *openFile(char *dir, char *mode);

void controlArgs(int argc, char *argv[]); 
int convert(char *argv[], int i); 
void send(FILE *fptr); 
void writeto(int argc, char *argv[], char *directory);
int controlStrings(int argc, char *argv[], int i);
void search(char *directory, char *argv[]); 
void print(char *directory);	


int main()
{
	if (argc > 1) {
		controlArgs(argc, argv);
	}


	return 0;
	}

FILE *openFile(char *dir, char *mode) {
	FILE *fptr;
	fptr = fopen(dir, mode);
	if (fptr == NULL) {
		printf("Could not open file or directory. Exiting.\n");
		exit(1);
	}
	else {
		return fptr;
	}

}

void controlArgs(int argc, char *argv[]) {

	store = (work*)malloc(sizeof(work));

	char *mode[] = { "\\a", "\\s","\\p" }; 
	char customDir[80];
	strcpy(customDir, argv[1]);

	const int baseArg = 3;

	if ((argc - baseArg) % 4 == 0 && strcmp(argv[2], mode[0]) == 0) 
	{
		writeto(argc, argv, customDir); 
	}
	else if (argc == 4)
	{
		if (strcmp(argv[2], mode[0]) == 0) { 
			puts("Not enough parameters, try again. Exiting...");
			exit(1);
		}
		if (strcmp(argv[2], mode[1]) == 0) {
			search(customDir, argv);
		}
		else if (strcmp(argv[2], mode[2]) == 0) { 
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
		printf("Enter data in the form:\log.txt \\a 1234 01/01/2018 12:34 12:34\n");
		printf("Multiples of 4 are allowed after \\a therefore incomplete records are not allowed.\n");
		printf("or\log.txt \\p 1234\n");
		printf("or\log.txt \\s 1234\n\n");
	}
}

int controlStrings(int index, char *argv[], int i) {
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

}

void writeto(int argc, char *argv[], char *directory) {

	FILE *fptr = NULL;
	char *mode[] = { "\\a", "\\s","\\p" }; 

	if (argc > 1) {
		strcpy(directory, argv[1]);
		fptr = openFile(directory, "a");
	
	}
	for (int i = 3; i < argc; i++)
		if ((i % 4) == 3 && strlen(argv[i]) == 4) {
			store->employeeID = convert(argv, i);
			printf("Employee ID is: %d\n", store->employeeID);
		}
		else if (i % 4 == 0 && strlen(argv[i]) <= 10) { 
			int index = 1; 		
			store->date.dd = controlStrings(index, argv, i);
			index++;
			store->date.mm = controlStrings(index, argv, i);
			store->date.yyyy = controlStrings(index, argv, i);

			printf("%02d/%02d/%04d\n", store->date.dd, store->date.mm, store->date.yyyy);
		}
		else if (i % 4 == 1 && strlen(argv[i]) <= 5) { 
			int index = 1;
			store->startTime.hour = controlStrings(index, argv, i);
			index++;
			store->startTime.minute = controlStrings(index, argv, i);

			printf("%02d:%02d\n", store->startTime.hour, store->startTime.minute);
		}
		else if (i % 4 == 2 && strlen(argv[i]) <= 5) { 
			int index = 1;
			store->endTime.hour = controlStrings(index, argv, i);
			index++;
			store->endTime.minute = controlStrings(index, argv, i);

			printf("%02d:%02d\n", store->endTime.hour, store->endTime.minute);
			if (fptr != NULL) {
				send(fptr);
			}
		}
		else
			puts("Error in append function.\n");

	}
	fclose(fptr);
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
		store->endTime.hour, store->endTime.minute);
}
// AgeSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

FILE *fopen(char *fileName, char *mode);
void closeFile(FILE *ptr);
struct result {
	char last[40];
	char first[40];
	int age;
	char email[40];
	struct result *next;
};

struct result *resultFirst, *resultCurrent, *resultNew;
FILE *fptr;
int age;

void Age();
int main()
{
	resultFirst = NULL;
	char trash[1000];
	const char delim[2] = ",";
	char *tkn;
	char temp[1000];
	resultFirst = NULL;

	fptr = fopen("C://Users//gameh//Desktop//Lectures//Assignments//Programming//AgeSearch//users.txt", "r");

	fscanf(fptr, "%s", trash, 300);
	while (!feof(fptr)) {
		fgets(temp, 300, fptr);
		while (!feof(fptr)) {
			if (fgets(temp, 300, fptr) != NULL) {
				tkn = strtok(temp, delim);
				while (tkn != NULL) {

					resultNew = (struct result *)malloc(sizeof(struct result));


					strcpy(resultNew->last, tkn);
					tkn = strtok(NULL, delim);

					strcpy(resultNew->first, tkn);
					tkn = strtok(NULL, delim);

					resultNew->age = atoi(tkn);
					tkn = strtok(NULL, delim);

					strcpy(resultNew->email, tkn);
					tkn = strtok(NULL, delim);



				}
				if (resultFirst == NULL) {
					resultFirst = resultNew;
					resultCurrent = resultNew;
				}
				else {
					resultCurrent->next = resultNew;
					resultCurrent = resultNew;
				}
			}
		}

	}
	resultCurrent->next = NULL;

	do {
		printf("\nEnter which age you want to search for(Enter 0 to end):");
		scanf_s("%d", &age);
		if (age != 0) {
			Age();
		}
		else {
			return 0;
		}
	} while (age != 0);

	fclose(fptr);
	free(resultFirst);
	free(resultCurrent);
	free(resultNew);
	return 0;
}

FILE *fopen(char *fileName, char *mode) {
	FILE *ptr;
	ptr = fopen(fileName, mode);
	if (ptr == NULL) {
		printf("File couldn't be open\n");
	}
	return (ptr);
}

void closeFile(FILE *ptr) {
	fclose(ptr);
}

void Age() {

	if (resultFirst == NULL) {
		puts("Error in printing ages");
	}
	else {
		resultCurrent = resultFirst;
		do {
			if (age == resultCurrent->age) {
				printf("\nFound this person aged %d : %s %s", age, resultCurrent->first, resultCurrent->last);

			}
		} while ((resultCurrent = resultCurrent->next) != NULL);
	}
}
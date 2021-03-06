// ContactDetails.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 4474)

int linelong = 0; 
int lineCount = 0; 

typedef struct
{
	char *UserName;
	char *firstName;
	char *lastName;
	char *displayName;
	char *jobTitle;
	char *department;
	char *officeNumber;
	char *officePhone;
	char *mobilePhone;
	char *fax;
	char *address;
	char *city;
	char *state;
	char *zip;
	char *country;
} contact;

FILE *openFile(char *directory, char *mode);
void readFile(FILE *fptr, contact arr[]);
void closeFile(FILE *fptr);
void Check(FILE *fptr);
void print(contact *theContact);


FILE *fptr;
contact *detailsArr;

int main()
{

	fptr = fopen("C:\\Users\\gameh\\Desktop\\Lectures\\Assignments\\Programming\\ContactDetails\\data.txt", "r");
	Check(fptr);
	detailsArr = (contact*)malloc(lineCount * sizeof(contact));
	closeFile(fptr);

	fptr = fopen("C:\\Users\\gameh\\Desktop\\Lectures\\Assignments\\Programming\\ContactDetails\\data.txt", "r");
	readFile(fptr, detailsArr);
	print(detailsArr);
	closeFile(fptr);

	free(detailsArr);
	detailsArr = NULL;
}

FILE *openFile(char *directory, char *mode)
{
	FILE *fptr;
	fptr = fopen(directory, mode);

	if (fptr == NULL)
	{
		printf("Error openning file!\n");
		exit(1);
	}
	return fptr;
}

void readFile(FILE *fptr, contact arr[])
{
	char fileLine[300];
	fgets(fileLine, 300, fptr);
	char *token;
	char delim[] = { "," };
	int i = 0;

	puts("Reading in file...");
	while (!feof(fptr))
	{
		int j = 0;
		fgets(fileLine, 300, fptr);
		token = strtok(fileLine, delim);

		while (token != NULL)
		{
			switch (j)
			{
			case 0:
				(arr + i)->UserName = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->UserName, token);
				j++;
				continue;
				break;
			case 1:
				token = strtok(NULL, delim);
				(arr + i)->firstName = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->firstName, token);
				j++;
				continue;
				break;
			case 2:
				token = strtok(NULL, delim);
				(arr + i)->lastName = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->lastName, token);
				j++;
				continue;
				break;
			case 3:
				token = strtok(NULL, delim);
				(arr + i)->displayName = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->displayName, token);
				j++;
				continue;
				break;
			case 4:
				token = strtok(NULL, delim);
				(arr + i)->jobTitle = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->jobTitle, token);
				j++;
				continue;
				break;
			case 5:
				token = strtok(NULL, delim);
				(arr + i)->department = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->department, token);
				j++;
				continue;
				break;
			case 6:
				token = strtok(NULL, delim);
				(arr + i)->officeNumber = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->officeNumber, token);
				j++;
				continue;
				break;
			case 7:
				token = strtok(NULL, delim);
				(arr + i)->officePhone = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->officePhone, token);
				j++;
				continue;
				break;
			case 8:
				token = strtok(NULL, delim);
				(arr + i)->mobilePhone = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->mobilePhone, token);
				j++;
				continue;
				break;
			case 9:
				token = strtok(NULL, delim);
				(arr + i)->fax = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->fax, token);
				j++;
				continue;
				break;
			case 10:
				token = strtok(NULL, delim);
				(arr + i)->address = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->address, token);
				j++;
				continue;
				break;
			case 11:
				token = strtok(NULL, delim);
				(arr + i)->city = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->city, token);
				j++;
				continue;
				break;
			case 12:
				token = strtok(NULL, delim);
				(arr + i)->state = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->state, token);
				j++;
				continue;
				break;
			case 13:
				token = strtok(NULL, delim);
				(arr + i)->zip = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->zip, token);
				j++;
				continue;
				break;
			case 14:
				token = strtok(NULL, delim);
				(arr + i)->country = (char*)malloc(sizeof(char*)*strlen(token) + 1);
				strcpy((arr + i)->country, token);
				j++;
				continue;
				break;
			default:
				i++;
				token = NULL;
				break;
			}


		}

		puts("Done.\n");
	}
}

void closeFile(FILE *fptr)
{
	fclose(fptr);
}

void Check(FILE *fptr)
{
	char fileLine[300];
	fgets(fileLine, 300, fptr); 

	int i = 0;
	while (!feof(fptr)) 
	{
		fgets(fileLine, 300, fptr);
		if (strlen(fileLine) > linelong)
		{
			linelong = strlen(fileLine);
		}
		lineCount++;
	}
}

void print(contact *theContact)
{

	for (int i = 0; i < lineCount; i++)
	{
		printf("Username: %s\nFirst Name: %s\nLast Name: %s\n",
			(theContact + i)->UserName, (theContact + i)->firstName,
			(theContact + i)->lastName);
		printf("Display Name: %s\Job Title: %s\nDepartment: %s\n",
			(theContact + i)->displayName, (theContact + i)->jobTitle,
			(theContact + i)->department);
		printf("Office Number: %s\nOffice Phone: %s\nMobile Phone: %s\n",
			(theContact + i)->officeNumber, (theContact + i)->officePhone,
			(theContact + i)->mobilePhone);
		printf("Fax: %s\nAddress: %s\nCity: %s\n",
			(theContact + i)->fax, (theContact + i)->address,
			(theContact + i)->city);
		printf("State: %s\nZIP: %s\nCountry: %s\n\n",
			(theContact + i)->state, (theContact + i)->zip,
			(theContact + i)->country);
	}
}
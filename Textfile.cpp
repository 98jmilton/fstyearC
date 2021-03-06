#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

FILE *openFile(char *fileName, char *mode);
void closeFile(FILE *fptr);

struct date
{
	int day, month, year;
};

struct student
{
	int studentID;
	char firstname[20];
	char lastname[20];
	char courseID[10];
	int year;
	struct date registrationDate;
	struct date dateOfBirth;
	int averageGrade;
};

int main()
{
	FILE *Textfile;
	Textfile = fopen("C:\\Users\\gameh\\Desktop\\Lectures\\Assignments\\Programming\\Textfile\\students.txt", "r");
	struct student file[2];
	for (int i = 0; i < 2; i++) {
		fscanf_s(Textfile, "%d %s %s %s %d %d %d %d %d %d", &file[i].studentID, &file[i].firstname, 20, &file[i].lastname, 20, &file[i].courseID, 20, &file[i].registrationDate.day, &file[i].registrationDate.month, &file[i].registrationDate.year, &file[i].dateOfBirth.day, &file[i].dateOfBirth.month, &file[i].dateOfBirth.year);
	}
	int num;
	srand(time(NULL));
	for (int i = 0; i < 2; i++) {
		num = (rand() % 100) + 1;
		file[i].averageGrade = num;
		printf(" %d %s %s %s %d %d %d %d %d %d %d \n", file[i].studentID, file[i].firstname, file[i].lastname, file[i].courseID, file[i].registrationDate.day, file[i].registrationDate.month, file[i].registrationDate.year, file[i].dateOfBirth.day, file[i].dateOfBirth.month, file[i].dateOfBirth.year, file[i].averageGrade);
	}
	fclose(Textfile);
	Textfile = fopen("C:\\Users\\gameh\\Desktop\\Lectures\\Assignments\\Programming\\Textfile\\students.txt", "w");
	for (int i = 0; i < 2; i++) {
		fprintf_s(Textfile, "%d %s %s %s %d %d %d %d %d %d %d \n", file[i].studentID, file[i].firstname, file[i].lastname, file[i].courseID, file[i].registrationDate.day, file[i].registrationDate.month, file[i].registrationDate.year, file[i].dateOfBirth.day, file[i].dateOfBirth.month, file[i].dateOfBirth.year, file[i].averageGrade);
		printf(" %d %s %s %s %d %d %d %d %d %d %d \n", file[i].studentID, file[i].firstname, file[i].lastname, file[i].courseID, file[i].registrationDate.day, file[i].registrationDate.month, file[i].registrationDate.year, file[i].dateOfBirth.day, file[i].dateOfBirth.month, file[i].dateOfBirth.year, file[i].averageGrade);
	}
	fclose(Textfile);
	return 0;
}

FILE * openFile(char *fileName, char *mode)
{

	FILE *fptr;
	fopen_s(&fptr, fileName, mode);

	if (fptr == NULL)
	{
		printf("Error opening this file! \n");
	}

	return fptr;
}

void closeFile(FILE *fptr)
{
	fclose(fptr);
}

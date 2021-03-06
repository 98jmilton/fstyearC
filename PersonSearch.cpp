// PersonSearch.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 4474)




FILE *openFile(char *fileName, char *mode);
void closeFile(FILE *ptr);
void searchName(char string[]);
void searchCompany(char string[]);
void searchCity(char string[]);
void searchCountry(char string[]);
void searchState(char string[]);
void searchZip(char string[]);

struct people {
	char firstName[30];
	char lastName[30];
	char companyName[30];
	char address[30];
	char city[30];
	char county[30];
	char state[30];
	char zip[30];
	char phone1[30];
	char phone2[30];
	char email[30];
	char web[30];
};


struct people data[1000];
FILE *fptr;

int main()
{
	int i, j;
	char temp[1000];
	char temp2[100];
	char *token;
	const char s[2] = ",";
	int choice;
	char search[20];

	fptr = fopen("C:\\Users\\gameh\\Desktop\\Lectures\\Assignments\\Programming\\PersonSearch\\us-500b.txt", "r");


	if (fptr != NULL) {
		for (i = 0; i < 1; i++) { fscanf(fptr, "%s", temp2, 200); }

		while (!feof(fptr)) {
			fgets(temp, 200, fptr);
			i = 0; j = 0;

			while (!feof(fptr)) {
				if (fgets(temp, 200, fptr) != NULL) {
					while (temp[j] != '\0')
					{
						if (temp[j] == '-' || temp[j] == '"') temp[j] = ' ';
						j++;
					}


					token = strtok(temp, s);
					while (token != NULL)
					{
						strcpy(data[i].firstName, token);
						token = strtok(NULL, s);

						strcpy(data[i].lastName, token);
						token = strtok(NULL, s);

						strcpy(data[i].companyName, token);
						token = strtok(NULL, s);

						strcpy(data[i].address, token);
						token = strtok(NULL, s);

						strcpy(data[i].city, token);
						token = strtok(NULL, s);

						strcpy(data[i].county, token);
						token = strtok(NULL, s);

						strcpy(data[i].state, token);
						token = strtok(NULL, s);

						strcpy(data[i].zip, token);
						token = strtok(NULL, s);

						strcpy(data[i].phone1, token);
						token = strtok(NULL, s);

						strcpy(data[i].phone2, token);
						token = strtok(NULL, s);

						strcpy(data[i].email, token);
						token = strtok(NULL, s);

						strcpy(data[i].web, token);
						token = strtok(NULL, s);
					}
					i++;
				}
			}
		}
	}

	printf("Options: \n 1-Search by name \n 2-Search by company \n 3-Search by city \n 4-Search by county \n 5-Search by state \n 6-Search by zip \n 0-Exit...\n ");
	scanf("%d", &choice);
	int k = 0;

	do {
		switch (choice) {
		case 1:
			printf("Enter all <or part> of the first name or surname you are looking for: \n");
			scanf("%s", search, 30);
			j = 0;
			while (search[j]) {
				search[j] = tolower(search[j]);
				j++;
			}
			searchName(search);
			break;

		case 2:
			printf("Enter all <or part> of the company name you are looking for: \n");
			scanf("%s", search, 30);
			j = 0;
			while (search[j]) {
				search[j] = tolower(search[j]);
				j++;
			}
			searchCompany(search);
			break;
		case 3:
			printf("Enter all <or part> of the city name you are looking for: \n");
			scanf("%s", search, 30);
			j = 0;
			while (search[j]) {
				search[j] = tolower(search[j]);
				j++;
			}
			searchCity(search);
			break;
		case 4:
			printf("Enter all <or part> of the county name you are looking for: \n");
			scanf("%s", search, 30);
			j = 0;
			while (search[j]) {
				search[j] = tolower(search[j]);
				j++;
			}
			searchCountry(search);
			break;

		case 5:
			printf("Enter all <or part> of the state name you are looking for: \n");
			scanf("%s", search, 30);
			j = 0;
			while (search[j]) {
				search[j] = tolower(search[j]);
				j++;
			}
			searchState(search);
			break;
		case 6:
			printf("Enter all <or part> of the ZIP  you are looking for: \n");
			scanf("%s", search, 30);
			j = 0;
			while (search[j]) {
				search[j] = tolower(search[j]);
				j++;
			}
			searchZip(search);
			break;
		default:
			printf("Incorrect Input");
			break;

		}
		printf(" \n \n Options: \n 1- search by name \n 2- search by company \n 3-search by city \n 4- search by county \n 5- search by state \n 6- search by zip \n 0- exit...\n ");
		scanf("%d", &choice);
	} while (choice != 0);


	fclose(fptr);
}

FILE *openFile(char *fileName, char *mode) {
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

void searchName(char string[]) {
	int i;
	int j = 0;
	char *ptr;
	char *ptr2;
	char storage[30];
	char storage2[30];
	for (i = 0; i < 500; i++) {
		strcpy(storage, data[i].firstName);
		while (storage[j]) {
			storage[j] = tolower(storage[j]);
			j++;
		}
		strcpy(storage2, data[i].lastName);
		j = 0;
		while (storage2[j]) {
			storage2[j] = tolower(storage2[j]);
			j++;
		}

		ptr = strstr(storage, string);
		ptr2 = strstr(storage2, string);
		if (ptr != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n\n\n ", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
		if (ptr2 != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n\n\n ", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
	}

}

void searchCompany(char string[]) {
	int i;
	int j = 0;
	char *ptr;
	char storage[80];
	for (i = 0; i < 500; i++) {
		strcpy(storage, data[i].companyName);
		while (storage[j]) {
			storage[j] = tolower(storage[j]);
			j++;
		}
		ptr = strstr(storage, string);
		if (ptr != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n \n\n", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
	}

}

void searchCity(char string[]) {
	int i;
	int j = 0;
	char *ptr;
	char storage[80];
	for (i = 0; i < 500; i++) {
		strcpy(storage, data[i].city);
		while (storage[j]) {
			storage[j] = tolower(storage[j]);
			j++;
		}
		ptr = strstr(storage, string);
		if (ptr != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n \n\n", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
	}

}

void searchCountry(char string[]) {
	int i;
	int j = 0;
	char *ptr;
	char storage[80];
	for (i = 0; i < 500; i++) {
		strcpy(storage, data[i].county);
		while (storage[j]) {
			storage[j] = tolower(storage[j]);
			j++;
		}
		ptr = strstr(storage, string);
		if (ptr != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n \n\n", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
	}

}

void searchState(char string[]) {
	int i;
	int j = 0;
	char *ptr;
	char storage[80];
	for (i = 0; i < 500; i++) {
		strcpy(storage, data[i].state);
		while (storage[j]) {
			storage[j] = tolower(storage[j]);
			j++;
		}
		ptr = strstr(storage, string);
		if (ptr != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n \n\n", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
	}

}

void searchZip(char string[]) {
	int i;
	int j = 0;
	char *ptr;
	char storage[80];
	for (i = 0; i < 500; i++) {
		strcpy(storage, data[i].zip);
		while (storage[j]) {
			storage[j] = tolower(storage[j]);
			j++;
		}
		ptr = strstr(storage, string);
		if (ptr != NULL) {
			printf("First Name: %s \nLast Name: %s \nCompany Name: %s\nAddress Name: %s\nCity: %s\nCounty: %s\nState: %s\nZip: %s\nPhone#1: %s \nPhone #2: %s\nemail: %s\nweb: %s\n \n\n", data[i].firstName, data[i].lastName, data[i].companyName, data[i].address, data[i].city,
				data[i].county, data[i].state, data[i].zip, data[i].phone1, data[i].phone2, data[i].email, data[i].web);
		}
	}

}



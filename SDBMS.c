#include <stdio.h>
#include <conio.h>

void addStudent();
void studentrecord();
void searchstudent();
void deletestudent();

typedef struct student {
	char first_name[20];
	char last_name[20];
	int studentNumber;
	char grade[10];
	char vill[20];
	float per;
} student;

void main() {
	int choice ;
	while (choice != 5) {
		printf("\t\t\t=====Student Database System=====");
		printf("\n\n\n\t\t\t\t  1.Add Student Record\n");
		printf("\t\t\t\t  2.Student Records\n");
		printf("\t\t\t\t  3.Search Student\n");
		printf("\t\t\t\t  4.Delete Student Record\n");
		printf("\t\t\t\t  5.Exit\n");
		printf("\t\t\t\t  _____________________________\n");
		printf("\t\t\t\t  \n");
		scanf("%d", &choice);
		switch(choice) {
		case(1):
			clrscr();
			addStudent();
			clrscr();
			break;
		case(2):
			clrscr();
			studentrecord();
			printf("\n\n\t\t\t\tPress any key to exit\n");
			getch();
			clrscr();
			break;
		case(3):
			clrscr();
			searchstudent();
			printf("\n\n\t\t\t\tPress any key to exit\n");
			getch();
			clrscr();
			break;
		case(4):
			clrscr();
			deletestudent();
			printf("\n\n\t\t\t\tPress any key to exit\n");
			getch();
			clrscr();
			break;
		}
	}
}

void addStudent() {
	char another;
	FILE *fp;
	student info;

	do {
		clrscr();

		printf("\t\t\t\t=====Add Student Info=====\n\n\n");
		fp = fopen("studentinfo.txt", "a");

		if (fp == NULL) {
			fprintf(stderr,"Can't Open File");
		}

		printf("\n\t\t\tEnter First Name. : ");
		scanf("%s", info.first_name);
		printf("\n\t\t\tEnter Last Name.  : ");
		scanf("%s", info.last_name);
		printf("\n\t\t\tEnter Roll Number : ");
		scanf("%d", &info.studentNumber);
		printf("\n\t\t\tEnter Class.      : ");
		scanf("%s", info.grade);
		printf("\n\t\t\tEnter Addrress.   : ");
		scanf("%s", info.vill);
		printf("\n\t\t\tEnter Percentage. : ");
		scanf("%f", &info.per);
		printf("\n\t\t\t_____________________________\n");


		printf("Records Stroed Successfully\n");

		fwrite(&info, sizeof(student),1,fp);
		fclose(fp);
		printf("\t\t\tDo you want to add another record?(y/n) : ");
		scanf(" %c", &another);
	} while(another == 'y' || another == 'Y');
}

void studentrecord() {
	FILE *fp;
	student info;
	fp = fopen("studentinfo.txt","r");
	printf("\t\t\t\t=====Student Record=====\n\n\n");
	if (fp == NULL) {
		printf("No records found!\n");
		getch();
		return;
	}
	else {
		printf("\t\t\t\tRecords\n");
		printf("\t\t\t\t___________\n\n");
	}
	while(fread(&info,sizeof(student), 1, fp)) {
		printf("\n\t\t\t\tStudent Name : %s %s", info.first_name, info.last_name);
		printf("\n\t\t\t\tStudent No.  : %d", info.studentNumber);
		printf("\n\t\t\t\tGrade        : %s", info.grade);
		printf("\n\t\t\t\tAddress      : %s", info.vill);
		printf("\n\t\t\t\tPercentage   : %f", info.per);
		printf("\n\t\t\t\t_____________________");
	}

	fclose(fp);
	getch();
}

void searchstudent() {
	FILE *fp;
	student info;
	int stuNumber, found = 0;
	fp = fopen("studentinfo.txt", "r");
	printf("\t\t\t\t=====Search Student=====\n\n\n");
	printf("t\t\tEnter Student Number: ");
	scanf("%d", &stuNumber);

	while(fread(&info,sizeof(student), 1, fp)) {
		if (info.studentNumber == stuNumber) {
			found = 1;
			printf("\n\t\t\t\tStudent Name : %s %s", info.first_name, info.last_name);
			printf("\n\t\t\t\tStudent No.  : %d", info.studentNumber);
			printf("\n\t\t\t\tGrade        : %s", info.grade);
			printf("\n\t\t\t\tAddress      : %s", info.vill);
			printf("\n\t\t\t\tPercentage   : %f", info.per);
			printf("\n\t\t\t\t_____________________");
		}
	}
	if (!found) {
		printf("\n\t\t\tRecord Not Found\n");
	}
	fclose(fp);
	getch();
}

void deletestudent() {
	FILE *fp, *fp1;
	student info;
	int stuNumber, found = 0;
	printf("\t\t\t\t=====Search Student=====\n\n\n");
	fp = fopen("studentinfo.txt", "r");
	fp1 = fopen("temp.txt", "w");
	printf("\t\t\tEnter Student Number to delete: ");
	scanf("%d", &stuNumber);

	if (fp == NULL || fp1 == NULL) {
		fprintf(stderr,"Can't Open File\n");
		getch();
		return;
	}
	while(fread(&info, sizeof(student), 1, fp)) {
		if (info.studentNumber == stuNumber) {
			found =1;
		}
		else {
			fwrite(&info, sizeof(student), 1, fp1);
		}
	}
	
	fclose(fp);
	fclose(fp1);
	if (found) {
		remove("studentinfo.txt");
		rename("temp.txt", "studentinfo.txt");
		printf("\n\t\t\tStudent Deleted Successfully\n");
	}
	if (!found) {
		printf("\n\t\t\tRecord Not Found\n");
	}
	getch();
}

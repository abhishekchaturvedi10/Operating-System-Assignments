#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LIMIT 100

void Edit() {

	int fd;
 
 	struct flock lock;

	char filename[MAX_LIMIT], str[MAX_LIMIT];

	printf("\nEnter the filename : ");

	fflush(stdout);

	scanf("%s", filename);
	
	memset (&lock, 0, sizeof(lock));
	
	fd = open (filename, O_WRONLY | O_CREAT, 0777);
	
	fcntl (fd, F_GETLK, &lock);
	
	if(lock.l_type == F_WRLCK) {
		
		printf("\nWARNING! \nFile is locked \n\n");
		
		memset (&lock, 0, sizeof(lock));
		
		lock.l_type = F_UNLCK;
 
 		fcntl (fd, F_SETLKW, &lock);
	}
	else {	
		
		memset (&lock, 0, sizeof(lock));
	
		printf ("\nlocking\n");
 
 		lock.l_type = F_WRLCK;
 	
 		fcntl (fd, F_SETLKW, &lock);
 	}

	FILE *fp;

	fp = fopen(filename, "a");

	printf("\nEnter the data to add to the file and save using / \n\n");

	scanf("%s", str);

	while (strcmp(str, "/") != 0) {

		fprintf(fp, "%s ", str);

		scanf("%s", str);
	}
	
	printf ("\nunlocking\n");
	
	lock.l_type = F_UNLCK;
 
 	fcntl (fd, F_SETLKW, &lock);

 	close (fd);

	fclose(fp);
}

void Display() {

	char filename[MAX_LIMIT];

	printf("\nEnter the filename : ");

	scanf("%s", filename);

	FILE *fp;

	fp = fopen(filename, "r");

	while (fp == NULL) {

		printf("\nFile doest not exist. Enter again! \n\n");

		scanf("%s", filename);

		fp = fopen(filename, "r");
	}

	printf("\n");

	char ch;

	ch = fgetc(fp);

	while (ch != EOF) {

		printf("%c", ch);

		ch = fgetc(fp);
	}

	printf("\n");

	fclose(fp);
}

int main() {

	int input;

	printf("\n\n *************  WELCOME TO TEXT EDITOR  ************* \n\n");

	while (1) {

		printf("\n1. EDIT \n2. DISPLAY\n3. EXIT\n\n");

		scanf("%d", &input);

		if (input == 1)
			Edit();

		else if (input == 2)
			Display();

		else if (input == 3)
			exit(0);

		else
			printf("\nIncorrect Input \n");
	}

	return 0;
}
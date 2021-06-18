#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int rollNo, marks1, marks2, marks3, marks4, r;
	char sec[1];

	pid_t pid = fork();

	if (pid == 0) {

		FILE *fp;

		fp = fopen("csv-os-2.csv", "rt");

		if (fp == NULL) {

			printf("File could not be opened!");
			perror("fopen");
			exit(1);
		}

		printf("\nCHILD PROCESS\n\n");

		while ((r = fscanf(fp, "%d %s %d %d %d %d", &rollNo, &sec[0], &marks1, &marks2, &marks3, &marks4)) != EOF) {

			if (*sec == 'A') {

				double avg = (double)(marks1 + marks2 + marks3 + marks4);
				avg /= 4;

				printf("Roll no. : %d  ", rollNo);
				printf("section : %s  ", sec);
				printf("marks1 : %d  ", marks1);
				printf("marks2 : %d  ", marks2);
				printf("marks3 : %d  ", marks3);
				printf("marks4 : %d  ", marks4);
				printf("average marks : %lf\n", avg);
			}
		}

		fclose(fp);

		exit(0);
	}
	else if (pid > 0) {

		waitpid(-1, NULL, 0);

		FILE *fp;

		fp = fopen("csv-os-2.csv", "rt");

		if (fp == NULL) {

			printf("File could not be opened!");
			perror("fopen");
			exit(1);
		}

		printf("\nPARENT PROCESS\n\n");

		while ((r = fscanf(fp, "%d %s %d %d %d %d", &rollNo, &sec[0], &marks1, &marks2, &marks3, &marks4)) != EOF) {

			if (*sec == 'B') {

				double avg = (double)(marks1 + marks2 + marks3 + marks4);
				avg /= 4;

				printf("Roll no. : %d  ", rollNo);
				printf("section : %s  ", sec);
				printf("marks1 : %d  ", marks1);
				printf("marks2 : %d  ", marks2);
				printf("marks3 : %d  ", marks3);
				printf("marks4 : %d  ", marks4);
				printf("average marks : %lf\n", avg);
			}
		}

		fclose(fp);
	}
	else {

		printf("Child forking process failed!");

		exit(1);
	}

	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

char *nameList[1500];
int size = 0;

void readFile (char *filename)
{
        FILE *fp;

	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Please specify a valid file.\n");
		exit(-1);
	}

	size_t len = 0;
	ssize_t read;

	while ((read = getdelim(&nameList[size], &len, '\n', fp)) != -1)
	{
		size++;
		len = 0;
	}

	fclose(fp);
}

void bubbleSort ()
{
	for (int i = 0; i < size - 1; i++)
	{
		bool hasSorted = false;

		for (int j = 0; j < size - i - 1; j++)
		{
			int compare = strcasecmp(nameList[j], nameList[j + 1]);

			if (compare > 0)
			{
				char *temp = nameList[j];
				nameList[j] = nameList[j + 1];
				nameList[j + 1] = temp;
				hasSorted = true;
			}
		}

		if (!hasSorted)
			break;
	}
}

void printList ()
{
	for (int i = 0; i < size; i++)
		printf("%s", nameList[i]);

	printf("Sorted %i names.\n", size);
}

void saveFile (char *filename)
{
	FILE *fp;

	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("Please specify a valid file to save result to.\n");
		exit(-1);
	}

	for (int i = 0; i < size; i++)
	{
		fprintf(fp, "%s", nameList[i]);
	}

	fclose(fp);

	printf("Sorted %i names and saved them to %s.\n", size, filename);
}

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please provide a file to sort.\n");
		printf("Valid arguments are:\n");
		printf("1: File with names sort (Required)\n");
		printf("2: File to save result (Optional)\n");
		printf("If argument 2 is not provided result will be printed to the terminal.\n");
		exit(-1);
	}

	readFile(argv[1]);

	bubbleSort();

	if (argc < 3)
		printList();
	else
		saveFile(argv[2]);

	return 0;
}

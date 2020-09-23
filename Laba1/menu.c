#include "menu.h"
int readInt(char sentence[])
{
	int number = -1;
	printf("������� %s: ", sentence);
	if (scanf_s("%d", &number) != 1)
	{
		fprintf(stderr, "\nError: �����������!\n");
		exit(1);
	}
	return number;
}
void readString(char string[], char sentence[], size_t size)
{
	printf("������� %s(max %d ����): ", sentence, size - 1);
	gets_s(string, 256);
	while (strlen(string) == 0) gets_s(string, 256);
	if (strlen(string) > size)
	{
		fprintf(stderr, "\nError: ����������� � ������!\n");
		exit(1);
	}
}
customer1 getCustomer(fileNames* names, index1* theIndex)                                           //get-m
{
	int indexesSize = 0;
	customer1 person = { -1, 0, "", -1, -1, -1 };
	index1* indexes = readIndexesFromFile(&indexesSize, names->index);
	if (indexesSize == 0)
	{
		printf("\n������ ������� ���.\n");
		return person;
	}
	printIndexes(indexes, indexesSize, "��������");
	int pKey = readInt("��������");
	int i = getIndexByPKey(indexes, indexesSize, pKey);
	if (i == -1)
	{
		printf("\n������ � ���� pKey=%d �� ������!\n", pKey);
		free(indexes);
		return person;
	}
	person = readStudentFromFile(indexes[i].address, names->data);
	*theIndex = indexes[i];
	allCustomers(person);
	free(indexes);
	return person;
} 
tour1 getTours(fileNames* names, index1* tourIndex)                                                    //get-s
{
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	int size = person.numberOfTours;
	tour1 trip = { -1, -1, "","","", -1, -1 };
	if (size < 0) return trip;
	if (size == 0)
	{
		printf("\n� ����� ������� ��� �����\n");
		return trip;
	}
	index1* indexes = (index1*)malloc(size * sizeof(index1));
	tour1* trips = allToursOfCustomer(person, indexes, names->tour);
	if (indexes == NULL || trips == NULL)
	{
		fprintf(stderr, "\nError!\n");
		exit(1);
	}
	printIndexes(indexes, size, "�����");
	int pKey = readInt("pKey ����");
	int i = getIndexByPKey(indexes, size, pKey);
	if (i == -1)
	{
		printf("\n��� � ����� pKey=%d �� ������!\n", pKey);
	}
	else
	{
		trip = trips[i];
		*tourIndex = indexes[i];
		printTours(trip);
	}
	free(indexes);
	free(trips);

	return trip;
}
customer1 createCustomer()
{
	printf("\n������� �������.\n");
	char name[256];
	readString(name, "��� �������", LEN);
	int phone = readInt("�������");
	customer1 person = { 0, 1, "", phone, -1, 0 };
	_memccpy(person.name, name, '\0', strlen(name));

	return person;
}
void insertCustomer(fileNames* names)                                                                 //insert-m
{
	customer1 person = createCustomer();
	index1 index;
	index = insertCustomerToFile(person, names->data, names->index, names->rubbish);
	addIndexToFileEnd(index, names->index);
	printf("��������!\n");
}
tour1 createTour()
{
	printf("\n��������� ���.\n");
	char Name[256];
	char b[256];
	char e[256];
	readString(Name, "�������� ����", LEN);
	readString(b, "������ ����", LEN / 2);
	readString(e, "���� ����", LEN / 2);
	int price = readInt("����");
	tour1 trip = { 0, 1, "","","", price, -1 };
	_memccpy(trip.tourName, Name, '\0', strlen(Name));
	_memccpy(trip.tourName, b, '\0', strlen(b));
	_memccpy(trip.tourName, e, '\0', strlen(e));

	return trip;
}
void insertTour(fileNames* names)                                                                 //insert-s
{
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	if (person.pKey <= 0) return;
	tour1 trip = createTour();
	insertToursToFile(trip, &person, names->tour, names->tourRubbish);
	updateCustomer(person, theIndex.address, names->data);
	printf("��� �������!\n");
}
void clearString(char string[])
{
	size_t size = strlen(string);
	for (size_t i = 0; i < size; i++) string[i] = '\0';
}
void updateTheCustomer(fileNames* names)                                                                 //update-m
{
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	if (person.pKey <= 0) return;
	int sum = 0;
	while (1)
	{
		printf("\n1)��� �������.\n2)�������.\n");
		int number = readInt("������� ����� ����, ��� ������ ��������");
		switch (number)
		{
		case 1:
		{
			char newName[256];
			clearString(person.name);
			readString(newName, "����� ���", LEN);
			_memccpy(person.name, newName, '\0', strlen(newName));
			sum++;
			continue;
		}
		break;
		case 2:
		{
			person.phone = readInt("����� �������");
			sum++;
			continue;
		}
		break;
		default:
		{
			if (sum != 0) updateCustomer(person, theIndex.address, names->data);
			printf("������ ��������!\n");
			return;
		}
		break;
		}
	}
}
void updateTheTour(fileNames* names)                                                                     //update-s
{
	index1 theIndex;
	tour1 trip = getTours(names, &theIndex);
	if (trip.pKey <= 0) return;
	int sum = 0;
	while (1)
	{
		printf("\n1)��������.\n2)������.\n3)�����.\n4)����.\n");
		int number = readInt("������� ����� ����, ��� ������ ��������");
		switch (number)
		{
		case 1:
		{
			char newName[256];
			clearString(trip.tourName);
			readString(newName, "����� ��������", LEN);
			_memccpy(trip.tourName, newName, '\0', strlen(newName));
			sum++;
			continue;
		}
		break;
		case 2:
		{
			char newbegin[256];
			clearString(trip.begin);
			readString(newbegin, "����� ��������", LEN / 2);
			_memccpy(trip.begin, newbegin, '\0', strlen(newbegin));
			sum++;
			continue;
		}
		break;
		case 3:
		{
			char newend[256];
			clearString(trip.end);
			readString(newend, "����� ��������", LEN / 2);
			_memccpy(trip.end, newend, '\0', strlen(newend));
			sum++;
			continue;
		}
		break;
		case 4:
		{
			trip.price = readInt("����� ����");
			sum++;
			continue;
		}
		break;
		default:
		{
			if (sum != 0) updateTour(trip, theIndex.address, names->tour);
			printf("The progress was updated!\n");
			return;
		}
		break;
		}
	}
}
void deleteCustomer(fileNames* names)                                                                              //del-m
{
	printf("\n�������� �������.");
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	if (person.pKey <= 0) return;
	removeCustomer(person, theIndex.address, names->data, names->tour, names->tourRubbish);
	removeIndex(theIndex.pKey, names->index, names->rubbish);
	printf("������ ������!!\n");
}
void deleteTour(fileNames* names)//del-s
{
	printf("\n�������� ����.");
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	int size = person.numberOfTours;
	if (size < 0) return;
	if (size == 0)
	{
		printf("\n� ����� ������� ��� �����.\n");
		return;
	}
	index1* indexes = (index1*)malloc(size * sizeof(index1));
	tour1* trips = allToursOfCustomer(person, indexes, names->tour);
	if (indexes == NULL || trips == NULL)
	{
		fprintf(stderr, "\nError!\n");
		exit(1);
	}
	printIndexes(indexes, size, "����");
	int pKey = readInt("pKey ����");
	int i = getIndexByPKey(indexes, size, pKey);
	if (i == -1)
	{
		printf("\n��� � ����� pKey=%d �� ������!\n", pKey);
	}
	else
	{
		removeTour(&person, indexes, trips, indexes[i].pKey, names->tour, names->tourRubbish);
		updateCustomer(person, theIndex.address, names->data);
		printf("��� ������!\n");
	}
	free(indexes);
	free(trips);
}
void UtilityCustomer(fileNames* names)                                                                        //ut-m
{
	printf("\n������� �������.\n");
	printAllDateFromIndexFile(names->index);
	printAllDateFromRubbishFile(names->rubbish);
	printAllDateFromDataFile(names->data);
}
void UtilityTour(fileNames* names)                                                                          //ut-s
{
	printf("\n������� ����.\n");
	printAllDateFromTourRubbishFile(names->tourRubbish);
	printAllDateFromTourFile(names->tour);
}
void printNamesOfFiles(fileNames* names)
{
	printf("\nAll files:\n1)%s.\n2)%s.\n3)%s.\n4)%s\n5)%s.\n\n", names->index, names->data, names->tour, names->rubbish, names->tourRubbish);
}
void printNumber(fileNames* names)
{
	printNamesOfFiles(names);
	while (1)
	{
		int numberOfFile = readInt("������� ����� �����, ��� � ������ ���������� ���������");
		char line[] = { "����������: %d\n\n" };
		switch (numberOfFile)
		{
		case 1: printf(line, getNumberOfItemsInFile(names->index));
			break;
		case 2: printf(line, getNumberOfItemsInFile(names->data));
			break;
		case 3: printf(line, getNumberOfItemsInFile(names->tour));
			break;
		case 4: printf(line, getNumberOfItemsInFile(names->rubbish));
			break;
		case 5: printf(line, getNumberOfItemsInFile(names->tourRubbish));
			break;
		default: return;
			break;
		}
	}
}
void printMenu(int showMenu)
{
	if (showMenu == 0) printf("\nMenu:\n1) Insert-m.\n2) Get-m.\n3) Update-m.\n4) Del-m.\n5) Ut-m.\n6) Insert-s.\n7) Get-s.\n8) Update-s.\n9) Del-s.\n10)Ut-s.\n11)Get number of Items.\n");
	
}
void menu()
{
	fileNames names = { "customers.ind", "customers.fl", "tours.bin", "listOfRubbish.bin", "listOftourRubbish.bin" };
	int showMenu = 0;
	while (1)
	{
		printMenu(showMenu);
		printf("\n");
		int number = readInt("����� ������ ���� ��� ��� ������");
		switch (number)
		{
		case 1: insertCustomer(&names);
			break;
		case 2:
		{
			index1 theIndex;
			customer1 person = getCustomer(&names, &theIndex);
		}
		break;
		case 3: updateTheCustomer(&names);
			break;
		case 4: deleteCustomer(&names);
			break;
		case 5: UtilityCustomer(&names);
			break;
		case 6: insertTour(&names);
			break;
		case 7:
		{
			index1 theIndex;
			tour1 trip = getTours(&names, &theIndex);
		}
		break;
		case 8: updateTheTour(&names);
			break;
		case 9: deleteTour(&names);
			break;
		case 10: UtilityTour(&names);
			break;
		case 11: printNumber(&names);
			break;
		default: return;
			break;
		}
	}
}
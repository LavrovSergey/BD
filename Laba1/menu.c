#include "menu.h"

customer1 getCustomer(files* names, index1* theIndex)                                           //get-m
{
	int indexesSize = 0;
	customer1 person = { -1, 0, "", -1, -1, -1 };
	index1* indexes = IndexesFromFile(&indexesSize, names->index);
	if (indexesSize == 0)
	{
		printf("\nТакого клиента нет.\n");
		return person;
	}
	printIndexes(indexes, indexesSize, "клиентов");
	int pKey = readInt("клиентов");
	int i = getIndexByPKey(indexes, indexesSize, pKey);
	if (i == -1)
	{
		printf("\nКлиент с таим pKey=%d не найден!\n", pKey);
		free(indexes);
		return person;
	}
	person = readStudentFromFile(indexes[i].address, names->data);
	*theIndex = indexes[i];
	allCustomers(person);
	free(indexes);
	return person;
} 
tour1 getTours(files* names, index1* tourIndex)                                                    //get-s
{
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	int size = person.numberOfTours;
	tour1 trip = { -1, -1, "","","", -1, -1 };
	if (size < 0) return trip;
	if (size == 0)
	{
		printf("\nУ этого клиента нет туров\n");
		return trip;
	}
	index1* indexes = (index1*)malloc(size * sizeof(index1));
	tour1* trips = allToursOfCustomer(person, indexes, names->tour);
	if (indexes == NULL || trips == NULL)
	{
		fprintf(stderr, "\nError!\n");
		exit(1);
	}
	printIndexes(indexes, size, "туров");
	int pKey = readInt("pKey тура");
	int i = getIndexByPKey(indexes, size, pKey);
	if (i == -1)
	{
		printf("\nТур с таким pKey=%d не найден!\n", pKey);
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
void insertCustomer(files* names)                                                                 //insert-m
{
	customer1 person = createCustomer();
	index1 index;
	index = CustomerToFile(person, names->data, names->index, names->rubbish);
	IndexToFileEnd(index, names->index);
	printf("Записали!\n");
}
void insertTour(files* names)                                                                 //insert-s
{
	index1 theIndex;
	customer1 person = getCustomer(names, &theIndex);
	if (person.pKey <= 0) return;
	tour1 trip = createTour();
	insertToursToFile(trip, &person, names->tour, names->tourRubbish);
	updateCustomer(person, theIndex.address, names->data);
	printf("Тур записан!\n");
}
customer1 createCustomer()
{
	printf("\nСоздаем клиента.\n");
	char name[256];
	readString(name, "Имя Фамилия", length);
	int phone = readInt("Телефон");
	customer1 person = { 0, 1, "", phone, -1, 0 };
	_memccpy(person.name, name, '\0', strlen(name));

	return person;
}
tour1 createTour()
{
	printf("\nДобавляем тур.\n");
	char Name[256], b[256], e[256];
	readString(Name, "Название тура", length);
	readString(b, "Начало тура", length / 2);
	readString(e, "Конц тура", length / 2);
	int price = readInt("Цена");
	tour1 trip = { 0, 1, "","","", price, -1 };
	_memccpy(trip.tourName, Name, '\0', strlen(Name));
	_memccpy(trip.tourName, b, '\0', strlen(b));
	_memccpy(trip.tourName, e, '\0', strlen(e));

	return trip;
}

void clearString(char string[])
{
	size_t size = strlen(string);
	for (size_t i = 0; i < size; i++) string[i] = '\0';
}

void printNamesOfFiles(files* names)
{
	printf("\nAll files:\n1)%s.\n2)%s.\n3)%s.\n4)%s\n5)%s.\n\n", names->index, names->data, names->tour, names->rubbish, names->tourRubbish);
}

void printNumber(files* names)
{
	printNamesOfFiles(names);
	while (1)
	{
		int numberOfFile = readInt("Введите номер файла, что б узнать количество елементов");
		char line[] = { "Количество: %d\n\n" };
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

void readString(char string[], char sentence[], size_t size)
{
	printf("Введите %s(max %d букв): ", sentence, size - 1);
	gets_s(string, 256);
	while (strlen(string) == 0) gets_s(string, 256);
	if (strlen(string) > size)
	{
		fprintf(stderr, "\nError: переборщили с длиной!\n");
		exit(1);
	}
}
int readInt(char sentence[])
{
	int number = -1;
	printf("Введите %s: ", sentence);
	if (scanf_s("%d", &number) != 1)
	{
		fprintf(stderr, "\nError: неправильно!\n");
		exit(1);
	}
	return number;
}
void menu()
{
	files names = { "customers.ind", "customers.fl", "tours.bin", "listOfRubbish.bin", "listOftourRubbish.bin" };
	int showMenu = 0;
	while (1)
	{
		printMenu(showMenu);
		printf("\n");
		int number = readInt("номер пункта меню для его выбора");
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
#include "base.h"

void Fileerrors(FILE* file, int numberOfError, char functionName[])
{
	fprintf(stderr, "Error%d in function '%s'!...\n", numberOfError, functionName);
	if (file != NULL) fclose(file);
	exit(1);
}
void writeIndexesInFile(index1* indexesTable, int size, char indexFileName[])
{
	char functionName[] = "writeIndexesInFile";
	checkFileEmptiness(indexFileName);
	FILE* file;
	fopen_s(&file, indexFileName, "wb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	fwrite(&size, sizeof(int), 1, file);
	if (fwrite(indexesTable, sizeof(index1), size, file) != size)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	fclose(file);
}
customer1 readStudentFromFile(int address, char dataFileName[])
{
	char functionName[] = "readStudentFromFile";
	checkFileEmptiness(dataFileName);
	FILE* file;
	fopen_s(&file, dataFileName, "rb");
	customer1 person = { -1, -1, "", -1, -1, -1 };
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return person;
	}
	fseek(file, (address * sizeof(customer1) + sizeof(int)), SEEK_SET);
	if (fread(&person, sizeof(customer1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return person;
	}
	fclose(file);

	return person;
}
index1* readIndexesFromFile(int* readSize, char indexFileName[])
{
	char functionName[] = "readIndexesFromFile";
	checkFileEmptiness(indexFileName);
	FILE* file;
	fopen_s(&file, indexFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return NULL;
	}
	if (fread(readSize, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return NULL;
	}
	if (readSize == 0) return NULL;
	index1* indexesTable = (index1*)malloc(*readSize * sizeof(index1));
	if (indexesTable == NULL)
	{
		Fileerrors(file, 3, functionName);
		return NULL;
	}
	if (fread(indexesTable, sizeof(index1), *readSize, file) != *readSize)
	{
		Fileerrors(file, 4, functionName);
		return NULL;
	}
	fclose(file);

	return indexesTable;
}
void addIndexToFileEnd(index1 theIndex, char indexFileName[])
{
	char functionName[] = "appendIndexToFile";
	checkFileEmptiness(indexFileName);
	FILE* file;
	fopen_s(&file, indexFileName, "ab");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	if (fwrite(&theIndex, sizeof(index1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	fclose(file);
	changeNumberOfItemsInFile(indexFileName, 1);
}
int getIndexByPKey(index1* indexesTable, int size, int pKey)
{
	for (int i = 0; i < size; i++)
	{
		if (indexesTable[i].pKey == pKey) return i;
	}

	return -1;
}
void printIndexes(index1* indexesTable, int size, char typeName[])
{
	printf("\nВсе pKeys %s: ", typeName);
	for (int i = 0; i < size - 1; i++)
	{
		printf("%d, ", indexesTable[i].pKey);
	}
	if (size - 1 >= 0) printf("%d.\n", indexesTable[size - 1].pKey);
	if (size == 0) printf("Нету pKeys.\n");
}
void allCustomers(customer1 person)
{
	printf("\nИмя Фамилия: %s, Телефон: %d, Количество туров: %d.\n", person.name, person.phone, person.numberOfTours);
}
void printTours(tour1 trip)
{
	printf("\nНазвание: %s, \nНачало: %s, \nКонец: %s, Цена: %d.\n", trip.tourName,trip.begin,trip.end, trip.price);
}
void createSourceFile(char fileName[])
{
	char functionName[] = "createSourceFile";
	FILE* file;
	fopen_s(&file, fileName, "wb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	int number = 0;
	if (fwrite(&number, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	fclose(file);
}
void changeNumberOfItemsInFile(char fileName[], int step)
{
	char functionName[] = "changeNumberOfItemsInFile";
	checkFileEmptiness(fileName);
	FILE* file;
	fopen_s(&file, fileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	int number = 0;
	if (fread(&number, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	number += step;
	fseek(file, 0L, SEEK_SET);
	if (fwrite(&number, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 3, functionName);
		return;
	}
	fclose(file);
}
index1 insertCustomerToFile(customer1 person, char dataFileName[], char indexFileName[], char rubbishFileName[])
{
	char functionName[] = "insertStudentToFile";
	index1 theIndex = getAddressOfEmptySpace(dataFileName, indexFileName, rubbishFileName), err = { -1, -1 };
	person.pKey = theIndex.pKey;
	checkFileEmptiness(dataFileName);
	FILE* file;
	fopen_s(&file, dataFileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return err;
	}
	fseek(file, (theIndex.address * sizeof(customer1) + sizeof(int)), SEEK_SET);
	if (fwrite(&person, sizeof(customer1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return err;
	}
	fclose(file);
	changeNumberOfItemsInFile(dataFileName, 1);

	return theIndex;
}
index1 getAddressOfEmptySpace(char dataFileName[], char indexFileName[], char rubbishFileName[])
{
	index1 newIndex = { -1, -1 };
	newIndex = findRubbishIndex(rubbishFileName, indexFileName);
	if (newIndex.address == -1 || newIndex.pKey == -1)
	{
		newIndex = createNewIndex(dataFileName, indexFileName);
	}

	return newIndex;
}
index1 findRubbishIndex(char rubbishFileName[], char indexFileName[])
{
	char functionName[] = "findRubbishIndex";
	index1 err = { -1, -1 };
	checkFileEmptiness(rubbishFileName);
	FILE* file;
	fopen_s(&file, rubbishFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return err;
	}
	int size = 0;
	if (fread(&size, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return err;
	}
	if (size > 0)
	{
		index1* indexes = (index1*)malloc(size * sizeof(index1));
		if (indexes == NULL)
		{
			Fileerrors(file, 3, functionName);
			return err;
		}
		if (fread(indexes, sizeof(index1), size, file) != size)
		{
			Fileerrors(file, 4, functionName);
			return err;
		}
		fclose(file);
		FILE* writeFile;
		fopen_s(&writeFile, rubbishFileName, "wb");
		if (writeFile == NULL)
		{
			Fileerrors(writeFile, 5, functionName);
			return err;
		}
		size--;
		if (fwrite(&size, sizeof(int), 1, writeFile) != 1)
		{
			Fileerrors(writeFile, 6, functionName);
			return err;
		}
		if (fwrite(indexes, sizeof(index1), size, writeFile) != size)
		{
			Fileerrors(writeFile, 7, functionName);
			return err;
		}
		index1 theIndex = indexes[size];
		theIndex.pKey = getLastPKey(indexFileName) + 1;
		free(indexes);
		fclose(writeFile);

		return theIndex;
	}
	fclose(file);

	return err;
}
index1 createNewIndex(char dataFileName[], char indexFileName[])
{
	index1 newIndex = { getLastPKey(indexFileName) + 1, getAddressOfEnd(dataFileName, sizeof(int), sizeof(customer1)) };

	return newIndex;
}

int getLastPKey(char indexFileName[])
{
	int lastPKey = -1;
	int size = 0;
	index1* indexes = readIndexesFromFile(&size, indexFileName);
	if (size != 0)
	{
		lastPKey = indexes[size - 1].pKey;
	}
	else
	{
		lastPKey = 0;
	}
	free(indexes);

	return lastPKey;
}
int getAddressOfEnd(char fileName[], unsigned long sizeOfBeginDate, unsigned long sizeOfOtherDate)
{
	char functionName[] = "getAddressOfEnd";
	checkFileEmptiness(fileName);
	FILE* file;
	fopen_s(&file, fileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return -1;
	}
	fseek(file, 0L, SEEK_END);
	int address = (ftell(file) - sizeOfBeginDate) / sizeOfOtherDate;
	fclose(file);

	return address;
}
int isEmpty(char fileName[])
{
	FILE* file;
	fopen_s(&file, fileName, "rb");
	if (file == NULL) return 0;
	int number;
	int size = fread(&number, sizeof(int), 1, file);
	fclose(file);

	return size;
}
void checkFileEmptiness(char fileName[])
{
	if (isEmpty(fileName) == 0)
	{
		createSourceFile(fileName);
	}
}

void removeIndex(int pKey, char indexFileName[], char rubbishFileName[])
{
	int size = 0;
	index1* indexes = readIndexesFromFile(&size, indexFileName);
	if (indexes == NULL) return;
	int pointer = 0;
	for (int i = 0; i < size; i++)
	{
		if (indexes[i].pKey == pKey)
		{
			pointer = i;
			break;
		}
	}
	addIndexToFileEnd(indexes[pointer], rubbishFileName);
	for (int i = pointer; i < size - 1; i++)
	{
		indexes[i] = indexes[i + 1];
	}
	size--;
	writeIndexesInFile(indexes, size, indexFileName);
	free(indexes);
}
void updateCustomer(customer1 newPerson, int address, char dataFileName[])
{
	char functionName[] = "updateStudent";
	checkFileEmptiness(dataFileName);
	FILE* file;
	fopen_s(&file, dataFileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	fseek(file, (address * sizeof(customer1) + sizeof(int)), SEEK_SET);
	customer1 person = { 0, 0, "none", 0, -1, 0 };
	if (fread(&person, sizeof(customer1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	newPerson.pKey = person.pKey;
	fseek(file, -1 * (long)sizeof(customer1), SEEK_CUR);
	if (fwrite(&newPerson, sizeof(customer1), 1, file) != 1)
	{
		Fileerrors(file, 3, functionName);
		return;
	}
	fclose(file);
}

void removeCustomer(customer1 person, int address, char dataFileName[], char tourFileName[], char tourRubbishFileName[])
{
	char functionName[] = "removeCustomer";
	checkFileEmptiness(dataFileName);
	FILE* file;
	fopen_s(&file, dataFileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	fseek(file, (address * sizeof(customer1) + sizeof(int)), SEEK_SET);
	person.status = 0;
	if (fwrite(&person, sizeof(customer1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	fclose(file);
	changeNumberOfItemsInFile(dataFileName, -1);
	if (person.headerAddress != -1)
	{
		removeAllTours(person, tourFileName, tourRubbishFileName);
	}
}
int getAddressForTour(char tourFileName[], char tourRubbishFileName[])
{
	char functionName[] = "getAddressForTour";
	checkFileEmptiness(tourRubbishFileName);
	FILE* file;
	fopen_s(&file, tourRubbishFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return -1;
	}
	int size = 0;
	if (fread(&size, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return -1;
	}
	if (size > 0)
	{
		int* addresses = (int*)malloc(size * sizeof(int));
		if (addresses == NULL)
		{
			Fileerrors(file, 3, functionName);
			return -1;
		}
		if (fread(addresses, sizeof(int), size, file) != size)
		{
			Fileerrors(file, 4, functionName);
			return -1;
		}
		fclose(file);
		FILE* writeFile;
		fopen_s(&writeFile, tourRubbishFileName, "wb");
		if (writeFile == NULL)
		{
			Fileerrors(writeFile, 5, functionName);
			return -1;
		}
		size--;
		if (fwrite(&size, sizeof(int), 1, writeFile) != 1)
		{
			Fileerrors(writeFile, 6, functionName);
			return -1;
		}
		if (fwrite(addresses, sizeof(int), size, writeFile) != size)
		{
			Fileerrors(writeFile, 7, functionName);
			return -1;
		}
		int address = addresses[size];
		free(addresses);
		fclose(writeFile);
		return address;
	}
	fclose(file);

	return getAddressOfEnd(tourFileName, sizeof(int), sizeof(tour1));
}
int getLastTourKey(char tourFileName[], customer1 person)
{
	if (person.headerAddress == -1) return 1;
	char functionName[] = "getLastTourKey";
	checkFileEmptiness(tourFileName);
	FILE* file;
	fopen_s(&file, tourFileName, "rb");
	tour1 trip = { 0, 0, "None", "None", "None", 0, -1 };
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return -1;
	}
	fseek(file, (person.headerAddress * sizeof(tour1) + sizeof(int)), SEEK_SET);
	if (fread(&trip, sizeof(tour1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return -1;
	}
	fclose(file);

	return trip.pKey + 1;
}
void insertToursToFile(tour1 trip, customer1* person, char tourFileName[], char tourRubbishFileName[])//inserts progress of student in empty space of file and add its address to student
{
	char functionName[] = "insertProgressToFile";
	int address = getAddressForTour(tourFileName, tourRubbishFileName);
	trip.pKey = getLastTourKey(tourFileName, *person);
	trip.nextAddress = person->headerAddress;
	person->headerAddress = address;
	person->numberOfTours++;
	checkFileEmptiness(tourFileName);
	FILE* file;
	fopen_s(&file, tourFileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	fseek(file, (address * sizeof(tour1) + sizeof(int)), SEEK_SET);
	if (fwrite(&trip, sizeof(tour1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	fclose(file);
	changeNumberOfItemsInFile(tourFileName, 1);
}
tour1* allToursOfCustomer(customer1 person, index1 indexes[], char tourFileName[])
{
	char functionName[] = "allToursOfCustomer";
	tour1* allTours = (tour1*)malloc(person.numberOfTours * sizeof(tour1));
	if (allTours == NULL)
	{
		Fileerrors(NULL, 1, functionName);
		return NULL;
	}
	if (indexes == NULL)
	{
		Fileerrors(NULL, 2, functionName);
		return NULL;
	}
	checkFileEmptiness(tourFileName);
	FILE* file;
	fopen_s(&file, tourFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 3, functionName);
		return NULL;
	}
	int address = person.headerAddress;
	for (int i = 0; i < person.numberOfTours; i++)
	{
		indexes[i].address = address;
		fseek(file, (address * sizeof(tour1) + sizeof(int)), SEEK_SET);
		if (fread(&allTours[i], sizeof(tour1), 1, file) != 1)
		{
			Fileerrors(file, 4, functionName);
			return NULL;
		}
		indexes[i].pKey = allTours[i].pKey;
		address = allTours[i].nextAddress;
		if (address == -1) break;
	}
	fclose(file);

	return allTours;
}
void updateTour(tour1 tourProgress, int address, char tourFileName[])
{
	char functionName[] = "updateProgress";
	checkFileEmptiness(tourFileName);
	FILE* file;
	fopen_s(&file, tourFileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	fseek(file, (address * sizeof(tour1) + sizeof(int)), SEEK_SET);
	tour1 trip = { 0, 1, "","","", 0, -1 };
	if (fread(&trip, sizeof(tour1), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	tourProgress.pKey = trip.pKey;
	fseek(file, -1 * (long)sizeof(tour1), SEEK_CUR);
	if (fwrite(&tourProgress, sizeof(tour1), 1, file) != 1)
	{
		Fileerrors(file, 3, functionName);
		return;
	}
	fclose(file);
}
void addAddressOfTourToRubbish(char progRubbishFileName[], int address)
{
	char functionName[] = "addAddressOfTourToRubbish";
	checkFileEmptiness(progRubbishFileName);
	FILE* file;
	fopen_s(&file, progRubbishFileName, "ab");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	if (fwrite(&address, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	fclose(file);
	changeNumberOfItemsInFile(progRubbishFileName, 1);
}
void removeTour(customer1* person, index1 indexes[], tour1 trip[], int pKey, char tourFileName[], char tourRubbishFileName[])
{
	for (int i = 0; i < person->numberOfTours; i++)
	{
		if (trip[i].pKey == pKey)
		{
			if (i - 1 >= 0)
			{
				trip[i - 1].nextAddress = trip[i].nextAddress;
				updateTour(trip[i - 1], indexes[i - 1].address, tourFileName);
			}
			else
			{
				person->headerAddress = trip[i].nextAddress;
			}
			person->numberOfTours--;
			trip[i].status = 0;
			updateTour(trip[i], indexes[i].address, tourFileName);
			addAddressOfTourToRubbish(tourRubbishFileName, indexes[i].address);
			changeNumberOfItemsInFile(tourFileName, -1);
			break;
		}
	}
}
void removeAllTours(customer1 person, char tourFileName[], char tourRubbishFileName[])
{
	char functionName[] = "removeAllProgresses";
	checkFileEmptiness(tourFileName);
	FILE* file;
	fopen_s(&file, tourFileName, "rb+");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	int address = person.headerAddress;
	tour1 trip = { -1, 0, "","","", -1, -1 };
	for (int i = 0; i < person.numberOfTours; i++)
	{
		fseek(file, (address * sizeof(tour1) + sizeof(int)), SEEK_SET);
		if (fread(&trip, sizeof(tour1), 1, file) != 1)
		{
			Fileerrors(file, 2, functionName);
			return;
		}
		trip.status = 0;
		addAddressOfTourToRubbish(tourRubbishFileName, address);
		fseek(file, (address * sizeof(tour1) + sizeof(int)), SEEK_SET);
		if (fwrite(&trip, sizeof(tour1), 1, file) != 1)
		{
			Fileerrors(file, 3, functionName);
			return;
		}
		address = trip.nextAddress;
		if (address == -1) break;
	}
	fclose(file);
	changeNumberOfItemsInFile(tourFileName, -1 * person.numberOfTours);
}
void printAllDateFromIndexFile(char indexFileName[])
{
	char functionName[] = "printAllDateFromIndexFile";
	printf("\nФайл: %s\n", indexFileName);
	int readSize = 0;
	checkFileEmptiness(indexFileName);
	FILE* file;
	fopen_s(&file, indexFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	if (fread(&readSize, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	printf("Размер=%d.\n", readSize);
	for (int i = 0;; i++)
	{
		if (feof(file) != 0) break;
		index1 theIndex = { -1, -1 };
		if (fread(&theIndex, sizeof(index1), 1, file) != 1)
		{
			if (feof(file) != 0) break;
			Fileerrors(file, 3 + i, functionName);
			return;
		}
		printf("%d) pKey=%d, адресс=%d.\n", i, theIndex.pKey, theIndex.address);
	}
	fclose(file);
}
void printAllDateFromDataFile(char dataFileName[])
{
	char functionName[] = "printAllDateFromDataFile";
	printf("\nФайл: %s\n", dataFileName);
	checkFileEmptiness(dataFileName);
	FILE* file;
	fopen_s(&file, dataFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return;
	}
	int readSize = 0;
	if (fread(&readSize, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	printf("Размер=%d.\n", readSize);
	for (int i = 0;; i++)
	{
		if (feof(file) != 0) break;
		customer1 person = { -1, -1, "",-1, -1, -1 };
		if (fread(&person, sizeof(customer1), 1, file) != 1)
		{
			if (feof(file) != 0) break;
			Fileerrors(file, 3 + i, functionName);
			return;
		}
		printf("%d) pKey=%d, статус=%d, имя=%s, телефон=%d, hAddress=%d, количество туров=%d.\n", i, person.pKey, person.status, person.name, person.phone, person.headerAddress, person.numberOfTours);
	}

	fclose(file);
}
void printAllDateFromRubbishFile(char rubbishFileName[])
{
	printAllDateFromIndexFile(rubbishFileName);
}
void printAllDateFromTourFile(char tourFileName[])
{
	char functionName[] = "printAllDateFromTourFile";
	printf("\nФайл: %s\n", tourFileName);
	checkFileEmptiness(tourFileName);
	FILE* file;
	fopen_s(&file, tourFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 3, functionName);
		return NULL;
	}
	int readSize = 0;
	if (fread(&readSize, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	printf("Размер=%d.\n", readSize);
	for (int i = 0;; i++)
	{
		if (feof(file) != 0) break;
		tour1 prog = { -1, -1, "", -1, -1 };
		if (fread(&prog, sizeof(tour1), 1, file) != 1)
		{
			if (feof(file) != 0) break;
			Fileerrors(file, 3 + i, functionName);
			return;
		}
		printf("%d) pKey=%d, статус=%d, название=%s,начало=%s,конец=%s, цена=%d, nextAddress=%d.\n", i, prog.pKey, prog.status, prog.tourName, prog.begin, prog.end, prog.price, prog.nextAddress);
	}
	fclose(file);
}
void printAllDateFromTourRubbishFile(char RubbishFileName[])
{
	char functionName[] = "printAllDateFromTourRubbishFile";
	printf("\nФайл: %s\n", RubbishFileName);
	checkFileEmptiness(RubbishFileName);
	FILE* file;
	fopen_s(&file, RubbishFileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 3, functionName);
		return NULL;
	}
	int readSize = 0;
	if (fread(&readSize, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return;
	}
	printf("Размер=%d.\n", readSize);
	for (int i = 0;; i++)
	{
		if (feof(file) != 0) break;
		int address = 0;
		if (fread(&address, sizeof(int), 1, file) != 1)
		{
			if (feof(file) != 0) break;
			Fileerrors(file, 3 + i, functionName);
			return;
		}
		printf("%d) адресс=%d.\n", i, address);
	}
	fclose(file);
}
int getNumberOfItemsInFile(char fileName[])
{
	char functionName[] = "getSizeOfItemsInFile";
	checkFileEmptiness(fileName);
	FILE* file;
	fopen_s(&file, fileName, "rb");
	if (file == NULL)
	{
		Fileerrors(file, 1, functionName);
		return -1;
	}
	int number = 0;
	if (fread(&number, sizeof(int), 1, file) != 1)
	{
		Fileerrors(file, 2, functionName);
		return -1;
	}
	fclose(file);

	return number;
}
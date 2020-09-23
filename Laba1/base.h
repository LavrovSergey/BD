#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define length 51

typedef struct Index
{
	int pKey;
	int address;

} index1;
typedef struct Customer
{
	int pKey;
	int status;
	char name[length];
	int phone;
	int headerAddress;
	int numberOfTours;

} customer1;
typedef struct Tour
{
	int pKey;
	int status;
	char tourName[length];
	char begin[length / 2];
	char end[length / 2];
	int price;
	int nextAddress;

} tour1;
void writeIndexesInFile(index1* indexesTable, int size, char indexFileName[]);
index1* readIndexesFromFile(int* readSize, char indexFileName[]);
void addIndexToFileEnd(index1 theIndex, char indexFileName[]);
int getIndexByPKey(index1* indexesTable, int size, int pKey);
void printIndexes(index1* indexesTable, int size, char typeName[]);
void allCustomers(customer1 person);
void printTours(tour1 progress);
void createSourceFile(char fileName[]);
void changeNumberOfItemsInFile(char fileName[], int step);
index1 insertCustomerToFile(customer1 person, char dataFileName[], char indexFileName[], char rubbishFileName[]);
index1 getAddressOfEmptySpace(char dataFileName[], char indexFileName[], char rubbishFileName[]);
index1 findRubbishIndex(char rubbishFileName[], char indexFileName[]);
index1 createNewIndex(char dataFileName[], char indexFileName[]);
int getAddressOfEnd(char fileName[], unsigned long sizeOfBeginDate, unsigned long sizeOfOtherDate);
int getLastPKey(char indexFileName[]);
int isEmpty(char fileName[]);
void checkFileEmptiness(char fileName[]);
customer1 readStudentFromFile(int address, char dataFileName[]);
void updateCustomer(customer1 newPerson, int address, char dataFileName[]);
void removeIndex(int pKey, char indexFileName[], char rubbishFileName[]);
void removeCustomer(customer1 person, int address, char dataFileName[], char progFileName[], char progRubbishFileName[]);
int getAddressForTour(char progFileName[], char progRubbishFileName[]);
int getLastTourKey(char progFileName[], customer1 person);
void insertToursToFile(tour1 prog, customer1* person, char progFileName[], char progRubbishFileName[]);
tour1* allToursOfCustomer(customer1 person, index1 indexes[], char progFileName[]);
void updateTour(tour1 newProgress, int address, char progFileName[]);
void addAddressOfTourToRubbish(char progRubbishFileName[], int address);
void removeTour(customer1* person, index1 indexes[], tour1 progresses[], int pKey, char progFileName[], char progRubbishFileName[]);
void removeAllTours(customer1 person, char progFileName[], char progRubbishFileName[]);
void printAllDateFromIndexFile(char indexFileName[]);
void printAllDateFromDataFile(char dataFileName[]);
void printAllDateFromRubbishFile(char rubbishFileName[]);
void printAllDateFromTourFile(char progFileName[]);
void printAllDateFromTourRubbishFile(char progRubbishFileName[]);
int getNumberOfItemsInFile(char fileName[]);
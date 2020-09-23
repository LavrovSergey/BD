#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define length 51


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
typedef struct Index
{
	int pKey;
	int address;

} index1;
void IndexesInFile(index1* indexesTable, int size, char indexFileName[]);
index1* IndexesFromFile(int* readSize, char indexFileName[]);
void IndexToFileEnd(index1 theIndex, char indexFileName[]);
int getIndexByPKey(index1* idTable, int size, int pKey);
void printIndexes(index1* indexesTable, int size, char typeName[]);
void allCustomers(customer1 person);
void printTours(tour1 progress);
void createFile(char fileName[]);
void checkFileEmptiness(char fileName[]);
customer1 readStudentFromFile(int address, char dataFileName[]);
void updateCustomer(customer1 newPerson, int address, char dataFileName[]);
void removeIndex(int pKey, char indexFileName[], char rubbishFileName[]);
void removeCustomer(customer1 person, int address, char dataFileName[], char progFileName[], char progRubbishFileName[]);
int getAddressForTour(char progFileName[], char progRubbishFileName[]);
int getLastTourKey(char progFileName[], customer1 person);
void changeNumberOfItemsInFile(char fileName[], int step);
index1 CustomerToFile(customer1 person, char dataFileName[], char indexFileName[], char rubbishFileName[]);
index1 AddressOfEmpty(char dataFileName[], char indexFileName[], char rubbishFileName[]);
index1 RubbishID(char rubbishFileName[], char indexFileName[]);
index1 createNewIndex(char dataFileName[], char indexFileName[]);
int getAddressOfEnd(char fileName[], unsigned long sizeOfBeginDate, unsigned long sizeOfOtherDate);
int getLastPKey(char indexFileName[]);
int isEmpty(char fileName[]);
int getNumberOfItemsInFile(char fileName[]);
tour1* allToursOfCustomer(customer1 person, index1 indexes[], char progFileName[]);
void updateTour(tour1 newProgress, int address, char progFileName[]);
void addAddressOfTourToRubbish(char progRubbishFileName[], int address);
void printAllDateFromTourFile(char progFileName[]);
void printAllDateFromTourRubbishFile(char progRubbishFileName[]);
void insertToursToFile(tour1 prog, customer1* person, char progFileName[], char progRubbishFileName[]);
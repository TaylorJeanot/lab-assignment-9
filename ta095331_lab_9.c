#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order;
	struct RecordType *next;
};

// Fill out this structure
struct HashType
{
   struct RecordType *pprecord;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    int index;
    return index = x% tableSize;


}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    // call the hash function to get the index
    int index = hash(record->id, tableSize);
    // if the RecordType at that index is NULL
    struct RecordType *current = hashTable[index].pprecord;
        // set 'record' equal to the HashType pointer in the table at index
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
    if (current == NULL)
        hashTable[index].pprecord =record;
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = record;
    }
}
// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print
		printf("index = %d", i);
		struct RecordType *current = pHashArray[i].pprecord;
		if (current != NULL) {
            while ( current != NULL) {
              printf("%d, %c, %d" , current->id, current->name, current->order);
              if (current->next == NULL) {
                printf("NULL");
            }
            current = current->next;
        }
        printf("\n");
        }
    }
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	// Initialize the hash table
	struct hashType *hashTable = NULL;
    // create a variable hashTableSize and assign it a value
    int hashTableSize = 11;
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    hashTable = (struct hashType*) calloc(sizeof(struct hashType*), hashTableSize);
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    for (int i =0; i <recordSz; i++)
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    // call the display records function
    displayRecordsInHash(hashTable, hashTableSize);
    // free all the allocated memory
    free(pRecords);
    free(hashTable);

}

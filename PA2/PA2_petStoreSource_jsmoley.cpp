/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 6, 2021
Assignment: PA2 
Description: This is a program that outputs a summary report based on the status
    of a variable amount of pets held in multiple pet stores, of which are
    given in a .csv file.
Notes: N/A
*/

#include "PA2_header_jsmoley.h"

int main() 
{
    // LOCAL VARIABLE BLOCK
    vector<string> header;
    vector<string> petStoreNames;
    vector<string> petNames;
    vector<string> petTypes;
    vector<string> uniquePetStoreNames;
    vector<string> alphabetizedPetNames;
    string storeMostPets = "", petOfTheMonth = "";

    // pointers for the prior int variables
    int numMostPets = 0, averageDaysAtStore = 0;
    int* numPetsPtr = &numMostPets;
    int* averagePtr = &averageDaysAtStore;

    // pointers to dynamic integer arrays and size values for both + their pointers
    int numDaysAtStoreSize = 0;
    int* numDaysAtStoreSizePtr = &numDaysAtStoreSize;
    int* numDaysAtStorePtr = nullptr;
    int uniquePetStoreNameCountsSize = 0;
    int* uniquePetStoreNameCountsSizePtr = &uniquePetStoreNameCountsSize;
    int* uniquePetStoreNameCountsPtr = nullptr;
    
    // fstream variables
    ifstream infile;
    ofstream outfile;
    string inName = "petstoredata.csv", outName = "petreport.txt";

    // read & perform calculations only when files open up
    if(fileManagement(infile, outfile, inName, outName))
    {
        // read from file, check if data is good
        readFile(infile, header, petStoreNames, petNames,
            petTypes, numDaysAtStorePtr, numDaysAtStoreSizePtr);

        // identify the number of pet stores involved
        namePetStores(petStoreNames, uniquePetStoreNames);
        
        // count how many pets are at each store
        countPetsAtStores(petStoreNames, uniquePetStoreNames,
            uniquePetStoreNameCountsPtr, uniquePetStoreNameCountsSizePtr);

        // parse the parallel name vectors and assign most pet data
        findMostPetStore(uniquePetStoreNames, uniquePetStoreNameCountsPtr,
            storeMostPets, numPetsPtr);

        // take an average of the number of days that pets spent in stores
        averagePtr = averageDays(numDaysAtStorePtr, numDaysAtStoreSizePtr, 
                        averagePtr);

        // choose pet of the month
        petOfTheMonth = petOfTheMonthChoice(petNames);

        // alphabetize names by first letter
        alphabetizePetNames(petNames, alphabetizedPetNames);

        // write to output file
        writeFile(outfile, petNames, uniquePetStoreNames, alphabetizedPetNames, 
            averagePtr, storeMostPets, numPetsPtr, petOfTheMonth);

        // close input/output file to preserve current file states
        fileManagement(infile, outfile, inName, outName);
    }
    else
    {
        cout << "File(s) were not opened..." << endl;
        return -1;
    }

    // free up memory once pointer use is done, set pointers to null
    delete[] numDaysAtStorePtr;
    numDaysAtStorePtr = nullptr;
    delete[] uniquePetStoreNameCountsPtr;
    uniquePetStoreNameCountsPtr = nullptr;

    return 0;
}
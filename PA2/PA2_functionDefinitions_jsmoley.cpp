/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 6, 2021
Programming Assignment: PA1 
Description: This is the function definitions file for
    programming assignment 2.
Notes: N/A
*/

#include "PA2_header_jsmoley.h"

/*************************************************************
* Function: fileManagement() 
* Date Created: 10/3/21 
* Date Last Modified: 10/3/21
* Description: This function opens io files if currently 
*   closed and closes io files if currently open.
* Input parameters: fstream variables for input/output files 
* Returns: a boolean value on whether files were opened/closed
* Pre: Files in use are either not open yet, or done being used.
* Post: Files are opened for use or closed for preservation. 
*************************************************************/
bool fileManagement(ifstream& infile, ofstream& outfile, string input, string output)
{
    if(infile.is_open() == false || outfile.is_open() == false)
    {
        infile.open(input);
        outfile.open(output);

        if(infile.is_open() == true && outfile.is_open() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        infile.close();
        outfile.close();

        if(infile.is_open() == false && outfile.is_open() == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*************************************************************
* Function: readFile()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: This function reads in all the data from the
*   input file, whether it be needed or not needed for later
*   calculations.
* Input parameters: fstream variable for the input file, 
*   vectors to collect the different types of data in each 
*   line of the file 
* Returns: boolean value to tell if all data was read in correctly,
*   progression statements in the console
* Pre: open input file, but no data for use in main() yet
* Post: vectors are full of new data for manipulation step
*************************************************************/
bool readFile(ifstream& infile, vector<string>& header, 
    vector<string>& petStoreNames, vector<string>& petNames, 
    vector<string>& petTypes, int*& daysPtr, int* size)
{
    // function variable block
    string currentLine = "", currentWord = "";
    int currentInt = 0, index = 0, tempNumDays = 0;

    // read into the header vector by parsing the top row first
    getline(infile, currentLine);
    stringstream lineToParse(currentLine);

    while(getline(lineToParse, currentWord, ','))
    {
        header.push_back(currentWord);
    }
    cout << "\nProcessed " << header.size() << " header columns: " << header.at(0) << ", "
        << header.at(1) << ", " << header.at(2) << ", " << header.at(3) << "\n" << endl;

    // read in a variable number of data rows by parsing columns
    while(!infile.eof())
    {
        getline(infile, currentLine);
        stringstream lineToParse(currentLine);

        getline(lineToParse, currentWord, ',');
        petStoreNames.push_back(currentWord);
        
        getline(lineToParse, currentWord, ',');
        petNames.push_back(currentWord);

        getline(lineToParse, currentWord, ',');
        petTypes.push_back(currentWord);

        lineToParse >> currentInt;
        daysPtr = pushBackInteger(daysPtr, size, currentInt);

        index = petStoreNames.size();

        cout << "Processed a: " << petTypes.at(index - 1) << ", \"" << petNames.at(index - 1)
            << "\" ... " << daysPtr[(*size) - 1] << " day(s) on site at store \"" 
            << petStoreNames.at(index - 1) << "\"" << endl;
    }

    // send progress message to the terminal depending on size of parallel vectors
    if(index == petStoreNames.size() && index == petNames.size() 
        && index == petTypes.size() && index == *size)
    {
        cout << "All pet store data processed!\n" << endl;

        return true;
    }
    else
    {
        cout << "Error processing data...\n" << endl;

        return false;
    }
}

/*************************************************************
* Function: namePetStores
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: This function computes the true number of stores
*   included in the csv file utilizing the linear search
*   algorithm.
* Input parameters: store name vector an empty string vector
* Returns: N/A
* Pre: pet store names listed (repetitive)
* Post: unique representation for number of pet stores listed
*************************************************************/
void namePetStores(vector<string> petStoreNames, vector<string>& uniquePetStoreNames)
{
    string tempString = "";
    bool isMatch = false;

    uniquePetStoreNames.push_back(petStoreNames.at(0));

    // fill the emtpy vector with unqiue names only once, skip if already in the vector
    for(int i = 1; i < petStoreNames.size(); i++)
    {
        tempString = petStoreNames.at(i);
        
        if(!stringIsInVector(uniquePetStoreNames, tempString))
        {
            uniquePetStoreNames.push_back(tempString);
        }
        else if(stringIsInVector(uniquePetStoreNames, tempString))
        {
            continue;
        }
    }
}

/*************************************************************
* Function: countPetsAtStores()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: This function counts the number of times each
*   store name appears to later find the max pets at a store
*   as well as what store that is.
* Input parameters: string vector for unique names and an int
*   vector for counts of those names
* Returns: N/A
* Pre: true count of stores listed in the .csv
* Post: count of how many times each store is listed in .csv
*************************************************************/
void countPetsAtStores(vector<string> petStoreNames, vector<string> uniquePetStoreNames, 
    int*& countsArrayPtr, int* countsSizePtr)
{
    // fill a vector with counts of pets at each pet store
    for(int i = 0; i < uniquePetStoreNames.size(); i++)
    {
        int nameCount = 0;

        for(int j = 0; j < petStoreNames.size(); j++)
        {
            if(uniquePetStoreNames.at(i) == petStoreNames.at(j))
            {
                nameCount++;
            }
        }
        
        countsArrayPtr = pushBackInteger(countsArrayPtr, countsSizePtr, nameCount);
    }
}

/*************************************************************
* Function: findMostPetStore()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: This function utilizes the new parallel vectors
*   for unique pet stores to find the store with the most pets.
* Input parameters: string vector for unique names, int vector
*   for counts of those names, string for most store name, 
*   int for most pets count
* Returns: N/A
* Pre: lists for unique store names and how many repeats of each
* Post: name of store with most pets, how many pets that is
*************************************************************/
void findMostPetStore(vector<string> uniquePetStoreNames, int* countsArrayPtr,
    string& storeMostPets, int* numMostPtr)
{
    int mostPetsIndex = 0;

    for(int k = 1; k < uniquePetStoreNames.size(); k++)
    {
        if(countsArrayPtr[k] > countsArrayPtr[k - 1])
        {
            mostPetsIndex = k;
        }

        *numMostPtr = (*(countsArrayPtr) + mostPetsIndex);
        storeMostPets = uniquePetStoreNames.at(mostPetsIndex);
    }
}

/*************************************************************
* Function: averageDays()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: This function computes the average days that a
*   pet spends in a store across all stores listed.
* Input parameters: int vector for days at each store
* Returns: average days spent at a pet store
* Pre: list of days each pet spent at their respective store
* Post: average number of days spent in store across all stores
*************************************************************/
int* averageDays(int* daysPtr, int* size, int* average)
{
    int daysAtStoreSum = 0, iterationCount = 0;

    for(int i = 0; i < *size; i++)
    {
        daysAtStoreSum += daysPtr[i];
        iterationCount++;
    }

    *average = daysAtStoreSum / iterationCount;

    return average;
}

/*************************************************************
* Function: petOfTheMonthChoice()
* Date Created: 10/3/21 
* Date Last Modified: 10/3/21
* Description: This function chooses a random index from the
*   amount of pets listed to be pet of the month
* Input parameters: names of pets in csv file
* Returns: name of pet of the month
* Pre: list of names in a vector
* Post: single name returned to a string variable
*************************************************************/
string petOfTheMonthChoice(vector<string> petNames)
{
    int petOfTheMonthIndex = 0;

    srand(time(0));

    petOfTheMonthIndex = rand() % petNames.size();

    return petNames.at(petOfTheMonthIndex);
}

/*************************************************************
* Function: pushBackInteger()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: Utilizes pointers to populate an array using
*   dynamic memory allocation in the moment.
* Input parameters: pointer to array being populated, pointer
*   to size of array, value to be added to the array
* Returns: pointer to newly-sized array
* Pre: last value passed hasn't been added to memory of array
* Post: memory has been allocated to add the new value
*************************************************************/
int* pushBackInteger(int* originalArray, int* size, int newInt)
{   
    int tempSize = (*size) + 1; // create a new size to allocate for

    int* newArray = new int[tempSize];

    for(int i = 0; i < *size; i++)
    {
        *(newArray + i) = *(originalArray + i); // copy values to a new array
    }

    *(newArray + (tempSize - 1)) = newInt; // add the new value to the end of the array

    *size = tempSize; // assign the new size to the pointer

    delete[] originalArray;
    
    return newArray;
}

/*************************************************************
* Function: stringIsInVector()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: Searches a given vector for a given string
*   value and tells whether it is found.
* Input parameters: vector to search, string to search for
* Returns: boolean value for whether the string was found
* Pre: holding a vector and a string to search for
* Post: return the status of the string in the vector
*************************************************************/
bool stringIsInVector(vector<string> searchVector, string targetString)
{
    int index = 0;
    bool found = false;

    for(int i = 0; i < searchVector.size() && !found; i++)
    {
        if(searchVector.at(i) == targetString)
        {
            found = true;
        }
    }

    return found;
}

/*************************************************************
* Function: alphabetizePetNames()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: creates a copy of the values in an unchanging 
*   vector and sorts those values by their first letters
* Input parameters: vector to copy, destination vector to sort
* Returns: N/A
* Pre: empty destination vector and unsorted vector to copy
* Post: destination vector is populated and sorted
*************************************************************/
void alphabetizePetNames(const vector<string> petNames, 
    vector<string>& alphabetizedNames)
{
    // alert user that alphabetization has begun
    cout << "Alphabetizing pet names... ";

    // copy values into the new vector
    for(int i = 0; i < petNames.size(); i++)
    {
        alphabetizedNames.push_back(petNames.at(i));
    }

    // implement bubble sort with the vector
    int maxElement;
    int index;

    for(maxElement = alphabetizedNames.size() - 1; maxElement > 0; maxElement--)
    {
        for(index = 0; index < maxElement; index++)
        {
            if(alphabetizedNames.at(index) > alphabetizedNames.at(index + 1))
            {
                swap(alphabetizedNames.at(index), alphabetizedNames.at(index + 1));
            }
        }
    }

    // alert user that names are now alphabetized
    cout << "done:" << endl;

    // print names to console in alphabetical order
    for(int k = 0; k < alphabetizedNames.size(); k++)
    {
        string word = alphabetizedNames.at(k);

        if(word != alphabetizedNames.at((alphabetizedNames.size() - 1)))
        {
            cout << alphabetizedNames.at(k) << ", ";
        }
        else
        {
            cout << alphabetizedNames.at(k) << endl;
        }
    }
}

/*************************************************************
* Function: swap()
* Date Created:  10/6/21
* Date Last Modified: 10/6/21
* Description: A function that swaps two specific values given
* Input parameters: each value to swap
* Returns: variables with the value of the other variable
* Pre: N/A
* Post: N/A
*************************************************************/
void swap(string& a, string& b)
{
    string temp = a;
    a = b;
    b = temp;
}

/*************************************************************
* Function: writeFile()
* Date Created: 10/3/21 
* Date Last Modified: 10/6/21
* Description: This function writes all the output data to the
*   output file.
* Input parameters: fstream variable for the output file, vectors
*   and singular variables for data either read in or computed
* Returns: N/A
* Pre: open ouput file, but no data written in yet
* Post: output file is populated with the summary report
*************************************************************/
void writeFile(ofstream& outfile, vector<string> petNames, vector<string> uniquePetStoreNames,
    vector<string> alphabetizedNames, int* averagePtr, string storeMostPets, int* numMostPtr,
    string petOfTheMonth)
{
    int index = 0;

    cout << "\nGenerating summary report...\n" << endl;

    outfile << "Pet Store CSV Summary Report\n" << endl;
    outfile << "----------------------------\n\n" << endl;
    outfile << "Pet Stores: ";

    index = uniquePetStoreNames.size();

    for(int i = 0; i < uniquePetStoreNames.size(); i++)
    {
        if(i != (index - 1))
        {
            outfile << uniquePetStoreNames.at(i) << ", ";
        }
        else
        {
            outfile << uniquePetStoreNames.at(i);
        }
    }
    
    outfile << "\nTotal Number of Pets: " << petNames.size() << "\n" << endl;
    outfile << "\nPet store with the most pets: " << storeMostPets << endl;
    outfile << "Number of pets at " << storeMostPets << ": " << *numMostPtr << "\n" << endl;
    outfile << "\nPet average days on site across all stores: " << *averagePtr << endl;
    outfile << "Employee pet of the month choice: \"" << petOfTheMonth << "\"\n" << endl;

    outfile << "Current Pet Inventory: ";

    for(int i = 0; i < alphabetizedNames.size(); i++)
    {
        string word = alphabetizedNames.at(i);
        if(word != alphabetizedNames.at((alphabetizedNames.size() - 1)))
        {
            outfile << alphabetizedNames.at(i) << ", ";
        }
        else
        {
            outfile << alphabetizedNames.at(i);
        }
    }

    cout << "Done!\n" << endl;
}
/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: September 15, 2021
Programming Assignment: PA1 
Description: This is the function definitions file for a program that outputs
    a summary report based on the status of a variable amount of pets held in
    multiple pet stores, of which are given in a .csv file.
Notes: I attempted the bonus task!
*/

#include "PA1_header_jsmoley.h"

/*************************************************************
* Function: fileManagement() 
* Date Created: 9/6/21 
* Date Last Modified: 9/6/21
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
* Date Created: 9/7/21 
* Date Last Modified: 9/7/21
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
    vector<string>& petTypes, vector<int>& numDaysAtStore)
{
    // function variable block
    string currentLine = "", currentWord = "";
    int currentInt = 0;

    // read into the header vector by parsing the top row first
    getline(infile, currentLine);
    stringstream lineToParse(currentLine);

    while(getline(lineToParse, currentWord, ','))
    {
        header.push_back(currentWord);
    }
    cout << "Processed " << header.size() << " header columns: " << header.at(0) << ", "
        << header.at(1) << ", " << header.at(2) << ", " << header.at(3) << "\n" << endl;

    // read in a vraiable number of data rows by parsing columns
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
        numDaysAtStore.push_back(currentInt);

        int index = petStoreNames.size();

        cout << "Processed a: " << petTypes.at(index - 1) << ", \"" << petNames.at(index - 1)
            << "\" ... " << numDaysAtStore.at(index - 1) << " day(s) on site at store \"" 
            << petStoreNames.at(index - 1) << "\"" << endl;
    }

    // send progress message to the terminal
    cout << "All pet store data processed!\n" << endl;

    return true;
}

/*************************************************************
* Function: namePetStores
* Date Created: 9/14/21 
* Date Last Modified: 9/15/21
* Description: This function computes the true number of stores
*   included in the csv file.
* Input parameters: store name vector an empty string vector
* Returns: N/A
* Pre: pet store names listed (repetitive)
* Post: unique representation for number of pet stores listed
*************************************************************/
void namePetStores(vector<string>& petStoreNames, vector<string>& uniquePetStoreNames)
{
    string tempString = "";
    bool isMatch = false;

    uniquePetStoreNames.push_back(petStoreNames.at(0));

    // fill the emtpy vector with unqiue names only once, skip if already in the vector
    for(int i = 1; i < petStoreNames.size(); i++)
    {
        tempString = petStoreNames.at(i);
        isMatch = false;

        for(int j = 0; j < uniquePetStoreNames.size(); j++)
        {
            if(tempString == uniquePetStoreNames.at(j))
            {
                isMatch = true;
                break;
            }
        }
        
        if(isMatch == false)
        {
            uniquePetStoreNames.push_back(tempString);
        }
    }
}

/*************************************************************
* Function: countPetsAtStores()
* Date Created: 9/14/21 
* Date Last Modified: 9/15/21
* Description: This function counts the number of times each
*   store name appears to later find the max pets at a store
*   as well as what store that is.
* Input parameters: string vector for unique names and an int
*   vector for counts of those names
* Returns: N/A
* Pre: true count of stores listed in the .csv
* Post: count of how many times each store is listed in .csv
*************************************************************/
void countPetsAtStores(vector<string>& petStoreNames, vector<string>& uniquePetStoreNames, 
    vector<int>& uniquePetStoreNameCounts)
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
        uniquePetStoreNameCounts.push_back(nameCount);
    }
}

/*************************************************************
* Function: findMostPetStore()
* Date Created: 9/14/21 
* Date Last Modified: 9/15/21
* Description: This function utilizes the new parallel vectors
*   for unique pet stores to find the store with the most pets.
* Input parameters: string vector for unique names, int vector
*   for counts of those names, string for most store name, 
*   int for most pets count
* Returns: N/A
* Pre: lists for unique store names and how many repeats of each
* Post: name of store with most pets, how many pets that is
*************************************************************/
void findMostPetStore(vector<string>& uniquePetStoreNames, vector<int>& uniquePetStoreNameCounts,
    string& storeMostPets, int& numMostPets)
{
    int mostPetsIndex = 0;

    for(int k = 1; k < uniquePetStoreNameCounts.size(); k++)
    {
        if(uniquePetStoreNameCounts.at(k) > uniquePetStoreNameCounts.at(k - 1))
        {
            mostPetsIndex = k; 
        }

        numMostPets = uniquePetStoreNameCounts.at(mostPetsIndex);
        storeMostPets = uniquePetStoreNames.at(mostPetsIndex);
    }
}

/*************************************************************
* Function: averageDays()
* Date Created: 9/7/21 
* Date Last Modified: 9/7/21
* Description: This function computes the average days that a
*   pet spends in a store across all stores listed.
* Input parameters: int vector for days at each store
* Returns: average days spent at a pet store
* Pre: list of days each pet spent at their respective store
* Post: average number of days spent in store across all stores
*************************************************************/
int averageDays(vector<int>& numDaysAtStore)
{
    int daysAtStoreSum = 0, iterationCount = 0, average = 0;

    for(int i = 0; i < numDaysAtStore.size(); i++)
    {
        daysAtStoreSum += numDaysAtStore.at(i);
        iterationCount++;
    }

    average = daysAtStoreSum / iterationCount;

    return average;
}

/*************************************************************
* Function: petOfTheMonthChoice()
* Date Created: 9/7/21 
* Date Last Modified: 9/7/21
* Description: This function chooses a random index from the
*   amount of pets listed to be pet of the month
* Input parameters: names of pets in csv file
* Returns: name of pet of the month
* Pre: list of names in a vector
* Post: single name returned to a string variable
*************************************************************/
string petOfTheMonthChoice(vector<string>& petNames)
{
    int petOfTheMonthIndex = 0;

    srand(time(0));

    petOfTheMonthIndex = rand() % petNames.size();

    return petNames.at(petOfTheMonthIndex);
}

/*************************************************************
* Function: writeFile()
* Date Created: 9/7/21 
* Date Last Modified: 9/15/21
* Description: This function writes all the output data to the
*   output file.
* Input parameters: fstream variable for the output file
* Returns: N/A
* Pre: open ouput file, but no data written in yet
* Post: output file is populated with the summary report
*************************************************************/
void writeFile(ofstream& outfile, vector<string>& petNames, vector<string>& uniquePetStoreNames,
    int averageDays, string storeMostPets, int numMostPets, string petOfTheMonth)
{
    int index = 0;

    cout << "Generating summary report...\n" << endl;

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
    outfile << "Number of pets at " << storeMostPets << ": " << numMostPets << "\n" << endl;
    outfile << "\nPet average days on site across all stores: " << averageDays << endl;
    outfile << "Employee pet of the month choice: \"" << petOfTheMonth << "\"";

    cout << "Done!" << endl;
}
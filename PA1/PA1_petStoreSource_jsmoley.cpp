/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: September 15, 2021
Programming Assignment: PA1 
Description: This is a program that outputs a summary report based on the status
    of a variable amount of pets held in multiple pet stores, of which are
    given in a .csv file.
Notes: I attempted the bonus task!
*/

#include "PA1_header_jsmoley.h"

int main() 
{
    
    // SW Development Method
    /*  1. specify the problem
        after reading in pet store data from a csv file, said data
        will be manipulated via calculations to produce a summary report 
    */

    /*  2. analyze the problem
        inputs: variable # of line of pet store data from input file
        outputs: progression of lines read, summary report with new data
        relationships: count number of pets (lines in file), take an avg
        of the days spent between all stores, choose rand pet of the month
    */

    /*  3. design the algorithm
        open input/output files:
            implement a function to complete the task
            check status of file(s) after task is complete

        read all data in from input file:
            input header line first, parsing the file by rows w/ getline
            input the line data second, parsing the file by columns w/ getline

        calculate data needed for later summary report:
            parse the parallel vector(s):
                - for unique names
                - for number of pets at each store
                - again for the store and the number of most pets
                - and sum the days each pet stayed to find an average
            randomly choose an index out of the size of a parallel vector to be pet (index) of the month

        write new data to output file:
            output the report header, vector of pet store names, how many pets listed, most pets data, 
                average days, and employee of the month

        close input/output files:
            utilize the same function from opening w/ a new status check too
   */

    //  4. implement the algorithm

    // local variable block
    vector<string> header;
    vector<string> petStoreNames;
    vector<string> petNames;
    vector<string> petTypes;
    vector<int> numDaysAtStore;
    vector<string> lineParts;
    vector<string> uniquePetStoreNames;
    vector<int> uniquePetStoreNameCounts;
    string storeMostPets = "", petOfTheMonth = "";
    int averageDaysAtStore = 0, numMostPets = 0;

    // fstream variables
    ifstream infile;
    ofstream outfile;
    string inName = "petstore.csv", outName = "petreport.txt";

    // read & perform calculations only when files open up
    if(fileManagement(infile, outfile, inName, outName))
    {
        // read from file
        readFile(infile, header, petStoreNames, petNames,
            petTypes, numDaysAtStore);
        
        // identify the number of pet stores involved
        namePetStores(petStoreNames, uniquePetStoreNames);

        // count how many pets are at each store
        countPetsAtStores(petStoreNames, uniquePetStoreNames,
            uniquePetStoreNameCounts);

        // parse the parallel name vectors and assign most pet data
        findMostPetStore(uniquePetStoreNames, uniquePetStoreNameCounts,
            storeMostPets, numMostPets);

        // take an average of the number of days that pets spent in stores
        averageDaysAtStore = averageDays(numDaysAtStore);

        // choose pet of the month
        petOfTheMonth = petOfTheMonthChoice(petNames);

        // write to output file
        writeFile(outfile, petNames, uniquePetStoreNames, averageDaysAtStore,
            storeMostPets, numMostPets, petOfTheMonth);

        // close input/output file to preserve current file states
        fileManagement(infile, outfile, inName, outName);
    }

    /*  5. test the completed program
        use the given values in 'petstore.csv' file
    */

    //  6. maintain the program

    return 0;
}
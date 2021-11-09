/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: September 15, 2021
Programming Assignment: PA1 
Description: This is the header file for a program that outputs a summary report based
    on the status of a variable amount of pets held in multiple pet stores, of which are 
    given in a .csv file.
Notes: I attempted the bonus task!
*/

// header file guard code
#ifndef PA1_HEADER_JSMOLEY_H
#define PA1_HEADER_JSMOLEY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool fileManagement(ifstream& infile, ofstream& outfile, string input, string output);

bool readFile(ifstream& infile, vector<string>& header, vector<string>& petStoreNames, 
    vector<string>& petNames, vector<string>& petTypes, vector<int>& numDaysAtStore);

void namePetStores(vector<string>& petStoreNames, vector<string>& uniquePetStoreNames);

void countPetsAtStores(vector<string>& petStoreNames, vector<string>& uniquePetStoreNames,
    vector<int>& uniquePetStoreNameCounts);

void findMostPetStore(vector<string>& uniquePetStoreNames, vector<int>& uniquePetStoreNameCounts,
    string& storeMostPets, int& numMostPets);

int averageDays(vector<int>& numDaysAtStore);

string petOfTheMonthChoice(vector<string>& petNames);

void writeFile(ofstream& outfile, vector<string>& petNames, vector<string>& uniquePetStoreNames,
    int averageDays, string storeMostPets, int numMostPets, string petOfTheMonth);

// end of header file guard code
#endif
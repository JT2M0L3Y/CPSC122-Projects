/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 6, 2021
Assignment: PA2
Description: This is the header file for programming
    assignment 2.
Notes: N/A
*/

// header file guard code
#ifndef PA2_HEADER_JSMOLEY_H
#define PA2_HEADER_JSMOLEY_H

// libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// function prototypes
bool fileManagement(ifstream& infile, ofstream& outfile, string input, string output);

bool readFile(ifstream& infile, vector<string>& header, vector<string>& petStoreNames, 
    vector<string>& petNames, vector<string>& petTypes, int*& daysPtr, int* daysArraySizePtr);

void namePetStores(vector<string> petStoreNames, vector<string>& uniquePetStoreNames);

void countPetsAtStores(vector<string> petStoreNames, vector<string> uniquePetStoreNames,
    int*& countsArrayPtr, int* countsArraySizePtr);

void findMostPetStore(vector<string> uniquePetStoreNames, int* countsArrayPtr,
    string& storeMostPets, int* numMostPtr);

int* averageDays(int* daysPtr, int* size, int* averagePtr);

string petOfTheMonthChoice(vector<string> petNames);

int* pushBackInteger(int* originalArray, int* size, int newInt);

bool stringIsInVector(vector<string> searchVector, string targetString);

void alphabetizePetNames(const vector<string> petNames, 
    vector<string>& alphabetizedNames);

void swap(int& a, int& b);

void writeFile(ofstream& outfile, vector<string> petNames, vector<string> uniquePetStoreNames,
    vector<string> alphabetizedPetNames, int* averagePtr, string storeMostPets, int* numMostPtr,
    string petOfTheMonth);

// end of header file guard code
#endif
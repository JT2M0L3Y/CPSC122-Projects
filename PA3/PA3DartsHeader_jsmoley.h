/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 13, 2021
Assignment: PA3
Description: This is the header file
    for PA3, the game of darts.
Notes: N/A
*/

#ifndef PA3DARTSHEADER_JSMOLEY_H
#define PA3DARTSHEADER_JSMOLEY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <cstring>

using namespace std;

// global constants
const int MAX_NAME_SIZE = 30;

// structs
struct PlayerCard
{
    int playerId;
    char playerName[MAX_NAME_SIZE];
    int playerScore;
    int gamesPlayed;
    double totAvgScore;
};

// function prototypes
void importPlayerScoreCards(ifstream& inputFile, vector<PlayerCard>& scoreCards);

bool fileManagement(ifstream& inputFile, string fileName);

void welcomeMessage(void);

void initializePlayerScoreCard(PlayerCard* player);

void printPlayerScoreCard(const PlayerCard& player);

char dartsRound(PlayerCard* player);

void showPreviousCards(vector<PlayerCard> scoreCards);

double computeAvg(PlayerCard* player);

bool choiceAnalysis(char ch);

#endif
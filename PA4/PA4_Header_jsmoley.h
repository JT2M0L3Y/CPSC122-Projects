/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 27, 2021
Assignment: PA4
Description: This is the header file
    for PA4, where a class is defined
    in addition to function prototypes.
    (acts as the specification file)
Notes: I attempted the Bonus:
    ------------------------------------------
    |               PlayerCard               |
    ------------------------------------------
    | - playerId: int                        |
    | - playerName: string                   |
    | - totalScore: int                      |
    | - gamesPlayed: int                     |
    | - avgScore: double                     |
    ------------------------------------------
    | - setPlayerId(id : int) : void         |
    | - setAvgScore(avg : double) : void     |
    | - PlayerCard() :                       |
    | - PlayerCard(name : string,            |
    |       id : int) :                      |
    | - ~PlayerCard() :                      |
    | + setPlayerName(name : string) : void  |
    | + setTotalScore(tot : int) : void      |
    | + setGamesPlayed(games : int) : void   |
    | + getPlayerId() : int                  |
    | + getPlayerName() : string             |
    | + getTotalScore() : int                |
    | + getGamesPlayed() : int               |
    | + getAvgScore() : double               |
    | + generatePlayerId(void) : void        |
    | + generatePlayerId(id : int) : void    |
    | + updateAvgScore() : void              |
    | + fileAvgScore(avg : double) : void    |
    ------------------------------------------
*/

#ifndef PA4_HEADER_JSMOLEY_H
#define PA4_HEADER_JSMOLEY_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// required class definition
class PlayerCard
{
    private:
        // PlayerCard attributes
        int playerId;
        string playerName;
        int totalScore;
        int gamesPlayed;
        double avgScore;

        // mutator prototypes for the playerId and avgScore attributes
        void setPlayerId(int id);
        void setAvgScore(double avg);
    public:
        // default constructor
        PlayerCard();

        // overloaded constructor
        PlayerCard(string name, int id);

        // destructor 
        ~PlayerCard();
        
        // mutator prototypes for playerName, totalScore, and gamesPlayed attributes
        void setPlayerName(string name);
        void setTotalScore(int tot);
        void setGamesPlayed(int games);

        // accessor for playerId attribute (constant, in-line)
        int getPlayerId() const { return playerId; }

        // accessor for playerName attribute (constant, in-line)
        string getPlayerName() const { return playerName; }

        // accessor for totalScore attribute (constant, in-line)
        int getTotalScore() const { return totalScore; }

        // accessor for gamesPlayed attribute (constant, in-line)
        int getGamesPlayed() const { return gamesPlayed; }

        // accessor for avgScore attribute (constant, in-line)
        double getAvgScore() const { return avgScore; }

        // member function prototypes for private mutators
        void generatePlayerId(void);
        void generatePlayerId(int id);
        void updateAverageScore(void);
        void fileAverageScore(double avg); // overloaded to pass existing averages
};

// function prototypes
void importPlayerScoreCards(ifstream& inputFile, vector<PlayerCard>& scoreCards);

bool fileManagement(ifstream& inputFile, string filename);

void welcomeMessage(void);

void initializePlayerScoreCard(PlayerCard* card);

void printPlayerScoreCard(const PlayerCard& card);

char dartsRound(PlayerCard* card);

void showPreviousCards(vector<PlayerCard> scoreCards);

bool choiceAnalysis(char ch);

#endif
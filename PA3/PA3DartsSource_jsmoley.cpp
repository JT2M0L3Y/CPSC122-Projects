/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 13, 2021
Assignment: PA3
Description: This program is a darts game
    that utilizes structs and c strings.
Notes: N/A
*/

#include "PA3DartsHeader_jsmoley.h"

int main()
{
    // local variable declaration/initialization
    PlayerCard p1;
    ifstream infile;
    vector<PlayerCard> scoreCards;
    bool play = true;
    char choice = '\0';
    string file = "playercards.txt";

    // check the status of the input file, only continue if open
    if(fileManagement(infile, file))
    {
        // print the welcome message
        welcomeMessage();

        // set up the player card & print it to console
        initializePlayerScoreCard(&p1);

        // output player's current score card
        cout << "Your game card:" << endl;
        printPlayerScoreCard(p1);
        cout << endl;

        // loop until the user decides not to throw a dart
        while(play)
        {
            // play round of darts, ask user if they want to continue
            choice = dartsRound(&p1);
            
            // test whether the user wants to continue playing
            play = choiceAnalysis(choice);
        }

        // print the player's resulting score card
        cout << "\nHere's your final score card!" << endl;
        printPlayerScoreCard(p1);

        // import data from input file
        importPlayerScoreCards(infile, scoreCards);

        // output the player cards read in from the input file
        cout << "\nSee how your score compares to previous players:" << endl;
        showPreviousCards(scoreCards);
    }
    else
    {
        // print error message
        cout << "File was not opened..." << endl;
        return -1;
    }

    // close the input file
    fileManagement(infile, file);

    return 0;
}
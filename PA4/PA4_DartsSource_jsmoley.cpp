/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 27, 2021
Assignment: PA4
Description: This is the source file for
    the PA4 program that uses classes and
    the string library instead of just
    structs and the c-string library.
Notes: I attempted the bonus in the header file!
*/

#include "PA4_Header_jsmoley.h"

int main()
{
    /*
    1. Problem:
        Use a class object to perform data management of input data
        to create a working game of darts and comparing the player's
        stats to a list of past player stats.

    2. Analysis:
        Inputs: current player's data member values, changed with each iteration,
            former players' data read in from an input file
        Ouputs: messages to the console of game progress and player score cards.
        Additional requirements: data has to be referenced with public class
            member functions alone as the data members are privately stored.
    
    3. Design:
        - open input file
            - one function
        - print welcome message
            - one function
        - create PlayerCard for the current player
            - singular class object (use public member functions)
        - run the dart game
            - use a loop
            - output a response through each iteration
            - track current player's stats
            - prompt user to continue playing or end the game
                - if continuing to play, compute the current totalScore and avgScore 
                - if quitting, print the player's score card
        - read in PlayerCard data (can go here or at the beginning)
            - vector of class objects (use public member functions)
        - output a list of previous player score cards to compare their card to

    4. Implement:
    */

    // local variable declaration/initialization
    PlayerCard p1;
    ifstream infile;
    vector<PlayerCard> scoreCards;
    bool play = true;
    char choice = '\0';
    string file = "playercards.txt";

    // seed the random number generator
    srand(time(0));
    // only seems to get a truly random value w/ rand() below, else the value increments up by 3-6 numbers
    rand(); 

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

    /*
    5. Test:
        - run test cases

    6. Maintain:
        - update according to necessary changes
    */
    
    return 0;
}
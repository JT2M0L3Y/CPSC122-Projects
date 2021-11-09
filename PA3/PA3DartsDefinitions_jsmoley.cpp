/*
Name: Jonathan Smoley
Class: CPSC 122, Fall 2021
Date: October 13, 2021
Assignment: PA3 
Description: This is the function
    definitions file for PA3,
    the game of darts
Notes: N/A
*/

#include "PA3DartsHeader_jsmoley.h"

/*************************************************************
* Function: importPlayerScoreCards()
* Date Created: 10/13/21 
* Date Last Modified: 10/15/21
* Description: Reads in rows of player data from the file
*   and store them in a PlayerCard type vector.
* Input parameters: file access variable, vector to populate
* Returns: PlayerCard vector
* Pre: vector is empty and file has not been read from
* Post: file access is done and vector is populated
*************************************************************/
void importPlayerScoreCards(ifstream& inputFile, vector<PlayerCard>& scoreCards)
{
    PlayerCard tempPlayer;
    int playerCount = 0;
    
    while(!inputFile.eof())
    {
        char first[] = ""; // c string for first name
        char last[] = ""; // c string for last name
        //char trash = ' ';
        int tempInt = 0;
        
        // increment number of players (really size of vector)
        ++playerCount;
        
        // read in player card data for each player in file
        inputFile >> tempInt;
        
        // check if empty line has been reached
        if(inputFile.fail())
        {
            break;
        }

        // add a new struct object to the vector
        scoreCards.push_back(tempPlayer);

        // add the id to the current player struct
        scoreCards.at(playerCount - 1).playerId = tempInt;

        // properly take in name of player using c string functions
        inputFile >> first;
        strcpy(scoreCards.at(playerCount - 1).playerName, first);
        strcat(scoreCards.at(playerCount - 1).playerName, " ");
        inputFile >> last;
        strcat(scoreCards.at(playerCount - 1).playerName, last);

        inputFile >> scoreCards.at(playerCount - 1).playerScore;
        inputFile >> scoreCards.at(playerCount - 1).gamesPlayed;
        inputFile >> scoreCards.at(playerCount - 1).totAvgScore;

        // grab newline character at end if an empty line is present
        //inputFile >> trash;
    }
}

/*************************************************************
* Function: fileManagement()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: open or close file(s)
* Input parameters: file reference
* Returns: status of file operation
* Pre: file in one state (open/closed)
* Post: file in another state (open/closed)
*************************************************************/
bool fileManagement(ifstream& inputFile, string fileName)
{
    // check if file is open or closed and change the state
    if(inputFile.is_open() == false)
    {
        inputFile.open(fileName);

        if(inputFile.is_open() == true)
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
        inputFile.close();

        if(inputFile.is_open() == false)
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
* Function: welcomeMessage()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: prints the welcome message to the console
* Input parameters: N/A
* Returns: N/A
* Pre: N/A
* Post: content printed to console
*************************************************************/
void welcomeMessage(void)
{
    // simple output statements to the console at start of game
    cout << "\nWelcome to the game of darts!" << endl;
    cout << "It's completely skill-based and not random luck, I promise!" << endl;
    cout << "...\n*wink*" << endl;
}

/*************************************************************
* Function: initializePlayerScoreCard()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: Initializes a dart player card through the
*   use of a pointer.
* Input parameters: pointer to the struct
* Returns: N/A
* Pre: "empty" struct variable to be populated
* Post: player card struct is now initialized
*************************************************************/
void initializePlayerScoreCard(PlayerCard* player)
{
    char first[] = "";
    char last[] = "";

    // seed the random number generator
    srand(time(0));

    // generate a random ID for the player
    player->playerId = 1000 + rand() % ((9999 + 1) - 1000);

    // initialize the other struct variables
    player->playerScore = 0;
    player->gamesPlayed = 0;
    player->totAvgScore = 0.0;

    // ask user for a player name
    cout << "Please enter a player name (first and last separated by a space):" << endl;
    //cin.getline(player->playerName, MAX_NAME_SIZE);

    cin >> first;
    strcpy(player->playerName, first);
    strcat(player->playerName, " ");
    cin >> last;
    strcat(player->playerName, last);
}

/*************************************************************
* Function: printPlayerScoreCard()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: Prints the contents of the player card
*   in a formattted manner if a player has actually played.
* Input parameters: constant reference to the struct
* Returns: N/A
* Pre: newly populated struct is passed in
* Post: struct is output to console but not returned
*************************************************************/
void printPlayerScoreCard(const PlayerCard& player)
{
    // output game card
    cout << "-----------------------|PID:" << player.playerId
        << "|" << endl;
    cout << player.playerName << "'s Score Card" << endl;
    cout << "---------------------------------" << endl;
    cout << "Games Played: " << player.gamesPlayed << endl;
    cout << "Running Score: " << player.playerScore << endl;
    
    // check if any games have been played (for the average calculation)
    if(player.gamesPlayed > 0)
    {
        cout << "Average Score: " << fixed << setprecision(2) 
            << player.totAvgScore << endl;
    }
    else
    {
        cout << "No games played" << endl;
    }
    cout << "---------------------------------"<< endl;
}

/*************************************************************
* Function: dartsRound()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: This function runs the actual game part where
*   a dart is "thrown".
* Input parameters: new player struct variable
* Returns: user's decision on whether or not to thrown again
* Pre: user wanted to take another thrown of a dart
* Post: user's card is modified to match their new score(s)
*************************************************************/
char dartsRound(PlayerCard* player)
{
    char option = ' ';
    int hit = 0;

    // seed the random number generator
    srand(time(0));

    // output each time a throw is made
    cout << "You throw a dart!" << endl;
    hit = rand() % 10; // the throw

    // notify player of the result
    if(hit < 11 && hit > 5)
    {
        cout << "Great Job! You hit a " << hit << ". That was a good throw!" << endl;
    }
    else if(hit < 6 && hit > 0)
    {
        cout << "Not too bad, you hit a " << hit << ". Maybe give it another go." << endl;
    }
    else
    {
        cout << "Here's the thing... you missed." << endl;
    }

    // modify the player's card values based on the hit
    player->gamesPlayed++;
    player->playerScore += hit;
    player->totAvgScore = computeAvg(player);

    // ask user thoughts on playing again
    cout << "Keep playing? (y/n) ";
    cin >> option;

    return option;
}

/*************************************************************
* Function: showPreviousCards()
* Date Created: 10/13/21 
* Date Last Modified: 10/14/21
* Description: output the data from the file in player card
*   format like the new player's
* Input parameters: vector of player card structs
* Returns: N/A
* Pre: vector hold data to be output in a vector of structs
* Post: console output is formatted and shown to user
*************************************************************/
void showPreviousCards(vector<PlayerCard> cards)
{
    for(int i = 0; i < cards.size(); i++)
        {
            printPlayerScoreCard(cards.at(i));
        }
}

/*************************************************************
* Function: computeAvg()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: Replaces an old average score with a new average
*   based on the incremented number of games and total score.
* Input parameters: current player's card
* Returns: the new score average
* Pre: player's card holds the old average score
* Post: player's card is updated to reflect a new throw made
*************************************************************/
double computeAvg(PlayerCard* player)
{
    double avg = 0.0;

    avg = player->playerScore / player->gamesPlayed;

    return avg;
}

/*************************************************************
* Function: choiceAnalysis()
* Date Created: 10/13/21 
* Date Last Modified: 10/13/21
* Description: Evaluates which choice the user took.
* Input parameters: character representing that choice
* Returns: status of the choice (since y/n is boolean too)
* Pre: choice given
* Post: boolean attribute tells the program to continue/end
*************************************************************/
bool choiceAnalysis(char ch)
{
    bool status;

    if(ch == 'n')
        {
            status = false;
        }
    else if(ch == 'y')
        {
            status = true;
        }
    
    return status;
}

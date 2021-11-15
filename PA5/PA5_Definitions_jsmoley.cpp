/*
	Jonathan Smoley
	CPSC 122, Fall 2021
	11/15/21
	PA5
	This file is the function definitions file for PA5.
	It contains member functions for the PetStoreList 
	class and the functions used in main().
*/

#include "PA5_Header_jsmoley.h"

/*************************************************************
* Function: PetStoreList() 
* Date Created: 11/13/21 
* Date Last Modified: 11/13/21
* Description: This is the default constructor for the 
* 	PetStoreList class.
* Input parameters: N/A
* Returns: N/A
* Pre: new PetStoreList object is created
* Post: new PetStoreList object initialized to empty
*************************************************************/
PetStoreList::PetStoreList()
{
	headPtr = nullptr;
}

/*************************************************************
* Function: ~PetStoreList() 
* Date Created: 11/13/21 
* Date Last Modified: 11/13/21
* Description: This is the destructor for the PetStoreList 
* 	class.
* Input parameters: N/A
* Returns: N/A
* Pre: PetStoreList object holds a # of nodes >= 0
* Post: PetStoreList object no longer holds any nodes
*************************************************************/
PetStoreList::~PetStoreList()
{
	PetStoreData* nodePtr = headPtr;
	PetStoreData* nextNode = nullptr;

	while(nodePtr != nullptr)
	{
		nextNode = nodePtr->nextStore;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

/*************************************************************
* Function: createNode() 
* Date Created: 11/13/21 
* Date Last Modified: 11/13/21
* Description: This function creates a new node for the 
* 	PetStoreData linked list.
* Input parameters: string for the store name
* Returns: newly allocated node
* Pre: PetStoreList object holds a # of nodes >= 0
* Post: PetStoreList object no longer holds any nodes
*************************************************************/
PetStoreList::PetStoreData* PetStoreList::createNode(string storeName)
{
	PetStoreData* newNode = new PetStoreData;

	newNode->petStoreName = storeName;
	newNode->nextStore = nullptr;

	return newNode;
}

/*************************************************************
* Function: insertAtEnd() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function appends a node to the end of the
* 	PetStoreData linked list.
* Input parameters: node to be added
* Returns: N/A
* Pre: PetStoreList object holds n nodes
* Post: PetStoreList object holds n+1 nodes
*************************************************************/
void PetStoreList::insertAtEnd(PetStoreData* newStoredata)
{
	PetStoreData* newNode = createNode(newStoredata->petStoreName);
	PetStoreData* nodePtr = nullptr;

	if(headPtr == nullptr)
	{
		headPtr = newStoredata;
	}
	else
	{
		nodePtr = headPtr;

		while(nodePtr->nextStore != nullptr)
		{
			nodePtr = nodePtr->nextStore;
		}

		nodePtr->nextStore = newStoredata;
	}
}

/*************************************************************
* Function: addPetData() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function fills the petData vector of a
* 	node in the linked list with data from the input file.
* Input parameters: storeName of node, pet name and type, and
* 	number of days at the store
* Returns: N/A
* Pre: petData vector in the node is empty
* Post: PetStoreList petData vector is filled with data
*************************************************************/
void PetStoreList::addPetData(string storeName, string pName, string pType, int numDays)
{
	PetStoreData* nodePtr = headPtr;
	PetData tempData;

	while(nodePtr != nullptr)
	{
		if(nodePtr->petStoreName == storeName)
		{
			// increment the total number of pets 
			summaryData.numPets++;

			tempData.petName = pName;
			tempData.petType = pType;
			tempData.numDaysAtStore = numDays;

			nodePtr->petData.push_back(tempData);

			break;
		}
		else
		{
			nodePtr = nodePtr->nextStore;
		}
	}
}

/*************************************************************
* Function: displayPetList() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function outputs the petStoreData linked
* 	list content to the console.
* Input parameters: N/A
* Returns: N/A
* Pre: PetStoreData linked list is filled with data
* Post: Report is visible in the console
*************************************************************/
void PetStoreList::displayPetList() const
{
	PetStoreData* nodePtr = headPtr;

	while(nodePtr != nullptr)
	{
		cout << "___________________________________" << endl;
		cout << "Pet Store Name: " << nodePtr->petStoreName << endl;
		cout << "***********************************" << endl;
		cout << "| Number of Pets: " << nodePtr->petData.size() << endl;
		cout << "| Pet Information:" << endl;

		for(int i = 0; i < nodePtr->petData.size(); i++)
		{
			cout << "> Pet " << i+1 << " Name: " << nodePtr->petData[i].petName << endl;
			cout << "> Pet Type: " << nodePtr->petData[i].petType << endl;
			cout << "> Number of days at store: " << nodePtr->petData[i].numDaysAtStore << endl;
			cout << "----------------------------" << endl;
		}

		nodePtr = nodePtr->nextStore;
	}
}

/*************************************************************
* Function: displayPetList() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function does the same thing as the 
* 	displayPetList() function, but outputs the data to an
* 	output file instead.
* Input parameters: N/A
* Returns: N/A
* Pre: PetStoreData linked list is filled with data
* Post: Report is visible in the output file
*************************************************************/
void PetStoreList::writePetList(ofstream& outfile)
{
	PetStoreData* nodePtr = headPtr;

	while(nodePtr != nullptr)
	{
		outfile << "___________________________________" << endl;
		outfile << "Pet Store Name: " << nodePtr->petStoreName << endl;
		outfile << "***********************************" << endl;
		outfile << "| Number of Pets: " << nodePtr->petData.size() << endl;
		outfile << "| Pet Information:" << endl;

		for(int i = 0; i < nodePtr->petData.size(); i++)
		{
			outfile << "> Pet " << i+1 << " Name: " << nodePtr->petData[i].petName << endl;
			outfile << "> Pet Type: " << nodePtr->petData[i].petType << endl;
			outfile << "> Number of days at store: " << nodePtr->petData[i].numDaysAtStore << endl;
			outfile << "----------------------------" << endl;
		}

		nodePtr = nodePtr->nextStore;
	}
}

/*************************************************************
* Function: storeInList() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function checks if the current store name
* 	is already in the linked list.
* Input parameters: name to check for
* Returns: true if store name is in the list, false otherwise
* Pre: store name is read from the file
* Post: new node will be created or just data will be added
*************************************************************/
bool PetStoreList::storeInList(string name)
{
	PetStoreData* nodePtr = headPtr;
	bool found = false;

	while(nodePtr != nullptr)
	{
		if(nodePtr->petStoreName == name)
		{
			found = true;
		}

		nodePtr = nodePtr->nextStore;
	}
	
	return found;
}

/*************************************************************
* Function: calculatePetSummary() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function traverses both the linked list
* 	and the petData vector to find summations and min/max
* 	values.
* Input parameters: N/A
* Returns: N/A
* Pre: Summary data object is declared but not initialized
* Post: Summary Data object is filled with data
*************************************************************/
void PetStoreList::calculatePetSummary()
{
	PetStoreData* nodePtr = headPtr;
	int totNumPets = 0, totalNumDays = 0;

	// initialize min/max values for traversal comparisons
	summaryData.minDaysAtStore = nodePtr->petData[0].numDaysAtStore;
	summaryData.maxDaysAtStore = nodePtr->petData[0].numDaysAtStore;

	// traverse the linked list to get summations for stats
	while(nodePtr != nullptr)
	{
		for(int i = 0; i < nodePtr->petData.size(); i++)
		{
			totNumPets++;

			totalNumDays += nodePtr->petData[i].numDaysAtStore;

			// check if current value is less than min
			if(nodePtr->petData[i].numDaysAtStore <= summaryData.minDaysAtStore)
			{
				summaryData.minDaysAtStore = nodePtr->petData[i].numDaysAtStore;
			}

			// check if current value is greater than max
			if(nodePtr->petData[i].numDaysAtStore >= summaryData.maxDaysAtStore)
			{
				summaryData.maxDaysAtStore = nodePtr->petData[i].numDaysAtStore;
			}
		}

		nodePtr = nodePtr->nextStore;
	}

	// initialize total number of pets and average days at store in summary data struct
	summaryData.numPets = totNumPets;
	summaryData.averageDaysAtStore = round(totalNumDays / totNumPets);
}

/*************************************************************
* Function: displayPetSummary() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function outputs the summary data to the
* 	console.
* Input parameters: N/A
* Returns: N/A
* Pre: a summary data object holds stats about the pet data
* Post: the console displays the summary data values
*************************************************************/
void PetStoreList::displayPetSummary() const
{
	cout << "__________________________________" << endl;
	cout << "Total number of pets: " << summaryData.numPets << endl;
	cout << "Average number of days at pet store: " << summaryData.averageDaysAtStore << endl;
	cout << "Shortest stay at pet store: " << summaryData.minDaysAtStore << endl;
	cout << "Longest stay at pet store: " << summaryData.maxDaysAtStore << endl;
}

/*************************************************************
* Function: writePetList() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function does the same thing as the 
* 	displayPetSummary() function, but outputs the data to an
* 	output file instead.
* Input parameters: N/A
* Returns: N/A
* Pre: summaryData struct object is filled with data
* Post: Summary Report is visible in the output file
*************************************************************/
void PetStoreList::writePetSummary(ofstream& outfile)
{
	outfile << "__________________________________" << endl;
	outfile << "Total number of pets: " << summaryData.numPets << endl;
	outfile << "Average number of days at pet store: " << summaryData.averageDaysAtStore << endl;
	outfile << "Shortest stay at pet store: " << summaryData.minDaysAtStore << endl;
	outfile << "Longest stay at pet store: " << summaryData.maxDaysAtStore << endl;
}

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
* Function: readHeader() 
* Date Created: 11/13/21 
* Date Last Modified: 11/13/21
* Description: This function reads the header from the input
* 	file into the stringsteram, parses for the headers, and 
* 	stores each in a vector.
* Input parameters: fstream variables for input/output files 
* Returns: a boolean value on whether files were opened/closed
* Pre: vector is empty and header is not yet read.
* Post: vector is filled with headers 
*************************************************************/
bool readHeader(ifstream& infile, vector<string>& header)
{
	string line = "";
	stringstream lineToParse;
	string tempString = "";

	getline(infile, line);

	lineToParse << line;

	while(getline(lineToParse, tempString, ','))
	{
		header.push_back(tempString);
	}

	if(header.size() == 4)
	{
		return true;
	}
	else
	{
		return -1;
	}
}

/*************************************************************
* Function: outputHeaderStatus() 
* Date Created: 11/13/21 
* Date Last Modified: 11/13/21
* Description: This function sends a message to the console.
* Input parameters: vector of headers
* Returns: N/A
* Pre: vector is filled with headers
* Post: vector contents are printed to console
*************************************************************/
void outputHeaderStatus(vector<string>& header)
{
	cout << "\nProcessed " << header.size() << " header columns: ";
	
	for(int i = 0; i < header.size() - 1; i++)
	{
		cout << header[i] << ", ";
	}

	cout << header[header.size() - 1] << "\n" << endl;
}

/*************************************************************
* Function: readPetData() 
* Date Created: 11/15/21 
* Date Last Modified: 11/15/21
* Description: This function processes the pet data in the 
* 	input file and stores it in a vector of PetData structs
* 	using class member functions.
* Input parameters: file stream reference, class object
* Returns: boolean value on whether file was read correctly
* Pre: pet data needs to be read into nodes that have yet to
* 	be allocated in the list.
* Post: Pet data is stored in the correct nodes based on store
*************************************************************/
void processPetData(ifstream& infile, PetStoreList& storeList)
{
	string tempString = "", petType = "", petName = "", storeName = "";
	int daysAtStore = 0, petCount = 0;

	// loop through the input file lines that hold data
	while(!infile.eof())
	{
		// read the store name
		getline(infile, storeName, ',');

		// check for empty line(s)
		if(infile.eof())
		{
			break;
		}

		// read the pet name
		getline(infile, petName, ',');
		// read the pet type
		getline(infile, petType, ',');
		// read the number of days at the store
		infile >> daysAtStore;
		// grab the newline character at the end of each line
		getline(infile, tempString);

		cout << "Processed a: " << petType << ", \"" << petName
            << "\" ... " << daysAtStore << " day(s) on site at store \"" 
            << storeName << "\"" << endl;


		// add the pet data to the list
		if(!storeList.storeInList(storeName))
		{
			storeList.insertAtEnd(storeList.createNode(storeName));
			storeList.addPetData(storeName, petName, petType, daysAtStore);
		}
		else
		{
			storeList.addPetData(storeName, petName, petType, daysAtStore);
		}
	}

	cout << "\nAll pet store data processed!\n" << endl;
}
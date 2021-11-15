/*
	Jonathan Smoley
	CPSC 122, Fall 2021
	11/15/21
	PA5
	This program utilizes linked lists
		to read in data from a .csv file,
		compute stats on that data, and
		output the stats to another file.
*/

#include "PA5_Header_jsmoley.h"

int main()
{
	// local variable declaration block
	ifstream infile;
	ofstream outfile;
	string inputFileName = "petstoredata.csv";
	string outputFileName = "petreport.txt";
	vector<string> header;
	PetStoreList storeList;

	// open the input/output files, and check for errors
    if(fileManagement(infile, outfile, inputFileName, outputFileName))
    {
        // read the header line from the input file
		if(readHeader(infile, header))
		{
			outputHeaderStatus(header);
		}
		else
		{
			cout << "Error reading header line from input file." << endl;
			return -1;
		}

		// read the data from the input file
		processPetData(infile, storeList);
		
		// calculate summary data
		cout << "Generating Summary Report...\n" << endl;
		storeList.calculatePetSummary();

		// output summary and linked list data to the console
		cout << "Done!\n" << endl;
		storeList.displayPetSummary();
		storeList.displayPetList();

		// write summary and linked list data to the output file
		outfile << "Pet Store CSV Summary Report" << endl;
		storeList.writePetSummary(outfile);
		storeList.writePetList(outfile);

        // close input/output files
        fileManagement(infile, outfile, inputFileName, outputFileName);
    }
    else
    {
        cout << "File(s) were not opened..." << endl;
        return -1;
    }

	return 0;
}

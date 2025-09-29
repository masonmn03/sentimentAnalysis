// CS201PGM8Sentiment 
// NAME:  Mason Nguyen
// ASSIGNMENT: Program 5
// DATE: 3/13/25

#include "Sentiment.h"
#include "Sentiment.cpp"
using namespace std;

int main()
{
    vector<wordList> sentList, posList, negList;
    srand(time(0));

    // load vectors 
    loadSentiment(sentList, posList, negList);

    // open output file 
    ofstream outputFile;
    outputFile.open("output.txt");
    // open review files

    string fileName;
    for (unsigned int i = 1; i < 9; i++) {
        ifstream input;
        string fileName = "review" + to_string(i) + ".txt";
        input.open(fileName);
        if (!input.good()) {
            cout << "Error opening file: " << fileName << endl;
            continue;
        }
        processFile(input, outputFile, fileName, sentList, posList, negList);
        input.close();
        
        // open input file adding to_string(i) + ".txt" to review
        // if not able to open, print a message and continue
        // else process the file & close it

    }
    outputFile.close();

    //close the output file
}
 

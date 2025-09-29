#include "Sentiment.h"

//SUPPORT FUNCTION TO FIND THE CURRENT WORD IN THE SENTIMENT VECTOR & RETURN THE SENTIMENT VALUE
//PRE:   accepts a string (in) and the words list
//POST:  returns the sentiment of the word if found or the value 0 if not
double sentimentVal(string in, vector<wordList> &words) {
    double sentVal;
    for (int i = 0; i < words.size(); i++) {
        if (words.at(i).word == in) {
            sentVal = words.at(i).value;
            return sentVal;
        }
    }
    return 0;
}


//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt
void loadSentiment(vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList) {
    ifstream input1;
    string line;
    vector<string> values; // The two values in each line
    string value;
    wordList temp;
    input1.open("sentiment.txt");
    while (getline(input1, line)) {
        stringstream ss(line);
        values.clear();
        while (getline(ss, value, ',')) {
            values.push_back(value);
        }
        temp.word = values.at(0);
        temp.value = stof(values.at(1));
        sentList.push_back(temp);

        if (temp.value > 1.25) {
            posList.push_back(temp);
        }
        else if (temp.value < -1.25) {
            negList.push_back(temp);
        }
    }
    input1.close();
    return;

}

//PRE:  positive & negative word lists are sent
//POST: Open the input file & output file (infile+Output 
//      'Clean' the input by removing syntax and setting all to lower case
//       Get the sentiment value for the edited word
//        store unedited word in vector with sentiment value
//         if sentiment < -1  find a positive word to replace it
//         if sentiment > 1   find a negative word to replace

void processFile(ifstream& inFile, ofstream& outFile, string fileName,
                    vector<wordList>& words,               // vectors containing the word & sentiment
                    vector<wordList>& posList, 
                    vector<wordList>& negList) {
 
    string inWord, newWord;
    char newChar;
    vector<wordList> origWords, negWords, posWords;
    origWords.clear();
    negWords.clear();
    posWords.clear();

    outFile << "PROCESSING FILE: " << fileName << endl << endl;

    // reset all vectors & values before processing inFile
    //   read and edit the initial file
    //   remove any unnecessary characters
    vector<string> temp;
    temp.clear();
    double totalSentimentValue = 0.0;
    while (inFile >> inWord) {
        //  the inFile read will read a word up to the next space.
        //  there may be some unwanted characters
        //  read char by char and only use alphabetic characters
        //  and change all uppercase to lowercase
        newWord = "";
        for (int i = 0, len = inWord.size(); i < len; i++) {
            if (isalpha(inWord[i])) {
                newChar = tolower(inWord[i]);
                newWord += newChar;
            }
        }
        temp.push_back(newWord);
        double sentVal = sentimentVal(newWord, words);
        
        wordList tempWord;
        tempWord.word = inWord;
        tempWord.value = sentVal;

        origWords.push_back(tempWord);
        totalSentimentValue += sentVal;


        // add the 'clean' word to a temp location & add original word & sentiment value to origWords

        //CHECK TO MAKE SENTIMENT MORE NEGATIVE
        //store current word before checking to replace
        //add original word or replacement to negVector

        //CHECK TO MAKE SENTIMENT MORE POSITIVE
        //store current word before checking to replace
        //add original word or replacement to posVector
    }

    //OUTPUT UPDATES
    //EDIT ORIGINAL WORDS VECTOR FOR OUTPUT
    //check to see if the length of the words written so far
    outFile << "FORMATTED REVIEW: " << endl;
    int lineLength = 0;
    for (unsigned int i = 0; i < origWords.size(); i++) {
        lineLength += origWords[i].word.length() + 1;
        if (lineLength > 80) {
            outFile << "\n";
            lineLength = origWords[i].word.length() + 1;
        }
        outFile << origWords[i].word + " ";
    }
    outFile << endl << endl;
    outFile << "ORIGINAL SENTIMENT: " << totalSentimentValue << endl << endl;
 

    //EDIT MORE NEGATIVE VECTOR FOR OUTPUT
    //CHECK THAT SOMETHING HAS BEEN UPDATED BEFORE BEGINNING PRINT
    //IF THE ORIGINAL SENTMENT & NEGATIVE SENTIMENT ARE EQUAL, PRINT "REVIEW NOT UPDATED, THE SENTIMENT REMAINS: "

    //  if sentiment < -1  find a positive word to replace it
    //  if sentiment > 1   find a negative word to replace
    vector<wordList> negToPos;
    vector<wordList> posToNeg;
    vector<wordList> original1;
    vector<wordList> original2;
    negToPos.clear();
    posToNeg.clear();
    original1.clear();
    original2.clear();
    double originalTotal = 0;
    double newTotal = 0;
    double originalTotal2 = 0;
    double newTotal2 = 0;

    vector<string> updatedNeg, updatedPos;
    updatedNeg.clear();
    updatedPos.clear();
    double updatedSentimentNeg = 0, updatedSentimentPos = 0;
    
    for (int i = 0; i < temp.size(); i++) {
        string word = temp.at(i);
        wordList placeholder;
        wordList newWord;
        int num;
        double sentValue = sentimentVal(word, words);
        placeholder.value = sentValue;
        placeholder.word = word;
        if (sentValue < -1) { ///FIXTHIS HERE
            original1.push_back(placeholder);
            originalTotal += placeholder.value;
            num = rand() % posList.size();
            newWord.word = posList.at(num).word;
            newWord.value = posList.at(num).value;
            newTotal += newWord.value;
            negToPos.push_back(newWord);
            updatedNeg.push_back(newWord.word);
        }
        else {
            updatedNeg.push_back(placeholder.word);
        }
    }

    for (int i = 0; i < temp.size(); i++) {
        string word = temp.at(i);
        wordList placeholder;
        wordList newWord;
        int num;
        double sentValue = sentimentVal(word, words);
        placeholder.value = sentValue;
        placeholder.word = word;
        if (sentValue > 1) {
            original2.push_back(placeholder);
            originalTotal2 += placeholder.value;
            num = rand() % negList.size();
            newWord.word = negList.at(num).word;
            newWord.value = negList.at(num).value;
            newTotal2 += newWord.value;
            posToNeg.push_back(newWord);
            updatedPos.push_back(newWord.word);
        }
        else {
            updatedPos.push_back(placeholder.word);
        }
    }

    outFile << "Words Updated to be more Positive: " << endl;
    if (negToPos.size() > 0) {
        for (int i = 0; i < original1.size(); i++) {
            outFile << setw(20) << right << original1.at(i).word << setw(10) << original1.at(i).value
            << setw(30) << negToPos.at(i).word << setw(10) << negToPos.at(i).value << endl;
        }

        outFile << "TOTALS: " << setw(22) << right << originalTotal << setw(40) << newTotal << endl << endl;
        outFile << "Updated Review (More positive): " << endl << "\"";
        
        int lineLength1 = 0;
        for (unsigned int i = 0; i < updatedNeg.size(); i++) {
            lineLength1 += updatedNeg.at(i).length() + 1;
            if (lineLength1 > 80) {
                outFile << "\n";
                lineLength1 = updatedNeg.at(i).length() + 1;
            }
            outFile << updatedNeg.at(i) + " ";
        }

        for (int i = 0; i < updatedNeg.size(); i++) {
            updatedSentimentNeg += sentimentVal(updatedNeg.at(i), words);
        }
        outFile << "\"" << endl << endl;
        outFile << "Updated sentiment: " << updatedSentimentNeg << endl << endl;
    }
    else {
        outFile << "Review not updated. The sentiment remains: " << totalSentimentValue << endl << endl;
    }

    outFile << "Words Updated to be more Negative: " << endl;
    if (posToNeg.size() > 0) {
        for (int i = 0; i < original2.size(); i++) {
            outFile << setw(20) << right << original2.at(i).word << setw(10) << original2.at(i).value
            << setw(30) << posToNeg.at(i).word << setw(10) << posToNeg.at(i).value << endl;
        }

        outFile << "TOTALS: " << setw(22) << right << originalTotal2 << setw(40) << newTotal2 << endl << endl;
        outFile << "Updated Review (More negative): " << endl << "\"";

        int lineLength2 = 0;
        for (unsigned int i = 0; i < updatedPos.size(); i++) {
            lineLength2 += updatedPos.at(i).length() + 1;
            if (lineLength2 > 80) {
                outFile << "\n";
                lineLength2 = updatedPos.at(i).length() + 1;
            }
            outFile << updatedPos.at(i) + " ";
        }
        for (int i = 0; i < updatedPos.size(); i++) {
            updatedSentimentPos += sentimentVal(updatedPos.at(i), words);
        }
        outFile << "\"" << endl << endl;
        outFile << "Updated sentiment: " << updatedSentimentPos << endl << endl << endl;
    }
    else {
        outFile << "Review not updated. The sentiment remains: " << totalSentimentValue << endl << endl;
    }

    
    //EDIT MORE POSITIVE VECTOR FOR OUTPUT
    //CHECK THAT SOMETHING HAS BEEN UPDATED BEFORE BEGINNING PRINT
    //IF THE ORIGINAL SENTMENT & NEW POSITIVE SENTIMENT ARE EQUAL, PRINT "REVIEW NOT UPDATED, THE SENTIMENT REMAINS: "
 
 
}
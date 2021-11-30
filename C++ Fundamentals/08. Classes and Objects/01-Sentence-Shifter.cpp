#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Sentence
{
    public:
        string sentence;

    Sentence(string sentence)
    {
        this -> sentence = sentence;
    }

    public:
        vector<string> allWords;

    void getAllWords()
    {
        stringstream myStream(this -> sentence);
        string currentWord;
        while(myStream >> currentWord)
        {
            (this -> allWords).push_back(currentWord);
        }
    }

    void printSentence(vector<string>& shiftedVector)
    {
        for(vector<string>::iterator it = shiftedVector.begin(); it != shiftedVector.end(); ++it)
        {
            cout << *it << endl;
        }
    }

    void shiftSentence(size_t numberOfShifts)
    {
        size_t SIZE = (this -> allWords).size();
        numberOfShifts %= SIZE;

        vector<string> newShiftedVector;
        vector<string>::iterator it = (this -> allWords).end();

        for(size_t i = 0; i < numberOfShifts; ++i)
        {
            --it;
        }

        vector<string>::iterator myIterator = it;

        for(; it != (this -> allWords).end(); ++it)
        {
            newShiftedVector.push_back(*it);
        }

        for(it = (this -> allWords).begin(); it != myIterator; ++it)
        {
            newShiftedVector.push_back(*it);
        }

        printSentence(newShiftedVector);
    }
};

int main()
{
    string myStr;
    getline (cin, myStr);

    Sentence newSentence(myStr);
    newSentence.getAllWords();

    size_t shiftingNumber = 0;
    cin >> shiftingNumber;

    newSentence.shiftSentence(shiftingNumber);
    return 0;
}



#include <iostream>
#include <vector>
#include <string>

//transform numbers into human readable number
//sum the numbers
//transform the result back into our new numeric system
//print the result

int getIntFromStr(const std::vector<int> & digits,
                  const std::string &      number)
{
    int result = 0;

    const int SIZE = (int)number.size();
    for(int i = 0 ; i < SIZE; ++i)
    {
        const int INDEX = (int)number[i];

        result = (result * 10) + digits[INDEX];
    }

    return result;
}

void readInput(std::vector<int> & outDigits,
               std::string & digitsRepresentation,
               std::string & firstNumber,
               std::string & secondNumber)
{
    std::cin >> digitsRepresentation >> firstNumber >> secondNumber;

    const int SIZE = (int)digitsRepresentation.size();
    for(int i = 0 ; i < SIZE; ++i)
    {
        const char currDigit = digitsRepresentation[i];
        outDigits[(int)currDigit] = i;
    }
}

std::string transformToNewNumbericSystem(const int number,
                                         const std::string & digitsRepresentation)
{
    std::string result;
    result.reserve(20);

    std::string numberStr = std::to_string(number);

    const int SIZE = (int)numberStr.size();
    for(int i = 0; i < SIZE; ++i)
    {
        const int INDEX = numberStr[i] - '0';
        const char LETTER = digitsRepresentation[INDEX];
        result.push_back(LETTER);
    }

    std::string first, second;

    first.append(second);

    return result;
}

int main()
{
    std::vector<int> digits(255);
    std::string digitsRepresentation;
    std::string firstNumber;
    std::string secondNumber;
    readInput(digits, digitsRepresentation, firstNumber, secondNumber);

    const int result = getIntFromStr(digits, firstNumber) +
                       getIntFromStr(digits, secondNumber);

    std::cout << transformToNewNumbericSystem(result, digitsRepresentation);

	return 0;
}

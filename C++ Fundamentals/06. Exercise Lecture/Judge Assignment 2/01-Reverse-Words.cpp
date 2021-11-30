#include <iostream>
#include <stack>
#include <string>
#include <sstream>

int main()
{
    std::stack<std::string> reverseWords;
    std::string input;
    std::string word;
    while(true)
    {
        getline(std::cin, input);

        if("end" == input)
        {
            break;
        }

        std::istringstream istr(input);

        while(istr >> word)
        {
            reverseWords.push(word);
        }
    }

    while(!reverseWords.empty())
    {
        std::cout << reverseWords.top() << ' ';
        reverseWords.pop();
    }

	return 0;
}

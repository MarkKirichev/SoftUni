#include "StringConcatenator.h"

StringConcatenator::StringConcatenator() {}

StringConcatenator::~StringConcatenator() {}

std::string StringConcatenator::concatenate(const ConcatenateStrategy strategy,
                                            const char * 			  left,
                                            const size_t 			  leftSize,
                                            const char * 			  right,
                                            const size_t 		      rightSize) const
{
    std::string finalString = "";

    bool leftEmpty = false;
    bool rightEmpty = false;

    size_t SIZE_LEFT = leftSize;
    size_t SIZE_RIGHT = rightSize;

    if(!leftSize)
    {
        leftEmpty = true;
    }
    if(!rightSize)
    {
        rightEmpty = true;
    }

    int i = 0,
        j = 0;

    switch(strategy)
    {
        case ConcatenateStrategy::LEFT_1_RIGHT_1:

            while(leftEmpty == false || rightEmpty == false)
            {
                if(SIZE_LEFT)
                {
                    finalString += left[i];
                    --SIZE_LEFT;
                }
                if(SIZE_RIGHT)
                {
                    finalString += right[i];
                    --SIZE_RIGHT;
                }

                if(!SIZE_LEFT)
                {
                    leftEmpty = true;
                }
                if(!SIZE_RIGHT)
                {
                    rightEmpty = true;
                }

                ++i;
            }
            break;

        case ConcatenateStrategy::LEFT_2_RIGHT_1:

            while(leftEmpty == false || rightEmpty == false)
            {
                if(SIZE_LEFT)
                {
                    finalString += left[i];
                    --SIZE_LEFT;
                    ++i;
                }
                if(SIZE_LEFT)
                {
                    finalString += left[i];
                    --SIZE_LEFT;
                    ++i;
                }

                if(SIZE_RIGHT)
                {
                    finalString += right[j];
                    --SIZE_RIGHT;
                    ++j;
                }

                if(!SIZE_LEFT)
                {
                    leftEmpty = true;
                }
                if(!SIZE_RIGHT)
                {
                    rightEmpty = true;
                }
            }
            break;

        case ConcatenateStrategy::LEFT_1_RIGHT_2:

            while(leftEmpty == false || rightEmpty == false)
            {
                if(SIZE_LEFT)
                {
                    finalString += left[i];
                    --SIZE_LEFT;
                    ++i;
                }
                if(SIZE_RIGHT)
                {
                    finalString += right[j];
                    --SIZE_RIGHT;
                    ++j;
                }
                if(SIZE_RIGHT)
                {
                    finalString += right[j];
                    --SIZE_RIGHT;
                    ++j;
                }

                if(!SIZE_LEFT)
                {
                    leftEmpty = true;
                }
                if(!SIZE_RIGHT)
                {
                    rightEmpty = true;
                }
            }
            break;
    }

    return finalString;
}

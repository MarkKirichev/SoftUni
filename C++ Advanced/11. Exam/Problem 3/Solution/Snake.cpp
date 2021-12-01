#include "Snake.h"
#include "Defines.h"
#include "Structs.h"

#include <deque>
#include <vector>
#include <iostream>

std::deque<Point>& Snake::getSnakeNodes()
{
    return _snakeNodes;
}

enum FieldType
{
    FREE_FIELD = 0,
    OBSTACLE_FIELD = 1,
    POWER_UP_FIELD = 2,
};

FieldType isThereSomething(const              Point& nextDirection,
                           const std::vector<Point>& obstacles,
                                 std::vector<Point>& powerUps)
{
    const size_t SIZE_OBSTACLES = obstacles.size();

    for(size_t i = 0; i < SIZE_OBSTACLES; ++i)
    {
        if(obstacles[i] == nextDirection)
        {
            return OBSTACLE_FIELD;
        }
    }

    const size_t SIZE_POWER_UPS = powerUps.size();
    int positionOfPowerUp = -1;

    for(size_t i = 0; i < SIZE_POWER_UPS; ++i)
    {
        if(powerUps[i] == nextDirection)
        {
            positionOfPowerUp = i;
            break;
        }
    }

    if(positionOfPowerUp >= 0)
    {
        powerUps.erase(powerUps.begin() + positionOfPowerUp);
        return POWER_UP_FIELD;
    }

    return FREE_FIELD;
}

bool isValid(Point& newPoint,
             const int _FIELD_ROWS,
             const int _FIELD_COLS)
{
    if(newPoint.row < 0 || newPoint.col < 0 ||
       newPoint.row >= _FIELD_ROWS || newPoint.col >= _FIELD_COLS)
    {
        return false;
    }

    return true;
}

Snake::Snake(const int     fieldRows,
             const int     fieldCols,
             const Point & startPos) :
             _FIELD_ROWS(fieldRows),
             _FIELD_COLS(fieldCols),
             _currPos(startPos)
             {
                 _snakeNodes.push_back(startPos);
             }

Snake::~Snake()
{
    _snakeNodes.clear();
}

StatusCode Snake::move(const Direction            dir,
                       const std::vector<Point> & obstacles,
                       std::vector<Point> &       powerUps)
{
    StatusCode statusCode = StatusCode::STATUS_UNKNOWN;

    Point newPosition;

    switch(dir)
    {
        case Direction::UP:
            newPosition.row = _snakeNodes[0].row - 1;
            newPosition.col = _snakeNodes[0].col;
            break;
        case Direction::RIGHT:
            newPosition.row = _snakeNodes[0].row;
            newPosition.col = _snakeNodes[0].col + 1;
            break;
        case Direction::DOWN:
            newPosition.row = _snakeNodes[0].row + 1;
            newPosition.col = _snakeNodes[0].col;
            break;
        case Direction::LEFT:
            newPosition.row = _snakeNodes[0].row;
            newPosition.col = _snakeNodes[0].col - 1;
            break;
    }

    if (!isValid(newPosition, _FIELD_ROWS, _FIELD_COLS))
    {
        statusCode = StatusCode::SNAKE_DEAD;
        return statusCode;
    }

    const size_t SNAKE_SIZE = _snakeNodes.size();

    for (size_t i = 0; i < SNAKE_SIZE; ++i)
    {
        if (newPosition == _snakeNodes[i])
        {
            statusCode = StatusCode::SNAKE_DEAD;
            return statusCode;
        }
    }

    FieldType typeOfField = isThereSomething(newPosition, obstacles, powerUps);

    switch(typeOfField)
    {
        case FREE_FIELD:
            _snakeNodes.push_front(newPosition);
            _snakeNodes.pop_back();
            _currPos = newPosition;
            statusCode = StatusCode::SNAKE_MOVING;
            break;
        case OBSTACLE_FIELD:
            statusCode = StatusCode::SNAKE_DEAD;
            break;
        case POWER_UP_FIELD:
            _snakeNodes.push_front(newPosition);
            _currPos = newPosition;
            statusCode = StatusCode::SNAKE_GROWING;
    }

    return statusCode;
}

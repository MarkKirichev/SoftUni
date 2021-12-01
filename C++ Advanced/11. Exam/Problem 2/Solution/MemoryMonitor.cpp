#include "MemoryMonitor.h"
#include "Defines.h"
#include "Structs.h"

#include <vector>
#include <iostream>

MemoryMonitor::MemoryMonitor() {}

MemoryMonitor::~MemoryMonitor()
{
    const size_t SIZE = _nodes.size();

    for(size_t i = 0; i < SIZE; ++i)
    {
        delete[] _nodes[i].data;
    }
}

void MemoryMonitor::pushNode(const int nodeSize)
{
    MemoryNode newNode;
    newNode.data = new int[nodeSize];
    newNode.size = nodeSize;

    _nodes.emplace_back(newNode);

    std::cout << "Pushed node with memory occupation: " << newNode.size * 4 << std::endl;
}

void MemoryMonitor::popNode()
{
    if(!_nodes.size())
    {
        std::cout << "No nodes to pop" << std::endl;
        return;
    }

    int deallocatedMemory = (getLastNode().size);
    std::cout << "Popped node with memory occupation: " << deallocatedMemory * 4 << std::endl;

    delete[] _nodes[_nodes.size() - 1].data;

    _nodes.pop_back();
}

void MemoryMonitor::printMemoryOccupation(const int numberOfNodes)
{
    const int SIZE = _nodes.size();
    size_t allMemory = 0;
    int numNodes = numberOfNodes;

    if(numberOfNodes > SIZE)
    {
        numNodes = SIZE;
    }

    for(int i = 0; i < numNodes; ++i)
    {
        allMemory += (_nodes[i].size * 4);
    }

    std::cout << "Memory occupation for first " << numberOfNodes
              << " memory nodes is: " << allMemory << std::endl;
}

MemoryNode MemoryMonitor::getLastNode() const
{
    return _nodes[_nodes.size() - 1];
}

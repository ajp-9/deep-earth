#pragma once

#include <memory>
#include "../Type/BaseBlockType.hpp"

struct Node
{
	Node();
	Node(byte id);

	byte m_ID; 

private:

	byte m_Data;
};

/*
data format

1 -
2 -
3 -
4 -
5 -
6 -
7 -
8 -

*/

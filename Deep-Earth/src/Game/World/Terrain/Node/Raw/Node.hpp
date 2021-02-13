#pragma once

#include <memory>
#include "../Type/BaseBlockType.hpp"

struct Node
{
	Node();
	Node(byte id);

	byte m_ID = 0;

private:

	byte m_Data = 0;
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

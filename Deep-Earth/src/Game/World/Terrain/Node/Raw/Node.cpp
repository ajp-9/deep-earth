#include "Node.hpp"

Node::Node()
	: m_ID(0) // air
{}

Node::Node(byte id)
	: m_ID(id)
	, m_Data(0)
{}

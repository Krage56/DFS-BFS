#include "GraphNode.h"



GraphNode::GraphNode(size_t num){
	_number = num;
}

const std::unordered_map<size_t, size_t>& GraphNode::getWays() const
{
	return _ways;
}


size_t GraphNode::getWay(size_t node) const{
	auto way = _ways.find(node);
	if (way != _ways.end()) {
		return way->second;
	}
	else {
		return 0;
	}
}

void GraphNode::addNeighbour(size_t node_num, size_t way){
	_ways.insert(std::make_pair(node_num, way));
}

GraphNode::~GraphNode()
{
}

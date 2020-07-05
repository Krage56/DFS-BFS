#include "GraphNode.h"



GraphNode::GraphNode(long long num){
	_number = num;
}

const std::unordered_map<long long, long long>& GraphNode::getWays() const
{
	return _ways;
}


long long GraphNode::getWay(long long node) const{
	auto way = _ways.find(node);
	if (way != _ways.end()) {
		return way->second;
	}
	else {
		return 0;
	}
}

void GraphNode::addNeighbour(long long node_num, long long way){
	_ways.insert(std::make_pair(node_num, way));
}

GraphNode::~GraphNode()
{
}

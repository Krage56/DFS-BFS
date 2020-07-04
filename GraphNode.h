#pragma once
#include <unordered_map>
class GraphNode{
	std::unordered_map<size_t, size_t> _ways;
public:
	GraphNode(size_t num);
	//порядковый номер вершины и расстояние до неё
	const std::unordered_map<size_t, size_t>& getWays() const;
	size_t _number;
	size_t getNum()const { return _number; };
	size_t getWay(size_t node)const;
	void addNeighbour(size_t node_num, size_t way);
	~GraphNode();
};


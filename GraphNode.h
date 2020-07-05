#pragma once
#include <unordered_map>
class GraphNode{
	std::unordered_map<long long, long long> _ways;
public:
	GraphNode(long long num);
	//порядковый номер вершины и расстояние до неё
	const std::unordered_map<long long, long long>& getWays() const;
	long long _number;
	long long getNum()const { return _number; };
	long long getWay(long long node)const;
	void addNeighbour(long long node_num, long long way);
	~GraphNode();
};


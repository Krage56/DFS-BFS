#pragma once
#include <map>
#include <fstream>
#include "GraphNode.h"
#include <tuple>
class Graph{
	std::unordered_map<size_t, GraphNode*>_data;
public:
	Graph();
	void getData(char*argv[]);
	void showData()const;
	bool DFS(size_t num)const;
	~Graph();
protected:
	void return_in_pos(std::fstream *file, bool pos)const;
	bool is_empty_file(std::fstream *file)const;
	bool processing(std::fstream *file);
};


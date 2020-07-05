#pragma once
#include <map>
#include <fstream>
#include "GraphNode.h"
#include <tuple>
#include <vector>
class Graph{
	std::unordered_map<long long, GraphNode*>_data;
public:
	Graph();
	void getData(char*argv[]);
	void showData()const;
	std::tuple<bool, std::vector<long long>> DFS(long long num, long long origin = 0)const;
	std::tuple<bool, std::vector<long long>> BFS(long long num, long long origin = 0)const;
	std::vector<long long> getPath(std::vector<long long>& prior, long long dest, long long origin = 0)const;
	~Graph();
protected:
	void return_in_pos(std::fstream *file, bool pos)const;
	bool is_empty_file(std::fstream *file)const;
	bool processing(std::fstream *file);
};


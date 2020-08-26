#include <iostream>
#include "Graph.h"
#include <tuple>
#include <vector>
using namespace std;

int main(int args, char*argv[]) {
	Graph g;
	g.getData(argv);
	//g.showData();
	bool isExist;
	vector<long long> way;
	std::tie(isExist, way) = g.BFS(7);
	if (isExist) {
		for (const auto el : g.getPath(way, 7))
			cout << el << " ";
	}
	cout <<"Hello world!" << endl;
	return 0;
}
#include <iostream>
#include "Graph.h"
#include <stack>
using namespace std;

int main(int args, char*argv[]) {
	Graph g;
	g.getData(argv);
	g.showData();
	g.DFS(8);
	system("pause");
	return 0;
}
#include "Graph.h"
#include <tuple>
#include <vector>
#include <stack>
using namespace std;
tuple<bool, vector<long long>> Graph::DFS(long long num, long long origin) const {
	stack<long long> stack;
	if (_data.find(num) == _data.end()) {
		vector<long long> empty;
		return make_tuple(false, empty);
	}
	stack.push(origin);
	vector<bool> visited(_data.size());
	vector<long long>prior(_data.size());
	for (long long i = 0; i < _data.size(); ++i) {
		prior[i] = -1;
	}
	long long current = origin;
	prior[origin] = origin;
	while (!stack.empty() && num != current) {
		current = stack.top();
		if (!visited[current]) {
			visited[current] = 1;
			for (const auto iter : _data.at(current)->getWays()) {
				stack.push(iter.first);
				prior[iter.first] = !visited[iter.first] ? current : prior[iter.first];
			}
		}
		else {
			stack.pop();
		}
	}
	return make_tuple(static_cast<bool>(visited[num]), prior);
}

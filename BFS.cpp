#include "Graph.h"
#include <tuple>
#include <vector>
#include <queue>
using namespace std;
tuple<bool, vector<long long>> Graph::BFS(long long num, long long origin) const {
	queue<long long> queue;
	if (_data.find(num) == _data.end()) {
		vector<long long> empty;
		return make_tuple(false, empty);
	}
	queue.push(origin);
	vector<bool> visited(_data.size());
	vector<long long>prior(_data.size());
	for (long long i = 0; i < _data.size(); ++i) {
		prior[i] = -1;
	}
	long long current = origin;
	prior[origin] = origin;
	while (!queue.empty() && num != current) {
		current = queue.front();
		if (!visited[current]) {
			visited[current] = 1;
			for (const auto iter : _data.at(current)->getWays()) {
				queue.push(iter.first);
				prior[iter.first] = !visited[iter.first] ? current : prior[iter.first];
			}
		}
		else {
			queue.pop();
		}
	}
	return make_tuple(static_cast<bool>(visited[num]), prior);
}

#include "Graph.h"
#include <tuple>
#include <vector>
#include <queue>
using namespace std;
auto Graph::BFS(long long num, long long origin) const {
	queue<long long> queue;
	if (_data.find(num) == _data.end()) {
		vector<long long> empty;
		return make_tuple(false, empty, empty);
	}
	queue.push(origin);
	vector<bool> visited(_data.size());
	vector<long long>prior(_data.size());
	vector<long long>prices(_data.size());
	for (long long i = 0; i < _data.size(); ++i) {
		prior[i] = -1;
		prices[i] = -1;
	}
	long long current = origin;
	prior[origin] = origin;
	prices[origin] = _data.at(origin)->getWay(origin);//сразу определяем, сколько от элемента до себя же
	while (!queue.empty() && num != current) {
		current = queue.front();
		if (!visited[current]) {
			visited[current] = true;
			for (const auto iter : _data.at(current)->getWays()) {
				queue.push(iter.first);
				if(prices[current] == 0){
                    if(!visited[iter.first] || prices[iter.first] > 1){
                        prices[iter.first] = 1;
                    }
				}
				if(!visited[iter.first] || prices[iter.first] > prices[current] + 1){
                    prices[iter.first] = prices[current] + 1;
				}
				prior[iter.first] = !visited[iter.first] ? current : prior[iter.first];
			}
		}
		else {
			queue.pop();
		}
	}
	return make_tuple(static_cast<bool>(visited[num]), prior, prices);
}

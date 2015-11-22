#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct node
{
	int weight;
	list<int> neighbours;
};

int process (vector<node> graph, vector<int> completed, int curr, int &sum)
{
	completed.push_back(curr);
	for (auto it = graph[curr].neighbours.begin(); it != graph[curr].neighbours.end(); it++)
	{
		if (find(completed.begin(), completed.end(), *it) == completed.end())
		{
			process(graph, completed, *it, sum);	
		}
	}
	sum += graph[curr].weight;
	return sum;
}

int dfs_weight_sum(vector<node> graph, int n, int start)
{
	vector<int> completed;
	int sum = 0;
	return process(graph, completed, start, sum);
}

int main()
{
	int n;
	cin >> n;

	vector<node> graph;

	node new_node;
	for (int i=0; i<n; i++)
	{
		cin >> new_node.weight;
		graph.push_back(new_node);
	}

	int node1, node2;
	for (int i=0; i<n-1; i++)
	{
		cin >> node1 >> node2;
		node1--;
		node2--;
		graph.at(node1).neighbours.push_back(node2);
		graph.at(node2).neighbours.push_back(node1);
	}

	// for (auto it=graph.begin(); it != graph.end(); it++)
	// {
	// 	cout << "Weight: " << it->weight <<". Neighbors: ";
	// 	for (auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
	// 	{
	// 		cout << *it2+1 << " ";
	// 	}
	// 	cout << endl;
	// }
	list<int> temp;
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		temp.clear();
		//copy (it->neighbours.begin(), it->neighbours.end(), temp.begin());
		temp = it->neighbours;
		for (auto it2 = temp.begin(); it2 != temp.end(); it2++)
		{
			it->neighbours.remove(*it2);
			graph[*it2].neighbours.remove(it-graph.begin());
			cout << dfs_weight_sum(graph, n, it-graph.begin()) << " " << dfs_weight_sum(graph, n, *it2)<< endl;

			it->neighbours.push_back(*it2);
			graph[*it2].neighbours.push_back(it-graph.begin());
		}
	}
	

	return 0;
}
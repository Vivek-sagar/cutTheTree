#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include <math.h>

using namespace std;

struct node
{
	int weight;
	int partial_sum;
	list<int> neighbours;
};

int partial_summer_recursive (vector<node> &graph, vector<int> &completed, int curr)
{
	completed.push_back(curr);
	graph[curr].partial_sum = graph[curr].weight;

	for (auto it = graph[curr].neighbours.begin(); it != graph[curr].neighbours.end(); it++)
	{
		if (find(completed.begin(), completed.end(), *it) == completed.end())
		{
			graph[curr].partial_sum += partial_summer_recursive(graph, completed, *it);	
		}
	}
	
	return graph[curr].partial_sum;
}

// int dfs_weight_sum(vector<node> graph, int n, int start)
// {
// 	vector<int> completed;
// 	int sum = 0;
// 	return process(graph, completed, start);
// }

int dfs_weight_sum_custom_stack(vector<node> &graph, int n, int start)
{
	int curr = start;
	list<int> to_check;
	to_check.push_back(curr);
	list<int> completed;
	int sum = 0;
	while (to_check.size() > 0)
	{
		curr = to_check.back();
		to_check.pop_back();
		for (auto it2=graph[curr].neighbours.begin(); it2 != graph[curr].neighbours.end(); it2++)
		{
			if (find(completed.begin(), completed.end(), *it2) == completed.end())
				to_check.push_back(*it2);
		}
		sum += graph[curr].weight;

		//graph[curr].partial_sum = sum;
		//cout << "node: " << curr << ": " << graph[curr].partial_sum << " " << endl;
		completed.push_back(curr);
	}
	return sum;
}

void print_partial_sums(vector<node> graph)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		cout << it-graph.begin() << ": " << it->partial_sum << endl;
	}
}

void print_graph(vector<node> graph)
{
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		cout << it-graph.begin() << "(" << it->weight << "){" << it->partial_sum << "}: ";
		for (auto it2 = it->neighbours.begin(); it2 != it->neighbours.end(); it2++)
		{
			cout << *it2 << " ";
		}
		cout << endl;
	}
}

int find_best_partial_sum(vector<node> graph, int sum)
{
	int best = graph[0].partial_sum;
	int best_node = 0;
	//cout << "sum/2 is: " << sum/2 << endl;
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		//cout << "considering: " << it-graph.begin() <<  " " << it->partial_sum  << "\n";
		if (abs(it->partial_sum - sum/2) < abs(best-sum/2))
		{
			//cout << "best\n";
			best_node = it-graph.begin();
			best = it->partial_sum;
		}
	}
	//best_node--;
	//cout << best_node << " " << best << endl;
	return best_node;
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

	// list<int> temp;
	// int smallest_difference = 10000;
	// int difference;
	// for (auto it = graph.begin(); it != graph.end(); it++)
	// {
	// 	temp.clear();
	// 	//copy (it->neighbours.begin(), it->neighbours.end(), temp.begin());
	// 	temp = it->neighbours;
	// 	for (auto it2 = temp.begin(); it2 != temp.end(); it2++)
	// 	{
	// 		it->neighbours.remove(*it2);
	// 		graph[*it2].neighbours.remove(it-graph.begin());
	// 		difference =  abs(dfs_weight_sum_custom_stack(graph, n, it-graph.begin()) - dfs_weight_sum_custom_stack(graph, n, *it2));
	// 		if (difference < smallest_difference)
	// 			smallest_difference = difference;
	// 		it->neighbours.push_back(*it2);
	// 		graph[*it2].neighbours.push_back(it-graph.begin());
	// 	}
	// }
	// cout << smallest_difference;

	//int sum = dfs_weight_sum_custom_stack(graph, n, 0);
	vector<int> completed;
	partial_summer_recursive(graph, completed, 0);
	int sum = graph[0].partial_sum;
	//print_graph(graph);
	int best_node = find_best_partial_sum(graph, sum);
	//cout << best_node << endl;
	// list<int> temp;
	// int smallest_difference = 10000;
	// int difference;
	// temp = graph[best_node].neighbours;
	// for (auto it = temp.begin(); it != temp.end(); it++)
	// {
	// 		graph[best_node].neighbours.remove(*it);
	// 		graph[*it].neighbours.remove(best_node);
	// 		//cout << "considering: "  << *it << endl;
	// 		completed.clear();
	// 		partial_summer_recursive(graph, completed, best_node);
	// 		int val1 = graph[best_node].partial_sum;
	// 		completed.clear();
	// 		partial_summer_recursive(graph, completed, *it);
	// 		int val2 = graph[*it].partial_sum;
	// 		//difference =  abs(dfs_weight_sum_custom_stack(graph, n, best_node) - dfs_weight_sum_custom_stack(graph, n, *it));
	// 		difference = abs(val1-val2);
	// 		if (difference < smallest_difference)
	// 			smallest_difference = difference;
	// 		graph[best_node].neighbours.push_back(*it);
	// 		graph[*it].neighbours.push_back(best_node);
	// }

	int largest_partial_sum = 0;
	int largest_partial_sum_node = 0;
	for (auto it = graph[best_node].neighbours.begin(); it != graph[best_node].neighbours.end(); it++)
	{
		if (graph[*it].partial_sum > largest_partial_sum)
		{
			largest_partial_sum = graph[*it].partial_sum;
			largest_partial_sum_node = *it;
		}
	}

	graph[best_node].neighbours.remove(largest_partial_sum_node);
	graph[largest_partial_sum_node].neighbours.remove(best_node);
	completed.clear();
	partial_summer_recursive(graph, completed, best_node);
	int val1 = graph[best_node].partial_sum;
	completed.clear();
	partial_summer_recursive(graph, completed, largest_partial_sum_node);
	int val2 = graph[largest_partial_sum_node].partial_sum;
	//difference =  abs(dfs_weight_sum_custom_stack(graph, n, best_node) - dfs_weight_sum_custom_stack(graph, n, *it));
	cout << abs(val1-val2) << endl;
	//print_partial_sums(graph);

	//cout << smallest_difference << endl;

	return 0;
}

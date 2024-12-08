#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

const float INF = numeric_limits<float>::max(); //used to represent infinity

//takes as parameters the starting node and the graph’s adjacency list representation where each node has a list of pairs (neighbor, weight)
void dijkstra(int startingNode, int target, const vector<vector<pair<int, float>>>& adjList, vector<float>& distances, vector<int>& previous) {
    int n = adjList.size(); //number of nodes
    distances.assign(n, INF); //to store shortest distances to all nodes from the starting node, initializes all distances to INF
    previous.assign(n, -1); //to keep track of the previous node, used to track the path, -1 because there's no previous node initially
    distances[startingNode] = 0; //distance of source node is set to 0 since it's the starting point

    //priority queue where the smallest element will always be at the top of the queue (specified on 'greater<pair>' parameter)
    priority_queue<pair<int, float>, vector<pair<int, float>>, greater<pair<int, float>>> pq;
    pq.push({0, startingNode});

    while(!pq.empty()) {
        float currentDistance = pq.top().first; //returns the top element (smallest element) of the pq, distance is the first element of the pair
        float currentNode = pq.top().second; //the current node being processed is the second element of the pair
        pq.pop(); //removes the node from the pq
        //in each iteration the node with the smallest distance is taken from pq

        if(currentDistance > distances[currentNode]) continue; //skip the path if the current distance is not the shortest distance

        for(const auto& neighbor : adjList[currentNode]) {
            int adjNode = neighbor.first;
            float weight = neighbor.second;

            //check if the distance to the adjNode through the current node is shorter than any distance recorded so far
            if(distances[currentNode] + weight < distances[adjNode]) {
                distances[adjNode] = distances[currentNode] + weight; //new distance for the adjNode
                previous[adjNode] = currentNode; //keep track of the previous node on the shortest path
                pq.push({distances[adjNode], adjNode});
            }
        }
    }
}

//function to trace back the path with the shortest distance and print it
void tracePath(int target, const vector<int>& previous) { //target is the final node to reach
    vector<int> path;

    //we begin from the target to find the path back to the starting node, reaching -1 means the start of the path has been reached
    //tracer = previous[tracer] will move to the previous node on the shortest path
    for (int tracer = target; tracer != -1; tracer = previous[tracer]) { //tracer refers to the current node we’re tracing back from
        path.push_back(tracer); //adds the current node to the path vector, the path is currently in reverse
    }
    reverse(path.begin(), path.end()); //reverse the path to get the right order of the nodes

    cout << "Shortest path: ";
    for (int i = 0; i < path.size(); ++i) { //++i increments the value of i and returns the incremented value (i++ returns the original value)
        cout << path[i];                    //optimal because no temporary copy of i is created
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;

    cout << "Steps taken: " << path.size() << endl;
}

/*int main() {
    int nodes = 8; //number of nodes
    vector<vector<pair<int, float>>> graph(nodes);

    //add vertices to the graph {adjNode, weight}
    //vertices based on my custom google maps' graph, where:
    //A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7
    graph[0].push_back({1, 129.74});
    graph[0].push_back({3, 51.23});
    graph[1].push_back({0, 129.74});
    graph[1].push_back({2, 49.83});
    graph[2].push_back({1, 49.83});
    graph[2].push_back({3, 128.96});
    graph[2].push_back({5, 103.45});
    graph[2].push_back({6, 200.90});
    graph[3].push_back({2, 128.96});
    graph[3].push_back({4, 94.47});
    graph[4].push_back({5, 132});
    graph[5].push_back({2, 103.45});
    graph[5].push_back({7, 198.46});
    graph[6].push_back({2, 200.90});
    graph[6].push_back({7, 103.12});
    graph[7].push_back({6, 103.12});

    float startingNode_, target_;
    cout << "Starting node: ";
    cin >> startingNode_;
    cout << "Final node: ";
    cin >> target_;

    if (startingNode_ > nodes || target_ > nodes) {
        cerr << "Error: Exceeded number of nodes." << endl;
        exit(-1);
    }

    vector<float> distances_;
    vector<int> previous_;
    dijkstra(startingNode_, target_, graph, distances_, previous_);

    if(distances_[target_] == INF) {
        cout << "Target node unreachable from the specified node. No existent path from " << startingNode_ << " to " << target_ << "." << endl;
    }
    else {
        cout << "Shortest distance from " << startingNode_ << " to " << target_ << ": " << distances_[target_]  << " meters" << endl;
        tracePath(target_, previous_);
    }

    return 0;
}*/

#endif
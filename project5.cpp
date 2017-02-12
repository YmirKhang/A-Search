/*
Student Name:A.Emirhan Karagül
Student Number: 2013400057
Project Number:5
Operating System:250.ova
Compile Status: Compiled
Program Status: Working
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;

struct LessThanByFValue
{
    bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs) const
    {
        return lhs.second > rhs.second;
    }
};

//The graph structure I used in project 4, the only difference is this is implemented with adjacency Matrix in this project.
struct DistrictGraph{

        int size;

        int **adjMatrix;
    //Default constructor of graph
        DistrictGraph(int n){
            size=n;
            adjMatrix = new int*[n];
            for (int i = 0; i <n ; ++i) {
                adjMatrix[i] = new int[n];
            }
        }
    //Func to add edges to the graph
        int addEdges(int i, int j,int dist){
            adjMatrix[i][j] =dist;
            adjMatrix[j][i] =dist;
        }
    //A star algorithm which takes a src node, dest node and the list of heuristic functions.
    //returns the magnitude of the shortest path.
        int AStar(int src, int dest, int heur []);




};

int DistrictGraph::AStar(int src, int dest, int *heur) {


    //A priority queue to order the vertices that are closest to the target like dijsktra
    priority_queue<pair<int,int>,vector<pair<int,int>>,LessThanByFValue> openNodes;

    openNodes.push(make_pair(src,heur[src]));

    int * fscore= new int[size];
    //List of f scores whih are the sum of dist and heur of a given vertex.
    for (int k = 0; k <size ; ++k) {
        fscore[k] =INFINITY;
    }
    fscore[src] = heur[src];

    bool *openSet = new bool[size];
    for (int i = 0; i <size ; ++i) {
        openSet[i] = false;
    }
    openSet[src] = true;
    bool *closedSet = new bool[size];
    for (int i = 0; i <size ; ++i) {
        closedSet[i] = false;
    }

    int *dist = new int[size];
    for (int j = 0; j <size ; ++j) {
        dist[j] = INFINITY;
    }
    dist[src] =0;
    pair<int,int> curr;
    int neig;
    int tempdist;
    while(!openNodes.empty()){
        curr = openNodes.top();
        if(curr.first==dest){
           return dist[curr.first]; //burası direk curr.second olabilir
        }
        openNodes.pop();
        openSet[curr.first] = false;
        closedSet[curr.first] = true;
        queue<int> neibors;
        for (int i = 0; i <size ; ++i) {
            if(adjMatrix[curr.first][i]!=0){
                neibors.push(i);
            }
        }
        while(!neibors.empty()){
            neig = neibors.front();
            neibors.pop();
         /*   if(closedSet[neig]){
                continue;
            } */
            tempdist = dist[curr.first]+adjMatrix[curr.first][neig];
            if(!openSet[neig]){

                openNodes.push(make_pair(neig,dist[neig]+heur[neig]));
                openSet[neig] = true;
            }else if(tempdist>=dist[neig]){
                continue;
            }
            dist[neig] = tempdist;
            fscore[neig] = dist[neig] + heur[neig];
        }

    }

    return 0;
}

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1[input_file] [output_file]" << endl;
        return 1;
    }

    ifstream infile(argv[1]);


    //This part initializes the graph with the given values in the input file.

    int size;
    infile >> size;
    int * heuristic = new int[size];
     DistrictGraph graph = DistrictGraph(size);
     int edges;
    infile >> edges;
    int temp= 0;
     for (int m = 0; m <size ; ++m) {
         infile>>temp;
         heuristic[m] =temp;
     }
    int j, k, dist;
    for (int i = 0; i < edges; i++) {
        infile >> j;
        infile >> k;
        infile >> dist;
        graph.addEdges(j, k, dist);
    }
     int source;
     int target;

     infile>>source;
     infile>>target;
    //Runs the A star algorithm to find the shortest path.
    int result = graph.AStar(source,target, heuristic);
    cout<<result<<endl;
    //writes to file.
    freopen(argv[2],"w",stdout);

    cout<<result;


}


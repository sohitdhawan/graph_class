// code by Sohit Dhawan
// 2022ucs0112
#include <bits/stdc++.h>
#define ll long long
using namespace std;

// improvements : I made for zero and one based indexing only

class Graph{
    private:
    // varialbes
    int V; // number of vertices
    int E; // number of edges
    vector<vector<int>> adj; // adjacency list 
    vector<pair<int,int>> edges;
    vector<vector<int>> mat;
    
    // #1.1 dfs
    void dfs_helper_print(int node , vector<vector<int>> adj,vector<int> &ans,int visited[]){
        visited[node] =1;
        ans.push_back(node);
        for(auto i : adj[node]){
            if(!visited[i]) dfs_helper_print(i,adj,ans,visited);
        }
    }
    
    // #1.2 dfs
    void dfs_connected_components(int node, vector<vector<int>> &adj, vector<int> &vis){  
        vis[node] = 1;
        for(auto x : adj[node] ){
            if(!vis[x]){
                dfs_connected_components(x,adj,vis);   
            }
        }
    }
    
    // #2 cycle detection
    bool detect_cycle_helper(int src,vector<int> &vis){
        // {node,parent}
        queue<pair<int,int>> q;
        q.push({src,-1});
        vis[src] = 1;
        while(!q.empty()){
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();
            for(auto it:adj[node]){
                if(!vis[it]){
                    q.push({it,node});
                    vis[it]=1;
                }
                // if standing at a node .. and its adjacent node is visited 
                // then that adjacent node has to be the parent .. else cycle
                else if(it!=parent){
                    return true;
                }
            }
        }
        return false;
    }
            
    public:
    // constructor - 1
    Graph(int V){
        this->V = V;
        adj.resize(V+1);
        mat.resize(V+1, vector<int>(V+1, 0)); 
    }
    
    // constructor - 2
    Graph(int V, int E){
        this->V = V;
        this->E = E;
        adj.resize(V+1);
        edges.resize(E);
        mat.resize(V+1, vector<int>(V+1, 0)); 
    }
    
    // #1 set edges (taking input)
    void set_edges(vector<pair<int,int>> &edges){
        E = edges.size();
        this->edges = edges;
    }
    
    // #2 function to print edges
    void print_edges(){
        cout<<"Edges of the graphs are : "<<endl;
        for(auto it:edges){
            cout<<it.first<<" "<<it.second<<endl;
        }
        cout<<endl;
    }
    
    // #3 function to return edges
    vector<pair<int,int>> get_edges(){
        return edges;
    }
    
    // #4 function to return No of possible graphs with V vertices 
    int countingGraphs()
    {
        return pow(2,(V*(V-1))/2);   
    }
    
    // #4 function to set the adjacency list 
    void set_adj_list() {
        for(int i=0;i<edges.size();i++){
            int u = edges[i].first;
            int v = edges[i].second;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    
    // #5 function to return the adjacency list
    vector<vector<int>>  get_adj_list(){
        return adj;
    }
    
    // #6 function to print adjacency list
    void print_adj_list(){
        cout<<"printing adjacency list of graph : "<<endl;
        for(int i=0;i<adj.size();i++){
            cout<<i<< ": ";
            for(int j=0;j<adj[i].size();j++) {
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    // #7 setting adjacency matrix
    void set_adj_mat() {
        // Initialize matrix
        for (auto it : edges) {
            int u = it.first;
            int v = it.second;
            mat[u][v] = 1;
            mat[v][u] = 1; // For undirected graph
        }
    }

    // #8 return adjacency matrix
    vector<vector<int>> get_adj_mat(){
        return mat;
    }
    
    // #9 print adjacency matrix
    void print_adj_mat(){
        for(auto i:mat){
            for(auto j:i){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }
    
    // #10 function to return bfs of Graph , starting from node 0.
    vector<int> print_BFS(){
        vector<bool> visited(V,0);
        vector<int> ans;
        queue<int> q;
        
        q.push(0);
        visited[0]=1;
        ans.push_back(0);
        
        while(!q.empty()){
            int temp = q.front();
            q.pop();
            
            for(auto x : adj[temp]){
                if(!visited[x]){
                    q.push(x);
                    visited[x]=1;
                    ans.push_back(x);
                }
            }
        }
        return ans;
        
    }
    
    // #11 function to return DFS of Graph
    vector<int> print_DFS(){
        vector<int> ans;
        int visited[V]={0};
        dfs_helper_print(0,adj,ans,visited);
        return ans;
    }
    
    // #12 number of connected components
    int connected_components() {
        // intitalising
        int count = 0;
        vector<int> vis(V,0);

        for(int i=0;i<V;i++){
            if(!vis[i]){
                count++;
                dfs_connected_components(i,adj,vis);
            }
        }

        return count;
    }
    
    
    // #13 check if cycle or not
    bool is_cycle(){
        vector<int> vis(V,0);
        for(int i=0;i<V;i++){
            if(!vis[i]){
                // if cycle found then true
                if(detect_cycle_helper(i,vis)){
                    return true;
                }
            }
        }
        return false;
    }
    
    
    

    
    
};
int main()
{
    // int V,E;
    // cin>>V>>E;
    // vector<pair<int,int>> edges(E);
    // for(int i=0;i<E;i++){
    //     cin>>edges[i].first>>edges[i].second;
    // }
    
    // input 1 -> normal 
    int V=6,E=5;
    vector<pair<int,int>> edges(E);
    edges[0]={0,3};
    edges[1]={0,4};
    edges[2]={3,1};
    edges[3]={4,2};
    edges[4]={3,5};
    
    // // input 2 -> single component cycle
    // int V=6,E=6;
    // vector<pair<int,int>> edges(E);
    // edges[0]={0,5};
    // edges[1]={0,4};
    // edges[2]={5,3};
    // edges[3]={4,2};
    // edges[4]={3,1};
    // edges[5]={2,1};
    
    // // input 3 -> disconnected components with cycle in 3rd
    // int V=6,E=4;
    // vector<pair<int,int>> edges(E);
    // edges[0]={2,4};
    // edges[1]={2,5};
    // edges[2]={4,3};
    // edges[3]={5,3};
    
    

    
    Graph g(V);
    g.set_edges(edges);
    g.set_adj_list();
    g.print_adj_list();


    return 0;
}
















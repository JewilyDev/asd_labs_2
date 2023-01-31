
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

std::queue<int> queue;
std::vector<int> used;
int A;
int **graph_matrix;
int main_node;
std::vector<std::vector<int>> sh_path;
int  *nodes;
void fill_path(int node,int past_node){
    if(node != main_node){
        if(!sh_path[past_node].empty()){
            std::cout << node << past_node << std::endl;
            for(int i = 0 ; i < sh_path[past_node].size(); i++){
                if(sh_path[past_node][i]){
                    std::cout << sh_path[past_node][i] << std::endl;
                    sh_path[node].push_back(sh_path[past_node][i]);
                }

            }
        }
        sh_path[node].push_back(node);
    }
}
bool queue_search(int e, std::queue<int> q){
    if(!q.empty()){
        for(int i = 0; i < q.size(); i++){
            int b = q.front();
            if(b == e)
                return true;
            q.pop();
        }
    }

    return false;
}
void bfs(int a){
    used.push_back(a);
    for(int i = 0 ; i < A; i++){
        int adjacent_node = graph_matrix[a][i];
        if(
                std::find(used.begin(),used.end(),adjacent_node) == std::end(used) &&
                !queue_search(adjacent_node,queue)
                && adjacent_node
                )
        {
            fill_path(adjacent_node,a);
            queue.push(adjacent_node);
        }
    }
    queue.pop();
}
int main() {
    std::ifstream in("D:\\inp.txt");
    int x,y;
    int c = 0;
    if (in.is_open())
    {
        while (in >> x >> y)
        {
            if(!c){
                A = x + 1;
                graph_matrix = new int*[A];
                nodes = new int[A];
                for (int i = 0; i < A; i++){
                    graph_matrix[i] = new int[A];
                    std::memset(graph_matrix[i],0,sizeof(int) * A);
                }
            }
            else{
                if(nodes[x] != 1){
                    nodes[x] = 1;
                }
                if(nodes[y] != 1){
                    nodes[y] = 1;
                }
                graph_matrix[x][y] = y;
                graph_matrix[y][x] = x;
            }
            c++;
        }
    }
    sh_path.resize(A,std::vector<int>(A));
    std::cin >> main_node;
    if(main_node > A){
        std::cout << "The node is out of the graph" << std::endl;
        return 0;
    }
    sh_path.at(main_node).push_back(main_node);
    queue.push(main_node);
    while(!queue.empty()){
        bfs(queue.front());
    }
    for(int x = 0; x < A; x++){
        if(nodes[x] == 1){
            if(!sh_path[x].empty()){
                std::cout << "The shortest path from the node with number  " << x << " :";
                std::reverse( sh_path[x].begin(), sh_path[x].end());
                for(auto n : sh_path[x]){
                    if(n)
                        std::cout << n << " ";
                }
                std::cout << std::endl;
            }
        }
    }
    for(int i = 0; i < A; ++i)
        delete[] graph_matrix[i];
    delete[] graph_matrix;
    return 0;
}

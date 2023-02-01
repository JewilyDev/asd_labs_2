
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

std::queue<int> queue;
std::vector<int> used;
std::vector<std::vector<int>> components;
std::vector<int> comp;
int A;
int components_count;
int **graph_matrix;

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
    comp.push_back(a);
    for(int i = 1 ; i < A; i++){
        int adjacent_node = graph_matrix[a][i];

        if(
                std::find(used.begin(),used.end(),adjacent_node) == std::end(used) &&
                !queue_search(adjacent_node,queue)
                && adjacent_node
                )
        {
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
                for (int i = 0; i < A; i++){
                    graph_matrix[i] = new int[A];
                    std::memset(graph_matrix[i],0,sizeof(int) * A);
                }
            }
            else{
                graph_matrix[x][y] = y;
                graph_matrix[y][x] = x;
            }
            c++;
        }
    }

    for(int i = 1; i < A; i++){
        comp.clear();
        if(std::find(used.begin(),used.end(),i) == std::end(used)){
            components_count += 1;
            queue.push(i);
            while(!queue.empty()){
                bfs(queue.front());
            }
            components.push_back(comp);
        }
    }

    for(auto n : components){
        for(auto x : n){
            std:: cout << x << " ";
        }
        std::cout << std::endl;
    }
    for(int i = 0; i < A; ++i)
        delete[] graph_matrix[i];
    delete[] graph_matrix;

    return 0;
}



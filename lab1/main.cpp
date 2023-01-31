#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Point {
    int x;
    int y;
    Point(int x_i,int y_i) : x(x_i),y(y_i)
    {}

};
int x_comp(Point a, Point b){
    return a.x <= b.x;
}
int y_comp(Point a, Point b){
    return a.y <= b.y;
}
int vector_prod(Point p1,Point p2, Point p3){
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p2.x));
}
std::vector<Point> createHull(std::vector<Point>res_hull,std::vector<Point> sub_hull){
    for(auto n : sub_hull){
        while(res_hull.size() >= 2 && vector_prod(res_hull[res_hull.size() - 2],res_hull[res_hull.size() - 1],n) >= 0){
            res_hull.pop_back();
        }
        res_hull.push_back(n);
    }
    return res_hull;
}


int main() {
    std::ifstream in("D:\\inp.txt"); // окрываем файл для чтения
    std::vector<Point> points;
    std::vector<Point> up;
    std::vector<Point> down;
    std::vector <Point> hull_up;
    std::vector <Point> hull_down;
    std::vector <Point> hull;

    int x,y = 0;
    if (in.is_open())
    {
        while (in >> x >> y)
        {
            points.push_back(Point(x,y));

        }
    }
    std::sort(points.begin(),points.end(),y_comp);
    std::sort(points.begin(),points.end(),x_comp);

    Point A = points[0];
    Point B = points[points.size() - 1];
    for(int i = 0; i< points.size() ; i++){
        if(vector_prod(A,B,points[i]) > 0){
            hull_up.push_back(points[i]);
        }else{
            hull_down.push_back(points[i]);
        }
    }

    std::reverse( hull_down.begin(), hull_down.end());
    up = createHull(up,hull_up);
    down = createHull(down,hull_down);
    hull.insert(hull.begin(), up.begin(), up.end());
    hull.insert(hull.end(), down.begin(), down.end());
    for(Point n : hull){
        std::cout << n.x << "  " << n.y << std::endl;
    }
    in.close();
    return 0;
}


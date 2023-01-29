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

int x_comp_stable(Point a, Point b){
    return a.x <= b.x;
}
int y_comp_stable(Point a, Point b){
    return a.y >= b.y && a.x == b.x;
}
int vector_prod(int x_1,int y_1,int x_2 , int y_2){
    return (x_1 * y_2 - x_2 * y_1);
}
bool isBad(Point p_1, Point p_2,Point p_3,int modifier){
    return ((vector_prod(p_2.x - p_1.x,p_2.y - p_1.y,p_3.x - p_2.x,p_3.y - p_2.y) * modifier) < 0);
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
    std::sort(points.begin(),points.end(),x_comp_stable); // Остортировали по возрастанию x
    Point A = Point(0,0);
    Point B = Point(0,0);
    for(int i = 0; i< points.size() ; i++){
        if(i && points[i].x != A.x)
            break;
        if(A.y < points[i].y)
          A = points[i];
    }
    std::sort(points.begin(),points.end(),y_comp_stable); // Остортировали по возрастанию y
    B = points[points.size() - 1];
    for(int i = 0; i < points.size() ; i++){
        if(points[i].y >= A.y){
            up.push_back(points[i]);
        } else{
            down.push_back(points[i]);
        }
    }
    int sz = 0;
    std::reverse( down.begin(), down.end() );
    hull_up.push_back(A);
    Point c = Point(0,0);
    for(Point n : up){

        c = n;
        while(sz >= 2 && isBad(c,hull_up[sz - 1],hull_up[sz - 2],1)){
            hull_up.erase(hull_up.end() - 2);
            sz--;
        }
        if(c.x != A.x && c.y != A.y){
            hull_up.push_back(c);
            sz++;
        }
    }
    hull_down.push_back(B);
    sz = 0;
    for(Point n : down){
        c = n;
        while(sz >= 2 && isBad(c,hull_down[sz - 1],hull_down[sz - 2],-1)){
            hull_down.erase(hull_down.end() - 2);
            sz--;
        }
        if(c.x != B.x && c.y != B.y){
            hull_down.push_back(c);
            sz++;
        }
    }

    hull.insert(hull.begin(), hull_up.begin(), hull_up.end());
    hull.insert(hull.end(), hull_down.begin(), hull_down.end());
    in.close();

    for(Point n : hull){
        std::cout << n.x << "  " << n.y << std::endl;
    }
    return 0;
}



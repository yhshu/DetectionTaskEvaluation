//
// Created by Yiheng Shu on 2018/7/1.
//

#ifndef DETECTIONTASKEVALUATION_BOUNDBOX_H
#define DETECTIONTASKEVALUATION_BOUNDBOX_H

#include <string>

using namespace std;

class Point {
public:
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

class Rectangle {
public:
    Point leftUp; // 左上角点
    Point rightDown; // 右下角点
    Rectangle(double sx, double sy, double ex, double ey) :
            leftUp(sx, sy), rightDown(ex, ey) {}

    double area() {
        if (leftUp.x >= rightDown.x || leftUp.y >= rightDown.y)
            return 0;
        return (rightDown.x - leftUp.x) * (rightDown.y - leftUp.y);
    }

    Rectangle intersect(Rectangle &r) {
        double startX = max(leftUp.x, r.leftUp.x);
        double startY = max(leftUp.y, r.leftUp.y);
        double endX = min(rightDown.x, r.rightDown.x);
        double endY = min(rightDown.y, r.rightDown.y);
        return Rectangle(startX, startY, endX, endY);
    }
};

class BoundBox : public Rectangle {
public:
    string type; // 目标类型
    bool visited;

    BoundBox(double sx, double sy, double ex, double ey, string type)
            : Rectangle(sx, sy, ex, ey), type(type), visited(false) {
    }
};

#endif //DETECTIONTASKEVALUATION_BOUNDBOX_H

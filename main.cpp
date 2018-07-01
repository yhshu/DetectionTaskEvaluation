#include <iostream>
#include <vector>
#include "BoundBox.h"

using namespace std;

void evaluation(vector<BoundBox> &, vector<BoundBox> &);

double overlap(BoundBox &, BoundBox &);

int main() {
    auto cnt = 0;
    string type;
    double sx = 0, sy = 0, ex = 0, ey = 0;
    bool finish = false;
    while (true) {
        vector<BoundBox> test;
        vector<BoundBox> real;
        cout << "This is photo #" << (++cnt) << endl;
        cout << "Enter the test result, using -1 to finish:" << endl;
        finish = false;
        do {
            cin >> sx;
            if (sx != -1)
                cin >> sy >> ex >> ey >> type;
            else finish = true;
            test.push_back(BoundBox(sx, sy, ex, ey, type));
        } while (!finish);
        cout << "Enter the real result, using -1 to finish:" << endl;

        finish = false;
        do {
            cin >> sx;
            if (sx != -1)
                cin >> sy >> ex >> ey >> type;
            else finish = true;
            real.push_back(BoundBox(sx, sy, ex, ey, type));
        } while (!finish);
        cout << endl;

        evaluation(test, real);

        cout << "Program continue? [Y/n]" << endl;
        cin >> type;
        if (type == "N" || type == "n")
            break;
    }
    return 0;
}

void evaluation(vector<BoundBox> &test, vector<BoundBox> &real) {
    const int test_size = test.size();
    const int real_size = real.size();
    for (int i = 0; i < real_size; i++) {
        for (int j = 0; j < test_size; j++) {

        }
    }
}

double overlap(BoundBox &b1, BoundBox &b2) {
    // 返回：两矩形的交集面积/两矩形的并集面积
    // 两矩形的并集面积 = 两矩形面积之和 - 两矩形的交集面积
    double interaction_area = b1.interact(b2).area();
    double union_area = b1.area() + b2.area() - interaction_area;
    return interaction_area / union_area;
}


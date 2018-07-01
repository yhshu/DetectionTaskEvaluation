#include <iostream>
#include <fstream>
#include <vector>
#include "BoundBox.h"

using namespace std;

void evaluation(vector<BoundBox> &, vector<BoundBox> &, ofstream &);

double overlap(BoundBox &, BoundBox &);

int main() {
    auto cnt = 0;
    string type;
    double sx = 0, sy = 0, ex = 0, ey = 0;
    bool finish = false;
    ofstream ofs("out.txt");
    while (true) {
        vector<BoundBox> test;
        vector<BoundBox> real;
        ofs << "Photo #" << (++cnt) << endl;
        cout << "Enter the real result, using -1 to finish:" << endl;
        finish = false;
        do {
            cin >> sx;
            if (sx != -1) {
                cin >> sy >> ex >> ey >> type;
                real.push_back(BoundBox(sx, sy, ex, ey, type));
            } else {
                finish = true;
            }
        } while (!finish);

        cout << "Enter the test result, using -1 to finish:" << endl;
        finish = false;
        do {
            cin >> sx;
            if (sx != -1) {
                cin >> sy >> ex >> ey >> type;
                test.push_back(BoundBox(sx, sy, ex, ey, type));
            } else {
                finish = true;
            }
        } while (!finish);

        evaluation(test, real, ofs);
        ofs << endl;
        cout << "Program continue? [Y/n]" << endl;
        cin >> type;
        if (type == "N" || type == "n")
            break;
    }
    ofs << "Program finished" << endl;
    return 0;
}

void evaluation(vector<BoundBox> &test, vector<BoundBox> &real, ofstream &ofs) {
    const int test_size = test.size();
    const int real_size = real.size();
    double correct_count = 0; // 正确检测数
    for (auto i = real.begin(); i != real.end(); i++) {
        for (auto j = test.begin(); j != test.end(); j++) {
            if (overlap(*i, *j) >= 0.5 && (*i).type == (*j).type && !(*j).visited) {
                correct_count++;
                (*j).visited = true;
            }
        }
    }
    double precision = correct_count / test_size; // 正确检测/所有实际检测
    double recall = correct_count / real_size; // 正确检测/所有应被检测
    ofs << "Precision: " << precision * 100 << "%, recall: " << recall * 100 << "%" << endl;
}

double overlap(BoundBox &b1, BoundBox &b2) {
    // 返回：两矩形的交集面积/两矩形的并集面积
    // 两矩形的并集面积 = 两矩形面积之和 - 两矩形的交集面积
    double intersection_area = b1.intersect(b2).area();
    double union_area = b1.area() + b2.area() - intersection_area;
    return intersection_area / union_area;
}

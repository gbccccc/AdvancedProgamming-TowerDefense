#ifndef LOC_H
#define LOC_H
#include <iostream>
using namespace std;

const int cellSize = 100;
const int startx = 50;
const int starty = 50;

typedef pair<int, int> Dir; // (1, 0) OR (-1, 0) OR (0, 1) OR (0, -1)
typedef pair<int, int> CellLoc;
typedef pair<double, double> ObjLoc;

pair<int, int> operator+(pair<int, int> loca, pair<int, int> locb);
pair<int, int> operator+=(pair<int, int> &loca, pair<int, int> locb);
pair<int, int> operator-(pair<int, int> loca, pair<int, int> locb);
pair<int, int> operator-=(pair<int, int> &loca, pair<int, int> locb);

pair<double, double> operator+(pair<double, double> loca, pair<double, double> locb);
pair<double, double> operator+=(pair<double, double> &loca, pair<double, double> locb);
pair<double, double> operator-(pair<double, double> loca, pair<double, double> locb);
pair<double, double> operator-=(pair<double, double> &loca, pair<double, double> locb);
pair<double, double> operator*(pair<double, double> loc, double mul);

extern double get_distance(pair<double, double> p);

extern Dir get_dir(ObjLoc curloc, CellLoc target);

extern Dir get_vertical_dir(Dir dir);

#endif // LOC_H

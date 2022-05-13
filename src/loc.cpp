#include <cmath>
#include "loc.h"

pair<int, int> operator+(pair<int, int> loca, pair<int, int> locb)
{
    return pair<int, int>(loca.first + locb.first, loca.second + locb.second);
}

pair<int, int> operator+=(pair<int, int> &loca, pair<int, int> locb)
{
    loca.first += locb.first;
    loca.second += locb.second;
    return loca;
}

pair<int, int> operator-(pair<int, int> loca, pair<int, int> locb)
{
    return pair<int, int>(loca.first - locb.first, loca.second - locb.second);
}

pair<int, int> operator-=(pair<int, int> &loca, pair<int, int> locb)
{
    loca.first -= locb.first;
    loca.second -= locb.second;
    return loca;
}

pair<double, double> operator+(pair<double, double> loca, pair<double, double> locb)
{
    return pair<double, double>(loca.first + locb.first, loca.second + locb.second);
}

pair<double, double> operator+=(pair<double, double> &loca, pair<double, double> locb)
{
    loca.first += locb.first;
    loca.second += locb.second;
    return loca;
}

pair<double, double> operator-(pair<double, double> loca, pair<double, double> locb)
{
    return pair<double, double>(loca.first - locb.first, loca.second - locb.second);
}

pair<double, double> operator-=(pair<double, double> &loca, pair<double, double> locb)
{
    loca.first -= locb.first;
    loca.second -= locb.second;
    return loca;
}

pair<double, double> operator*(pair<double, double> loc, double mul)
{
    return pair<double, double>(loc.first * mul, loc.second * mul);
}

extern double get_distance(pair<double, double> p)
{
    return pow(pow(p.first, 2) + pow(p.second, 2), 0.5);
}

extern Dir get_dir(ObjLoc curloc, CellLoc target)
{
    Dir dir = (pair<double, double>)target - curloc;
    dir.first = dir.first == 0 ? 0 : (dir.first > 0 ? 1 : -1);
    dir.second = dir.second == 0 ? 0 : (dir.second > 0 ? 1 : -1);
    return dir;
}

extern Dir get_vertical_dir(Dir dir)
{
    if (dir == Dir(1, 0) || dir == Dir(-1, 0))
        return Dir(0, 1);
    else
        return Dir(1, 0);
}

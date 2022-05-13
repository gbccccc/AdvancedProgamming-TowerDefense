#include <algorithm>
#include <sstream>

#include "route.h"

Route::Route(string str)
{
    stringstream ss(str);
    int x, y;
    ss >> x >> y;
    while (x != -1)
    {
        turnLocs.push_back(CellLoc(x, y));
        ss >> x >> y;
    }
    summon = turnLocs.front();
    home = turnLocs.back();
}

CellLoc Route::get_next_turn_loc(CellLoc loc)
{
    vector<CellLoc>::iterator itr = find(turnLocs.begin(), turnLocs.end(), loc);
    ++itr;
    return *itr;
}

#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <iostream>

#include "loc.h"

using namespace std;

typedef pair<double, double> ObjLoc;

class Route
{
private:
    vector<CellLoc> turnLocs;
    CellLoc summon;
    CellLoc home;

public:
    Route(string str);

    CellLoc get_summon() {return this->summon;}
    bool is_home(CellLoc loc) {return loc == this->home;}
    CellLoc get_next_turn_loc(CellLoc loc);
};

#endif // ROUTE_H

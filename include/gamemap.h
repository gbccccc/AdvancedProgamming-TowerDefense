#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <fstream>
#include <map>
#include <QPainter>
using namespace std;

#include "cell.h"
#include "route.h"
#include "loc.h"

class GameMap
{
private:
    static const int length = 15;
    static const int width = 9;
    static Cell nullCell;

    Cell *mapCells[length][width] = {{}};

    QPixmap pix;

    Cell *&get_cell_ref(CellLoc loc);

public:
    GameMap();
    GameMap(list<Route *> &routes, ifstream &initer);
    ~GameMap();

    void paint(QPainter &painter);

    Cell *get_cell(CellLoc loc);
    Cell **operator[](int x) { return mapCells[x]; }
};

#endif // GAMEMAP_H

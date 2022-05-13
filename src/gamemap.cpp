#include "gamemap.h"

GameMap::GameMap() {}

GameMap::GameMap(list<Route *> &routes, ifstream &initer):
    pix(QPixmap(1500, 900))
{
    // cells relative to routes
    for (Route *route : routes)
    {
        // summon
        CellLoc curLoc = route->get_summon();
        if (!this->get_cell_ref(curLoc))
            this->get_cell_ref(curLoc) = new Cell(Cell::summon, curLoc);

        // on route
        while (!route->is_home(curLoc))
        {
            CellLoc nextTurnLoc = route->get_next_turn_loc(curLoc);
            Dir dir = get_dir(curLoc, nextTurnLoc);
            while (curLoc != nextTurnLoc && !route->is_home(curLoc))
            {
                curLoc += dir;
                if (!this->get_cell_ref(curLoc))
                    this->get_cell_ref(curLoc) = new Cell(Cell::onRoute, curLoc);
            }
        }

        // home
        this->get_cell_ref(curLoc) = new Cell(Cell::home, curLoc);
    }

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < length; ++j)
        {
            if (!this->mapCells[j][i])
                mapCells[j][i] = new Cell(Cell::common, make_pair(j, i));

            bool block;
            initer >> block;
            mapCells[j][i]->block = block;
        }

    // initial painting pix
    pix.fill(Qt::white);
    QPainter pixPainter(&pix);
    for (int i = 0; i < length; ++i)
        for (int j = 0; j < width; ++j)
            mapCells[i][j]->paint(pixPainter);
}

Cell GameMap::nullCell = Cell(Cell::NA_route, CellLoc(-1, -1));

GameMap::~GameMap()
{
    for (int i = 0; i < length; ++i)
        for (int j = 0; j < width; ++j)
            if (mapCells[i][j])
                delete mapCells[i][j];
}

Cell *&GameMap::get_cell_ref(CellLoc loc)
{
    return mapCells[loc.first][loc.second];
}

Cell *GameMap::get_cell(CellLoc loc)
{
    if (loc.first >= length || loc.second >= width || loc.first < 0 || loc.second < 0)
        return &nullCell;
    return mapCells[loc.first][loc.second];
}

void GameMap::paint(QPainter &painter)
{
    painter.drawPixmap(0, 0, pix);
}

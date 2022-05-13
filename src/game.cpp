#include "game.h"
#include "friendly_types.h"
#include "enemy_types.h"
#include <windows.h>
using namespace std;

Game::Game(string fileName):
    initer(fileName),
    summonGap(16401),
    lastSummonTime(GetTickCount()),
    frdIndex(0),
    chosen(CellLoc(-1, -1)),
    player(*new Player(20)),
    pix(QPixmap(1500, 900))
{
    // initialize number of routes
    int routesNum;
    initer >> routesNum;
    initer.ignore();

    // initialize routes
    string routeIniter;
    for (int i = 0; i < routesNum; ++i)
    {
        getline(initer, routeIniter);
        routes.push_back(new Route(routeIniter));
    }

    // initialize game map
    gmp = new GameMap(routes, initer);

    start();
}

Game::~Game()
{
    delete &player;
    for (Route *route : routes)
        delete route;
    for (GameObject *obj : objects)
        delete obj;
    delete gmp;
}

void Game::start()
{
}

static int enmTypeNum = 6;
bool Game::update()
{
    // generate enemies
    static int index = 0;
    unsigned curTime = GetTickCount();
    if (curTime - lastSummonTime >= summonGap)
    {
        //        for (Route *route : routes)
        //            generate_enemy(*route, index);
        lastSummonTime = curTime;
        index = (index + enmTypeNum + 1) % enmTypeNum;
    }

    // objects update
    for (GameObject *obj : objects)
        obj->update();

    // remove objects if they are dead
    for (list<GameObject *>::iterator itr = objects.begin(); itr != objects.end(); itr++)
        if (!(*itr)->is_alive())
        {
            delete *itr;
            itr = objects.erase(itr);
        }

    return !player.is_alive();
}

void Game::sudo_generate_enemy(int index)
{
    for (Route *route : routes)
        generate_enemy(*route, index);
}

void Game::resume_time_set()
{
    for (GameObject *obj : objects)
        obj->resume_time_set();
}

void Game::paint(QPainter &painter)
{
    QPainter gamePainter(&pix);

    // draw game map
    gmp->paint(gamePainter);

    if (chosen.first != -1 && chosen.second != -1)
        draw_chosen(gamePainter);

    // draw objects
    for (GameObject *obj : objects)
        obj->paint(gamePainter);
    for (GameObject *obj : objects)
        obj->draw_attack_effect(gamePainter);

    player.paint(painter);
    draw_cur_friend_name(painter);
    painter.drawPixmap(startx, starty, pix);
}

void Game::draw_chosen(QPainter &painter)
{
    QColor color(Qt::yellow);
    color.setAlpha(150);
    painter.setBrush(color);
    painter.setPen(NULL_PEN);
    painter.drawRect(chosen.first * cellSize, chosen.second * cellSize, cellSize, cellSize);

    if (!gmp->get_cell(chosen)->is_frd_empty())
        gmp->get_cell(chosen)->get_friend()->draw_detail(painter);
}

void Game::draw_cur_friend_name(QPainter &painter)
{
    QString friendName;
    switch (frdIndex)
    {
    case 0:
        friendName = "Sphere";
        break;
    case 1:
        friendName = "Guard";
        break;
    case 2:
        friendName = "Guard Mother";
        break;
    case 3:
        friendName = "Bomber";
        break;
    case 4:
        friendName = "Axe";
        break;
    case 5:
        friendName = "Archer";
        break;
    case 6:
        friendName = "Thorn";
        break;

    default:
        friendName = "Null";
    }
    QRectF rect(800, 0, 100, 40);
    painter.drawText(rect, friendName);
}

bool Game::generate_friend(CellLoc loc, Dir dir)
{
    return generate_friend(loc, dir, frdIndex);
}

int Game::frdTypeNum = 7;
bool Game::generate_friend(CellLoc loc, Dir dir, int index)
{
    Cell *cell = gmp->get_cell(loc);
    if (cell->get_route_state() == Cell::NA_route)
        return false;

    bool generateSuccess = false;
    switch (index)
    {
    case -1:
        // LittleGuard
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::onRoute)
            generateSuccess = add_friend_2_list(new FrdLittleGuard(loc, dir, *gmp));
        break;
    case 0:
        // Sphere
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::onRoute)
            generateSuccess = add_friend_2_list(new FrdSphere(loc, dir, *gmp));
        break;
    case 1:
        // Guard
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::onRoute)
            generateSuccess = add_friend_2_list(new FrdGuard(loc, dir, *gmp));
        break;
    case 2:
        // GuardMother
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::common)
            generateSuccess = add_friend_2_list(new FrdGuardMother(loc, dir, *gmp, this));
        break;
    case 3:
        // Bomber
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::common)
            generateSuccess = add_friend_2_list(new FrdBomber(loc, dir, *gmp));
        break;
    case 4:
        // Axe
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::onRoute)
            generateSuccess = add_friend_2_list(new FrdAxe(loc, dir, *gmp));
        break;
    case 5:
        // Archer
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::common)
            generateSuccess = add_friend_2_list(new FrdArcher(loc, dir, *gmp));
        break;
    case 6:
        // Thorn
        if (!cell->is_block() && cell->is_frd_empty() && cell->get_route_state() == Cell::RouteState::onRoute)
            generateSuccess = add_friend_2_list(new FrdThorn(loc, dir, *gmp));
        break;

    default:
        generateSuccess = false;
    }

    return generateSuccess;
}

bool Game::add_friend_2_list(Friendly *frd)
{
    objects.push_back(frd);
    return true;
}

bool Game::rm_friend(CellLoc loc)
{
    // no friend condition
    if (gmp->get_cell(loc)->is_frd_empty())
        return false;

    Friendly *frd = gmp->get_cell(loc)->get_friend();
    gmp->get_cell(loc)->rm_friend(frd);

    objects.remove(frd);

    return true;
}

void Game::generate_enemy(Route &route, int index)
{
    switch (index)
    {
    case 0:
        objects.push_back(new EnmThief(route, *gmp, player));
        break;
    case 1:
        objects.push_back(new EnmArcher(route, *gmp, player));
        break;
    case 2:
        objects.push_back(new EnmSphere(route, *gmp, player));
        break;
    case 3:
        objects.push_back(new EnmBat(route, *gmp, player));
        break;
    case 4:
        objects.push_back(new EnmDragon(route, *gmp, player));
        break;
    case 5:
        objects.push_back(new EnmDamageUpper(route, *gmp, player));
        break;
    }
}

void Game::unchoose()
{
    chosen = CellLoc(-1, -1);
}

void Game::choose(CellLoc loc)
{
    if (loc == chosen)
        generate_friend(loc, Dir(1, 0));
    chosen = loc;
}

void Game::turn_chosen(Dir dir)
{
    if (chosen.first == -1 || chosen.second == -1 || gmp->get_cell(chosen)->is_frd_empty())
        return;
    gmp->get_cell(chosen)->get_friend()->turn(dir);
}

void Game::change_friend_index(int offset)
{
    frdIndex = (frdIndex + frdTypeNum + offset) % frdTypeNum;
}

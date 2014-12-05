#ifndef MOVEMENTPROCESSOR_H
#define MOVEMENTPROCESSOR_H

#include "Player.h"
#include "StaticWorld.h"
#include "TileSetLoader.h"
#include "ZoneSetLoader.h"
#include "Position.h"

class MovementProcessor
{
public:
    MovementProcessor();
    virtual ~MovementProcessor();

    static void init();
    static void free();

    static void move(Player::Move & move, Player & player, StaticWorld* world);

protected:
private:
    static Movement* ms_movements;

    static bool m_outOfSet(Position const& pos, TileSetLoader::TileSet const& tileSet);
    static bool m_outOfSet(Position const& pos, ZoneSetLoader::ZoneSet const& zoneSet);
};

#endif // MOVEMENTPROCESSOR_H

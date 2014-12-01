#ifndef MOVEMENTPROCESSOR_H
#define MOVEMENTPROCESSOR_H

#include "oq.h"
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

    void move(oq::Move & move, Player & player, StaticWorld* world);

protected:
private:
    static Movement* ms_movements;

    bool m_outOfSet(Position const& pos, TileSetLoader::TileSet const& tileSet) const;
    bool m_outOfSet(Position const& pos, ZoneSetLoader::ZoneSet const& zoneSet) const;
};

#endif // MOVEMENTPROCESSOR_H
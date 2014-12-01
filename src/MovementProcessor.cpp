#include "MovementProcessor.h"

Movement* MovementProcessor::ms_movements = NULL;

MovementProcessor::MovementProcessor()
{
    //ctor
}

MovementProcessor::~MovementProcessor()
{
    //dtor
}

void MovementProcessor::init()
{
    ms_movements = new Movement[Player::MOVE_LIST_SIZE];

    ms_movements[Player::MOVE_NOT] = {0,0};
    ms_movements[Player::MOVE_RIGHT] = {1,0};
    ms_movements[Player::MOVE_LEFT] = {-1,0};
    ms_movements[Player::MOVE_UP] = {0,-1};
    ms_movements[Player::MOVE_DOWN] = {0,1};
}

void MovementProcessor::free()
{
    delete[] ms_movements;
    ms_movements = NULL;
}

void MovementProcessor::move(Player::Move & move, Player & player, StaticWorld* world)
{
    if (Player::MOVE_NOT != move)
    {
        Position previewTile = player.m_tile;
        Position previewZone = player.m_zone;
        previewTile += ms_movements[move];

        if (m_outOfSet(previewTile, world->getArea(player.m_area)->getZone(player.m_zone)))
        {
            previewZone += ms_movements[move];
            if (m_outOfSet(previewZone, world->getArea(player.m_area)->getZoneSet()))
            {
                move = Player::MOVE_NOT;
            }
            else
            {
                switch(move)
                {
                case Player::MOVE_RIGHT:
                    previewTile.x = 0;
                    break;
                case Player::MOVE_DOWN:
                    previewTile.y = 0;
                    break;
                case Player::MOVE_LEFT:
                    previewTile.x = world->getArea(player.m_area)->getZone(previewZone)[previewTile.y].size() - 1;
                    break;
                case Player::MOVE_UP:
                    previewTile.y = world->getArea(player.m_area)->getZone(previewZone).size() - 1;
                    break;
                default:
                    break;
                }

                if (m_outOfSet(previewTile, world->getArea(player.m_area)->getZone(player.m_zone)))
                {
                    move = Player::MOVE_NOT;
                }
            }
        }

        if (Player::MOVE_NOT != move)
        {
            TileSetLoader::Tile tile = world->getArea(player.m_area)->getZone(previewZone)[previewTile.y][previewTile.x];
            switch (tile)
            {
            case TileSetLoader::TILE_CAVE:
            case TileSetLoader::TILE_DIRT:
            case TileSetLoader::TILE_FOREST:
            case TileSetLoader::TILE_GRASS:
            case TileSetLoader::TILE_HILL:
                break;

            case TileSetLoader::TILE_MOUNT:
            case TileSetLoader::TILE_WATER:
            case TileSetLoader::TILE_NONE:
            default:
                move = Player::MOVE_NOT;
                break;

            }

            if (Player::MOVE_NOT != move)
            {
                player.m_zone = previewZone;
                player.m_tile = previewTile;
            }
        }
    }
}

bool MovementProcessor::m_outOfSet(Position const& pos, TileSetLoader::TileSet const& tileSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= tileSet.size()) || (pos.x >= tileSet[pos.y].size()));
}

bool MovementProcessor::m_outOfSet(Position const& pos, ZoneSetLoader::ZoneSet const& zoneSet) const
{
    return ((pos.x < 0) || (pos.y < 0) || (pos.y >= zoneSet.size()) || (pos.x >= zoneSet[pos.y].size()));
}

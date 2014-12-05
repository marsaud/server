#include "ActionProcessor.h"

ActionProcessor::ActionProcessor()
{
    //ctor
}

ActionProcessor::~ActionProcessor()
{
    //dtor
}

void ActionProcessor::process(Player::Action & action, Player & player, StaticWorld* world)
{
    switch (action)
    {
    case Player::ACTION_ENTER_ZONE:
        m_link(action, player, world);
        break;
    default:
        action = Player::ACTION_NONE;
        break;
    }
}

void ActionProcessor::m_link(Player::Action & action, Player & player, StaticWorld* world)
{
    const ZoneLinker::ZoneLink* zLink = world->getArea(player.m_area)->getLinker()->find(player.m_zone, player.m_tile);
    if ((NULL != zLink) && ("#" != zLink->targetSet))
    {
        const ZoneLinker* targetLinker = world->getArea(zLink->targetSet)->getLinker();
        const ZoneLinker::ZoneLink* targetLink = targetLinker->find(zLink->targetLinkTag);
        if (NULL != targetLink)
        {
            player.m_area = zLink->targetSet;
            player.m_zone = targetLink->zone;
            player.m_tile = targetLink->tile;
        }
        else
        {
            action = Player::ACTION_NONE;
        }
    }
    else
    {
        action = Player::ACTION_NONE;
    }
}

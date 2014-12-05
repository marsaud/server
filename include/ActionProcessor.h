#ifndef ACTIONPROCESSOR_H
#define ACTIONPROCESSOR_H

#include "Player.h"
#include "StaticWorld.h"
#include "ZoneLinker.h"
#include "Position.h"

class ActionProcessor
{
    public:
        ActionProcessor();
        virtual ~ActionProcessor();

        static void process(Player::Action & action, Player & player, StaticWorld* world);
    protected:
    private:
        static void m_link(Player::Action & action, Player & player, StaticWorld* world);
};

#endif // ACTIONPROCESSOR_H

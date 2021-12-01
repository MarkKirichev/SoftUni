#include "Glock.h"
#include "Structs.h"
#include "Defines.h"

#include <iostream>

Glock::Glock(const int damagePerRound,
             const int clipSize,
             const int remainingAmmo) :
             Pistol(damagePerRound, clipSize, remainingAmmo) {}


bool Glock::fire(PlayerVitalData & enemyPlayerData)
{
    bool isAlive = true;

    for(int i = 0; i < Glock::InternalDefines::ROUNDS_PER_FIRE; ++i)
    {
        if(_currClipBullets > 0)
        {
            if(enemyPlayerData.armor == 0)
            {
                enemyPlayerData.health -= _damagePerRound;
                if(enemyPlayerData.health <= 0)
                {
                    isAlive = false;
                }
            }

            else
            {
                int damageToArmor = (_damagePerRound / 2);
                int damageToPerson = damageToArmor;

                if(damageToArmor <= enemyPlayerData.armor)
                {
                    enemyPlayerData.armor -= damageToArmor;
                    damageToArmor = 0;
                }

                else if(damageToArmor > enemyPlayerData.armor)
                {
                    damageToArmor -= enemyPlayerData.armor;
                    enemyPlayerData.armor = 0;
                }

                enemyPlayerData.health -= damageToPerson;
                enemyPlayerData.health -= damageToArmor;

                if(enemyPlayerData.health <= 0)
                {
                    isAlive = false;
                }
            }

            std::cout << "Enemy left with: " << enemyPlayerData.health
                      << " health and " << enemyPlayerData.armor
                      << " armor" << std::endl;

            --_currClipBullets;
            if(enemyPlayerData.health <= 0)
            {
                break;
            }
        }

        else
        {
            Pistol::reload();
            break;
        }
    }

    return (!isAlive);
}

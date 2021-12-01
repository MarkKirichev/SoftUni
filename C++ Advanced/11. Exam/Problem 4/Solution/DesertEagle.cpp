#include "DesertEagle.h"
#include "Structs.h"
#include "Defines.h"

#include <iostream>

DesertEagle::DesertEagle(const int damagePerRound,
                         const int clipSize,
                         const int remainingAmmo) :
                         Pistol(damagePerRound, clipSize, remainingAmmo) {}

bool DesertEagle::fire(PlayerVitalData & enemyPlayerData)
{
    bool isAlive = true;

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
            int damageToArmor = (_damagePerRound / 4);
            int damageToPerson = (damageToArmor * 3);

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
    }

    else
    {
        Pistol::reload();
    }

    return (!isAlive);
}

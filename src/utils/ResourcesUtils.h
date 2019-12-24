//
// Created by Tomás Macía on 18/12/2019.
//

#ifndef GAME_RESOURCESUTILS_H
#define GAME_RESOURCESUTILS_H

#include <string>
#include <map>
#include <list>
#include <utility>
#include "MapUtils.h"
#include "../XMLparser/config/config.h"

using namespace std;

class ResourcesUtils {
public:
    ResourcesUtils(Config *config) {
        int i = 1;
        for (auto &level : config->gameplay.levels) {
            for (auto &path : level.floor) {
                idsToResources.emplace(make_pair(i, path));
                i++;
            }
            for (auto &path : level.middle) {
                idsToResources.emplace(make_pair(i, path));
                i++;
            }
            for (auto &path : level.far) {
                idsToResources.emplace(make_pair(i, path));
                i++;
            }
            for (auto &path : level.overlay) {
                idsToResources.emplace(make_pair(i, path));
                i++;
            }
        }

        for (auto &character : config->gameplay.characters) {
            idsToResources.emplace(make_pair(i, character.stand));
            i++;
            idsToResources.emplace(make_pair(i, character.walk));
            i++;
            idsToResources.emplace(make_pair(i, character.jump));
            i++;
            idsToResources.emplace(make_pair(i, character.punch));
            i++;
            idsToResources.emplace(make_pair(i, character.crouch));
            i++;
            idsToResources.emplace(make_pair(i, character.kick));
            i++;
            idsToResources.emplace(make_pair(i, character.jumpkick));
            i++;
            idsToResources.emplace(make_pair(i, character.dying));
            i++;
            idsToResources.emplace(make_pair(i, character.beingAttacked));
            i++;
            idsToResources.emplace(make_pair(i, character.knifeHit));
            i++;
            idsToResources.emplace(make_pair(i, character.knifeStand));
            i++;
            idsToResources.emplace(make_pair(i, character.knifeWalk));
            i++;
            idsToResources.emplace(make_pair(i, character.pipeHit));
            i++;
            idsToResources.emplace(make_pair(i, character.pipeStand));
            i++;
            idsToResources.emplace(make_pair(i, character.pipeWalk));
            i++;
            idsToResources.emplace(make_pair(i, character.disconnected));
            i++;
        }

        idsToResources.emplace(make_pair(i, config->gameplay.boss.stand));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.boss.beingAttacked));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.boss.walk));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.boss.dying));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.boss.punch));
        i++;

        idsToResources.emplace(make_pair(i, config->gameplay.weapons.tube.sprite));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.weapons.knife.sprite));
        i++;

        idsToResources.emplace(make_pair(i, config->gameplay.utilities.barrel.standSprite));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.utilities.barrel.damagedSprite));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.utilities.barrel.brokenSprite));
        i++;

        idsToResources.emplace(make_pair(i, config->gameplay.utilities.box.standSprite));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.utilities.box.damagedSprite));
        i++;
        idsToResources.emplace(make_pair(i, config->gameplay.utilities.box.brokenSprite));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/fondo_celeste.png")));
        i++;

        for (auto &npc : config->gameplay.npcs) {
            idsToResources.emplace(make_pair(i, npc.walk));
            i++;
            idsToResources.emplace(make_pair(i, npc.dying));
            i++;
            idsToResources.emplace(make_pair(i, npc.punch));
            i++;
            idsToResources.emplace(make_pair(i, npc.stand));
            i++;
            idsToResources.emplace(make_pair(i, npc.beingAttacked));
            i++;
        }

        idsToResources.emplace(make_pair(i, string("resources/sprites/score/fran.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/cris.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/axel.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/tomi.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/zero.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/one.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/two.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/three.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/four.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/five.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/six.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/seven.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/eigth.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/nine.png")));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Blue/0v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Blue/20v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Blue/40v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Blue/60v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Blue/80v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Blue/100v2.png")));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Red/0v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Red/20v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Red/40v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Red/60v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Red/80v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Red/100v2.png")));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Green/0v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Green/20v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Green/40v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Green/60v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Green/80v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Green/100v2.png")));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Yellow/0v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Yellow/20v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Yellow/40v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Yellow/60v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Yellow/80v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/Yellow/100v2.png")));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/score/disconnect/20v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/disconnect/40v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/disconnect/60v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/disconnect/80v2.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/score/disconnect/100v2.png")));
        i++;

        idsToResources.emplace(make_pair(i, string("resources/sprites/screens/waiting_for_your_teammates.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/screens/disconnection.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/screens/mid.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/screens/complete.png")));
        i++;
        idsToResources.emplace(make_pair(i, string("resources/sprites/fondo_amarillo.png")));
        i++;

        for( auto const& [key, val] : idsToResources) {
            resourcesToIds.emplace(make_pair(val, key));
        }

    }

    string getResource(int id) {
        return MapUtils::getOrDefault(idsToResources, id, string(""));
    }

    int getId(string resourcePath) {
        return MapUtils::getOrDefault(resourcesToIds, resourcePath, 0);
    }

private:
    map<int, string> idsToResources;
    map<string, int> resourcesToIds;

};


#endif //GAME_RESOURCESUTILS_H

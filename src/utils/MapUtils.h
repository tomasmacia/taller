//
// Created by Tomás Macía on 15/12/2019.
//

#ifndef GAME_MAPUTILS_H
#define GAME_MAPUTILS_H

#include <map>


class MapUtils {
public:

    template <typename K, typename V>
    static V getOrDefault(const std::map<K,V> &map, const K &key, const V &defaultValue) {
        V value;
        auto pos = map.find(key);
        if (pos != map.end()) {
            value = pos->second;
        } else {
            value = defaultValue;
        }

        return value;
    }
};


#endif //GAME_MAPUTILS_H

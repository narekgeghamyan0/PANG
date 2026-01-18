#ifndef LIFEMANAGER_H
#define LIFEMANAGER_H

#include "moment.h"

#include <set>

class LifeManager
{
public:
    LifeManager() = default;
    void addMoment(const Moment& moment);
    bool removeMoment(uint32_t moment_id);
    const Moment& getMoment(const uint32_t moment_id) const;
private:
    std::unordered_map<uint32_t, Moment> moments_;
};


#endif // LIFEMANAGER_H
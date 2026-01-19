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
    const Moment& getLastMoment() const;
    std::vector<std::reference_wrapper<const Moment>> getAllMoments() const;
    std::vector<std::reference_wrapper<const Moment>> findByType(const MomentType type) const;
private:
    std::unordered_map<uint32_t, Moment> moments_;
};


#endif // LIFEMANAGER_H
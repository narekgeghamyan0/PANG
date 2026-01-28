#ifndef LIFEMANAGER_H
#define LIFEMANAGER_H

#include "moment.h"
#include <unordered_map>
#include <vector>
#include <functional>

#include <set>

/// @details At the moment, the LifeManager class owns only moments. It will be extended in the future.
class LifeManager
{
public:
    LifeManager() = default;
    void addMoment(const Moment& moment);
    bool removeMoment(IdType moment_id);
    const Moment& getMoment(const IdType moment_id) const;
    const Moment& getLastMoment() const;
    std::vector<std::reference_wrapper<const Moment>> getAllMoments() const;
    std::vector<std::reference_wrapper<const Moment>> findByType(const MomentType type) const;
    IdType getMomentCount() const;
    IdType getMomentCountByType(MomentType type) const;
private:
    std::unordered_map<IdType, Moment> moments_;
};


#endif // LIFEMANAGER_H
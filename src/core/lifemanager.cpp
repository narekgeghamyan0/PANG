#include "lifemanager.h"

void LifeManager::addMoment(const Moment& moment)
{
    moments_.emplace(moment.getId(), moment);
}

bool LifeManager::removeMoment(uint32_t moment_id)
{
    return moments_.erase(moment_id) > 0;
}

const Moment& LifeManager::getMoment(const uint32_t moment_id) const
{
    auto it = moments_.find(moment_id);
    if (it == moments_.end())
        throw std::runtime_error("Moment not found");

    return it->second;
}
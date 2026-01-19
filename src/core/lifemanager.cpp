#include "lifemanager.h"

void LifeManager::addMoment(const Moment& moment)
{
    if (!moment.getId().has_value()) {
        throw std::invalid_argument("Moment must have an id before adding to LifeManager");
    }
    moments_.emplace(moment.getId().value(), moment);
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

std::vector<std::reference_wrapper<const Moment>> LifeManager::getAllMoments() const
{
    std::vector<std::reference_wrapper<const Moment>> all_moments;
    for (const auto& [id, moment] : moments_)
    {
        all_moments.push_back(moment);
    }
    return all_moments;
}

const Moment& LifeManager::getLastMoment() const
{
    if (moments_.empty())
        throw std::runtime_error("No moments available");

    auto it = std::max_element(moments_.begin(), moments_.end(),
        [](const auto& a, const auto& b) {
            return a.second.getMomentCreationTime() < b.second.getMomentCreationTime();
        });

    if (it == moments_.end())
        throw std::runtime_error("No moments available");

    return it->second;
}

std::vector<std::reference_wrapper<const Moment>> LifeManager::findByType(const MomentType type) const
{
    std::vector<std::reference_wrapper<const Moment>> res;
    for (const auto& [id, moment] : moments_)
    {
        if (type == moment.getType())
        {
            res.push_back(moment);
        }
    }
    return res;
}

uint32_t LifeManager::getMomentCount() const
{
    return moments_.size();
}

uint32_t LifeManager::getMomentCountByType(MomentType type) const
{
    uint32_t count = 0;
    for (const auto& [id, moment] : moments_)
    {
        if (moment.getType() == type)
            ++count;
    }
    return count;
}
#ifndef MOMENT_H
#define MOMENT_H

#include "media.h"

#include <string>
#include <chrono>
#include <vector>

class Moment
{
public:
    Moment(std::string title, std::string description);
public:
    const std::string& getDescription() const;
    const std::string& getTitle() const;
    void updateDescription(const std::string& new_description);
    void updateTitle(const std::string& new_title);
    bool isSaved() const;
    void addMedia();
    void removeMedia();
    std::chrono::system_clock::time_point getMomentCreationTime() const;
private:
    std::string description_;
    std::string title_;
    std::optional<uint32_t> id_;
    std::vector<uint32_t> media_ids;
    std::chrono::system_clock::time_point created_at_;
    std::chrono::system_clock::time_point updated_at_;
};

#endif // MOMENT_H
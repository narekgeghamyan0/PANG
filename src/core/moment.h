#ifndef _MOMENT_H_
#define _MOMENT_H_

#include "media.h"

#include <string>
#include <chrono>
#include <vector>

class Moment
{
public:
    Moment(std::string& title, std::string& description);
public:
    std::string getDescription() const;
    std::string getTitle() const;
    bool isSaved() const;
    void addMedia();
    void removeMedia();
    std::chrono::system_clock::time_point getMomentCreationTime() const;

private:
    std::string description_;
    std::string title_;
    std::chrono::system_clock::time_point time_;
    std::optional<uint32_t> id_;
    std::vector<uint32_t> media_ids;
};

#endif // _MOMENT_H_
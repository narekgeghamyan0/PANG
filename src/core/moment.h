#ifndef MOMENT_H
#define MOMENT_H

#include "media.h"

#include <string>
#include <chrono>
#include <vector>

enum MomentType {
    Personal,
    Work,
    Travel
};

class Moment
{
public:
    Moment(std::string title, std::string text, MomentType type = MomentType::Personal);
public:
    const std::string& getText() const;
    const std::string& getTitle() const;
    MomentType getType() const;
    void updateText(const std::string& new_text);
    void updateTitle(const std::string& new_title);
    void updateType(MomentType new_type);
    bool isSaved() const;
    void addMedia();
    void removeMedia();
    std::chrono::system_clock::time_point getMomentCreationTime() const;
private:
    std::string text_;
    std::string title_;
    std::optional<uint32_t> id_;
    MomentType type_;
    std::vector<uint32_t> media_ids;
    std::chrono::system_clock::time_point created_at_;
    std::chrono::system_clock::time_point updated_at_;
};

#endif // MOMENT_H
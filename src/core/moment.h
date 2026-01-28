#ifndef MOMENT_H
#define MOMENT_H

#include "media.h"

#include <string>
#include <chrono>
#include <vector>
#include <optional>

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
    std::optional<IdType> getId() const;
    bool operator<(const Moment& other) const;
    bool operator==(const Moment& other) const;
    void updateText(const std::string& new_text);
    void updateTitle(const std::string& new_title);
    void updateType(MomentType new_type);
    bool isSaved() const;
    void addMedia(IdType media_id);
    void removeMedia(IdType media_id);
    TimePoint getMomentCreationTime() const;
    void setId(IdType id);
    void generateId();
private:
    std::string text_;
    std::string title_;
    std::optional<IdType> id_;
    MomentType type_;
    std::vector<IdType> media_ids;
    TimePoint created_at_;
    TimePoint updated_at_;
};

#endif // MOMENT_H
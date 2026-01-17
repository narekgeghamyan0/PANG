#include "moment.h"

Moment::Moment(std::string& title, std::string& description)
      : description_(std::move(description)), title_(std::move(title)),
        time_(std::chrono::system_clock::now())
        
{
}

std::string Moment::getDescription() const
{
    return description_;
}

std::string Moment::getTitle() const
{
    return title_;
}

bool Moment::isSaved() const
{
    return id_.has_value();
}

std::chrono::system_clock::time_point Moment::getMomentCreationTime() const
{
    return time_;
}

void Moment::addMedia()
{
    // TODO Narek: Implement functional for add new media.
}

void Moment::removeMedia()
{
    // TODO Narek: Implement functional for remove media.
}
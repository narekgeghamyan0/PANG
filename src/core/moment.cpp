#include "moment.h"

Moment::Moment(std::string title, std::string description)
      : description_(std::move(description)), title_(std::move(title)),
        created_at_(std::chrono::system_clock::now()), updated_at_(created_at_)

{
}

const std::string& Moment::getDescription() const
{
    return description_;
}

const std::string& Moment::getTitle() const
{
    return title_;
}

bool Moment::isSaved() const
{
    return id_.has_value();
}

std::chrono::system_clock::time_point Moment::getMomentCreationTime() const
{
    return created_at_;
}

void Moment::updateDescription(const std::string& new_description)
{
    description_ = new_description;
    updated_at_ = std::chrono::system_clock::now();
}

void Moment::updateTitle(const std::string& new_title)
{
    title_ = new_title;
    updated_at_ = std::chrono::system_clock::now();
}

void Moment::addMedia()
{
    // TODO Narek: Implement functional for add new media.
}

void Moment::removeMedia()
{
    // TODO Narek: Implement functional for remove media.
}
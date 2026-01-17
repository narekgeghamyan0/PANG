#include "moment.h"

Moment::Moment(std::string title, std::string text, MomentType type)
      : text_(std::move(text)), title_(std::move(title)), type_(type),
        created_at_(std::chrono::system_clock::now()), updated_at_(created_at_)

{
}

const std::string& Moment::getText() const
{
    return text_;
}

const std::string& Moment::getTitle() const
{
    return title_;
}

MomentType Moment::getType() const
{
    return type_;
}

void Moment::updateType(MomentType new_type)
{
    type_ = new_type;
    updated_at_ = std::chrono::system_clock::now();
}

bool Moment::isSaved() const
{
    return id_.has_value();
}

std::chrono::system_clock::time_point Moment::getMomentCreationTime() const
{
    return created_at_;
}

void Moment::updateText(const std::string& new_text)
{
    text_ = new_text;
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
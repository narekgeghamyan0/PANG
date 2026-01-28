#include "moment.h"

Moment::Moment(std::string title, std::string text, MomentType type)
      : text_(std::move(text)), title_(std::move(title)), id_(std::nullopt), type_(type),
        media_ids(),
        created_at_(std::chrono::system_clock::now()), updated_at_(created_at_)
{
}

const std::string&
Moment::getText() const
{
    return text_;
}

const std::string&
Moment::getTitle() const
{
    return title_;
}

MomentType
Moment::getType() const
{
    return type_;
}

void
Moment::updateType(MomentType new_type)
{
    type_ = new_type;
    updated_at_ = std::chrono::system_clock::now();
}

bool
Moment::isSaved() const
{
    return id_.has_value();
}

TimePoint
Moment::getMomentCreationTime() const
{
    return created_at_;
}

void
Moment::updateText(const std::string& new_text)
{
    text_ = new_text;
    updated_at_ = std::chrono::system_clock::now();
}

std::optional<IdType>
Moment::getId() const
{
    return id_;
}

void
Moment::updateTitle(const std::string& new_title)
{
    title_ = new_title;
    updated_at_ = std::chrono::system_clock::now();
}

bool
Moment::operator<(const Moment& other) const
{
    if (id_ && other.id_) return id_.value() < other.id_.value();
    return false;
}

bool
Moment::operator==(const Moment& other) const
{
    if (id_ && other.id_) return id_.value() == other.id_.value();
    return false;
}

/// @attention This function will be used when a moment is loaded into the database;
///            at that point, the moment will have a unique ID.
void
Moment::generateId()
{
    static IdType current_id = 0;
    id_ = ++current_id;
}

void
Moment::setId(IdType id)
{
    id_ = id;
}

void
Moment::addMedia(IdType media_id)
{
}

void
Moment::removeMedia(IdType media_id)
{
}
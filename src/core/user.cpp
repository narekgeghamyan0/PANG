#include "user.h"

User::User(const std::string& name, const std::string& bio, const std::string& profile_picture_path)
    : name_(name), id_(std::nullopt), life_(), created_at_(std::chrono::system_clock::now()),
      bio_(bio), profile_picture_path_(profile_picture_path)
{

}

const std::string&
User::getName() const
{
    return name_;
}

void
User::setId(uint32_t id)
{
    id_ = id;
}

std::optional<uint32_t>
User::getId() const
{
    return id_;
}

void
User::rename(const std::string& new_name)
{
    name_ = new_name;
}

void
User::changeBio(const std::string& new_bio)
{
    bio_ = new_bio;
}

std::chrono::system_clock::time_point
User::getCreatedAt() const
{
    return created_at_;
}

void
User::addMoment(const Moment& moment)
{
    life_.addMoment(moment);
}

void
User::removeMoment(uint32_t moment_id)
{
    life_.removeMoment(moment_id);
}

const Moment&
User::getMoment(const uint32_t moment_id) const
{
    return life_.getMoment(moment_id);
}

const std::string&
User::getBio() const
{
    return bio_;
}

void
User::changeProfilePicture(const std::string& new_profile_picture_path)
{
    profile_picture_path_ = new_profile_picture_path;
}

const std::string&
User::getProfilePicturePath() const
{
    return profile_picture_path_;
}

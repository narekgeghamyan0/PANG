#include "user.h"

User::User(const std::string& name, const std::string& login, const std::string& pass,
           const std::string& bio, const std::string& profile_picture_path)
    : name_(name), email_(login), password_(pass), id_(std::nullopt), life_(), created_at_(std::chrono::system_clock::now()),
      bio_(bio), profile_picture_path_(profile_picture_path)
{

}

const std::string&
User::getName() const
{
    return name_;
}

void
User::setId(IdType id)
{
    id_ = id;
}

std::optional<IdType>
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

TimePoint
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
User::removeMoment(IdType moment_id)
{
    life_.removeMoment(moment_id);
}

const Moment&
User::getMoment(const IdType moment_id) const
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

void
User::setLogin(const std::string& email)
{
    /// @todo Implement email validation check.
    email_ = email;
}

void
User::setPass(const std::string& pass)
{
    /// @todo Implement password requirement check.
    password_ = pass;
}

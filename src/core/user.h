#ifndef USER_H
#define USER_H

#include "lifemanager.h"

#include <string>
#include <optional>

class User
{
public:
    User(const std::string& name, const std::string& login, const std::string& pass,
         const std::string& bio = "", const std::string& profile_picture_path = "");
    const std::string& getName() const;
    void setId(IdType id);
    std::optional<IdType> getId() const;
    void rename(const std::string& new_name);
    void changeBio(const std::string& new_bio);
    const std::string& getBio() const;
    void changeProfilePicture(const std::string& new_profile_picture_path);
    const std::string& getProfilePicturePath() const;
    TimePoint getCreatedAt() const;
    void addMoment(const Moment& moment);
    void removeMoment(IdType moment_id);
    const Moment& getMoment(const IdType moment_id) const;
    // void addMediaToMoment(IdType moment_id, IdType media_id); /// @todo Narek
    // void removeMediaFromMoment(IdType moment_id, IdType media_id); /// @todo Narek
private:
    void  setLogin(const std::string& email);
    void  setPass(const std::string& pass);
private:
    std::string name_;
    std::optional<IdType> id_;
    LifeManager life_;
    TimePoint created_at_;
    std::string bio_;
    std::string profile_picture_path_;
    std::string email_;
    std::string password_;
};

#endif /// USER_H
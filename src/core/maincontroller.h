#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "user.h"

#include <optional>

class MainController
{
public:
    explicit MainController() = default;
    void setCurrentUser(const User& user);
    std::optional<User> getCurrentUser() const;
    void registerUser(const std::string& name, const std::string& login, const std::string& pass,
                      const std::string& bio = "",
                      const std::string& profile_picture_path = "");
    void loginUser(const std::string& email, const std::string& password);
    void logoutUser();
private:
    std::optional<User> current_user;
};

#endif /// MAIN_CONTROLLER_H
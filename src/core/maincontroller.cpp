#include "maincontroller.h"

void
MainController::setCurrentUser(const User& user)
{
    current_user = user;
}

std::optional<User>
MainController::getCurrentUser() const
{
    return current_user;
}

void
MainController::registerUser(const std::string& name, const std::string& login, const std::string& pass,
             const std::string& bio,
             const std::string& profile_picture_path)

{
    current_user = User(name, login, pass, bio, profile_picture_path);
    /// @attention There should be a part here that adds the user to the db.
}

void
MainController::loginUser(const std::string& email, const std::string& password)
{
    /// @todo Implement login logic.
}

void
MainController::logoutUser()
{
    current_user = std::nullopt;
}


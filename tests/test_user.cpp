#include <boost/test/unit_test.hpp>

#include "../src/core/user.h"

BOOST_AUTO_TEST_SUITE(UserTests)

BOOST_AUTO_TEST_CASE(user_creation_and_getters)
{
    User user("Alice", "example@gmail.com", "mypass", "Bio text");

    BOOST_CHECK_EQUAL(user.getName(), "Alice");
    BOOST_CHECK_EQUAL(user.getBio(), "Bio text");
}

BOOST_AUTO_TEST_CASE(user_id_management)
{
    User user("Bob", "example@gmail.com", "mypass", "Bio text");
    BOOST_CHECK(!user.getId().has_value());

    user.setId(42);
    BOOST_CHECK_EQUAL(user.getId().value(), 42);
}

BOOST_AUTO_TEST_CASE(user_rename_and_bio_change)
{
    User user("Charlie", "example@gmail.com", "mypass", "Initial bio");
    user.rename("Chuck");
    user.changeBio("Updated bio");

    BOOST_CHECK_EQUAL(user.getName(), "Chuck");
    BOOST_CHECK_EQUAL(user.getBio(), "Updated bio");
}

BOOST_AUTO_TEST_SUITE_END()
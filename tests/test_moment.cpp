#define BOOST_TEST_MODULE PangTests
#include <boost/test/included/unit_test.hpp>

#include "../src/core/moment.h"


BOOST_AUTO_TEST_SUITE(MomentTests)

BOOST_AUTO_TEST_CASE(moment_creation_and_getters)
{
    Moment moment("My Title", "This is a test moment.", MomentType::Travel);

    BOOST_CHECK_EQUAL(moment.getTitle(), "My Title");
    BOOST_CHECK_EQUAL(moment.getText(), "This is a test moment.");
    BOOST_CHECK_EQUAL(moment.getType(), MomentType::Travel);
    BOOST_CHECK(!moment.getId().has_value());
    BOOST_CHECK(moment.isSaved() == false);
}

BOOST_AUTO_TEST_CASE(moment_update_methods)
{
    Moment moment("Initial Title", "Initial text.", MomentType::Personal);

    moment.updateTitle("Updated Title");
    moment.updateText("Updated text.");
    moment.updateType(MomentType::Work);

    BOOST_CHECK_EQUAL(moment.getTitle(), "Updated Title");
    BOOST_CHECK_EQUAL(moment.getText(), "Updated text.");
    BOOST_CHECK_EQUAL(moment.getType(), MomentType::Work);
}

BOOST_AUTO_TEST_CASE(moment_id_management)
{
    Moment moment("Title", "Text");

    BOOST_CHECK(!moment.getId().has_value());

    moment.setId(42);
    BOOST_CHECK_EQUAL(moment.getId().value(), 42);
    BOOST_CHECK(moment.isSaved() == true);
}


BOOST_AUTO_TEST_SUITE_END()

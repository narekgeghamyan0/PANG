#include <boost/test/unit_test.hpp>

#include "../src/core/lifemanager.h"

BOOST_AUTO_TEST_SUITE(LifeManagerTests)

BOOST_AUTO_TEST_CASE(life_manager_creation)
{
    LifeManager lifeManager;
    BOOST_CHECK(lifeManager.getAllMoments().empty());
}

BOOST_AUTO_TEST_CASE(add_and_get_moment)
{
    LifeManager lifeManager;
    Moment moment("Title", "Text", MomentType::Personal);
    moment.setId(1);
    lifeManager.addMoment(moment);

    const Moment& retrievedMoment = lifeManager.getMoment(1);
    BOOST_CHECK_EQUAL(retrievedMoment.getTitle(), "Title");
    BOOST_CHECK_EQUAL(retrievedMoment.getText(), "Text");
    BOOST_CHECK_EQUAL(retrievedMoment.getType(), MomentType::Personal);
}

BOOST_AUTO_TEST_CASE(remove_moment)
{
    LifeManager lifeManager;
    Moment moment("Title", "Text", MomentType::Personal);
    moment.setId(1);
    lifeManager.addMoment(moment);

    bool removed = lifeManager.removeMoment(1);
    BOOST_CHECK(removed);
    BOOST_CHECK_THROW(lifeManager.getMoment(1), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(get_all_moments)
{
    LifeManager lifeManager;
    Moment moment1("Title1", "Text1", MomentType::Personal);
    moment1.setId(1);
    lifeManager.addMoment(moment1);

    Moment moment2("Title2", "Text2", MomentType::Work);
    moment2.setId(2);
    lifeManager.addMoment(moment2);

    auto allMoments = lifeManager.getAllMoments();
    BOOST_CHECK_EQUAL(allMoments.size(), 2);
}

BOOST_AUTO_TEST_SUITE_END()

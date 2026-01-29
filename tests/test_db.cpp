#include <boost/test/unit_test.hpp>
#include <filesystem>

#include "../src/db/dataBase.h"

BOOST_AUTO_TEST_SUITE(DabaBase)

BOOST_AUTO_TEST_CASE(data_base_creation)
{
    string dbName = "test.db";
    DataBase db(dbName);
    db.useTable("memory");
    db.insert(3, "/path/to/image.jpg", "My first memory");
    std::string imagePath = db.getImagePath(3);
    std::string note = db.getNote(3);

    BOOST_CHECK_EQUAL(imagePath, "/path/to/image.jpg");
    BOOST_CHECK_EQUAL(note, "My first memory");

    db.erase(3);

    imagePath = db.getImagePath(3);
    note = db.getNote(3);

    BOOST_CHECK_EQUAL(imagePath, "");
    BOOST_CHECK_EQUAL(note, "");
    std::filesystem::remove(dbName);
}

BOOST_AUTO_TEST_SUITE_END()
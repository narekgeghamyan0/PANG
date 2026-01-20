#include <string>
#include <iostream>
#include <sqlite3.h>

using string = std::string;
using ID     = size_t;

class DataBase {
public:
    DataBase(const string& db_path);
    ~DataBase();
    // const string& getImagePath(ID id) const;
    // const string& getNote(ID id) const;
    // void insertNoteAndImage(ID id, string& image_path, string& note);

private:
    void createDataBase(const string& db_path);
    void executeCommand(const string& command);
    void createTable(string&& user);
    void createMemoryTable();
    void createQuery(string&& item, string&& column, ID id, string& query);
    void createQueryForImage(ID id, string& query);
    void createQueryForNote(ID id, string& query);

private:
    sqlite3* db_;
};
#include "db/dataBase.h"

DataBase::DataBase(const string& db_path)
    : db_(nullptr)
{
    // Open (or create) database
    createDataBase(db_path);
    // Create table user if not exists
    createMemoryTable();
}

DataBase::~DataBase()
{
    if (db_) {
        sqlite3_close(db_);
    }
    std::cout << "Opened Database Successfully!" << std::endl;
}

void
DataBase::createDataBase(const string& db_path)
{
    if (sqlite3_open(db_path.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error("ERROR 1: Can't create database");
    }
}

void
DataBase::executeCommand(const string& command)
{
    char* errMsg = nullptr;
    int rd = sqlite3_exec(db_, command.c_str(), nullptr, nullptr, &errMsg);
    if (rd != SQLITE_OK) {
        throw std::runtime_error("ERROR 2: Can't execute " + command);
    }
}

void
DataBase::createTable(string&& tableName)
{
    // Create table query
    const string createTable = 
        "CREATE TABLE IF EXISTS " + tableName + "(" +
        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
        "note TEXT NOT NULL," +
        "image_path TEXT NOT NULL";

    executeCommand(createTable);
}

void
DataBase::createMemoryTable()
{
    createTable("memories");
}

void
DataBase::createQuery(string&& item, string&& column, ID id, string& query)
{
    query.reserve(item.size() + column.size() + 32);

    query.append("SELECT ")
         .append(item)
         .append(" FROM ")
         .append(column)
         .append(" WHERE id = ")
         .append(std::to_string(id))
         .append(";");
}

void
DataBase::createQueryForImage(ID id, string& query)
{
    return createQuery("path", "images", id, query);
}

void
DataBase::createQueryForNote(ID id, string& query)
{
    return createQuery("note", "notes", id, query);
}

// const string&
// DataBase::getImagePath(ID id) const
// {
//     if (!db_) {
//         return "";
//     }
//     string query;
//     createQueryForImage(id, query);
//     return "TODO: Image path from db";
// }

// const string&
// DataBase::getNote(ID id) const
// {
//     if (!db_) {
//         return "";
//     }
//     string query;
//     createQueryForNote(id, string& query);
//     return "TODO: Note from db";
// }
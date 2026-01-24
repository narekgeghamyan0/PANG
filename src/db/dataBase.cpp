#include "db/dataBase.h"
struct callbackForCheck
{ 
    void operator()(void* data, int argc, char** argv, char** azColName) {
        int i;
        fprintf(stderr, "%s: ", (const char*)data);

        for (i = 0; i < argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }

        printf("\n");
    }
};

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
DataBase::executeCommand(const string& command, sqlite3_stmt* stmt)
{
    char* errMsg = nullptr;
    int rd = sqlite3_exec(db_, command.c_str(), 0, stmt, &errMsg);
    if (rd != SQLITE_OK) {
        throw std::runtime_error("ERROR 2: Can't execute " + command);
    }
}

void
DataBase::createDataBase(const string& db_path)
{
    if (sqlite3_open(db_path.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error("ERROR 1: Can't create database");
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
DataBase::createPrintAllQuery(const string& tableName, string& query)
{
    query.reserve(QUERY_MAX_SIZE);

    query.append("SELECT * FROM ")
         .append(tableName)
         .append(";");
}

void
DataBase::createSelectQuery(string&& item, string&& column, ID id, string& query)
{
    query.reserve(QUERY_MAX_SIZE);

    query.append("SELECT ")
         .append(item)
         .append(" FROM ")
         .append(column)
         .append(" WHERE id = ")
         .append(std::to_string(id))
         .append(";");
}

void
DataBase::createInsertQuery(const string& tableName, ID id, const string& image_path, const string& note, string& query)
{
    query.reserve(QUERY_MAX_SIZE);

    query.append("INSERT INTO")
         .append(tableName)
         .append(" VALUES(")
         .append(std::to_string(id))
         .append(", ")
         .append(image_path)
         .append(", ")
         .append(note)
         .append(");");
}

void
DataBase::createEraseQuery(const string& tableName, ID id, string& query)
{
    query.reserve(QUERY_MAX_SIZE);

    query.append("DELETE FROM ")
         .append(tableName)
         .append(" WHERE ID = ")
         .append(std::to_string(id))
         .append("; ");
}

void
DataBase::createQueryForImage(ID id, string& query)
{
    return createSelectQuery("path", "images", id, query);
}

void
DataBase::createQueryForNote(ID id, string& query)
{
    return createSelectQuery("note", "notes", id, query);
}

void
DataBase::insert(const string& tableName, ID id, const string& image_path, const string& note)
{
    string query;
    createInsertQuery(tableName, id, image_path, note, query);
    executeCommand(query);
}

void
DataBase::erase(const string& tableName, ID id)
{
    string query;
    createEraseQuery(tableName, id, query);
    executeCommand(query);
}

string
DataBase::getImagePath(ID id)
{
    if (!db_) {
        return "";
    }
    string query;
    createQueryForImage(id, query);
    // sqlite3_stmt* stmt;
    // executeCommand(query, stmt);
    return "TODO: Image path from db";
}

string
DataBase::getNote(ID id)
{
    if (!db_) {
        return "";
    }
    string query;
    createQueryForNote(id, query);
    return "TODO: Note from db";
}
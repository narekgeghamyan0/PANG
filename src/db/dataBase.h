#ifndef DB_DATA_BASE_H
#define DB_DATA_BASE_H

#include <string>
#include <iostream>
#include <vector>
#include <sqlite3.h>

#define QUERY_MAX_SIZE 256

using ID = size_t;
using Index = size_t;
using string = std::string;
using string_view = std::string_view;

using SQL_string = string;

// SQL Keywords
// TODO: Create queries using these keywords
const SQL_string SQL_CREATE = "CREATE";
const SQL_string SQL_TABLE = "TABLE";
const SQL_string SQL_IF = "IF";
const SQL_string SQL_EXISTS = "EXISTS";
const SQL_string SQL_OPEN_BRACKET = "(";
const SQL_string SQL_CLOSE_BRACKET = ")";
const SQL_string SQL_INTEGER = "INTEGER";
const SQL_string SQL_PRIMARY = "PRIMARY";
const SQL_string SQL_KEY = "KEY";
const SQL_string SQL_AUTOINCREMENT = "AUTOINCREMENT";
const SQL_string SQL_COMMA = ",";
const SQL_string SQL_TEXT = "TEXT";
const SQL_string SQL_NOT = "NOT";
const SQL_string SQL_NULL = "NULL";
const SQL_string SQL_ASTERICS = "*";
const SQL_string SQL_EQ = "=";
const SQL_string SQL_SELECT = "SELECT";
const SQL_string SQL_FROM = "FROM";
const SQL_string SQL_WHERE = "WHERE";
const SQL_string SQL_INSERT = "INSERT";
const SQL_string SQL_INTO = "INTO";
const SQL_string SQL_DELETE = "DELETE";
const SQL_string SQL_VALUES = "VALUES";
const SQL_string SQL_SEMICOLON = ";";

class DataBase
{
public:
    DataBase(const string &db_path);
    ~DataBase();
    void useTable(string_view tableName);
    void insert(ID id, string_view image_path, string_view note);
    void erase(ID id);
    string getImagePath(ID id);
    string getNote(ID id);
    int isUpdated();

private:
    void createDataBase(string_view db_path);
    template<typename T> T getFromDB(string_view query);
    void executeCommand(string_view command);
    void createTableIfNotExists(string_view tableNmae);
    string createPrintAllQuery();
    string createSelectQuery(ID id, string_view item);
    string createQueryForImage(ID id);
    string createQueryForNote(ID id);
    string createInsertQuery(ID id, string_view image_path, string_view note);
    string createEraseQuery(ID id);

private:
    sqlite3 *db_;
    string currentTable_;
};

#endif // DB_DATA_BASE_H
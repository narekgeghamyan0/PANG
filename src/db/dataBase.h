#ifndef DB_DATA_BASE_H
#define DB_DATA_BASE_H

#include <string>
#include <iostream>
#include <vector>
#include <sqlite3.h>

#define QUERY_MAX_SIZE 256

using ID = size_t;
using string = std::string;
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
    void insert(const string &tableName, ID id, const string &image_path, const string &note);
    void erase(const string &tableName, ID id);
    string getImagePath(ID id);
    string getNote(ID id);

private:
    template<typename T> void getFromDB(const string& query, ID id, T& result);
    void createDataBase(const string &db_path);
    void executeCommand(const string& command);
    void createTable(string &&user);
    void createMemoryTable();
    void createPrintAllQuery(const string &tableName, string &query);
    void createSelectQuery(string &&item, string &&column, ID id, string &query);
    void createQueryForImage(ID id, string &query);
    void createQueryForNote(ID id, string &query);
    void createInsertQuery(const string &tableName, ID id, const string &image_path, const string &note, string &query);
    void createEraseQuery(const string &tableName, ID id, string &query);

private:
    sqlite3 *db_;
};

#endif // DB_DATA_BASE_H
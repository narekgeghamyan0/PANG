#include "dataBase.h"

#include <cassert>


template<typename CPP_Type>
CPP_Type sqlite3_column(sqlite3_stmt* stpmt)
{
    return CPP_Type();
}

template<>
int sqlite3_column<int>(sqlite3_stmt* stpmt)
{
    return sqlite3_column_int(stpmt, 0);
}

template<>
double sqlite3_column<double>(sqlite3_stmt* stpmt)
{
    return sqlite3_column_double(stpmt, 0);
}

template<>
ID sqlite3_column<ID>(sqlite3_stmt* stpmt)
{
    return static_cast<ID>(sqlite3_column_int64(stpmt, 0));
}

template<>
string sqlite3_column<string>(sqlite3_stmt* stpmt)
{
    const unsigned char* text = sqlite3_column_text(stpmt, 0);
    return string(reinterpret_cast<const char*>(text));
}

template<>
std::vector<unsigned char> sqlite3_column<std::vector<unsigned char>>(sqlite3_stmt* stpmt)
{
    std::vector<unsigned char> data;
    const void* blob = sqlite3_column_blob(stpmt, 0);
    int size = sqlite3_column_bytes(stpmt, 0);

    if (blob && size > 0) {
        const unsigned char* bytes =
            static_cast<const unsigned char*>(blob);

        data.assign(bytes, bytes + size);
    }
    return data;
}

DataBase::DataBase(const string& db_path)
    : db_(nullptr)
{
    // Open (or create) database
    createDataBase(db_path);
}

DataBase::~DataBase()
{
    if (db_) {
        sqlite3_close(db_);
    }
}

void
DataBase::useTable(string_view tableName)
{
    if (currentTable_ != tableName) {
        createTableIfNotExists(tableName);
        currentTable_ = tableName;
    }
}

void
DataBase::insert(ID id, string_view image_path, string_view note)
{
    string query = createInsertQuery(id, image_path, note);
    executeCommand(query);
}

void
DataBase::erase(ID id)
{
    string query = createEraseQuery(id);
    executeCommand(query);
}

string
DataBase::getImagePath(ID id)
{
    assert(db_ != nullptr);
    string query = createQueryForImage(id);
    string result = getFromDB<string>(query);
    return result;
}

string
DataBase::getNote(ID id)
{
    assert(db_ != nullptr);
    string query = createQueryForNote(id);
    string result = getFromDB<string>(query);
    return result;
}

int
DataBase::isUpdated()
{
    // If the result is not 1, that mean data base chenged at last execution.
    return sqlite3_changes(db_);
}

void
DataBase::createDataBase(string_view db_path)
{
    if (sqlite3_open(db_path.data(), &db_) != SQLITE_OK) {
        throw std::runtime_error(string("ERROR 1: Can't create database: ") + db_path.data());
    }
}

template<typename T>
T
DataBase::getFromDB(string_view query)
{
    sqlite3_stmt* stmt = nullptr;
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db_, query.data(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(string("ERROR 3: Failed to prepare statement for query: ") + query.data());
    }
    // Bind the ID parameter
    // TODO: Need variatic template for different types, counts of arguments and sqlite3_bind_xxx functions
    // sqlite3_bind_int(stmt, 1, id);

    T result = T();
    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column<T>(stmt);
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
    return result;
}

void
DataBase::executeCommand(string_view command)
{
    char* errMsg = nullptr;
    int rd = sqlite3_exec(db_, command.data(), 0, nullptr, &errMsg);
    if (rd != SQLITE_OK) {
        string errStr("ERROR 2: ");
        errStr.append(errMsg);
        sqlite3_free(errMsg);
        throw std::runtime_error(errStr);
    }
}

void
DataBase::createTableIfNotExists(string_view tableName)
{
    // Create table query
    string query;
    query.reserve(QUERY_MAX_SIZE);

    query.append("CREATE TABLE IF NOT EXISTS ")
         .append(tableName.data())
         .append("(")
         .append("id INTEGER PRIMARY KEY,")
         .append("image_path TEXT NOT NULL,")
         .append("note TEXT NOT NULL);");

    executeCommand(query);
}

string
DataBase::createPrintAllQuery()
{
    string query;
    query.reserve(QUERY_MAX_SIZE);

    query.append("SELECT * FROM ")
         .append(currentTable_)
         .append(";");

    return query;
}

string
DataBase::createSelectQuery(ID id, string_view item)
{
    string query;
    query.reserve(QUERY_MAX_SIZE);

    query.append("SELECT ")
         .append(item)
         .append(" FROM ")
         .append(currentTable_)
         .append(" WHERE id = ")
         .append(std::to_string(id))
         .append(";");

    return query;
}

string
DataBase::createQueryForImage(ID id)
{
    return createSelectQuery(id, "image_path");
}

string
DataBase::createQueryForNote(ID id)
{
    return createSelectQuery(id, "note");
}

string
DataBase::createInsertQuery(ID id, string_view image_path, string_view note)
{
    string query;
    query.reserve(QUERY_MAX_SIZE);

    query.append("INSERT INTO ")
         .append(currentTable_)
         .append(" VALUES(")
         .append(std::to_string(id))
         .append(", \'")
         .append(image_path)
         .append("\', \'")
         .append(note)
         .append("\');");

    return query;
}

string
DataBase::createEraseQuery(ID id)
{
    string query;
    query.reserve(QUERY_MAX_SIZE);

    query.append("DELETE FROM ")
         .append(currentTable_)
         .append(" WHERE ID = ")
         .append(std::to_string(id))
         .append("; ");

    return query;
}
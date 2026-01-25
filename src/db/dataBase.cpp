#include "db/dataBase.h"
struct CallbackForCheck
{ 
    void operator()(void* data, int argc, char** argv, char** azColName) {
        int i;
        fprintf(stderr, "%s: ", (const char*)data);

        for (i = 0; i < argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }

        printf("\n");
    }
} callbackForCheck;


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

template<typename T>
void
DataBase::getFromDB(const string& query, ID id, T& result)
{
    sqlite3_stmt* stmt = nullptr;
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("ERROR 3: Failed to prepare statement for query: " + query);
    }

    // Bind the ID parameter
    // TODO: Need variatic template for different types, counts of arguments and sqlite3_bind_xxx functions
    sqlite3_bind_int(stmt, 1, id);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        result = sqlite3_column<T>(stmt, 0);
        sqlite3_finalize(stmt);
        throw std::runtime_error("ERROR 4: Failed to execute statement for query: " + query);
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
}

void
DataBase::executeCommand(const string& command)
{
    char* errMsg = nullptr;
    int rd = sqlite3_exec(db_, command.c_str(), 0, nullptr, &errMsg);
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
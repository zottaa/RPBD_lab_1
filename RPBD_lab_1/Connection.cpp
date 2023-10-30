#include "Connection.h"

Connection::Connection(const wstring& connectionString)
{
    this->connectionString = connectionString;
    this->connect();
}

Connection::~Connection()
{
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}

SQLHSTMT& Connection::query(const wchar_t* sql)
{
    checkConnection();
    SQLRETURN retcode = SQLExecDirect(hstmt, (SQLWCHAR*)sql, SQL_NTS);
    if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO && retcode != SQL_NO_DATA) {
        SQLSMALLINT recNumber = 1;
        SQLWCHAR sqlState[6];
        SQLINTEGER nativeError;
        SQLWCHAR errMsg[SQL_MAX_MESSAGE_LENGTH];
        SQLSMALLINT errMsgLength;
        SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, recNumber, sqlState, &nativeError, errMsg, SQL_MAX_MESSAGE_LENGTH, &errMsgLength);
        std::wcerr << L"SQL query execution failed. SQL State: " << sqlState << L", Native Error: " << nativeError << L", Error Message: " << errMsg << std::endl;
        throw std::runtime_error("SQL query execution failed");
    }
    return hstmt;
}

void Connection::connect()
{
    SQLRETURN retcode;
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

    retcode = SQLDriverConnect(hdbc, NULL, (SQLWCHAR*)connectionString.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Connected to the database." << std::endl;
    }
    else {
        std::cerr << "Connection failed." << std::endl;
    }

    this->checkTables();
}

void Connection::checkTables()
{
    wstring sql = L"CREATE TABLE IF not exists student (id serial primary key, lastname varchar(255), name varchar(255), surname varchar(255), address varchar(255), birth_date varchar(255), class integer, entry_year varchar(255));";
    this->query(sql.c_str());
    
    sql = L"CREATE TABLE IF not exists parent (id serial primary key, lastname varchar(255), name varchar(255), surname varchar(255), address varchar(255), relation_degree varchar(255));";
    this->query(sql.c_str());

    sql = L"CREATE TABLE IF not exists performance (id serial primary key, student_id integer references student(id), year date, class integer, subject varchar(255), quarterly_grade integer, semester_grade integer, annual_grade integer, examination_grade integer, final_grade integer);";
    this->query(sql.c_str());

    sql = L"create table if not exists students_to_parents (id serial primary key, student_id integer references student(id), parent_id integer references parent(id));";
    this->query(sql.c_str());
   
}

void Connection::checkConnection()
{
    SQLRETURN retcode = SQLTables(hstmt, NULL, 0, NULL, 0, NULL, 0, NULL, 0);
    if (retcode == SQL_ERROR) {
        this->connect();
    }
    SQLCloseCursor(hstmt);
}

#pragma once


#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>


using namespace std;


class Connection
{
private:
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
	wstring connectionString;
public:
	Connection(const wstring& connectionString = L"DSN=PostgreSQL35W;UID=admin;PWD=12345;");
	~Connection();
	SQLHSTMT& query(const SQLWCHAR* sql);
	void connect();
	void checkTables();
	void checkConnection();
};


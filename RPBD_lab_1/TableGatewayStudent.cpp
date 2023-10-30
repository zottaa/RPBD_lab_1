#include "TableGatewayStudent.h"

void TableGatewayStudent::loadData()
{
	for (auto student : recordSet) {
		delete student;
	}
	recordSet.clear();
	try {
		int rows = getRows(L"select * from student;");
		int columns = 8;

		SQLHSTMT stmt = connection.query(L"select * from student;");
		SQLRETURN retcode;
		SQLCHAR* ColumnData[8];

		ColumnData[0] = (SQLCHAR*)malloc(7);
		ColumnData[1] = (SQLCHAR*)malloc(255);
		ColumnData[2] = (SQLCHAR*)malloc(255);
		ColumnData[3] = (SQLCHAR*)malloc(255);
		ColumnData[4] = (SQLCHAR*)malloc(255);
		ColumnData[5] = (SQLCHAR*)malloc(255);
		ColumnData[6] = (SQLCHAR*)malloc(7);
		ColumnData[7] = (SQLCHAR*)malloc(255);

		SQLBindCol(stmt, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
		SQLBindCol(stmt, 2, SQL_C_CHAR, ColumnData[1], 255, nullptr);
		SQLBindCol(stmt, 3, SQL_C_CHAR, ColumnData[2], 255, nullptr);
		SQLBindCol(stmt, 4, SQL_C_CHAR, ColumnData[3], 255, nullptr);
		SQLBindCol(stmt, 5, SQL_C_CHAR, ColumnData[4], 255, nullptr);
		SQLBindCol(stmt, 6, SQL_C_CHAR, ColumnData[5], 255, nullptr);
		SQLBindCol(stmt, 7, SQL_C_CHAR, ColumnData[6], 7, nullptr);
		SQLBindCol(stmt, 8, SQL_C_CHAR, ColumnData[7], 255, nullptr);

		while (1) {
			retcode = SQLFetch(stmt);

			if (retcode == SQL_NO_DATA) {
				break;
			}
			int id = stoi((const char*)ColumnData[0]);
			string lastname = string((const char*)ColumnData[1]);
			string name = string((const char*)ColumnData[2]);
			string surname = string((const char*)ColumnData[3]);
			string address = string((const char*)ColumnData[4]);
			string birth_date = string((const char*)ColumnData[5]);
			int _class = stoi((const char*)ColumnData[6]);
			string entry_date = string((const char*)ColumnData[7]);
			Student* student = new Student(id, lastname, name, surname, address, birth_date, _class, entry_date);
			recordSet.push_back(student);
		}
		SQLFreeStmt(stmt, SQL_CLOSE);
	} 
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void TableGatewayStudent::getNow()
{
	this->loadData();
	if (getRecordSetSize())
		this->currentIndex = 0;
	else
		this->currentIndex = -1;
}

void TableGatewayStudent::find(int id)
{
	if (1 > id || id - 1 >= recordSet.size()) {
		throw std::out_of_range("Invalid index");
	}
	this->currentIndex = id - 1;
}

const int TableGatewayStudent::getCursor()
{
	return this->currentIndex + 1;
}

const int TableGatewayStudent::getId()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getId();
}

const string& TableGatewayStudent::getLastname()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getLastname();
}

const string& TableGatewayStudent::getName()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getName();
}

const string& TableGatewayStudent::getSurname()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getSurname();
}

const string& TableGatewayStudent::getAddress()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getAddress();
}

const string& TableGatewayStudent::getBirthDate()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getBirthDate();
}

const int TableGatewayStudent::getClass()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getClass();
}

const string& TableGatewayStudent::getEntryDate()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getEntryDate();
}

void TableGatewayStudent::setLastname(const string& newLastname)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, newLastname, this->getName(), this->getSurname(), this->getAddress(), this->getBirthDate(), this->getClass(), this->getEntryDate());
}

void TableGatewayStudent::setName(const string& newName)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), newName, this->getSurname(), this->getAddress(), this->getBirthDate(), this->getClass(), this->getEntryDate());
}

void TableGatewayStudent::setSurname(const string& newSurname)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), newSurname, this->getAddress(), this->getBirthDate(), this->getClass(), this->getEntryDate());
}

void TableGatewayStudent::setAddress(const string& newAddress)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), this->getSurname(), newAddress, this->getBirthDate(), this->getClass(), this->getEntryDate());
}

void TableGatewayStudent::setBirthDate(const string& newBirthDate)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), this->getSurname(), this->getAddress(), newBirthDate, this->getClass(), this->getEntryDate());
}

void TableGatewayStudent::setClass(int newClass)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), this->getSurname(), this->getAddress(), this->getBirthDate(), newClass, this->getEntryDate());
}

void TableGatewayStudent::setEntryDate(const string& newEntryDate)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), this->getSurname(), this->getAddress(), this->getBirthDate(), this->getClass(), newEntryDate);
}

void TableGatewayStudent::insert(string lastname, string name, string surname, string address, string birth_date, int _class, string entry_date)
{
	try {
		const string preSql = "INSERT INTO Student (lastname, name, surname, address, birth_date, class, entry_year) VALUES ('" + lastname + "', '" + name + "', '" + surname + "', '" + address + "', '" + birth_date + "', " + to_string(_class) + ", '" + entry_date + "');";
		const wstring sql = wstring(preSql.begin(), preSql.end());
		SQLHSTMT stmt = connection.query(sql.c_str());

		this->loadData();
		SQLFreeStmt(stmt, SQL_CLOSE);
	} 
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void TableGatewayStudent::update(int id, string lastname, string name, string surname, string address, string birth_date, int _class, string entry_date) 
{
	try {
		if ((0 > (id - 1)) || ((id - 1) >= getRecordSetSize())) {
			throw std::out_of_range("Invalid id");
		}

		int realId = recordSet[id - 1]->getId();
		const string preSql = "UPDATE student SET lastname = '" + lastname + "', name = '" + name + "', surname = '" + surname + "', address = '" + address + "', birth_date = '" + birth_date + "', class = " + to_string(_class) + ", entry_year = '" + entry_date + "' where id = " + to_string(realId) + ';';
		const wstring sql = wstring(preSql.begin(), preSql.end());

		SQLHSTMT stmt = connection.query(sql.c_str());

		recordSet[id - 1]->setLastname(lastname);
		recordSet[id - 1]->setName(name);
		recordSet[id - 1]->setSurname(surname);
		recordSet[id - 1]->setAddress(address);
		recordSet[id - 1]->setBirthDate(birth_date);
		recordSet[id - 1]->setClass(_class);
		recordSet[id - 1]->setEntryDate(entry_date);

		SQLFreeStmt(stmt, SQL_CLOSE);
	}
	catch (const out_of_range& e) {
		cerr << e.what() << endl;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void TableGatewayStudent::deleteById(int id)
{
	try {
		if (1 > id || id - 1 > recordSet.size()) {
			throw std::out_of_range("Invalid id");
		}

		if (getRecordSetSize() <= 0) {
			throw std::logic_error("Table is empty");
		}

		int realId = recordSet[id - 1]->getId();

		const string preSqlFamilyRelationships = "DELETE from students_to_parents WHERE student_id = " + to_string(realId) + ';';
		const wstring sqlFamilyRelationships = wstring(preSqlFamilyRelationships.begin(), preSqlFamilyRelationships.end());
		SQLHSTMT stmt = connection.query(sqlFamilyRelationships.c_str());
		SQLFreeStmt(stmt, SQL_CLOSE);

		const string preSqlPerformance = "DELETE from performance WHERE student_id = " + to_string(realId) + ';';
		const wstring sqlPerformance = wstring(preSqlPerformance.begin(), preSqlPerformance.end());
		stmt = connection.query(sqlPerformance.c_str());
		SQLFreeStmt(stmt, SQL_CLOSE);

		const string preSql = "DELETE from student WHERE id = " + to_string(realId) + ';';
		const wstring sql = wstring(preSql.begin(), preSql.end());
		stmt = connection.query(sql.c_str());

		delete recordSet[id - 1];
		recordSet.erase(recordSet.begin() + (id - 1));
		if (getRecordSetSize() <= 0) {
			currentIndex = -1;
		}

		SQLFreeStmt(stmt, SQL_CLOSE);
	}
	catch (const out_of_range& e) {
		cerr << e.what() << endl;
	}
	catch (const logic_error& e) {
		cerr << e.what() << endl;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void TableGatewayStudent::deleteCurrent()
{
	deleteById(currentIndex + 1);
}

int TableGatewayStudent::getRecordSetSize()
{
	return recordSet.size();
}

int TableGatewayStudent::getRows(const wchar_t* sql)
{
	int rows = 0;
	SQLHSTMT stmt = connection.query(sql);
	while (1) {
		SQLRETURN retcode = SQLFetch(stmt);

		if (retcode == SQL_NO_DATA) {
			break;
		}
		rows++;
	}
	SQLFreeStmt(stmt, SQL_CLOSE);
	return rows;
}

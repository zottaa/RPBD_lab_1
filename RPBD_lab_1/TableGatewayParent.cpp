#include "TableGatewayParent.h"

void TableGatewayParent::loadData()
{
	for (auto parent : recordSet) {
		delete parent;
	}
	recordSet.clear();
	try {
		int rows = getRows(L"select * from parent;");
		int columns = 6;

		SQLHSTMT stmt = connection.query(L"select * from parent;");
		SQLRETURN retcode;
		SQLCHAR* ColumnData[6];

		ColumnData[0] = (SQLCHAR*)malloc(7);
		ColumnData[1] = (SQLCHAR*)malloc(255);
		ColumnData[2] = (SQLCHAR*)malloc(255);
		ColumnData[3] = (SQLCHAR*)malloc(255);
		ColumnData[4] = (SQLCHAR*)malloc(255);
		ColumnData[5] = (SQLCHAR*)malloc(255);

		SQLBindCol(stmt, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
		SQLBindCol(stmt, 2, SQL_C_CHAR, ColumnData[1], 255, nullptr);
		SQLBindCol(stmt, 3, SQL_C_CHAR, ColumnData[2], 255, nullptr);
		SQLBindCol(stmt, 4, SQL_C_CHAR, ColumnData[3], 255, nullptr);
		SQLBindCol(stmt, 5, SQL_C_CHAR, ColumnData[4], 255, nullptr);
		SQLBindCol(stmt, 6, SQL_C_CHAR, ColumnData[5], 255, nullptr);

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
			string relationDegree = string((const char*)ColumnData[5]);
			Parent* parent = new Parent(id, lastname, name, surname, address, relationDegree);
			recordSet.push_back(parent);
		}
		SQLFreeStmt(stmt, SQL_CLOSE);
	} 
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

int TableGatewayParent::getRows(const wchar_t* sql)
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

void TableGatewayParent::getNow()
{
	this->loadData();
	if (getRecordSetSize())
		this->currentIndex = 0;
	else
		this->currentIndex = -1;
}

void TableGatewayParent::find(int id)
{
	if (1 > id || id - 1 >= recordSet.size()) {
		throw std::out_of_range("Invalid index");
	}
	this->currentIndex = id - 1;
}

const int TableGatewayParent::getCursor()
{
	return this->currentIndex + 1;
}

const int TableGatewayParent::getId()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getId();
}

const string& TableGatewayParent::getLastname()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getLastname();
}

const string& TableGatewayParent::getName()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getName();
}

const string& TableGatewayParent::getSurname()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getSurname();
}

const string& TableGatewayParent::getAddress()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getAddress();
}

const string& TableGatewayParent::getRelationDegree()
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	return recordSet.at(currentIndex)->getRelationDegree();
}

void TableGatewayParent::setLastname(const string& newLastname)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, newLastname, this->getName(), this->getSurname(), this->getAddress(), this->getRelationDegree());
}

void TableGatewayParent::setName(const string& newName)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), newName, this->getSurname(), this->getAddress(), this->getRelationDegree());
}

void TableGatewayParent::setSurname(const string& newSurname)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), newSurname, this->getAddress(), this->getRelationDegree());
}

void TableGatewayParent::setAddress(const string& newAddress)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), this->getSurname(), newAddress, this->getRelationDegree());
}

void TableGatewayParent::setRelationDegree(const string& newRelationDegree)
{
	if (this->currentIndex == -1) {
		throw std::logic_error("No records");
	}
	this->update(this->currentIndex + 1, this->getLastname(), this->getName(), this->getSurname(), this->getAddress(), newRelationDegree);
}

void TableGatewayParent::insert(string lastname, string name, string surname, string address, string relationDegree)
{
	try {
		const string preSql = "INSERT INTO Parent (lastname, name, surname, address, relation_degree) VALUES ('" + lastname + "', '" + name + "', '" + surname + "', '" + address + "', '" + relationDegree + "');";
		const wstring sql = wstring(preSql.begin(), preSql.end());
		SQLHSTMT stmt = connection.query(sql.c_str());

		this->loadData();
		SQLFreeStmt(stmt, SQL_CLOSE);
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void TableGatewayParent::update(int id, string lastname, string name, string surname, string address, string relationDegree)
{
	try {
		if ((0 > (id - 1)) || ((id - 1) >= getRecordSetSize())) {
			throw std::out_of_range("Invalid id");
		}

		int realId = recordSet[id - 1]->getId();
		const string preSql = "UPDATE parent SET lastname = '" + lastname + "', name = '" + name + "', surname = '" + surname + "', address = '" + address + "', relation_degree = '" + relationDegree + "' where id = " + to_string(realId) + ';';
		const wstring sql = wstring(preSql.begin(), preSql.end());

		SQLHSTMT stmt = connection.query(sql.c_str());

		recordSet[id - 1]->setLastname(lastname);
		recordSet[id - 1]->setName(name);
		recordSet[id - 1]->setSurname(surname);
		recordSet[id - 1]->setAddress(address);
		recordSet[id - 1]->setRelationDegree(relationDegree);

		SQLFreeStmt(stmt, SQL_CLOSE);
	}
	catch (const out_of_range& e) {
		cerr << e.what() << endl;
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void TableGatewayParent::deleteById(int id)
{
	try {
		if (1 > id || id - 1 > recordSet.size()) {
			throw std::out_of_range("Invalid id");
		}

		if (getRecordSetSize() <= 0) {
			throw std::logic_error("Table is empty");
		}

		int realId = recordSet[id - 1]->getId();

		const string preSqlFamilyRelationships = "DELETE from students_to_parents WHERE parent_id = " + to_string(realId) + ';';
		const wstring sqlFamilyRelationships = wstring(preSqlFamilyRelationships.begin(), preSqlFamilyRelationships.end());
		SQLHSTMT stmt = connection.query(sqlFamilyRelationships.c_str());
		SQLFreeStmt(stmt, SQL_CLOSE);

		const string preSql = "DELETE from parent WHERE id = " + to_string(realId) + ';';
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

void TableGatewayParent::deleteCurrent()
{
	deleteById(currentIndex + 1);
}

int TableGatewayParent::getRecordSetSize()
{
	return recordSet.size();
}

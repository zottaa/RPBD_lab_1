#pragma once
#include "Connection.h"
#include "Student.h"
#include "TableGatewayPerformance.h"
#include <vector>

class TableGatewayStudent
{
private:
	Connection& connection;
	vector<Student*> recordSet;
	void loadData();
	int getRows(const wchar_t* sql);
	int currentIndex;
public:
	TableGatewayStudent(Connection& connection) : connection(connection) {
		loadData();
		if (getRecordSetSize())
			this->currentIndex = 0;
		else
			this->currentIndex = -1;
	}

	~TableGatewayStudent() {
		for (auto student : recordSet) {
			delete student;
		}
		recordSet.clear();
	}

	void getNow();
	void find(int id);
	const int getCursor();
	const int getId();
	const string& getLastname();
	const string& getName();
	const string& getSurname();
	const string& getAddress();
	const string& getBirthDate();
	const int getClass();
	const string& getEntryDate();
	void setLastname(const string& newLastname);
	void setName(const string& newName);
	void setSurname(const string& newSurname);
	void setAddress(const string& newAddress);
	void setBirthDate(const string& newBirthDate);
	void setClass(int newClass);
	void setEntryDate(const string& newEntryDate);
	void insert(string lastname, string name, string surname, string address, string birth_date, int _class, string entry_date);
	void update(int id, string lastname, string name, string surname, string address, string birth_date, int _class, string entry_date);
	void deleteById(int id);
	void deleteCurrent();
	int getRecordSetSize();
};


#pragma once

#include "Connection.h"
#include "Parent.h"
#include <vector>

class TableGatewayParent
{
private:
	Connection& connection;
	vector<Parent*> recordSet;
	void loadData();
	int getRows(const wchar_t* sql);
	int currentIndex;
public:
	TableGatewayParent(Connection& connection) : connection(connection) {
		loadData();
		if (getRecordSetSize())
			this->currentIndex = 0;
		else
			this->currentIndex = -1;
	}
	~TableGatewayParent() {
		for (auto parent : recordSet) {
			delete parent;
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
	const string& getRelationDegree();
	void setLastname(const string& newLastname);
	void setName(const string& newName);
	void setSurname(const string& newSurname);
	void setAddress(const string& newAddress);
	void setRelationDegree(const string& newRelationDegree);

	void insert(string lastname, string name, string surname, string address, string relationDegree);
	void update(int id, string lastname, string name, string surname, string address, string relationDegree);
	void deleteById(int id);
	void deleteCurrent();
	int getRecordSetSize();
};


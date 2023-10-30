#pragma once

#include "FamilyRelationships.h"
#include "TableGatewayParent.h"
#include "TableGatewayStudent.h"
#include "Connection.h"

class TableGatewayFamilyRelationships
{
private:
	Connection& connection;
	vector<FamilyRelationships*> recordSet;
	void loadData();
	int getRows(const wchar_t* sql);
	int currentIndex;
public:
	TableGatewayFamilyRelationships(Connection& connection) : connection(connection) {
		loadData();
		if (getRecordSetSize())
			this->currentIndex = 0;
		else
			this->currentIndex = -1;
	}

	~TableGatewayFamilyRelationships() {
		for (auto familyRelationships : recordSet) {
			delete familyRelationships->getParent();
			delete familyRelationships->getStudent();
			delete familyRelationships;
		}
		recordSet.clear();
	}

	void getNow();
	void find(int id);
	const int getCursor();
	const int getId();
	Student* getStudent();
	Parent* getParent();

	void setStudent(const int newStudentId);
	void setParent(const int newParentId);

	void insert(int student_id, int parent_id);
	void update(int id, int student_id, int parent_id);
	void deleteById(int id);
	void deleteCurrent();
	int getRecordSetSize();
};


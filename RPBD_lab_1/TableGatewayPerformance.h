#pragma once

#include "Performance.h"
#include "Connection.h"
#include <vector>
#include "TableGatewayStudent.h"


class TableGatewayPerformance
{
private:
	Connection& connection;
	vector<Performance*> recordSet;
	void loadData();
	int getRows(const wchar_t* sql);
	int currentIndex;
public:
	TableGatewayPerformance(Connection& connection) : connection(connection) {
		loadData();
		if (getRecordSetSize())
			this->currentIndex = 0;
		else
			this->currentIndex = -1;
	}

	~TableGatewayPerformance() {
		for (auto performance : recordSet) {
			delete performance->getStudent();
			delete performance;
		}
		recordSet.clear();
	}

	void getNow();
	void find(int id);
	const int getCursor();
	const int getId();
	Student* getStudent();
	const string& getYear();
	const int getClass();
	const string& getSubject();
	const int getQuarterlyGrade();
	const int getSemesterGrade();
	const int getAnnualGrade();
	const int getExaminationGrade();
	const int getFinalGrade();


	void setStudent(const int newStudentId);
	void setYear(const string& newYear);
	void setClass(const int newClass);
	void setSubject(const string& newSubject);
	void setQuarterlyGrade(const int newQuarterlyGrade);
	void setSemesterGrade(const int newSemesterGrade);
	void setAnnualGrade(const int newAnnualGrade);
	void setExaminationGrade(const int newExaminationGrade);
	void setFinalGrade(const int newFinalGrade);
	

	void insert(int student_id, string year, int _class, string subject, int quarterlyGrade, int semesterGrade, int annualGrade, int examinationGrade, int finalGrade);
	void update(int id, int student_id, string year, int _class, string subject, int quarterlyGrade, int semesterGrade, int annualGrade, int examinationGrade, int finalGrade);
	void deleteById(int id);
	void deleteCurrent();
	int getRecordSetSize();
};


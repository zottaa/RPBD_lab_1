#pragma once
#include "Student.h"


class Performance
{
private:
	int id;
	Student* student;
	string year;
	int _class;
	string subject;
	int quarterlyGrade;
	int semesterGrade;
	int annualGrade;
	int examinationGrade;
	int finalGrade;
public:
	Performance(int id, Student* student, string year, int _class, string subject, int quarterlyGrade, int semesterGrade, int annualGrade, int examinationGrade, int finalGrade) : 
		id(id), student(student), year(year), _class(_class), subject(subject), quarterlyGrade(quarterlyGrade), semesterGrade(semesterGrade), annualGrade(annualGrade), examinationGrade(examinationGrade), finalGrade(finalGrade) {}
	
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

	void setStudent(Student* newStudent);
	void setYear(const string& newYear);
	void setClass(const int newClass);
	void setSubject(const string& newSubject);
	void setQuarterlyGrade(const int newQuarterlyGrade);
	void setSemesterGrade(const int newSemesterGrade);
	void setAnnualGrade(const int newAnnualGrade);
	void setExaminationGrade(const int newExaminationGrade);
	void setFinalGrade(const int newFinalGrade);

};


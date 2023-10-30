#include "Performance.h"

const int Performance::getId()
{
	return this->id;
}

Student* Performance::getStudent()
{
	return this->student;
}

const string& Performance::getYear()
{
	return this->year;
}

const int Performance::getClass()
{
	return this->_class;
}

const string& Performance::getSubject()
{
	return this->subject;
}

const int Performance::getQuarterlyGrade()
{
	return this->quarterlyGrade;
}

const int Performance::getSemesterGrade()
{
	return this->semesterGrade;
}

const int Performance::getAnnualGrade()
{
	return this->annualGrade;
}

const int Performance::getExaminationGrade()
{
	return this->examinationGrade;
}

const int Performance::getFinalGrade()
{
	return this->finalGrade;
}

void Performance::setStudent(Student* newStudent)
{
	this->student = newStudent;
}

void Performance::setYear(const string& newYear)
{
	this->year = newYear;
}

void Performance::setClass(const int newClass)
{
	this->_class = newClass;
}

void Performance::setSubject(const string& newSubject)
{
	this->subject = newSubject;
}

void Performance::setQuarterlyGrade(const int newQuarterlyGrade)
{
	this->quarterlyGrade = newQuarterlyGrade;
}

void Performance::setSemesterGrade(const int newSemesterGrade)
{
	this->semesterGrade = newSemesterGrade;
}

void Performance::setAnnualGrade(const int newAnnualGrade)
{
	this->annualGrade = newAnnualGrade;
}

void Performance::setExaminationGrade(const int newExaminationGrade)
{
	this->examinationGrade = newExaminationGrade;
}

void Performance::setFinalGrade(const int newFinalGrade)
{
	this->finalGrade = newFinalGrade;
}

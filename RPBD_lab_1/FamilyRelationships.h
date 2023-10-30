#pragma once
#include "Student.h"
#include "Parent.h"

class FamilyRelationships
{
private:
	int id;
	Student* student;
	Parent* parent;
public:
	FamilyRelationships(int id, Student* student, Parent* parent) : id(id), student(student), parent(parent) {}

	const int getId();
	Student* getStudent();
	Parent* getParent();

	void setStudent(Student* newStudent);
	void setParent(Parent* newParent);
};


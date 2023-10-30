#include "FamilyRelationships.h"

const int FamilyRelationships::getId()
{
	return this->id;
}

Student* FamilyRelationships::getStudent()
{
	return this->student;
}

Parent* FamilyRelationships::getParent()
{
	return this->parent;
}

void FamilyRelationships::setStudent(Student* newStudent)
{
	this->student = newStudent;
}

void FamilyRelationships::setParent(Parent* newParent)
{
	this->parent = newParent;
}

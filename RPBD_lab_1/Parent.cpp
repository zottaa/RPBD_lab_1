#include "Parent.h"

const int Parent::getId()
{
	return this->id;
}

const string& Parent::getLastname()
{
	return this->lastname;
}

const string& Parent::getName()
{
	return this->name;
}

const string& Parent::getSurname()
{
	return this->surname;
}

const string& Parent::getAddress()
{
	return this->address;
}

const string& Parent::getRelationDegree()
{
	return this->relationDegree;
}

void Parent::setLastname(const string& newLastname)
{
	this->lastname = newLastname;
}

void Parent::setName(const string& newName)
{
	this->name = newName;
}

void Parent::setSurname(const string& newSurname)
{
	this->surname = newSurname;
}

void Parent::setAddress(const string& newAddress)
{
	this->address = newAddress;
}

void Parent::setRelationDegree(const string& newRelationDegree)
{
	this->relationDegree = newRelationDegree;
}

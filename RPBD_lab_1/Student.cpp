#include "Student.h"

const int Student::getId()
{
    return this->id;
}

const string& Student::getLastname()
{
    return this->lastname;
}

const string& Student::getName()
{
    return this->name;
}

const string& Student::getSurname()
{
    return this->surname;
}

const string& Student::getAddress()
{
    return this->address;
}

const string& Student::getBirthDate()
{
    return this->birth_date;
}

const int Student::getClass()
{
    return this->_class;
}

const string& Student::getEntryDate()
{
    return this->entry_date;
}

void Student::setLastname(const string& newLastname)
{
    this->lastname = newLastname;
}

void Student::setName(const string& newName)
{
    this->name = newName;
}

void Student::setSurname(const string& newSurname)
{
    this->surname = newSurname;
}

void Student::setAddress(const string& newAddress)
{
    this->address = newAddress;
}

void Student::setBirthDate(const string& newBirthDate)
{
    this->birth_date = newBirthDate;
}

void Student::setClass(int newClass)
{
    this->_class = newClass;
}

void Student::setEntryDate(const string& newEntryDate)
{
    this->entry_date = newEntryDate;
}



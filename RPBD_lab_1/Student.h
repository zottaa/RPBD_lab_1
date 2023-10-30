#pragma once

#include <string>


using namespace std;


class Student
{
private:
	int id;
	string lastname;
	string name;
	string surname;
	string address;
	string birth_date;
	int _class;
	string entry_date;
public:
	Student(int id, string lastname, string name, string surname, string address, string birth_date, int _class, string entry_date) : id(id), lastname(lastname), name(name), surname(surname),
		address(address), birth_date(birth_date), _class(_class), entry_date(entry_date)
	{};
	
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
	void setClass(int  newClass);
	void setEntryDate(const string& newEntryDate);
};


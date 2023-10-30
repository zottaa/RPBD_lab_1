#pragma once


#include <string>


using namespace std;


class Parent
{
private:
	int id;
	string lastname;
	string name;
	string surname;
	string address;
	string relationDegree;
public:
	Parent(int id, string lastname, string name, string surname, string address, string relationDegree) : id(id), lastname(lastname), name(name), surname(surname),
		address(address), relationDegree(relationDegree) {}

	const int getId();
	const string& getLastname();
	const string& getName();
	const string& getSurname();
	const string& getAddress();
	const string& getRelationDegree();

	void setLastname(const string& newLastname);
	void setName(const string& newName);
	void setSurname(const string& newSurname);
	void setAddress(const string& newAdress);
	void setRelationDegree(const string& newRelationDegree);
};


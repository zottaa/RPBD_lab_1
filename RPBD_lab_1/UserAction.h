#pragma once
#include "TableGatewayFamilyRelationships.h"
#include "TableGatewayParent.h"
#include "TableGatewayPerformance.h"
#include "TableGatewayStudent.h"
#include <iostream>
#include <iomanip>

class UserAction
{
private:
	void printStudent(TableGatewayStudent& gatewayStudent, int id);
	void printParent(TableGatewayParent& gatewayParent, int id);
	void printPerformance(TableGatewayPerformance& gatewayPerformance, TableGatewayStudent& gatewayStudent, int id);
	void printFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships, TableGatewayStudent& gatewayStudent, TableGatewayParent& gatewayParent, int id);

public:
	void viewStudent(TableGatewayStudent& gatewayStudent);
	void insertStudent(TableGatewayStudent& gatewayStudent);
	void updateStudent(TableGatewayStudent& gatewayStudent);
	void deleteStudent(TableGatewayStudent& gatewayStudent);

	void viewParent(TableGatewayParent& gatewayParent);
	void insertParent(TableGatewayParent& gatewayParent);
	void updateParent(TableGatewayParent& gatewayParent);
	void deleteParent(TableGatewayParent& gatewayParent);

	void viewPerformance(TableGatewayPerformance& gatewayPerformance, TableGatewayStudent& gatewayStudent);
	void insertPerformance(TableGatewayPerformance& gatewayPerformance);
	void updatePerformance(TableGatewayPerformance& gatewayPerformance);
	void deletePerformance(TableGatewayPerformance& gatewayPerformance);

	void viewFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships, TableGatewayStudent& gatewayStudent, TableGatewayParent& gatewayParent);
	void insertFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships);
	void updateFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships);
	void deleteFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships);
};


#include "UserAction.h"

void UserAction::printStudent(TableGatewayStudent& gatewayStudent, int id)
{
    try {
        gatewayStudent.find(id);

        cout << left << setw(7) << gatewayStudent.getCursor();
        cout << left << setw(20) << gatewayStudent.getLastname();
        cout << left << setw(20) << gatewayStudent.getName();
        cout << left << setw(20) << gatewayStudent.getSurname();
        cout << left << setw(20) << gatewayStudent.getAddress();
        cout << left << setw(20) << gatewayStudent.getBirthDate();
        cout << left << setw(20) << gatewayStudent.getClass();
        cout << left << setw(20) << gatewayStudent.getEntryDate() << endl;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::printParent(TableGatewayParent& gatewayParent, int id)
{
    try {
        gatewayParent.find(id);

        cout << left << setw(7) << gatewayParent.getCursor();
        cout << left << setw(20) << gatewayParent.getLastname();
        cout << left << setw(20) << gatewayParent.getName();
        cout << left << setw(20) << gatewayParent.getSurname();
        cout << left << setw(40) << gatewayParent.getAddress();
        cout << left << setw(20) << gatewayParent.getRelationDegree() << endl;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::printPerformance(TableGatewayPerformance& gatewayPerformance, TableGatewayStudent& gatewayStudent, int id)
{
    try {
        gatewayPerformance.find(id);
        Student* student = gatewayPerformance.getStudent();

        cout << left << setw(7) << gatewayPerformance.getCursor();
        int cursorStudent = 0;
        for (int i = 0; i < gatewayStudent.getRecordSetSize(); i++) {
            gatewayStudent.find(i + 1);
            if (gatewayStudent.getId() == student->getId()) {
                cursorStudent = gatewayStudent.getCursor();
                break;
            }
        }

        cout << left << setw(11) << cursorStudent;
        cout << left << setw(10) << student->getLastname();
        cout << left << setw(10) << student->getName();
        cout << left << setw(10) << student->getSurname();
        cout << left << setw(20) << student->getAddress();
        cout << left << setw(12) << student->getBirthDate();
        cout << left << setw(7) << student->getClass();
        cout << left << setw(12) << student->getEntryDate();
        cout << left << setw(10) << gatewayPerformance.getYear();
        cout << left << setw(7) << gatewayPerformance.getClass();
        cout << left << setw(10) << gatewayPerformance.getSubject();
        cout << left << setw(18) << gatewayPerformance.getQuarterlyGrade();
        cout << left << setw(18) << gatewayPerformance.getSemesterGrade();
        cout << left << setw(18) << gatewayPerformance.getAnnualGrade();
        cout << left << setw(18) << gatewayPerformance.getExaminationGrade();
        cout << left << setw(18) << gatewayPerformance.getFinalGrade() << endl;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::printFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships, TableGatewayStudent& gatewayStudent, TableGatewayParent& gatewayParent, int id)
{
    try {
        gatewayFamilyRelationships.find(id);
        Student* student = gatewayFamilyRelationships.getStudent();
        Parent* parent = gatewayFamilyRelationships.getParent();

        cout << left << setw(7) << gatewayFamilyRelationships.getCursor();
        int cursorStudent = 0;
        for (int i = 0; i < gatewayStudent.getRecordSetSize(); i++) {
            gatewayStudent.find(i + 1);
            if (gatewayStudent.getId() == student->getId()) {
                cursorStudent = gatewayStudent.getCursor();
                break;
            }
        }

        int cursorParent = 0;
        for (int i = 0; i < gatewayParent.getRecordSetSize(); i++) {
            gatewayParent.find(i + 1);
            if (gatewayParent.getId() == parent->getId()) {
                cursorParent = gatewayParent.getCursor();
                break;
            }
        }

        cout << left << setw(11) << cursorStudent;
        cout << left << setw(10) << student->getLastname();
        cout << left << setw(10) << student->getName();
        cout << left << setw(15) << student->getSurname();
        cout << left << setw(20) << student->getAddress();
        cout << left << setw(12) << student->getBirthDate();
        cout << left << setw(7) << student->getClass();
        cout << left << setw(12) << student->getEntryDate();
        cout << left << setw(11) << cursorParent;
        cout << left << setw(10) << parent->getLastname();
        cout << left << setw(10) << parent->getName();
        cout << left << setw(15) << parent->getSurname();
        cout << left << setw(40) << parent->getAddress();
        cout << left << setw(12) << parent->getRelationDegree() << endl;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::viewStudent(TableGatewayStudent& gatewayStudent)
{
    cout << left << setw(7) << "ID";
    cout << left << setw(20) << "Lastname";
    cout << left << setw(20) << "Name";
    cout << left << setw(20) << "Surname";
    cout << left << setw(20) << "Address";
    cout << left << setw(20) << "Birth Date";
    cout << left << setw(20) << "Class";
    cout << left << setw(20) << "Entry Date" << endl;

    for (int i = 0; i < gatewayStudent.getRecordSetSize(); i++) {
        printStudent(gatewayStudent, i + 1);

        if (i != 0 && (i % 10) == 0) {
            string decision; 
            cout << "Enter 0 to stop printing or enter anything else to continue:";
            getline(cin, decision);
            if (decision == "0") {
                break;
            }
        }
    }
}

void UserAction::insertStudent(TableGatewayStudent& gatewayStudent)
{
    try {
        string lastname, name, surname, address, birth_date, entry_year, classInput;

        cout << "Enter student information:" << endl;
        cout << "Lastname: ";
        getline(cin, lastname);
        cout << "Name: ";
        getline(cin, name);
        cout << "Surname: ";
        getline(cin, surname);
        cout << "Address: ";
        getline(cin, address);
        cout << "Birth date (YYYY-MM-DD): ";
        getline(cin, birth_date);
        cout << "Class: ";
        getline(cin, classInput);
        cout << "Entry year: ";
        getline(cin, entry_year);

        gatewayStudent.insert(lastname, name, surname, address, birth_date, stoi(classInput), entry_year);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::updateStudent(TableGatewayStudent& gatewayStudent)
{
    try {
        string id;
        std::cout << "Enter student ID to update: ";
        getline(std::cin, id);
        gatewayStudent.find(stoi(id));

        std::string lastname, name, surname, address, birth_date, entry_year, classInput;
        int _class;

        cout << "Last Name (Enter to keep the existing value): ";
        getline(std::cin, lastname);
        if (lastname.empty()) {
            lastname = gatewayStudent.getLastname();
        }

        cout << "Name (Enter to keep the existing value): ";
        getline(std::cin, name);
        if (name.empty()) {
            name = gatewayStudent.getName(); 
        }

        cout << "Surname (Enter to keep the existing value): ";
        getline(std::cin, surname);
        if (surname.empty()) {
            surname = gatewayStudent.getSurname();
        }

        cout << "Address (Enter to keep the existing value): ";
        getline(std::cin, address);
        if (address.empty()) {
            address = gatewayStudent.getAddress();
        }

        cout << "Birth Date (Enter to keep the existing value): ";
        getline(std::cin, birth_date);
        if (birth_date.empty()) {
            birth_date = gatewayStudent.getBirthDate();
        }

        cout << "Class (Enter to keep the existing value): ";
        getline(std::cin, classInput);
        if (classInput.empty()) {
            _class = gatewayStudent.getClass();
        }
        else {
            _class = stoi(classInput);
        }

        cout << "Entry Year (Enter to keep the existing value): ";
        getline(std::cin, entry_year);
        if (entry_year.empty()) {
            entry_year = gatewayStudent.getEntryDate();
        }

        gatewayStudent.update(stoi(id), lastname, name, surname, address, birth_date, _class, entry_year);
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::deleteStudent(TableGatewayStudent& gatewayStudent)
{
    try {
        int id;
        std::cout << "Enter student ID to delete: ";
        std::cin >> id;

        gatewayStudent.deleteById(id);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::viewParent(TableGatewayParent& gatewayParent)
{
    cout << left << setw(7) << "ID";
    cout << left << setw(20) << "Lastname";
    cout << left << setw(20) << "Name";
    cout << left << setw(20) << "Surname";
    cout << left << setw(40) << "Address";
    cout << left << setw(20) << "Relation Degree" << endl;

    for (int i = 0; i < gatewayParent.getRecordSetSize(); i++) {
        printParent(gatewayParent, i + 1);

        if (i != 0 && (i % 10) == 0) {
            string decision;
            cout << "Enter 0 to stop printing or enter anything else to continue:";
            getline(cin, decision);
            if (decision == "0") {
                break;
            }
        }
    }
}

void UserAction::insertParent(TableGatewayParent& gatewayParent)
{
    try {
        string lastname, name, surname, address, relation_degree;

        cout << "Enter parent information:" << endl;
        cout << "Lastname: ";
        getline(cin, lastname);
        cout << "Name: ";
        getline(cin, name);
        cout << "Surname: ";
        getline(cin, surname);
        cout << "Address: ";
        getline(cin, address);
        cout << "Relation Degree: ";
        getline(cin, relation_degree);

        gatewayParent.insert(lastname, name, surname, address, relation_degree);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::updateParent(TableGatewayParent& gatewayParent)
{
    try {
        string id;
        std::cout << "Enter parent ID to update: ";
        getline(std::cin, id);
        gatewayParent.find(stoi(id));

        std::string lastname, name, surname, address, relation_degree;

        cout << "Last Name (Enter to keep the existing value): ";
        getline(std::cin, lastname);
        if (lastname.empty()) {
            lastname = gatewayParent.getLastname();
        }

        cout << "Name (Enter to keep the existing value): ";
        getline(std::cin, name);
        if (name.empty()) {
            name = gatewayParent.getName();
        }

        cout << "Surname (Enter to keep the existing value): ";
        getline(std::cin, surname);
        if (surname.empty()) {
            surname = gatewayParent.getSurname();
        }

        cout << "Address (Enter to keep the existing value): ";
        getline(std::cin, address);
        if (address.empty()) {
            address = gatewayParent.getAddress();
        }

        cout << "Relation Degree (Enter to keep the existing value): ";
        getline(std::cin, relation_degree);
        if (relation_degree.empty()) {
            relation_degree = gatewayParent.getRelationDegree();
        }

        gatewayParent.update(stoi(id), lastname, name, surname, address, relation_degree);
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::deleteParent(TableGatewayParent& gatewayParent)
{
    try {
        int id;
        std::cout << "Enter parent ID to delete: ";
        std::cin >> id;

        gatewayParent.deleteById(id);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::viewPerformance(TableGatewayPerformance& gatewayPerformance, TableGatewayStudent& gatewayStudent)
{
    cout << left << setw(7) << "ID";
    cout << left << setw(11) << "Student ID";
    cout << left << setw(10) << "Lastname";
    cout << left << setw(10) << "Name";
    cout << left << setw(10) << "Surname";
    cout << left << setw(20) << "Address";
    cout << left << setw(12) << "Birth Date";
    cout << left << setw(7) << "Class";
    cout << left << setw(12) << "Entry Date";
    cout << left << setw(10) << "Year";
    cout << left << setw(7) << "Class";
    cout << left << setw(10) << "Subject";
    cout << left << setw(18) << "Quarterly Grade";
    cout << left << setw(18) << "Semester Grade";
    cout << left << setw(18) << "Annual Grade";
    cout << left << setw(18) << "Examination Grade";
    cout << left << setw(18) << "Final Grade" << endl;

    for (int i = 0; i < gatewayPerformance.getRecordSetSize(); i++) {
        printPerformance(gatewayPerformance, gatewayStudent, i + 1);

        if (i != 0 && (i % 10) == 0) {
            string decision;
            cout << "Enter 0 to stop printing or enter anything else to continue:";
            getline(cin, decision);
            if (decision == "0") {
                break;
            }
        }
    }
}

void UserAction::insertPerformance(TableGatewayPerformance& gatewayPerformance)
{
    try {
        string studentId, year, classInput, subject, quarterlyGrade, semesterGrade, annualGrade, examinationGrade, finalGrade;

        cout << "Enter performance information:" << endl;
        cout << "Student ID: ";
        getline(cin, studentId);
        cout << "Year: ";
        getline(cin, year);
        cout << "Class: ";
        getline(cin, classInput);
        cout << "Subject: ";
        getline(cin, subject);
        cout << "Quarterly Grade: ";
        getline(cin, quarterlyGrade);
        cout << "Semester Grade: ";
        getline(cin, semesterGrade);
        cout << "Annual Grade: ";
        getline(cin, annualGrade);
        cout << "Examination Grade: ";
        getline(cin, examinationGrade);
        cout << "Final Grade: ";
        getline(cin, finalGrade);

        gatewayPerformance.insert(stoi(studentId), year, stoi(classInput), subject, stoi(quarterlyGrade), stoi(semesterGrade), stoi(annualGrade), stoi(examinationGrade), stoi(finalGrade));
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::updatePerformance(TableGatewayPerformance& gatewayPerformance)
{
    try {
        string id;
        cout << "Enter performance ID to update: ";
        getline(cin, id);
        gatewayPerformance.find(stoi(id));

        string studentId, year, classInput, subject, quarterlyGrade, semesterGrade, annualGrade, examinationGrade, finalGrade;

        cout << "Student ID (Enter to keep the existing value): ";
        getline(cin, studentId);
        if (studentId.empty()) {
            studentId = to_string(gatewayPerformance.getStudent()->getId());
        }

        cout << "Year (Enter to keep the existing value): ";
        getline(cin, year);
        if (year.empty()) {
            year = gatewayPerformance.getYear();
        }

        cout << "Class (Enter to keep the existing value): ";
        getline(cin, classInput);
        if (classInput.empty()) {
            classInput = to_string(gatewayPerformance.getClass());
        }

        cout << "Subject (Enter to keep the existing value): ";
        getline(cin, subject);
        if (subject.empty()) {
            subject = gatewayPerformance.getSubject();
        }

        cout << "Quarterly Grade (Enter to keep the existing value): ";
        getline(cin, quarterlyGrade);
        if (quarterlyGrade.empty()) {
            quarterlyGrade = to_string(gatewayPerformance.getQuarterlyGrade());
        }

        cout << "Semester Grade (Enter to keep the existing value): ";
        getline(cin, semesterGrade);
        if (semesterGrade.empty()) {
            semesterGrade = to_string(gatewayPerformance.getSemesterGrade());
        }

        cout << "Annual Grade (Enter to keep the existing value): ";
        getline(cin, annualGrade);
        if (annualGrade.empty()) {
            annualGrade = to_string(gatewayPerformance.getAnnualGrade());
        }

        cout << "Examination Grade (Enter to keep the existing value): ";
        getline(cin, examinationGrade);
        if (examinationGrade.empty()) {
            examinationGrade = to_string(gatewayPerformance.getExaminationGrade());
        }

        cout << "Final Grade (Enter to keep the existing value): ";
        getline(cin, finalGrade);
        if (finalGrade.empty()) {
            finalGrade = to_string(gatewayPerformance.getFinalGrade());
        }

        gatewayPerformance.update(stoi(id), stoi(studentId), year, stoi(classInput), subject, stoi(quarterlyGrade), stoi(semesterGrade), stoi(annualGrade), stoi(examinationGrade), stoi(finalGrade));
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::deletePerformance(TableGatewayPerformance& gatewayPerformance)
{
    try {
        int id;
        cout << "Enter performance ID to delete: ";
        cin >> id;

        gatewayPerformance.deleteById(id);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::viewFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships, TableGatewayStudent& gatewayStudent, TableGatewayParent& gatewayParent)
{
    cout << left << setw(7) << "ID";

    cout << left << setw(11) << "Student ID";
    cout << left << setw(10) << "Lastname";
    cout << left << setw(10) << "Name";
    cout << left << setw(15) << "Surname";
    cout << left << setw(20) << "Address";
    cout << left << setw(12) << "Birth Date";
    cout << left << setw(7) << "Class";
    cout << left << setw(12) << "Entry Date";

    cout << left << setw(11) << "Parent ID";
    cout << left << setw(10) << "Lastname";
    cout << left << setw(10) << "Name";
    cout << left << setw(15) << "Surname";
    cout << left << setw(40) << "Address";
    cout << left << setw(12) << "Relation Degree" << endl;

    for (int i = 0; i < gatewayFamilyRelationships.getRecordSetSize(); i++) {
        printFamilyRelationships(gatewayFamilyRelationships, gatewayStudent, gatewayParent, i + 1);

        if (i != 0 && (i % 10) == 0) {
            string decision;
            cout << "Enter 0 to stop printing or enter anything else to continue:";
            getline(cin, decision);
            if (decision == "0") {
                break;
            }
        }
    }
}

void UserAction::insertFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships)
{
    try {
        string studentId, parentId;

        cout << "Enter family relationships information:" << endl;
        cout << "Student ID: ";
        getline(cin, studentId);
        cout << "Parent ID: ";
        getline(cin, parentId);

        gatewayFamilyRelationships.insert(stoi(studentId), stoi(parentId));
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::updateFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships)
{
    try {
        string id;
        cout << "Enter family relationships ID to update: ";
        getline(cin, id);
        gatewayFamilyRelationships.find(stoi(id));

        string studentId, parentId;

        cout << "Student ID (Enter to keep the existing value): ";
        getline(cin, studentId);
        if (studentId.empty()) {
            studentId = to_string(gatewayFamilyRelationships.getStudent()->getId());
        }

        cout << "Parent ID (Enter to keep the existing value): ";
        getline(cin, parentId);
        if (parentId.empty()) {
            parentId = to_string(gatewayFamilyRelationships.getParent()->getId());
        }

        gatewayFamilyRelationships.update(stoi(id), stoi(studentId), stoi(parentId));
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void UserAction::deleteFamilyRelationships(TableGatewayFamilyRelationships& gatewayFamilyRelationships)
{
    try {
        int id;
        cout << "Enter family relationships ID to delete: ";
        cin >> id;

        gatewayFamilyRelationships.deleteById(id);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

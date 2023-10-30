#include "TableGatewayFamilyRelationships.h"

void TableGatewayFamilyRelationships::loadData()
{
    for (auto performance : recordSet) {
        delete performance->getStudent();
        delete performance;
    }
    recordSet.clear();
    try {
        int rows = getRows(L"select * from students_to_parents, student, parent where students_to_parents.student_id = student.id and students_to_parents.parent_id = parent.id;");
        int columns = 17; 
        SQLHSTMT stmt = connection.query(L"select * from students_to_parents, student, parent where students_to_parents.student_id = student.id and students_to_parents.parent_id = parent.id;");

        SQLRETURN retcode;
        SQLCHAR* ColumnData[17];

        ColumnData[0] = (SQLCHAR*)malloc(7);
        ColumnData[1] = (SQLCHAR*)malloc(7);
        ColumnData[2] = (SQLCHAR*)malloc(7);
        ColumnData[4] = (SQLCHAR*)malloc(255);
        ColumnData[5] = (SQLCHAR*)malloc(255);
        ColumnData[6] = (SQLCHAR*)malloc(255);
        ColumnData[7] = (SQLCHAR*)malloc(255);
        ColumnData[8] = (SQLCHAR*)malloc(255);
        ColumnData[9] = (SQLCHAR*)malloc(7);
        ColumnData[10] = (SQLCHAR*)malloc(255);
        ColumnData[12] = (SQLCHAR*)malloc(255);
        ColumnData[13] = (SQLCHAR*)malloc(255);
        ColumnData[14] = (SQLCHAR*)malloc(255);
        ColumnData[15] = (SQLCHAR*)malloc(255);
        ColumnData[16] = (SQLCHAR*)malloc(255);

        SQLBindCol(stmt, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
        SQLBindCol(stmt, 2, SQL_C_CHAR, ColumnData[1], 7, nullptr);
        SQLBindCol(stmt, 3, SQL_C_CHAR, ColumnData[2], 7, nullptr);
        SQLBindCol(stmt, 5, SQL_C_CHAR, ColumnData[4], 255, nullptr);
        SQLBindCol(stmt, 6, SQL_C_CHAR, ColumnData[5], 255, nullptr);
        SQLBindCol(stmt, 7, SQL_C_CHAR, ColumnData[6], 255, nullptr);
        SQLBindCol(stmt, 8, SQL_C_CHAR, ColumnData[7], 255, nullptr);
        SQLBindCol(stmt, 9, SQL_C_CHAR, ColumnData[8], 255, nullptr);
        SQLBindCol(stmt, 10, SQL_C_CHAR, ColumnData[9], 7, nullptr);
        SQLBindCol(stmt, 11, SQL_C_CHAR, ColumnData[10], 255, nullptr);
        SQLBindCol(stmt, 13, SQL_C_CHAR, ColumnData[12], 255, nullptr);
        SQLBindCol(stmt, 14, SQL_C_CHAR, ColumnData[13], 255, nullptr);
        SQLBindCol(stmt, 15, SQL_C_CHAR, ColumnData[14], 255, nullptr);
        SQLBindCol(stmt, 16, SQL_C_CHAR, ColumnData[15], 255, nullptr);
        SQLBindCol(stmt, 17, SQL_C_CHAR, ColumnData[16], 255, nullptr);

        while (1) {
            retcode = SQLFetch(stmt);

            if (retcode == SQL_NO_DATA) {
                break;
            }
            int id = stoi((const char*)ColumnData[0]);
            int student_id = stoi((const char*)ColumnData[1]);
            int parent_id = stoi((const char*)ColumnData[2]);
            string studentLastname = string((const char*)ColumnData[4]);
            string studentName = string((const char*)ColumnData[5]);
            string studentSurname = string((const char*)ColumnData[6]);
            string studentAddress = string((const char*)ColumnData[7]);
            string studentBirthDate = string((const char*)ColumnData[8]);
            int studentClass = stoi((const char*)ColumnData[9]);
            string studentEntryYear = string((const char*)ColumnData[10]);
            string parentLastname = string((const char*)ColumnData[12]);
            string parentName = string((const char*)ColumnData[13]);
            string parentSurname = string((const char*)ColumnData[14]);
            string parentAddress = string((const char*)ColumnData[15]);
            string parentRelationDegree = string((const char*)ColumnData[16]);

            FamilyRelationships* familyRelationships = new FamilyRelationships(id, new Student(student_id, studentLastname, studentName, studentSurname, studentAddress, studentBirthDate, studentClass, studentEntryYear), new Parent(parent_id, parentLastname, parentName, parentSurname, parentAddress, parentRelationDegree));
            recordSet.push_back(familyRelationships);
        }
        SQLFreeStmt(stmt, SQL_CLOSE);
    } 
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

int TableGatewayFamilyRelationships::getRows(const wchar_t* sql)
{
    int rows = 0;
    SQLHSTMT stmt = connection.query(sql);
    while (1) {
        SQLRETURN retcode = SQLFetch(stmt);

        if (retcode == SQL_NO_DATA) {
            break;
        }
        rows++;
    }
    SQLFreeStmt(stmt, SQL_CLOSE);
    return rows;
}

void TableGatewayFamilyRelationships::getNow()
{
    this->loadData();
    if (getRecordSetSize())
        this->currentIndex = 0;
    else
        this->currentIndex = -1;
}

void TableGatewayFamilyRelationships::find(int id)
{
    if (1 > id || id - 1 >= recordSet.size()) {
        throw std::out_of_range("Invalid index");
    }
    this->currentIndex = id - 1;
}

const int TableGatewayFamilyRelationships::getCursor()
{
	return this->currentIndex + 1;
}

const int TableGatewayFamilyRelationships::getId()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getId();
}

Student* TableGatewayFamilyRelationships::getStudent()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getStudent();
}

Parent* TableGatewayFamilyRelationships::getParent()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getParent();
}

void TableGatewayFamilyRelationships::setStudent(const int newStudentId)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, newStudentId, this->getParent()->getId());
}

void TableGatewayFamilyRelationships::setParent(const int newParentId)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), newParentId);
}

void TableGatewayFamilyRelationships::insert(int student_id, int parent_id)
{
    try {
        TableGatewayStudent studentGateway(connection);
        TableGatewayParent parentGateway(connection);
        studentGateway.find(student_id);
        int realStudentId = studentGateway.getId();
        parentGateway.find(parent_id);
        int realParentId = parentGateway.getId();
        const string preSql = "INSERT INTO students_to_parents (student_id, parent_id) VALUES (" + to_string(realStudentId) + ", " + to_string(realParentId) + ");";
        const wstring sql = wstring(preSql.begin(), preSql.end());
        SQLHSTMT stmt = connection.query(sql.c_str());

        this->loadData();
        SQLFreeStmt(stmt, SQL_CLOSE);
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

void TableGatewayFamilyRelationships::update(int id, int student_id, int parent_id)
{
    try {
        if ((0 > (id - 1)) || ((id - 1) >= getRecordSetSize())) {
            throw std::out_of_range("Invalid id");
        }

        int realId = recordSet[id - 1]->getId();
        int realStudentId = student_id;
        int realParentId = parent_id;
        TableGatewayStudent studentGateway(connection);
        TableGatewayParent parentGateway(connection);
        if (student_id != this->getStudent()->getId()) {
            studentGateway.find(student_id);
            realStudentId = studentGateway.getId();
        }
        if (parent_id != this->getParent()->getId()) {
            parentGateway.find(parent_id);
            realParentId = parentGateway.getId();
        }

        const string preSql = "UPDATE students_to_parents SET student_id = " + to_string(realStudentId) + ", parent_id = " + to_string(realParentId) + " where id = " + to_string(realId) + ';';
        const wstring sql = wstring(preSql.begin(), preSql.end());

        SQLHSTMT stmt = connection.query(sql.c_str());

        if (student_id != realStudentId) {
            delete recordSet[id - 1]->getStudent();
            recordSet[id - 1]->setStudent(new Student(studentGateway.getId(), studentGateway.getLastname(), studentGateway.getName(), studentGateway.getSurname(), studentGateway.getAddress(), studentGateway.getBirthDate(), studentGateway.getClass(), studentGateway.getEntryDate()));
        }
        if (parent_id != realParentId) {
            delete recordSet[id - 1]->getParent();
            recordSet[id - 1]->setParent(new Parent(parentGateway.getId(), parentGateway.getLastname(), parentGateway.getName(), parentGateway.getSurname(), parentGateway.getAddress(), parentGateway.getRelationDegree()));
        }

        SQLFreeStmt(stmt, SQL_CLOSE);
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

void TableGatewayFamilyRelationships::deleteById(int id)
{
    try {
        if (1 > id || id - 1 > recordSet.size()) {
            throw std::out_of_range("Invalid id");
        }

        if (getRecordSetSize() <= 0) {
            throw std::logic_error("Table is empty");
        }

        int realId = recordSet[id - 1]->getId();

        const string preSql = "DELETE from students_to_parents WHERE id = " + to_string(realId) + ';';
        const wstring sql = wstring(preSql.begin(), preSql.end());


        SQLHSTMT stmt = connection.query(sql.c_str());
        delete recordSet[id - 1]->getParent();
        delete recordSet[id - 1]->getStudent();
        delete recordSet[id - 1];
        recordSet.erase(recordSet.begin() + (id - 1));
        if (getRecordSetSize() <= 0) {
            currentIndex = -1;
        }

        SQLFreeStmt(stmt, SQL_CLOSE);
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const logic_error& e) {
        cerr << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

void TableGatewayFamilyRelationships::deleteCurrent()
{
    this->deleteById(this->currentIndex + 1);
}

int TableGatewayFamilyRelationships::getRecordSetSize()
{
	return recordSet.size();
}

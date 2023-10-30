#include "TableGatewayPerformance.h"

void TableGatewayPerformance::loadData()
{
    for (auto performance : recordSet) {
        delete performance->getStudent();
        delete performance;
    }
    recordSet.clear();
    try {
        int rows = getRows(L"select * from performance, student where student.id = performance.student_id;");
        int columns = 18;

        SQLHSTMT stmt = connection.query(L"select * from performance, student where student.id = performance.student_id;");
        SQLRETURN retcode;
        SQLCHAR* ColumnData[18];

        ColumnData[0] = (SQLCHAR*)malloc(7);
        ColumnData[1] = (SQLCHAR*)malloc(7);
        ColumnData[2] = (SQLCHAR*)malloc(255);
        ColumnData[3] = (SQLCHAR*)malloc(7);
        ColumnData[4] = (SQLCHAR*)malloc(255);
        ColumnData[5] = (SQLCHAR*)malloc(7);
        ColumnData[6] = (SQLCHAR*)malloc(7);
        ColumnData[7] = (SQLCHAR*)malloc(7);
        ColumnData[8] = (SQLCHAR*)malloc(7);
        ColumnData[9] = (SQLCHAR*)malloc(7);
        ColumnData[11] = (SQLCHAR*)malloc(255);
        ColumnData[12] = (SQLCHAR*)malloc(255);
        ColumnData[13] = (SQLCHAR*)malloc(255);
        ColumnData[14] = (SQLCHAR*)malloc(255);
        ColumnData[15] = (SQLCHAR*)malloc(255);
        ColumnData[16] = (SQLCHAR*)malloc(7);
        ColumnData[17] = (SQLCHAR*)malloc(255);

        SQLBindCol(stmt, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
        SQLBindCol(stmt, 2, SQL_C_CHAR, ColumnData[1], 7, nullptr);
        SQLBindCol(stmt, 3, SQL_C_CHAR, ColumnData[2], 255, nullptr);
        SQLBindCol(stmt, 4, SQL_C_CHAR, ColumnData[3], 7, nullptr);
        SQLBindCol(stmt, 5, SQL_C_CHAR, ColumnData[4], 255, nullptr);
        SQLBindCol(stmt, 6, SQL_C_CHAR, ColumnData[5], 7, nullptr);
        SQLBindCol(stmt, 7, SQL_C_CHAR, ColumnData[6], 7, nullptr);
        SQLBindCol(stmt, 8, SQL_C_CHAR, ColumnData[7], 7, nullptr);
        SQLBindCol(stmt, 9, SQL_C_CHAR, ColumnData[8], 7, nullptr);
        SQLBindCol(stmt, 10, SQL_C_CHAR, ColumnData[9], 7, nullptr);
        SQLBindCol(stmt, 12, SQL_C_CHAR, ColumnData[11], 255, nullptr);
        SQLBindCol(stmt, 13, SQL_C_CHAR, ColumnData[12], 255, nullptr);
        SQLBindCol(stmt, 14, SQL_C_CHAR, ColumnData[13], 255, nullptr);
        SQLBindCol(stmt, 15, SQL_C_CHAR, ColumnData[14], 255, nullptr);
        SQLBindCol(stmt, 16, SQL_C_CHAR, ColumnData[15], 255, nullptr);
        SQLBindCol(stmt, 17, SQL_C_CHAR, ColumnData[16], 7, nullptr);
        SQLBindCol(stmt, 18, SQL_C_CHAR, ColumnData[17], 255, nullptr);

        while (1) {
            retcode = SQLFetch(stmt);

            if (retcode == SQL_NO_DATA) {
                break;
            }
            int id = stoi((const char*)ColumnData[0]);
            int student_id = stoi((const char*)ColumnData[1]);
            string year = string((const char*)ColumnData[2]);
            int performanceClass = stoi((const char*)ColumnData[3]);
            string subject = string((const char*)ColumnData[4]);
            int quarterlyGrade = stoi((const char*)ColumnData[5]);
            int semesterGrade = stoi((const char*)ColumnData[6]);
            int annualGrade = stoi((const char*)ColumnData[7]);
            int examinationGrade = stoi((const char*)ColumnData[8]);
            int finalGrade = stoi((const char*)ColumnData[9]);
            string lastname = string((const char*)ColumnData[11]);
            string name = string((const char*)ColumnData[12]);
            string surname = string((const char*)ColumnData[13]);
            string address = string((const char*)ColumnData[14]);
            string birth_date = string((const char*)ColumnData[15]);
            int studentClass = stoi((const char*)ColumnData[16]);
            string entry_date = string((const char*)ColumnData[17]);

            Performance* performance = new Performance(id, new Student(student_id, lastname, name, surname, address, birth_date, studentClass, entry_date), year, performanceClass, subject, quarterlyGrade, semesterGrade, annualGrade, examinationGrade, finalGrade);
            recordSet.push_back(performance);
        }
        SQLFreeStmt(stmt, SQL_CLOSE);
    } 
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

int TableGatewayPerformance::getRows(const wchar_t* sql)
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

void TableGatewayPerformance::getNow()
{
    this->loadData();
    if (getRecordSetSize())
        this->currentIndex = 0;
    else
        this->currentIndex = -1;
}

void TableGatewayPerformance::find(int id)
{
    if (1 > id || id - 1 >= recordSet.size()) {
        throw std::out_of_range("Invalid index");
    }
    this->currentIndex = id - 1;
}

const int TableGatewayPerformance::getCursor()
{
    return this->currentIndex + 1;
}

const int TableGatewayPerformance::getId()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getId();
}

Student* TableGatewayPerformance::getStudent()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getStudent();
}

const string& TableGatewayPerformance::getYear()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getYear();
}

const int TableGatewayPerformance::getClass()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getClass();
}

const string& TableGatewayPerformance::getSubject()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getSubject();
}

const int TableGatewayPerformance::getQuarterlyGrade()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getQuarterlyGrade();
}

const int TableGatewayPerformance::getSemesterGrade()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getSemesterGrade();
}

const int TableGatewayPerformance::getAnnualGrade()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getAnnualGrade();
}

const int TableGatewayPerformance::getExaminationGrade()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getExaminationGrade();
}

const int TableGatewayPerformance::getFinalGrade()
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    return recordSet.at(currentIndex)->getFinalGrade();
}

void TableGatewayPerformance::setStudent(const int newStudentId)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, newStudentId, this->getYear(), this->getClass(), this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), this->getFinalGrade());
}

void TableGatewayPerformance::setYear(const string& newYear)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), newYear, this->getClass(), this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), this->getFinalGrade());
}

void TableGatewayPerformance::setClass(const int newClass)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), newClass, this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), this->getFinalGrade());

}

void TableGatewayPerformance::setSubject(const string& newSubject)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), this->getClass(), newSubject, this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), this->getFinalGrade());

}

void TableGatewayPerformance::setQuarterlyGrade(const int newQuarterlyGrade)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), this->getClass(), this->getSubject(), newQuarterlyGrade, this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), this->getFinalGrade());

}

void TableGatewayPerformance::setSemesterGrade(const int newSemesterGrade)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), this->getClass(), this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), this->getFinalGrade());

}

void TableGatewayPerformance::setAnnualGrade(const int newAnnualGrade)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), this->getClass(), this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), newAnnualGrade, this->getExaminationGrade(), this->getFinalGrade());

}

void TableGatewayPerformance::setExaminationGrade(const int newExaminationGrade)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), this->getClass(), this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), newExaminationGrade, this->getFinalGrade());

}

void TableGatewayPerformance::setFinalGrade(const int newFinalGrade)
{
    if (this->currentIndex == -1) {
        throw std::logic_error("No records");
    }
    this->update(this->currentIndex + 1, this->getStudent()->getId(), this->getYear(), this->getClass(), this->getSubject(), this->getQuarterlyGrade(), this->getSemesterGrade(), this->getAnnualGrade(), this->getExaminationGrade(), newFinalGrade);

}

void TableGatewayPerformance::insert(int student_id, string year, int _class, string subject, int quarterlyGrade, int semesterGrade, int annualGrade, int examinationGrade, int finalGrade)
{
    try { 
        TableGatewayStudent studentGateway(connection);
        studentGateway.find(student_id);
        int realId = studentGateway.getId();
        const string preSql = "INSERT INTO Performance (student_id, year, class, subject, quarterly_grade, semester_grade, annual_grade, examination_grade, final_grade) VALUES (" + to_string(realId) + ", '" + year + "', " + to_string(_class) + ", '" + subject + "', " + to_string(quarterlyGrade) + ", " + to_string(semesterGrade) + ", " + to_string(annualGrade) + ", " + to_string(examinationGrade) + ", " + to_string(finalGrade) + ");";
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

void TableGatewayPerformance::update(int id, int student_id, string year, int _class, string subject, int quarterlyGrade, int semesterGrade, int annualGrade, int examinationGrade, int finalGrade)
{
    try {
        if ((0 > (id - 1)) || ((id - 1) >= getRecordSetSize())) {
            throw std::out_of_range("Invalid id");
        }

        int realId = recordSet[id - 1]->getId();
        int realStudentId = student_id;
        TableGatewayStudent studentGateway(connection);
        if (student_id != this->getStudent()->getId()) {
            studentGateway.find(student_id);
            realStudentId = studentGateway.getId();
        }

        const string preSql = "UPDATE performance SET student_id = " + to_string(realStudentId) + ", year = '" + year + "', class = " + to_string(_class) + ", subject = '" + subject + "', quarterly_grade = " + to_string(quarterlyGrade) + ", semester_grade = " + to_string(semesterGrade) + ", annual_grade = " + to_string(annualGrade) + ", examination_grade = " + to_string(examinationGrade) + ", final_grade = " + to_string(finalGrade) + " where id = " + to_string(realId) + ';';
        const wstring sql = wstring(preSql.begin(), preSql.end());

        SQLHSTMT stmt = connection.query(sql.c_str());

        if (student_id != realStudentId) {
            delete recordSet[id - 1]->getStudent();
            recordSet[id - 1]->setStudent(new Student(studentGateway.getId(), studentGateway.getLastname(), studentGateway.getName(), studentGateway.getSurname(), studentGateway.getAddress(), studentGateway.getBirthDate(), studentGateway.getClass(), studentGateway.getEntryDate()));
        }
        recordSet[id - 1]->setYear(year);
        recordSet[id - 1]->setClass(_class);
        recordSet[id - 1]->setSubject(subject);
        recordSet[id - 1]->setQuarterlyGrade(quarterlyGrade);
        recordSet[id - 1]->setSemesterGrade(semesterGrade);
        recordSet[id - 1]->setAnnualGrade(annualGrade);
        recordSet[id - 1]->setExaminationGrade(examinationGrade);
        recordSet[id - 1]->setFinalGrade(finalGrade);

        SQLFreeStmt(stmt, SQL_CLOSE);
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

void TableGatewayPerformance::deleteById(int id)
{
    try {
        if (1 > id || id - 1 > recordSet.size()) {
            throw std::out_of_range("Wrong id");
        }

        if (getRecordSetSize() <= 0) {
            throw std::logic_error("Table is empty");
        }

        int realId = recordSet[id - 1]->getId();

        const string preSql = "DELETE from performance WHERE id = " + to_string(realId) + ';';
        const wstring sql = wstring(preSql.begin(), preSql.end());


        SQLHSTMT stmt = connection.query(sql.c_str());
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

void TableGatewayPerformance::deleteCurrent()
{
    deleteById(currentIndex + 1);
}

int TableGatewayPerformance::getRecordSetSize()
{
    return this->recordSet.size();
}



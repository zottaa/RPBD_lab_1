#include "Menu.h"

void Menu::menu()
{
	Connection connection;
	TableGatewayStudent gatewayStudent(connection);
	TableGatewayParent gatewayParent(connection);
	TableGatewayPerformance gatewayPerformance(connection);
	TableGatewayFamilyRelationships gatewayFamilyRelationships(connection);
	UserAction userAction;

    int choice;
    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. View Students" << std::endl;
        std::cout << "2. Insert Student" << std::endl;
        std::cout << "3. Update Student" << std::endl;
        std::cout << "4. Delete Student" << std::endl;
        std::cout << "5. View Parents" << std::endl;
        std::cout << "6. Insert Parent" << std::endl;
        std::cout << "7. Update Parent" << std::endl;
        std::cout << "8. Delete Parent" << std::endl;
        std::cout << "9. View Performances" << std::endl;
        std::cout << "10. Insert Performance" << std::endl;
        std::cout << "11. Update Performance" << std::endl;
        std::cout << "12. Delete Performance" << std::endl;
        std::cout << "13. View Family Relationships" << std::endl;
        std::cout << "14. Insert Family Relationship" << std::endl;
        std::cout << "15. Update Family Relationship" << std::endl;
        std::cout << "16. Delete Family Relationship" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            gatewayStudent.getNow();
            userAction.viewStudent(gatewayStudent);
            break;
        case 2:
            gatewayStudent.getNow();
            userAction.insertStudent(gatewayStudent);
            break;
        case 3:
            gatewayStudent.getNow();
            userAction.updateStudent(gatewayStudent);
            break;
        case 4:
            gatewayStudent.getNow();
            userAction.deleteStudent(gatewayStudent);
            break;
        case 5:
            gatewayParent.getNow();
            userAction.viewParent(gatewayParent);
            break;
        case 6:
            gatewayParent.getNow();
            userAction.insertParent(gatewayParent);
            break;
        case 7:
            gatewayParent.getNow();
            userAction.updateParent(gatewayParent);
            break;
        case 8:
            gatewayParent.getNow();
            userAction.deleteParent(gatewayParent);
            break;
        case 9:
            gatewayStudent.getNow();
            gatewayPerformance.getNow();
            userAction.viewPerformance(gatewayPerformance, gatewayStudent);
            break;
        case 10:
            gatewayStudent.getNow();
            gatewayPerformance.getNow();
            userAction.insertPerformance(gatewayPerformance);
            break;
        case 11:
            gatewayStudent.getNow();
            gatewayPerformance.getNow();
            userAction.updatePerformance(gatewayPerformance);
            break;
        case 12:
            gatewayStudent.getNow();
            gatewayPerformance.getNow();
            userAction.deletePerformance(gatewayPerformance);
            break;
        case 13:
            gatewayFamilyRelationships.getNow();
            gatewayStudent.getNow();
            gatewayParent.getNow();
            userAction.viewFamilyRelationships(gatewayFamilyRelationships, gatewayStudent, gatewayParent);
            break;
        case 14:
            gatewayFamilyRelationships.getNow();
            gatewayStudent.getNow();
            gatewayParent.getNow();
            userAction.insertFamilyRelationships(gatewayFamilyRelationships);
            break;
        case 15:
            gatewayFamilyRelationships.getNow();
            gatewayStudent.getNow();
            gatewayParent.getNow();
            userAction.updateFamilyRelationships(gatewayFamilyRelationships);
            break;
        case 16:
            gatewayFamilyRelationships.getNow();
            gatewayStudent.getNow();
            gatewayParent.getNow();
            userAction.deleteFamilyRelationships(gatewayFamilyRelationships);
            break;
        case 0:
            std::cout << "Exiting the program." << std::endl;
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
    return;
}

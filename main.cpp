#include "main.h"
#include "restaurant.cpp"

// void printCustomer(restaurant* r) {
//     restaurant* ptr = r;
//     cout << "Restaurant Tables: \n";
//     int flag = 1;
//     while (1) {
//         if (flag == MAXSIZE + 1) {
//             break;
//         }
//         cout << ptr->recentTable->next->ID << " " << ptr->recentTable->next->name << " " << ptr->recentTable->next->age << endl;;
//         flag++;
//         ptr->recentTable = ptr->recentTable->next;
//     }
// }

int main(int argc, char* argv[]) {

    restaurant* r = new restaurant();
    string fileName = "D:\\HK2 - 222\\Data Structures and Algorithms\\Assignment\\Assignment 1\\result source code\\test.txt";

    //initialize table with ID, name and age
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //1
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //2
    //r->recentTable = r->insert(r->recentTable, 1, "", 1); //3
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //4
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //5
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //6
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //7
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //8
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //9
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //10
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //11
    //r->recentTable = r->insert(r->recentTable, 1, "", 1); //12
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //13
    //r->recentTable = r->insert(r->recentTable, 1, "", 0); //14
    //r->recentTable = r->insert(r->recentTable, 1, "", 1); //15
    simulate(fileName,r);
    //printCustomer(r);
    delete r;

    return 0;
}

#include "main.h"

class Node {
public:
	int customerID;
	string customerName;
	int customerAge;
	int ageIDX;
	Node* next;
public:
	Node() {
		customerID = 0;
		customerName = "";
		customerAge = 0;
		ageIDX = 1;
		next = NULL;
	}
	Node(int ID, string name, int age, Node* next = 0) {
		customerID = ID;
		customerName = name;
		customerAge = age;
		ageIDX = 1;
		this->next = next;
	}
	~Node() {
		customerID = 0;
		customerName = "";
		customerAge = 0;
		ageIDX = 0;
		next = NULL;
	}
};
// Class Queue
class queue {
public:
	int size = 0;
	Node* head = NULL;
	Node* tail = NULL;

	queue() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	~queue() {
		this->clear();
		size = 0;
		head = NULL;
		tail = NULL;
	}

	void clear() {
		if (!head) return;
		Node* delPtr = this->head;
		while (head) {
			head = head->next;
			delete delPtr;
			delPtr = head;
		}
		delete delPtr;
	}

	void add(int ID, string name, int age) {
		Node* newNode = new Node(ID, name, age, NULL);
		if (size >= MAXSIZE * 2) return;
		if (!head) {
			head = tail = newNode;
			size++;
		}
		else {
			Node* ptr = head;
			while (ptr) {
				if (ptr->customerAge == age) {
					newNode->ageIDX = ptr->ageIDX + 1;
				}
				ptr = ptr->next;
			}
			tail->next = newNode;
			tail = newNode;
			size++;
		}
	}

	void addPS(int ID, string name, int age) {
		Node* newNode = new Node(ID, name, age, NULL);
		if (size >= MAXSIZE * 2) return;
		if (!head) {
			head = tail = newNode;
			size++;
		}
		else {
			newNode->next = head;
			head = newNode;
			size++;
		}
	}

	Node* pop() {
		if (size == 0) return NULL;
		Node* firstNode = head;
		head = head->next;
		size--;
		return firstNode;
	}

	bool isEmpty() {
		return size == 0;
	}

	void remove(string name, int age) {
		Node* ptr = head;
		Node* delPtr = NULL;
		// if Head is the node to be removed
		if (head->customerName == name && head->customerAge == age) {
			delPtr = head;
			head = head->next;
			delete delPtr;
			size--;
			return;
		}
		// if Tail is the node to be removed
		if (tail->customerName == name && tail->customerAge == age) {
			while (ptr->next != tail) {
				ptr = ptr->next;
			}
			delPtr = tail;
			ptr->next = NULL;
			tail = ptr;
			delete delPtr;
			size--;
			return;
		}
		// Truong hop con lai
		while (1) {
			if (ptr->next->customerName == name && ptr->next->customerAge == age) break;
			ptr = ptr->next;
		}
		delPtr = ptr->next;
		ptr->next = ptr->next->next;
		delete delPtr;
		size--;
	}

	void swapData(Node* a, Node* b) {
		Node* temp = new Node();
		temp->customerID = b->customerID;
		temp->customerName = b->customerName;
		temp->customerAge = b->customerAge;
		temp->ageIDX = b->ageIDX;
		b->customerID = a->customerID;
		b->customerName = a->customerName;
		b->customerAge = a->customerAge;
		if (b->customerAge == a->customerAge) {
			b->ageIDX = a->ageIDX;
		}
		a->customerID = temp->customerID;
		a->customerName = temp->customerName;
		a->customerAge = temp->customerAge;
		if (a->customerAge == temp->customerAge) {
			a->ageIDX = temp->ageIDX;
		}
		delete temp;
	}

	void selectionSort(int NUM) {
		if (!head) return;
		int  count = 0;
		Node* ptr = head;
		Node* max = ptr;
		for (int i = 0; i < size - 1; i++) {
			max = ptr;
			Node* tmp = ptr->next;
			for (int j = i + 1; j < size; j++) {
				if (tmp->customerAge > max->customerAge) {
					max = tmp;
				}
				tmp = tmp->next;
			}
			if (count == NUM) break;
			if (max != ptr) {
				swapData(ptr, max);
				Node* ptr2 = ptr->next;
				while (ptr2) {
					if (ptr2->customerAge == ptr->customerAge && ptr2->ageIDX < ptr->ageIDX) {
						swapData(ptr2, ptr);
					}
					ptr2 = ptr2->next;
				}
			}
			else {
				Node* ptr2 = ptr->next;
				while (ptr2) {
					if (ptr2->customerAge == ptr->customerAge && ptr2->ageIDX < ptr->ageIDX) {
						swapData(ptr2, ptr);
					}
					ptr2 = ptr2->next;
				}
			}
			count++;
			ptr = ptr->next;
		}
	}

	void print(int NUM) {
		Node* ptr = head;
		int count = 0;
		if (head == NULL) cout << "Empty\n";
		while (ptr) {
			if (count == NUM) break;
			cout << ptr->customerName << "\n";
			ptr = ptr->next;
			count++;
		}
	}
};

// COMMANDS
bool checkREG(string s1, int* customerID, string* customerName, int* customerAge);
bool checkREGM(string s1, restaurant* r, string* customerName, int* customerAge, int* NUM, bool* flag);
bool checkCLE(string s1, int* customerID);
bool checkPS(string s1, int* customerNUM);
bool checkPQ(string s1, int* customerNUM);
bool checkSQ(string s1, int* customerNUM);
bool checkPT(string s1);
// OTHER FUNCTIONS
bool checkFullTable(table* t);
void setTableForCustomer(table* recent, table* VIP, int* customerID, string customerName, int customerAge, bool flag);
int maxEmptyTable(restaurant* r);
table* mergeTable(restaurant* r, int NUM);
void clearTable(restaurant* r, int ID, bool* flag, bool* flagCLE);
void printCustomer(table* t);
// Create queue
queue* restaurantQueue = new queue();
queue* PSQueue = new queue();
queue* PQ_Queue = new queue();
queue* onlyInRestaurant = new queue();
// Base Information
string getCommand = "";
int customerID = 0;
string customerName = "";
int customerAge = 0;
int customerNUM = 0;
// REGM variables
bool flagREGM = 0;
table* afterMerge = NULL;
table* storingVIP = NULL;
table* afterVIP = NULL;
// CLE variables
bool flagCLE = 0;
// PT variables
Node* pointerPT = NULL;

void simulate(string filename, restaurant* r)
{
	// Read file
	ifstream myFile;
	myFile.open(filename);
	while (getline(myFile, getCommand)) {
		customerID = 0;
		customerName = "";
		customerAge = 0;
		customerNUM = 0;
		// REG COMMAND
		if (checkREG(getCommand, &customerID, &customerName, &customerAge)) {
			if (checkFullTable(r->recentTable)) {
				// Transfer the customer to a queue
				if (restaurantQueue->size < MAXSIZE) {
					restaurantQueue->add(customerID, customerName, customerAge);
					PQ_Queue->add(customerID, customerName, customerAge);
					PSQueue->addPS(customerID, customerName, customerAge); // Add to PS queue
				}
			}
			else {
				setTableForCustomer(r->recentTable, storingVIP, &customerID, customerName, customerAge, flagREGM);
				PSQueue->addPS(customerID, customerName, customerAge); // Add to PS queue
				onlyInRestaurant->addPS(customerID, customerName, customerAge); // Add customer to the onlyInRestaurant queue
			}
		}
		// REGM COMMAND
		else if (checkREGM(getCommand, r, &customerName, &customerAge, &customerNUM, &flagREGM)) {
			afterMerge = mergeTable(r, customerNUM);
			table* ptr = afterMerge;
			table* ptr2 = afterMerge;
			if (customerNUM == 1) {
				ptr = afterMerge->next;
				storingVIP = NULL;
			}
			else {
				for (int i = 0; i < customerNUM; i++)
				{
					if (i == customerNUM - 1) {
						ptr = ptr2->next; // Find the last + 1 VIP table
						ptr2->next = afterMerge;
					}
					ptr2 = ptr2->next;
				}
				storingVIP = afterMerge->next;
			}
			afterVIP = ptr;
			// Get the last->next VIP table
			afterMerge->next = afterVIP;
			// Setting customer information
			afterMerge->name = customerName;
			afterMerge->age = customerAge;
			// Add to PS queue
			PSQueue->addPS(afterMerge->ID, customerName, customerAge);
			onlyInRestaurant->addPS(afterMerge->ID, customerName, customerAge);
			// Checking recent table of restaurant
			table* checkRecentTable = storingVIP;
			while (1) {
				if (r->recentTable == afterMerge) break;
				if (checkRecentTable == r->recentTable) {
					r->recentTable = afterMerge;
					break;
				}
				if (checkRecentTable == afterMerge) {
					break;
				}
				checkRecentTable = checkRecentTable->next;
			}
		}
		// CLE COMMAND
		else if (checkCLE(getCommand, &customerID)) {
			clearTable(r, customerID, &flagREGM, &flagCLE);
			// After CLE, if there're customers in restaurantQueue, add them in.
			if (flagCLE) {
				while (!checkFullTable(r->recentTable)) {
					if (restaurantQueue->isEmpty()) break;
					Node* getFirstInQueue = restaurantQueue->pop();
					PQ_Queue->remove(getFirstInQueue->customerName, getFirstInQueue->customerAge); // remove from PQ_Queue
					customerName = getFirstInQueue->customerName;
					customerAge = getFirstInQueue->customerAge;
					setTableForCustomer(r->recentTable, storingVIP, &(getFirstInQueue->customerID), customerName, customerAge, flagREGM);
					onlyInRestaurant->addPS(customerID, customerName, customerAge);
					delete getFirstInQueue;
				}
				flagCLE = 0;
			}
		}
		// PS COMMAND
		else if (checkPS(getCommand, &customerNUM)) {
			PSQueue->print(customerNUM);
		}
		// PQ COMMAND
		else if (checkPQ(getCommand, &customerNUM)) {
			PQ_Queue->print(customerNUM);
		}
		// SQ COMMAND
		else if (checkSQ(getCommand, &customerNUM)) {
			restaurantQueue->selectionSort(customerNUM);
			restaurantQueue->print(MAXSIZE);
		}
		// PT COMMAND
		else if (checkPT(getCommand)) {
			pointerPT = onlyInRestaurant->head;
			table* ptr1 = r->recentTable;
			while (ptr1) {
				if (!onlyInRestaurant->head) break;
				if (ptr1->next->name == pointerPT->customerName && ptr1->next->age == pointerPT->customerAge) {
					break;
				}
				ptr1 = ptr1->next;
			}
			printCustomer(ptr1);
		}
	}
	myFile.close();
	// Free memory
	delete restaurantQueue;
	delete PSQueue;
	delete PQ_Queue;
	delete onlyInRestaurant;
	table* ptr = r->recentTable->next;
	while (ptr != r->recentTable) {
		table* delPtr = ptr;
		ptr = ptr->next;
		delete delPtr;
	}
}

/*
 *****************************
 * FUNCTIONS FOR REG COMMAND *
 *****************************
 */
bool checkREG(string s1, int* customerID, string* customerName, int* customerAge) {
	// Find command
	string checkStr = "REG ";
	if (s1.find(checkStr) == 0) {
		int space1 = s1.find(" ");
		int space2 = s1.find(" ", space1 + 1);
		int space3 = s1.find(" ", space2 + 1);
		// Case have ID
		if (space3 != -1) {
			*customerID = stoi(s1.substr(space1 + 1, space2 - space1 - 1));
			*customerName = s1.substr(space2 + 1, space3 - space2 - 1);
			*customerAge = stoi(s1.substr(space3 + 1, s1.length() - space3 - 1));
		}
		// Case no ID
		else {
			*customerName = s1.substr(space1 + 1, space2 - space1 - 1);
			*customerAge = stoi(s1.substr(space2 + 1, s1.length() - space2 - 1));
			*customerID = 0;
		}
		if (*customerAge < 16) return 0;
		return 1;
	}
	return 0;
}
bool checkFullTable(table* t) {
	int flag = 1; // Counting variable
	table* ptr = t;
	while (1) {
		// full table
		if (flag == MAXSIZE + 1) {
			flag = 1;
			break;
		}
		// table is null
		if (ptr->age == 0) {
			flag = 0;
			break;
		}
		ptr = ptr->next;
		flag++;
	}
	if (flag == 1) return 1;
	return 0;
}
void setTableForCustomer(table* recent, table* VIP, int* customerID, string customerName, int customerAge, bool flag) {
	table* ptr = recent;
	// Case if has VIP customer
	if (flag) {
		table* ptr1 = VIP;
		while (VIP) {
			if (ptr1->next == afterMerge) {
				if (ptr1->ID == *customerID) {
					(*customerID) = 0;
					break;
				}
				break;
			}
			if (ptr1->ID == *customerID) {
				*customerID = 0;
				break;
			}
			ptr1 = ptr1->next;
		}
	}

	// Customers didn't choose ID
	if ((*customerID) == 0) {
		while (1) {
			ptr = ptr->next;
			if (ptr->age == 0) {
				*customerID = ptr->ID; // Assign table ID to customer
				ptr->name = customerName;
				ptr->age = customerAge;
				break;
			}
		}
	}
	// Customers chose ID (WORST CASE : 2*N - 1)
	else {
		while (1) {
			ptr = ptr->next;
			// Find table
			if (ptr->ID == *customerID) {
				// Table is NULL
				if (ptr->age == 0) {
					ptr->name = customerName;
					ptr->age = customerAge;
					break;
				}
				// Table is already occupied
				else {
					//Find another table
					while (1) {
						ptr = ptr->next;
						if (ptr->age == 0) {
							*customerID = ptr->ID; // Assign table ID to customer
							ptr->name = customerName;
							ptr->age = customerAge;
							break;
						}
					}
					break;
				}
			}
		}
	}
}
/*
 ******************************
 * FUNCTIONS FOR REGM COMMAND *
 ******************************
 */
bool checkREGM(string s1, restaurant* r, string* customerName, int* customerAge, int* NUM, bool* flag) {
	if (*flag) {
		return 0;
	}
	string checkStr = "REGM ";
	int maxTable = maxEmptyTable(r);
	if (s1.find(checkStr) == 0) {
		int space1 = s1.find(" ");
		int space2 = s1.find(" ", space1 + 1);
		int space3 = s1.find(" ", space2 + 1);
		*customerName = s1.substr(space1 + 1, space2 - space1 - 1);
		*customerAge = stoi(s1.substr(space2 + 1, space3 - space2 - 1));
		*NUM = stoi(s1.substr(space3 + 1, s1.length() - space3 - 1));
		// Error conditions
		if (*customerAge < 16 || *NUM > maxTable) return 0;
		*flag = 1;
		return 1;
	}
	return 0;
}
int maxEmptyTable(restaurant* r) {
	int countTable = 0;
	int result = 0;
	table* ptr = r->recentTable;
	table* flag = NULL;
	// Find an occupied table for flag
	for (int i = 0; i < MAXSIZE + 1; i++)
	{
		if (countTable >= MAXSIZE) {
			return MAXSIZE;
		}
		if (ptr->age == 0) {
			countTable++;
		}
		else {
			flag = ptr;
			ptr = r->recentTable;
			countTable = 0;
			break;
		}
		ptr = ptr->next;
	}
	// Find max
	// Duyet 2 lan phong truong hop xau nhat
	for (int i = 1; i < MAXSIZE * 2; i++)
	{
		if (ptr->age == 0) {
			countTable++;
			ptr = ptr->next;
		}
		else {
			if (i >= MAXSIZE) {
				// Break if meet flag
				if (ptr == flag) {
					if (result < countTable) {
						result = countTable;
						return result;
					}
					else {
						return result;
					}
				}
			}
			// Continue the ptr
			if (result < countTable) {
				result = countTable;
			}
			countTable = 0;
			ptr = ptr->next;
		}
	}
	return 0;
}
table* mergeTable(restaurant* r, int NUM) {
	table* flagPtr = r->recentTable->next; // It will be the first table which has no customer
	table* resultTable = r->recentTable->next;
	table* headPtr = r->recentTable; // Pointer to recent table of restaurant
	int count = 0;
	while (1) {
		// If the table is free
		if (headPtr->age == 0) {
			if (count == 0) {
				flagPtr = headPtr; // Set the flag
			}
			count++;
			if (count == NUM) {
				// check if it meet the result table, which means that the loop travel 2 times
				if (resultTable->ID >= flagPtr->ID) {
					return resultTable;
				}
				// if meet the NUM, set count back to 0 and assign result
				resultTable = flagPtr;
				headPtr = flagPtr;
				count = 0;
			}
		}
		else {
			flagPtr = r->recentTable->next;
			count = 0;
		}
		headPtr = headPtr->next;
	}
}
/*
 *****************************
 * FUNCTIONS FOR CLE COMMAND *
 *****************************
 */
bool checkCLE(string s1, int* customerID) {
	string checkStr = "CLE ";
	if (s1.find(checkStr) == 0) {
		int space1 = s1.find(" ");
		*customerID = stoi(s1.substr(space1 + 1, s1.length() - space1 - 1));
		if (*customerID > MAXSIZE) return 0;
		return 1;
	}
	return 0;
}
void clearTable(restaurant* r, int ID, bool* flag, bool* flagCLE) {
	table* ptr = r->recentTable;
	if (ptr->ID != ID) {
		while (1) {
			ptr = ptr->next;
			if (ptr == r->recentTable) return;
			if (ptr->ID == ID) break;
		}
	}
	if (*flag) {
		if (ptr->ID == afterMerge->ID) {
			// Delete in PSQueue
			PSQueue->remove(afterMerge->name, afterMerge->age);
			onlyInRestaurant->remove(afterMerge->name, afterMerge->age);
			// Setting variables
			if (!storingVIP) {
				afterMerge->name = "";
				afterMerge->age = 0;
			}
			else {
				afterMerge->next = storingVIP;
				while (storingVIP->next != afterMerge) {
					storingVIP = storingVIP->next;
				}
				storingVIP->next = afterVIP;
				afterMerge->name = "";
				afterMerge->age = 0;
			}
			*flag = 0;
			// Return recent table
			if (r->recentTable == afterMerge) {
				while (1) {
					if (r->recentTable->ID == MAXSIZE) break;
					r->recentTable = r->recentTable->next;
				}
			}
			*flagCLE = 1;
		}
		else {
			if (ptr->age == 0) return;
			else {
				PSQueue->remove(ptr->name, ptr->age);
				onlyInRestaurant->remove(ptr->name, ptr->age);
				ptr->age = 0;
				ptr->name = "";
				*flagCLE = 1;
			}
		}
	}
	else {
		if (ptr->age == 0) return;
		else {
			PSQueue->remove(ptr->name, ptr->age);
			onlyInRestaurant->remove(ptr->name, ptr->age);
			ptr->age = 0;
			ptr->name = "";
			*flagCLE = 1;
		}
	}
}
/*
 ****************************
 * FUNCTIONS FOR PS COMMAND *
 ****************************
 */
bool checkPS(string s1, int* customerNUM) {
	string checkStr = "PS ";
	if (s1 == "PS") {
		*customerNUM = 2 * MAXSIZE;
		return 1;
	}
	if (s1.find(checkStr) == 0) {
		int space1 = s1.find(" ");
		*customerNUM = stoi(s1.substr(space1 + 1, s1.length() - space1 - 1));
		return 1;
	}
	return 0;
}
/*
 ****************************
 * FUNCTIONS FOR PQ COMMAND *
 ****************************
 */
bool checkPQ(string s1, int* customerNUM) {
	string checkStr = "PQ ";
	string strNUM = "";
	if (s1 == "PQ") {
		*customerNUM = MAXSIZE;
		return 1;
	}
	if (s1.find(checkStr) == 0) {
		int space1 = s1.find(" ");
		*customerNUM = stoi(s1.substr(space1 + 1, s1.length() - space1 - 1));
		return 1;
	}
	return 0;
}
/*
 ****************************
 * FUNCTIONS FOR SQ COMMAND *
 ****************************
 */
bool checkSQ(string s1, int* customerNUM) {
	string checkStr = "SQ ";
	if (s1.find(checkStr) == 0) {
		int space1 = s1.find(" ");
		*customerNUM = stoi(s1.substr(space1 + 1, s1.length() - space1 - 1));
		return 1;
	}
	return 0;
}
/*
 ****************************
 * FUNCTIONS FOR PT COMMAND *
 ****************************
 */
bool checkPT(string s1) {
	if (s1 == "PT") return 1;
	return 0;
}
void printCustomer(table* t) {
	table* ptr = t->next;
	while (1) {
		if (ptr == t) {
			break;
		}
		if (ptr->age != 0) cout << ptr->ID << "-" << ptr->name << "\n";
		ptr = ptr->next;
	}
	if (ptr->age != 0) cout << ptr->ID << "-" << ptr->name << "\n";
}
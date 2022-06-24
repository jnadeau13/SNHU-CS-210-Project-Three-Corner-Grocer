/*
 * Jen Nadeau
 * CS 210 
 * Project 3: Corner Grocer
 * Grocery.cpp
 */

#include <Python.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

// Declares variables and functions
int menuChoice;
void printMainMenu();
int validIntInput();
string nCharString(size_t n, char c);
void itemAndQuantityList();
void specificItemQuantity();
void histogram();
string userInput;
string contents;
string item;
int itemQuantity;
int quantity;
ifstream newFileFS;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	// Do while loop to select menu option
	do
	{
		system("cls");
		system("Color 70");
		printMainMenu();
		switch (menuChoice)
		{
			// List of items purchased in a given day and quantity purchased of each option
			case 1:
				system("cls");
				system("Color 74");

				// Calls function to obtain list of items purchased and number purchased for each
				itemAndQuantityList();

				system("PAUSE");
				break;

			// Number of times a specific item was purchased in a given day option
			case 2:
				system("cls");
				system("Color 75");

				cout << "Which item would you like to look up? ";
				
				// Calls funtion to get number of purchases for a specific item obtained from user input
				specificItemQuantity();

				system("PAUSE");
				break;

			// Histogram of all items purchased in a given day and quantity purchased of each option
			case 3:
				system("cls");
				system("Color 71");

				// Calls function to display histogram of items
				histogram();

				system("PAUSE");
				break;

			// Exit program option
			case 4:
				break;

			// Handles input of integer not 1, 2, 3, or 4
			default:
				cout << "Invalid selection." << endl;
				system("PAUSE");
				break;
		}

	} while (menuChoice != 4);

}

// Prints main menu
void printMainMenu()
{
	cout << "*************************************************************************************" << endl;
	cout << "                              Corner Grocer Tracking" << endl;
	cout << "*************************************************************************************" << endl << endl;
	cout << "Please enter your selection as a number (1, 2, 3, or 4)" << endl << endl;
	cout << "1: List of items purchased in a given day and quantity purchased of each" << endl;
	cout << "2: Number of times a specific item was purchased in a given day" << endl;
	cout << "3: Histogram of all items purchased in a given day and quantity purchased of each" << endl;
	cout << "4: Exit program" << endl << endl;
	cout << "Enter your selection: ";
	menuChoice = validIntInput();
}

// User input validation to make sure input is an integer
int validIntInput() 
{
	int x;

	while (1) 
	{
		if (cin >> x) 
		{
			// valid number
			break;
		}
		else 
		{
			// not a valid number
			cout << "Invalid Input! Please enter 1, 2, 3, or 4: ";
			cin.clear();
			while (cin.get() != '\n');
		}
	}

	return x;
}

// Returns character string as character input times a certain input number
string nCharString(size_t n, char c) 
{
	string characterString = "";
	unsigned int i;

	for (i = 0; i < n; ++i) {
		characterString = characterString + c;
	}

	return characterString;
}

// Function to obtain list of items purchased and number purchased for each
void itemAndQuantityList()
{
	cout << "*************************************************************************************" << endl;
	cout << "                        Items purchased and quantity of each" << endl;
	cout << "*************************************************************************************" << endl << endl;

	// Calls Python function to read and display list of items and quantity of each purchased
	CallProcedure("read_file");
}

// Function to get number of purchases for a specific item obtained from user input
void specificItemQuantity()
{
	cin >> userInput;
	cout << endl;

	// Calls Python function to return number of times a specific item was purchased
	quantity = callIntFunc("specific_item_quantity", userInput);

	// If function returns -1, then item was not in list
	if (quantity == -1)
	{
		cout << "Item not found in file or entered incorrectly." << endl;
	}
	else
	{
		cout << "Total of " << quantity << " " << userInput << " sold today." << endl << endl;
	}
}

// Function to display histogram of items
void histogram()
{
	// Calls Python function to read input file and create a new one 
	CallProcedure("read_and_create_file");

	// Open file to read
	newFileFS.open("frequency.dat");

	// Check to see if file opened successfully
	if (!newFileFS.is_open())
	{
		cout << "Could not open file." << endl;
	}

	newFileFS >> item;
	newFileFS >> itemQuantity;
	while (!newFileFS.fail())
	{
		cout << item << " " << nCharString(itemQuantity, '*') << endl;
		newFileFS >> item;
		newFileFS >> itemQuantity;
	}

	// Close file
	newFileFS.close();

	cout << endl;
}

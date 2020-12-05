#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class Project {
private: //Each Project has an ID, Title , Status, a "list" of "employees" working on the project
	int ID;
	string Title;
public:
	Project(int Id = 0, string title = "") {
		ID = Id;
		Title = title;
	}
	// Function returns ID of the Project 
	int getID() {
		return ID;
	}
	// Function returns title of the Project 
	string getTitle() {
		return Title;
	}
};

class ListOfProjects {
private:
	vector <Project> AllProjects;
public:
	ListOfProjects() {
		AllProjects.clear();
	}
	// Function used to add project (input) to the ListOfProjects vector
	void AddProjectToList(Project &p) {
		AllProjects.push_back(p);
	}
	// Function used to return number of all projects (size)
	long AllProjectSize() {
		return AllProjects.size();
	}
	// Function used to return the project at index (input)
	Project getProjectAt(int i) {
		return AllProjects.at(i);
	}
	// Function used to find the project from the user's input of either the title or the project ID. It returns the project ID and title of the project.
	vector <Project> FindProject(string title = "", int id = 0) {
		vector<Project> match;
		if (title == "") {
			for (int i = 0; i < AllProjects.size(); i++) {
				if (AllProjects.at(i).getID() == id) {
					match.push_back(AllProjects.at(i));
				}
			}
		}
		for (int i = 0; i < AllProjects.size(); i++) {
			if (AllProjects.at(i).getTitle() == title || AllProjects.at(i).getID() == id) {
				match.push_back(AllProjects.at(i));
			}
		}
		if (title != "") {
			for (int i = 0; i < AllProjects.size(); i++) {
				if (AllProjects.at(i).getTitle().find(title) != -1) {
					match.push_back(AllProjects.at(i));
				}
			}
		}
		return match;
	}

};

//Declaring a Class of ONE AND ONLY ONE Employee
class Employee {
private:
	int ID; //Employee ID
	string FirstName, LastName; // Each employee has a first name and a last name
	vector<Project> AssignedTo; //Vector of Projects assigned to ONE Employee
	vector<bool> Status; //Status of the Projects assigned to one employee
public:

	Employee(string a = "", string b = "", int IDx = 0) // Default constructor for Employee, setting the first and last name to " " and ID to 0.
	{
		FirstName = a;
		LastName = b;
		ID = IDx;

		AssignedTo.clear();
		Status.clear();
	}
	//Function used to return the project (output) corresponding to the index given (input).
	Project getEmployeeProjectAt(int index) {
		return AssignedTo.at(index);
	}
	//Function used to return the list of projects assigned to a given employee
	vector<Project> getAllProjects() {
		return AssignedTo;
	}
	int getID() { // returns employee ID
		return ID;
	}
	//Function used to return the status of a project (complete/incomplete) (output) at a given index (input)
	bool getStatusAt(int index) {
		return Status.at(index);
	}
	// Function returns first name of employee
	string getFirstName() {
		return FirstName;
	}
	// Function returns last name of employee
	string getLastName() {
		return LastName;
	}
	//Function used to add a project (input: project title and status) to the employees' list of projects
	bool AddProjectToEmployee(Project &proj, bool stat = 0) {
		AssignedTo.push_back(proj);
		Status.push_back(stat);
		return true;
	}
	//Function used to change the status of a project (complete/incomplete) at a given index (input: index and new status)
	void ChangeProjectStatus(int index, bool new_stat) {
		Status.at(index) = new_stat;
		string stat;
		if (new_stat == true) {
			stat = "Completed";
		}
		else {
			stat = "Incompleted";
		}
		cout << "\n >>> S U C C E S S: Project " << AssignedTo.at(index).getTitle() << " with ID (" << AssignedTo.at(index).getID() << ") was marked as " << stat << " for " << FirstName << " " << LastName << " with ID (" << ID << ")\n";
	}
};
//
class ListOfEmployees {
private:
	vector<Employee> AllEmployees;
public:
	// returns the number of employees in the list (size)
	long getEmployeeSize() {
		return AllEmployees.size();
	}
	ListOfEmployees() {
		AllEmployees.clear();
	}
	// Function used to return an employee (output: first name, last name, ID, vector of projects assigned to the employee, and their status) at a given index (input)
	Employee getEmployeeAt(int i) {
		return AllEmployees.at(i);
	}
	// Function used to add an employee (of type Employee) to the ListOfEmployees
	void addEmployeeToList(Employee &emp) {
		AllEmployees.push_back(emp);
	}
	// Function used to return an employee's first name (output) of a given index (input)
	string getEmployeeFirstNameAt(int i) {
		return AllEmployees.at(i).getFirstName();
	}
	// Function used to return an employee's last name (output) of a given index (input)
	string getEmployeeLastNameAt(int i) {
		return AllEmployees.at(i).getLastName();
	}
	// Function used to return an Employee (output) at a given first name, last name, or ID (input)
	vector <Employee> FindEmployee(string ef = "", string el = "", int id = 0) {
		vector<Employee> match;
		for (int i = 0; i < AllEmployees.size(); i++) {
			if (AllEmployees.at(i).getFirstName() == ef || AllEmployees.at(i).getLastName() == el || AllEmployees.at(i).getID() == id) {
				match.push_back(AllEmployees.at(i));
			}
		}
		return match;
	}
	// Function used to assign a Project (of type Project) to an Employee at a given index (input: Project, Employee index, status of project)
	bool AddProjectToEmp(Project &proj, int index, bool status = 0) {
		int ndx = 0; // this variable is changed depending of the for loop result and then triggers the next action accordingly
		for (int i = 0; i < getEmployeeAt(index).getAllProjects().size(); i++) {
			//Error message displayed if given Employee is already assigned to the project
			if (getEmployeeAt(index).getEmployeeProjectAt(i).getID() == proj.getID()) {
				cout << "\n !!! A T T E N T I O N !!! " << getEmployeeAt(index).getFirstName() << " " << getEmployeeAt(index).getLastName() << " is already assigned to the project !\n";
				ndx = -1;
				return false;
			}
			else {
				ndx = 0;
			}
		}
		if (ndx == 0) {
			return AllEmployees.at(index).AddProjectToEmployee(proj, status);
		}
	}
	// Function used to change the status of a Project for an employee (input: Project, Employee index, new status of project)
	void ChangeProjectStat(Project &proj, int index, bool new_stat) {
		int ndx = 0;
		for (int i = 0; i < getEmployeeAt(index).getAllProjects().size(); i++) {
			if (getEmployeeAt(index).getEmployeeProjectAt(i).getID() == proj.getID()) {
				ndx = i;
				break;
			}
		}
		AllEmployees.at(index).ChangeProjectStatus(ndx, new_stat);
	}
};
//Declaring a Class of ONE AND ONLY ONE Project

//Print menu for the user
void PrintMenu(int i = 1)
{
	if (i == 0) {
		cout << "\n\t  W E L C O M E ! \n";
	}
	cout << "\n";
	cout << "Please choose an option: " << endl;
	cout << "   1 - Add a new employee to the list of employees" << endl;
	cout << "   2 - Add a new project to the list of projects." << endl;
	cout << "   3 - List all employees and the projects they are assigned to (if any)." << endl;
	cout << "   4 - List all projects (project name & ID)." << endl;
	cout << "   5 - List all completed projects (Employees name & ID, project’s name & ID)." << endl;
	cout << "   6 - List all incomplete projects (Employees name & ID, projects name & ID)." << endl;
	cout << "   7 - Search for a given employee or project by ID or name." << endl;
	cout << "   8 - Assign an employee to a project (if not assigned already)." << endl;
	cout << "   9 - Set a project as complete or incomplete for a given employee." << endl;
	cout << "   0 - Exit" << endl;

}

void Read(ListOfEmployees &le, ListOfProjects &lp) { // Reading the Neccesary Files

	ifstream in("Employees.txt");
	if (in.fail())
	{
		cout << "Your Employees File Didn't Open Successfully" << endl;
		exit(1);
	}
	int ID;
	string FirstName;
	string LastName;
	while (in >> ID)
	{
		in >> FirstName;
		in >> LastName;
		Employee e(FirstName, LastName, ID);
		le.addEmployeeToList(e);
	}

	ifstream gin("Projects.txt");
	if (gin.fail())
	{
		cout << "Your Projects File Didn't Open Successfully" << endl;
		exit(1);
	}

	int xID;
	string Title;
	// Adds projects to ListOfProjects
	while (gin >> xID)
	{
		getline(gin, Title);
		Project a(xID, Title);
		lp.AddProjectToList(a);
	}

	ifstream hin("ProjandEmp.txt");
	if (hin.fail())
	{
		cout << "Your Employee - Project File Didn't Open Successfully" << endl;
		exit(1);
	}
	bool status;
	while (hin >> ID)
	{
		int ndx = 0;
		int ndx2 = 0;
		int num = 0;
		for (int i = 0; i < le.getEmployeeSize(); i++) {
			if (le.getEmployeeAt(i).getID() == ID) {
				ndx = i;
				break;
			}
		}
		hin >> num;

		for (int i = 0; i < lp.AllProjectSize(); i++) {
			if (lp.getProjectAt(i).getID() == num) {
				ndx2 = i;
				break;
			}
		}
		Project p(lp.getProjectAt(ndx2).getID(), lp.getProjectAt(ndx2).getTitle());
		hin >> status;
		le.AddProjectToEmp(p, ndx, status);
	}
	hin.close();
	in.close();
	gin.close();
}

//////// MAIN STARTS HERE !!!

int main() {

	ListOfEmployees AllEmployees;
	ListOfProjects AllProjects;
	//ReadProject(AllProjects)
	Read(AllEmployees, AllProjects);
	int pointer = -1;
	int iii = 0;
	while (pointer != 0) {
		PrintMenu(iii);
		iii++;
		cout << "\t\t---->  ";
		cin >> pointer;

		/*cout << "\n >>> S U C C E S S: "<< fName << " " << lName << " with ID (" << ID << ") was added to the list of employees\n";*/
		if (pointer == 1) // Add new Employee to the list of Employees
		{
			cout << "\t Please enter the Employee's firstname and lastname --> ";
			string fName, lName;
			int ID = -1;
			cin >> fName >> lName;
			cout << "\t Please enter " << fName << " " << lName << "\'s ID --> ";
			cin >> ID;
			if (ID == -1) {
				cin >> ID;
			}
			Employee e(fName, lName, ID); // creates Employee entered by user (input: first name, last name, and ID)
			vector<Employee> check = AllEmployees.FindEmployee("", "", ID); // Checking if the employee already exists, if so, user can reinput details
			while (check.size() != 0)
			{
				cout << "\n\t   !!! A T T E N T I O N  !!! An Employee with ID (" << ID << ") already exists ! \n\n";
				cout << "\t Please enter the Employee's firstname and lastname --> ";
				string fName, lName;
				int ID = -1;
				cin >> fName >> lName;
				cout << "\t Please enter " << fName << " " << lName << "\'s ID --> ";
				cin >> ID;
				if (ID == -1) { cin >> ID; }
				Employee e(fName, lName, ID);
				vector<Employee> check = AllEmployees.FindEmployee("", "", ID);
			}
			AllEmployees.addEmployeeToList(e); // Employee added if they do not already exist
			cout << "\n >>> S U C C E S S: " << fName << " " << lName << " with ID (" << ID << ") was added to the list of employees\n";
			ofstream out("Employees.txt");
			if (out.fail())
			{
				cout << "Entering Data to File has failed" << endl;
				exit(1);
			}
			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) // Outputs the list of Employees' ID's and full names at corresponding index (input) in the text file (updated list of employees)
			{
				out << AllEmployees.getEmployeeAt(i).getID() << " " << AllEmployees.getEmployeeAt(i).getFirstName() << " " << AllEmployees.getEmployeeAt(i).getLastName() << endl;
			}
			out.flush();
			out.close();
		}
		if (pointer == 2) // new Project to the list of Projects
		{
			int ID;
			char Title[1000];
			cout << "\t Please enter the Title of the Project --> ";
			cin.ignore(); // Used to Clear the Cin , function retrieved from the C++ Documentation on cplusplus.com
			cin.get(Title, 1000);
			cout << "\n";
			cout << "\t Enter the ID of the " << Title << " Project --> ";
			cin >> ID;

			Project p(ID, Title);
			vector<Project> check = AllProjects.FindProject(Title, ID);
			while (check.size() != 0) // checks to see if project already exists, it it does, user can re-enter details of different project to add
			{
				cout << "\n\t   >>> !!! A T T E N T I O N  !!! Project " << Title << " " << " with ID (" << ID << ") already exists ! \n\n";
				cout << "\t Please enter the Title of the Project --> ";
				cin.ignore(); // Used to Clear the Cin , function retrieved from the C++ Documentation on cplusplus.com
				cin.get(Title, 1000);
				cout << "\n";
				cout << "\t Enter the ID of the " << Title << " Project --> ";
				cin >> ID;
			}
			AllProjects.AddProjectToList(p); // project added to list of projects
			cout << "\n >>> S U C C E S S: The Project Titled " << Title << " with ID (" << ID << ") was added to the list of projects\n";
			//  Project p(ID,Title,Status);

			ofstream out("Projects.txt");
			if (out.fail())
			{
				cout << "Entering Data to File has failed" << endl;
				exit(1);
			}
			for (int i = 0; i < AllProjects.AllProjectSize(); i++) // prints out the project IDs and titles (output) at corresponding index (input) onto text file (updated project list)
			{
				out << AllProjects.getProjectAt(i).getID() << " " << AllProjects.getProjectAt(i).getTitle() << endl;
			}
			out.flush();
			out.close();
		}
		if (pointer == 3) // Show all Employees
		{
			cout << "\n\n";
			cout << "_______________________________________________________\n\n";
			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) { 
				// Outputs all employees' full names and IDs
				cout << "    Employee's Name:\t" << AllEmployees.getEmployeeAt(i).getFirstName() << " " << AllEmployees.getEmployeeAt(i).getLastName() << "\n";
				cout << "    Employee's ID:\t" << AllEmployees.getEmployeeAt(i).getID() << "\n";
				cout << endl;

				if (AllEmployees.getEmployeeAt(i).getAllProjects().size() != 0) { // Checks to see if employee is assigned to any projects, if so projects (ID's and title) will be outputted.
					cout << "    Employee's Projects:\n\n";
					for (int j = 0; j < AllEmployees.getEmployeeAt(i).getAllProjects().size(); j++) {
						cout << "\t" << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getID() << " " << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getTitle();
						cout << endl;
						// Outputs each projects' status
						if (AllEmployees.getEmployeeAt(i).getStatusAt(j) == 0)
						{
							cout << "\t*** Project Status:\t Incomplete" << endl;
							cout << endl;
						}
						else
						{
							cout << "\t*** Project Status:\t Complete" << endl;
							cout << endl;
						}

					}

				}
				cout << "_______________________________________________________\n\n";

			}
		}
		if (pointer == 4) // Show All Projects
		{
			for (int i = 0; i < AllProjects.AllProjectSize(); i++) {
				cout << "   Project's Name:\t" << AllProjects.getProjectAt(i).getTitle() << "\n";
				cout << "   Projects's ID:\t" << AllProjects.getProjectAt(i).getID() << "\n";
				cout << "\n\n";
			}
		}
		if (pointer == 5) // Show All Compeleted Projects
		{
			int project_index = 0;
			bool Status = true;
			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) // loops through each employee from list AllEmployees
			{
				if (AllEmployees.getEmployeeAt(i).getAllProjects().size() != 0) // checks to see if any projects are assigned to employee
				{
					project_index = 0;
					for (int j = 0; j < AllEmployees.getEmployeeAt(i).getAllProjects().size(); j++)// loops through the projects assigned to each employee
					{
						for (int k = 0; k < AllProjects.AllProjectSize(); k++) // loops through the projects in the project list AllProjects
						{
							if (AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getTitle() == AllProjects.getProjectAt(k).getTitle())
							{
								if (AllEmployees.getEmployeeAt(i).getStatusAt(j) == Status) // If the status of a project is completed, title and ID of said project will be printed (output)
								{
									cout << "\n\t\t" << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getTitle() << " " << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getID() << endl;
									project_index++;
								}
							}
						}
					}
					if (project_index != 0) // Printing the full names and ID's of employees who completed the project
					{
						cout << "\n\n\t" << ">>> Completed by " << AllEmployees.getEmployeeAt(i).getFirstName() << " " << AllEmployees.getEmployeeAt(i).getLastName() << " " << AllEmployees.getEmployeeAt(i).getID() << endl;
					}
				}
			}
		}
		if (pointer == 6) // Show All incompleted Projects
		{
			int project_index = 0;
			bool Status = false;
			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) // loop through all employees
			{
				if (AllEmployees.getEmployeeAt(i).getAllProjects().size() != 0) // checks to see if any project is assigned to employee, if no = exits, if not -->
				{
					project_index = 0;
					for (int j = 0; j < AllEmployees.getEmployeeAt(i).getAllProjects().size(); j++) // loops through projects assigned to employee
					{
						for (int k = 0; k < AllProjects.AllProjectSize(); k++) // loops through all projects listed in AllProjects
						{
							if (AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getTitle() == AllProjects.getProjectAt(k).getTitle()) // if the title of project assigned to employee matches (==) the title in AllProjects, the status will be checked
							{
								if (AllEmployees.getEmployeeAt(i).getStatusAt(j) == Status)
								{// Checks the status of projects, prints the name and ID's of incomplete projects
									cout << "\n\t\t" << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getTitle() << " " << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getID() << endl;
									project_index++;
								}
							}
						}
					}
					if (project_index != 0)
					{// Prints the employees still working on the pending projects
						cout << "\n\n\t" << ">>> Still Pending from " << AllEmployees.getEmployeeAt(i).getFirstName() << " " << AllEmployees.getEmployeeAt(i).getLastName() << " " << AllEmployees.getEmployeeAt(i).getID() << endl;
					}
				}
			}
		}
		if (pointer == 7) //Search for Employee \ ID
		{
			string fName = "";
			string lName = "";
			string Title = "";
			int id = 0;
			int choice = 0;
			while (choice < 1 || choice > 5) // Allows user to search for Employee or project by Employee ID, first name, last name, project name, or project ID (input by user)
			{
				cout << "\n\n\t\t1-Search by Employee's ID\n\t\t2-Search by Employee's First Name\n\t\t3-Search by Employee's Last Name\n\t\t4-Search by Project's ID\n\t\t5-Search by Project's Title\n\n\t\t\t---> ";
				cin >> choice;
			}
			if (choice == 1) { // Searches for employee by ID (input), outputs employee ID, first name, and last name. Otherwise, "employee not found" error is displayed.
				cout << "\t Enter ID to search for a corresponding employee ---> ";
				cin >> id;
				vector<Employee> search = AllEmployees.FindEmployee(fName, lName, id);
				if (search.size() == 0) {
					cout << "\n\t\t\t\t >>> Not Found !";
				}
				else {
					cout << "\n\n\t\t\t >>> R E S U L T\n\n";
					for (int i = 0; i < search.size(); i++) {
						cout << "\t\t\t\t" << search.at(i).getID() << "\t" << search.at(i).getFirstName() << "\t" << search.at(i).getLastName() << endl;
					}
				}
			}
			if (choice == 2) { // Searched for employee of a given first name (input). If found, employee ID, first name, and last name displayed; otherwise, error displayed (output)
				cout << "\t Enter First Name to search for corresponding employee(s) ---> ";
				cin >> fName;
				vector<Employee> search = AllEmployees.FindEmployee(fName);
				if (search.size() == 0) {
					cout << "\n\t\t\t\t >>> Not Found !";
				}
				else {
					cout << "\n\n\t\t\t >>> R E S U L T\n\n";
					for (int i = 0; i < search.size(); i++) {
						cout << "\t\t\t\t" << search.at(i).getID() << "\t" << search.at(i).getFirstName() << "\t" << search.at(i).getLastName() << endl;
					}
				}
			}
			if (choice == 3) { // Searched for employee of a given last name (input). If found, employee ID, first name, and last name displayed; otherwise, error displayed (output)
				cout << "\t Enter Last Name to search for corresponding employee(s) ---> ";
				cin >> lName;
				vector<Employee> search = AllEmployees.FindEmployee(fName, lName, id);
				if (search.size() == 0) {
					cout << "\n\t\t\t\t >>> Not Found !";
				}
				else {
					cout << "\n\n\t\t\t >>> R E S U L T\n\n";
					for (int i = 0; i < search.size(); i++) {
						cout << "\t\t\t\t" << search.at(i).getID() << "\t" << search.at(i).getFirstName() << "\t" << search.at(i).getLastName() << endl;
					}
				}
			}
			if (choice == 4) { // Searches for project corresponding to project ID (input). If found, project ID and title are printed; otherwise, an error message is printed (output).
				cout << "\t Enter ID to search for corresponding project(s) ---> ";
				cin >> id;
				vector<Project> _search = AllProjects.FindProject("", id);
				if (_search.size() == 0) {
					cout << "\n\t\t\t\t >>> Not Found !";
				}
				else {
					cout << "\n\n\t\t\t >>> R E S U L T\n\n";
					for (int i = 0; i < _search.size(); i++) {
						cout << "\t\t\t\t" << _search.at(i).getID() << "\t" << _search.at(i).getTitle() << endl;
					}
				}
			}
			if (choice == 5) {// Searches for project corresponding to project title (input). If found, project ID and title are printed; otherwise, an error message is printed (output).
				cout << "\t Enter Title to search for corresponding project(s) ---> ";
				cin >> Title;
				vector<Project> _search = AllProjects.FindProject(Title, -1);
				if (_search.size() == 0) {
					cout << "\n\t\t\t\t >>> Not Found !";
				}
				else {
					cout << "\n\n\t\t\t >>> R E S U L T\n\n";
					for (int i = 0; i < _search.size(); i++) {
						cout << "\t\t\t\t" << _search.at(i).getID() << "\t" << _search.at(i).getTitle() << endl;
					}
				}
			}
			choice == 0;
		}
		if (pointer == 8) //Assign Project to Employee
		{
			string fName = "";
			string lName = "";
			int id = 0;
			int choice = 0;

			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) { // Prints out all Employee ID's and full names
				cout << "\t\t\t\t" << AllEmployees.getEmployeeAt(i).getID() << "\t" << AllEmployees.getEmployeeAt(i).getFirstName() << "\t" << AllEmployees.getEmployeeAt(i).getLastName() << endl;
			}
			int _id = -1;
			int ndx = -1;
			cout << "\n\t\t\t <<< Enter Desired Employee's ID -->  "; // User inputs ID of employee ID they want to assign a project to
			cin >> id;
			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) { 
				if (id == AllEmployees.getEmployeeAt(i).getID()) { // If employee ID input by the user is valid, index of corresponding employee is returned
					ndx = i;
					break;
				}
				if (i == (AllEmployees.getEmployeeSize() - 1) && ndx == -1) { // else (employee ID input is invalid), error message displayed and user asked to input another employee ID
					cout << "\t\tWrong ID ! Please Enter one of the IDs listed above ---> ";
					cin >> id;
					i = 0;
				}
			}
			cout << "\n";
			for (int i = 0; i < AllProjects.AllProjectSize(); i++) { // Prints out all Project ID's and titles
				cout << "\t\t\t\t" << AllProjects.getProjectAt(i).getID() << " " << AllProjects.getProjectAt(i).getTitle();
				cout << "\n\n";
			}
			cout << "\n"; // User asked what project is to be assigned to given employee
			cout << "\n\t\t\t\tSelect which Project to be assigned to " << AllEmployees.getEmployeeAt(ndx).getFirstName() << " " << AllEmployees.getEmployeeAt(ndx).getLastName() << " ---> ";
			cin >> _id;
			int _ndx = -1;
			for (int i = 0; i < AllProjects.AllProjectSize(); i++) {
				if (_id == AllProjects.getProjectAt(i).getID()) { // If project ID input by the user is valid, index of corresponding project is returned
					_ndx = i;
					break;
				}
				if (i == AllProjects.AllProjectSize() - 1 && _ndx == -1) { // else (project ID input is invalid), error message displayed and user asked to input another project ID
					cout << "\t\tWrong ID ! Please Enter one of the IDs listed above ---> ";
					cin >> _id;
					i = 0;
				}
			}
			Project p(AllProjects.getProjectAt(_ndx).getID(), AllProjects.getProjectAt(_ndx).getTitle()); // project (index returned) is assigned to employee (index returned)
			bool result = AllEmployees.AddProjectToEmp(p, ndx); // check to see if project is assigned to employee
			if (result == true) { // Confirmation message outputs the project title and ID, and states the ID and full name of the employee it was assigned to 
				cout << "\n >>> S U C C E S S: " << p.getTitle() << " " << " with ID (" << p.getID() << ") was Assigned to " << AllEmployees.getEmployeeAt(ndx).getFirstName() << " " << AllEmployees.getEmployeeAt(ndx).getLastName() << "\n";
			}
			//Save Back to File
			ofstream out("ProjandEmp.txt");
			if (out.fail())
			{
				cout << "Error writing back to file" << endl;
				exit(1);
			}
			for (int i = 0; i<AllEmployees.getEmployeeSize(); i++)
			{
				if (AllEmployees.getEmployeeAt(i).getAllProjects().size() != 0) {
					for (int j = 0; j < AllEmployees.getEmployeeAt(i).getAllProjects().size(); j++) // Outputs employee ID, project ID, and project status at corresponding index
					{
						out << AllEmployees.getEmployeeAt(i).getID() << " " << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getID() << " " << AllEmployees.getEmployeeAt(i).getStatusAt(j) << endl;
					}
				}
			}
			out.flush();
			out.close();
		}
		if (pointer == 9) //Change Project Status for a Given Employee
		{
			string fName = "";
			string lName = "";
			int id = 0;
			int choice = 0;

			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) {
				cout << "\t\t\t\t" << AllEmployees.getEmployeeAt(i).getID() << "\t" << AllEmployees.getEmployeeAt(i).getFirstName() << "\t" << AllEmployees.getEmployeeAt(i).getLastName() << endl;
			} // Prints all the Employee IDs and Names
			int _id = -1;
			int ndx = -1;
			cout << "\n\t\t\t <<< Enter Desired Employee's ID -->  ";
			cin >> id;
			for (int i = 0; i < AllEmployees.getEmployeeSize(); i++) {
				if (id == AllEmployees.getEmployeeAt(i).getID()) { // Returns index of employee corresponding to given ID (input)
					ndx = i;
					break;
				}
				if (i == AllEmployees.getEmployeeSize() - 1 && ndx == -1) { // Checks if employee ID is valid, if not, user asked to input a valid employee ID
					cout << "\t\tWrong ID ! Please Enter one of the IDs listed above ---> ";
					cin >> id;
					i = 0;
				}
			}
			cout << "\n";
			if (AllEmployees.getEmployeeAt(ndx).getAllProjects().size() == 0) { // Message printed if employee is not assigned to any projects
				cout << " !!! A T T E N T I O N !!! " << AllEmployees.getEmployeeAt(ndx).getFirstName() << " " << AllEmployees.getEmployeeAt(ndx).getLastName() << " is not assigned to any project\n";
				//break;
			}
			else {
				string emp_proj_status;
				for (int i = 0; i < AllEmployees.getEmployeeAt(ndx).getAllProjects().size(); i++) {
					if (AllEmployees.getEmployeeAt(ndx).getStatusAt(i) == false) {
						emp_proj_status = "Incomplete";
					}
					if (AllEmployees.getEmployeeAt(ndx).getStatusAt(i) == true) {
						emp_proj_status = "Complete";
					} // Prints all project IDs, titles, and statuses assigned to the given employee
					cout << "\t\t\t\t" << AllEmployees.getEmployeeAt(ndx).getEmployeeProjectAt(i).getID() << " " << AllEmployees.getEmployeeAt(ndx).getEmployeeProjectAt(i).getTitle() << " *** " << emp_proj_status;
					cout << "\n\n";
				}
				cout << "\n"; // User asked to input the project ID they want to modify the status of for a given employee
				cout << "\n\t\t\t\tSelect the Project you want to modify its Status for " << AllEmployees.getEmployeeAt(ndx).getFirstName() << " " << AllEmployees.getEmployeeAt(ndx).getLastName() << " ---> ";
				cin >> _id;
				int _ndx = -1;
				//cout << "OKOKOKOKOKOK"<<endl;
				for (int i = 0; i < AllEmployees.getEmployeeAt(ndx).getAllProjects().size(); i++) {
					if (_id == AllEmployees.getEmployeeAt(ndx).getEmployeeProjectAt(i).getID()) { // checks to see if project ID is valid, if it is, the project index is returned
						_ndx = i;
						break;
					}
					if (i == AllEmployees.getEmployeeAt(ndx).getAllProjects().size() - 1 && _ndx == -1) {
						cout << "\t\tWrong ID ! Please Enter one of the IDs listed above ---> "; // Error message printed if project ID is invalid, user asked to input different ID
						cin >> _id;
						i = 0;
					}
				}
				Project pp(AllProjects.getProjectAt(_ndx).getID(), AllProjects.getProjectAt(_ndx).getTitle()); // Project that the status of which needs to be changed for a given employee
				bool new_stat, curr_stat;
				//cout << " Current Project Status is ---> " << AllEmployees.getEmployeeAt(ndx).getStatusAt(_ndx) << endl;
				curr_stat = AllEmployees.getEmployeeAt(ndx).getStatusAt(_ndx); // returns status of project assigned to employee
				
				if (curr_stat == true) {
					new_stat = false;
				}
				if (curr_stat == false) {
					new_stat = true;
				}
				//cout << "OKOKOKOKOKOK"<<endl;
				
				AllEmployees.ChangeProjectStat(pp, ndx, new_stat);// Changes project status
				//Save Back to File
				ofstream out("ProjandEmp.txt");
				if (out.fail())
				{
					cout << "Error writing back to file" << endl;
					exit(1);
				}
				for (int i = 0; i<AllEmployees.getEmployeeSize(); i++)
				{
					if (AllEmployees.getEmployeeAt(i).getAllProjects().size() != 0) {
						for (int j = 0; j < AllEmployees.getEmployeeAt(i).getAllProjects().size(); j++) // Prints Employee IDs, project IDs, and updated statuses.
						{
							out << AllEmployees.getEmployeeAt(i).getID() << " " << AllEmployees.getEmployeeAt(i).getEmployeeProjectAt(j).getID() << " " << AllEmployees.getEmployeeAt(i).getStatusAt(j) << endl;
						}
					}
				}
				out.flush();
				out.close();
			}
		}
		else {
			pointer == 0;
		}
		pointer == -1;
	}
	return 0;
}
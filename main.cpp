#include <iostream>
#include <limits>
#include <objects.cpp>
using namespace std;

class MainWindow {
    private:
	HospitalManager Hospital;

    public:
	MainWindow(HospitalManager &hpt) : Hospital(hpt) {}

	// Setters

	void mwPatientAdd() {
	    cout << "\nFormat: (Name, Age, Sex)\n";
	    string name;
	    int age;
	    char sex;
	    cout << "Name: ";
	    getline(cin, name);
	    cout << "Age: ";
	    while (!(cin >> age)) {
		cout << "Please enter a valid age!";
		cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    }
	    cout << "Sex: ";
	    cin >> sex;
	    Hospital.hospitalPatientAdd(name, age, sex);
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	void mwPatientsPrint(){
	    Hospital.hospitalPrintPatients();
	}


};

int main() {
    HospitalManager ADNUHospital("db/patientSave.txt", "db/doctorSave.txt");
    MainWindow Window(ADNUHospital);
    while (true) {
	int input;
	std::cout << "--------------------------------------------------\n";
	std::cout << "(1) Add Patient (2) Print Patients\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "Input: ";
	std::cin >> input;
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	switch (input) {
	    case 1:
		Window.mwPatientAdd();
		break;
	    case 2:
		Window.mwPatientsPrint();
		break;
	}
    }
}

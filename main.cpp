#include <iostream>
#include <objects.cpp>
using namespace std;

class MainWindow {
    private:
	HospitalManager Hospital;
    public:
	MainWindow(HospitalManager& hpt) : Hospital(hpt) {}
    
	// Setters
	
	void mwPatientAdd(){
	    cout << "\nFormat: (Name, Age, Sex)\n";    
	    string name; int age; char sex;
	    cout << "Name: ";
	    getline(cin, name);
	    cin.ignore();
	    cout << "Age: ";
	    while(!(cin >> age)){
		cout << "Please enter a valid age!";
		cin.clear();
	    }
	    cout << "Sex: ";
	    cin >> sex;
	    cout << "\n n: " << name << ", s: " << sex << ", a: " << age;
	}
};

int main(){
    HospitalManager ADNUHospital("db/patientSave.txt", "db/doctorSave.txt");
    MainWindow Window(ADNUHospital);
    while(true){
	int input;
	std::cout << "--------------------------------------------------\n";
	std::cout << "(1) Add Patient (2) Print Patients\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "Input: ";
	switch(input){
	    case 1:
		break;
	}
    }
}

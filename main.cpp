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
	    cout << "Sex (M/F): ";
	    cin >> sex;
	    Hospital.hospitalPatientAdd(name, age, sex);
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	void mwPatientsPrint(){
	    Hospital.hospitalPrintPatients();
	}
    
	void mwDoctorAdd(){
	    cout << "\nFormat: (Name, Age, Sex, Specialization)\n";
	    string name, specialization;
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
	    cout << "Sex (M/F): ";
	    cin >> sex;
	    cout << "Specialization: ";
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    getline(cin, specialization);
	    Hospital.hospitalDoctorAdd(name, age, sex, specialization);
	}
	
	void mwDoctorsPrint(){
	    Hospital.hospitalPrintDoctors();
	}

	void mwSetDoctorSchedule(){
	    int id;
	    cout << "Doctor ID: ";
	    cin >> id;
	    Doctor* chosenDoctor = Hospital.hospitalGetDoctor(id);
	    if(chosenDoctor == nullptr || chosenDoctor->getName() == "_null"){
		cout << "Doctor with ID: " << id << " doesn't exist!\n";
		return;
	    }

	    cout << "Doctor: " << chosenDoctor->getName();
	    return;
	}

	void mwSetAppointment(){
	    return;
	}
};

int main() {
    HospitalManager ADNUHospital("db/patientSave.txt", "db/doctorSave.txt");
    MainWindow Window(ADNUHospital);
    while (true) {
	int input;
	std::cout << "------------------------  Add  ------------------------\n";
	std::cout << "- (1) Add Patient 	      (2) Add Doctor\n";
	std::cout << "------------------------ Print ------------------------\n";
	std::cout << "- (3) Print Patients	      (4) Print Doctors\n";
	std::cout << "------------------------  Set  ------------------------\n";
	std::cout << "- (5) Set Doctor Schedule       (6) Set Appointment\n";
	std::cout << "-------------------------------------------------------\n";
	std::cout << "Input: ";
	std::cin >> input;
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	switch (input) {
	    case 1:
		Window.mwPatientAdd();
		break;
	    case 2:
		Window.mwDoctorAdd();
		break;
	    case 3:
		Window.mwPatientsPrint();
		break;
	    case 4:
		Window.mwDoctorsPrint();
		break;
	    case 5:
		Window.mwSetDoctorSchedule();
		break;
	    case 6:
		Window.mwSetAppointment();
		break;
	}
    }
}

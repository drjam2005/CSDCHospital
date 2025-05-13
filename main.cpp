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
	    int id, hs, he;
	    string dd, mm, yyyy;

	    cout << "Doctor ID: ";
	    cin >> id;
	    Doctor* chosenDoctor = Hospital.hospitalGetDoctor(id);

	    if(chosenDoctor == nullptr || chosenDoctor->getName() == "_null"){
		cout << "Doctor with ID: " << id << " doesn't exist!\n";
		return;
	    }

	    cout << "\n  Chosen Doctor: " << chosenDoctor->getName() << '\n';
	    cout << "  Schedule to add:\n\tFormat (DD MM YYYY)\n\tDate: ";
	    cin >> dd >> mm >> yyyy;
	    
	    // parsing date
	    if(stoi(dd) < 10)
		dd = "0" + dd;
	    if(stoi(mm) < 10)
		mm = "0" + mm;
	    
	    cout << "\n\tFormat (hourStart hourEnd)\n\t       (ex: 10 15 ) [10am -> 3pm]\n\tHours: ";
	    cin >> hs >> he;
	    string fulldate = yyyy + mm + dd + ':' + to_string(hs) + ',' + to_string(he);
	    Hospital.hospitalSetDoctorSchedule(id, fulldate);

	}

	void mwSetAppointment(){
	    int patID, docID;
	    cout << "Patient ID: ";
	    cin >> patID;
	    Patient* patient = Hospital.hospitalGetPatient(patID);
	    if(patient == nullptr || patient->getName() == "_null"){
		cout << "Patient with ID: " << patID << " doesn't exist!\n";
		return;
	    }
	    cout << "Doctor ID : ";
	    cin >> docID;
	    Doctor* doctor = Hospital.hospitalGetDoctor(docID);
	    if(doctor == nullptr || doctor->getName() == "_null"){
		cout << "Doctor with ID: " << docID << " doesn't exist!\n";
		return;
	    }
	    if(doctor->getSchedules().size() <= 0){
		cout << "Doctor " << doctor->getName() << " doesn't have any schedules yet!\n";
		return;
	    }

	    cout << "\nPatient: " << patient->getName();
	    cout << "\nDoctor: " << doctor->getName() << ", Specialization: " << doctor->getSpecialization();
	    cout << "\nDoctor " << doctor->getName() << "'s Schedules:\n";
	    Hospital.hospitalPrintDoctorSchedules(docID);
	    
	    int chosenSched;
	    cout << "\nChoose a schedule from the doctor: ";
	    cin >> chosenSched;
	    
	    string schedule = Hospital.hospitalGetSchedule(docID, chosenSched);
	    cout << "\nSched: " << schedule << '\n';
	    // Hospital.hospitalAddAppointment(patID, docID, chosenSched, chosenHour);
	    return;
    }

    void mwPatientAppointmentsPrint(){
	int patID;
	cout << "Patient ID: ";
	return;
    }

    void mwCheckupRecord(){
	return;
    }
};

int main() {
    HospitalManager MainHospital("db/patientSave.txt", "db/doctorSave.txt", "db/schedulesSave.txt");
    MainWindow Window(MainHospital);
    while (true) {
	int input;
	std::cout << "---------------------------   Add   ---------------------------\n";
	std::cout << "- (1) Add Patient                  (2) Add Doctor\n";
	std::cout << "---------------------------   Set   ---------------------------\n";
	std::cout << "- (3) Set Doctor Schedule          (4) Set Appointment\n";
	std::cout << "---------------------------  Print  ---------------------------\n";
	std::cout << "- (5) Print Patients               (6) Print Doctors\n";
	std::cout << "- (7) Print Patient Appointments\n";
	std::cout << "--------------------------- Records ---------------------------\n";
	std::cout << "- (8) Record Checkup\n";
	std::cout << "---------------------------------------------------------------\n";
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
		Window.mwSetDoctorSchedule();
		break;
	    case 4:
		Window.mwSetAppointment();
		break;
	    case 5:
		Window.mwPatientsPrint();
		break;
	    case 6:
		Window.mwDoctorsPrint();
		break;
	    case 7:
		Window.mwPatientAppointmentsPrint();
		break;
	    case 8:
		Window.mwCheckupRecord();
		break;
	}
    }
}

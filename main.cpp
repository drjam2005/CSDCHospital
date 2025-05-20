#include <iostream>
#include <limits>
#include <cstdlib>
#include "assets/objects.cpp"
using namespace std;
#ifdef _WIN32
    void clear() {system("cls");}
#else
    void clear() {system("clear");}
#endif

class MainWindow {
    private:
	HospitalManager Hospital;
	std::string* logOut;
    public:
	MainWindow(HospitalManager &hpt, std::string& log) : Hospital(hpt), logOut(&log){}

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
	    *logOut = "Log: Added Patient: " + name + "!\n";
	    Hospital.hospitalPatientAdd(name, age, sex);
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	void mwPatientsPrint(){
	    Hospital.hospitalPrintPatients();
	    cout << "Press any key to continue...\n";
	    cin.ignore();
	    clear();
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
	    *logOut = "Added Doctor: " + name + "!\n";
	}

	void mwDoctorsPrint(){
	    Hospital.hospitalPrintDoctors();
	    cout << "Press any key to continue...\n";
	    cin.ignore();
	    clear();
	}

	void mwSetDoctorSchedule(){
	    int id, hs, he;
	    string dd, mm, yyyy;
	    Doctor* chosenDoctor;
	    while (true){
		cout << "Doctor ID: ";
		cin >> id;
		chosenDoctor = Hospital.hospitalGetDoctor(id);

		if(chosenDoctor == nullptr || chosenDoctor->getName() == "_null"){
		    cout << "Doctor with ID: " + to_string(id) + " doesn't exist!\n";
			return;
		}else{
		    break;
		}
	    }

	    cout << "\n  Chosen Doctor: " << chosenDoctor->getName() << '\n';
	    while(true){
		cout << "  Schedule to add:\n\tFormat (DD MM YYYY)\n\tDate: ";
		cin >> dd >> mm >> yyyy;
		if(stoi(dd) < 1 || 31 < stoi(dd) || stoi(mm) < 1 || 12 < stoi(mm)){
		    cout << "Invalid date, please enter again!\n";
		}else{
		    break;
		}
	    }

	    // parsing date
	    if(stoi(dd) < 10)
		dd = "0" + std::to_string(stoi(dd));
	    if(stoi(mm) < 10)
		mm = "0" + std::to_string(stoi(mm));

	    cout << "\n\tFormat (hourStart hourEnd)\n\t       (ex: 10 15 ) [10am -> 3pm]\n\tHours: ";
	    cin >> hs >> he;
	    string fulldate = yyyy + mm + dd + ':' + to_string(hs) + ',' + to_string(he);
	    *logOut = "Added schedule to "+ chosenDoctor->getName() + "\n";
	    Hospital.hospitalSetDoctorSchedule(id, fulldate);
	}

	void mwSetAppointment(){
	    int patID, docID;
	    cout << "Patient ID: ";
	    cin >> patID;
	    Patient* patient = Hospital.hospitalGetPatient(patID);
	    if(patient == nullptr || patient->getName() == "_null"){
		*logOut = "Patient with ID: " + to_string(patID) + " doesn't exist!\n";
		return;
	    }
	    cout << "Doctor ID : ";
	    cin >> docID;
	    Doctor* doctor = Hospital.hospitalGetDoctor(docID);
	    if(doctor == nullptr || doctor->getName() == "_null"){
		*logOut = "Doctor with ID: " + to_string(docID) + " doesn't exist!\n";
		return;
	    }
	    if(doctor->getSchedules().size() <= 0){
		*logOut = "Doctor " + doctor->getName() + " doesn't have any schedules yet!\n";
		return;
	    }

	    cout << "\nPatient: " << patient->getName();
	    cout << "\nDoctor: " << doctor->getName() << ", Specialization: " << doctor->getSpecialization();
	    cout << "\nDoctor " << doctor->getName() << "'s Schedules:\n";
	    Hospital.hospitalPrintDoctorSchedules(docID);
	    int numberOfScheds = doctor->getSchedules().size();
	    int chosenSched;
	    cout << "\nChoose a schedule from the doctor: ";
	    cin >> chosenSched;
	    if(chosenSched < 1 || chosenSched > numberOfScheds){
		*logOut = "Invalid Schedule Number!\n";
		return;
	    }
	    string schedule = Hospital.hospitalGetSchedule(docID, chosenSched);
	    string rawSched = Hospital.hospitalGetRawSched(docID, chosenSched);
	    vector<int> hours = vecDate(doctor->getSchedules()[chosenSched-1]);
	    cout << "\nSched: " << schedule << '\n';
	    cout << "Choose hour (" << hours[1] << " -> " << hours[2] << "): ";
	    int chosenHour;
	    cin >> chosenHour;
	    if(chosenHour > hours[2] || chosenHour < hours[1]){
		*logOut = "Invalid hour!\n";
		return;
	    }
	    // validate

	    vector<int> occupiedHours = Hospital.hospitalGetOccupiedHours(docID, chosenSched);
	    bool isValid = Hospital.hospitalValidateAppointment(occupiedHours, chosenHour);

	    if(!isValid){
		*logOut = "This hour has been taken!\n";
		return;
	    }

	    *logOut = "Set Appointment of " + patient->getName() + " to " + doctor->getName() + "!\n";
	    Hospital.hospitalSetAppointment(patID, docID, rawSched, chosenHour);
	    return;
	}

	void mwPatientAppointmentsPrint(){
	    int patID;
	    cout << "Patient ID: ";
	    cin >> patID;

	    Patient* patient = Hospital.hospitalGetPatient(patID);
	    if(patient == nullptr){
		*logOut = "Patient with this ID doesn't exist!!\n";
		return;
	    }

	    cout << "Patient " << patient->getName() << "'s Appointments: \n";
	    patient->printAppointments();
	    cout << "Press any key to continue...";
	    cin.ignore();
	    cin.ignore();
	    clear();
	    return;
	}

	void mwRecordCheckup(){
	    int appID;
	    cout << "Appointment ID: ";
	    cin >> appID;
	    Appointment* chosenApp = Hospital.hospitalGetAppointment(appID);
	    if(chosenApp == nullptr){
		*logOut = "Appointment with this ID doesn't exist!!\n";
		return;
	    }

	    string symptoms, treatments;
	    cout << "Doctor: " << Hospital.hospitalGetDoctor(chosenApp->getDocID())->getName() << '\n';
	    cout << "Patient: " << Hospital.hospitalGetPatient(chosenApp->getPatID())->getName() << '\n';
	    cout << "-------------\n";
	    cout << "Symptoms: ";
	    cin.ignore();
	    getline(cin, symptoms);
	    cout << "Treatments: ";
	    getline(cin, treatments);

	    Hospital.hospitalRecordCheckup(appID, symptoms, treatments);
	    return;
	}

	// Removing shit
	void mwRemovePatient(){
	    int patID;
	    cout << "Patient ID: ";
	    cin >> patID;


	    Patient* chosenPatient = Hospital.hospitalGetPatient(patID);
	    cout << "Patient Name: " << chosenPatient->getName() << '\n';
	    cout << "Are you sure you want to remove " << chosenPatient->getName() << "?\n";
	    cout << "Choice (y/n): ";
	    char choice;
	    cin >> choice;
	    if(tolower(choice) == 'y'){
		Hospital.hospitalRemovePatient(patID);
	    }
	    return;
	}

	void mwRemoveDoctor(){
	    int docID;
	    cout << "Doctor ID: ";
	    cin >> docID;

	    Doctor* chosenDoctor = Hospital.hospitalGetDoctor(docID);
	    cout << "Doctor Name: " << chosenDoctor->getName() << '\n';
	    cout << "Are you sure you want to remove " << chosenDoctor->getName() << "?\n";
	    cout << "Choice (y/n): ";
	    char choice;
	    cin >> choice;
	    if(tolower(choice) == 'y'){
		Hospital.hospitalRemoveDoctor(docID);
	    }
	    return;
	}

	void mwGetDocFromSpec(){
	    std::string spec;
	    cout << "Specialization: ";
	    cin >> spec;

	    Hospital.hospitalGetDoctorsFromSpecialization(spec);
	    cout << "Press any key to continue...";
	    cin.ignore();
	    cin.ignore();
	    clear();
	    return;
	}
};

int main() {
    HospitalManager MainHospital("db/patientSave.txt", "db/doctorSave.txt", "db/schedulesSave.txt", "db/appointmentsSave.txt", "db/recordsSave.txt");
    std::string log;
    MainWindow Window(MainHospital, log);
    while (true) {
	int input;
	std::cout << "\n";
	std::cout << "--------------------\n";
	std::cout << "- HOSPITAL MANAGER -\n";
	std::cout << "-------------------------------------   Add   -------------------------------------\n";
	std::cout << "- (1) Add Patient                             (2) Add Doctor                      -\n";
	std::cout << "-------------------------------------   Set   -------------------------------------\n";
	std::cout << "- (3) Set Doctor Schedule                     (4) Set Appointment                 -\n";
	std::cout << "-------------------------------------  Print  -------------------------------------\n";
	std::cout << "- (5) Print Patients                          (6) Print Doctors                   -\n";
	std::cout << "- (7) Print Patient Appointments                                                  -\n";
	std::cout << "------------------------------------- Records -------------------------------------\n";
	std::cout << "- (8) Record Checkup                                                              -\n";
	std::cout << "------------------------------------- Removes -------------------------------------\n";
	std::cout << "- (9) Remove Patient                          (10) Remove Doctor                  -\n";
	std::cout << "------------------------------------- Special -------------------------------------\n";
	std::cout << "- (11) Get Doctor From Specializaiton                                             -\n";
	std::cout << "-----------------------------------------------------------------------------------\n";
	std::cout << "  (12) Exit  -\n";
	std::cout << "--------------\n";
	std::cout << log;
	std::cout << "Input: ";
	std::cin >> input;
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	switch (input) {
	    case 1:
		Window.mwPatientAdd();
		clear();
		break;
	    case 2:
		Window.mwDoctorAdd();
		clear();
		break;
	    case 3:
		Window.mwSetDoctorSchedule();
		clear();
		break;
	    case 4:
		Window.mwSetAppointment();
		clear();
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
		Window.mwRecordCheckup();
		clear();
		break;
	    case 9:
		Window.mwRemovePatient();
		clear();
		break;
	    case 10:
		Window.mwRemoveDoctor();
		clear();
		break;
	    case 11:
		Window.mwGetDocFromSpec();
		break;
	    case 12:
		clear();
		cout << "Exiting...\n";
		return 0;
	    default:
		clear();
		cout << "Couldn't Recognize command! Exiting...\n";
		return 0;
	}
    }
}

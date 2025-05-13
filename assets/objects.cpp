#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

const std::string months[12] = {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

std::string parseDate(int date){
    std::string fulldate = std::to_string(date);
    std::string year = fulldate.substr(0,4);
    std::string month = months[std::stoi(fulldate.substr(4,2))-1];
    int day = std::stoi(fulldate.substr(6));
    std::string full = month + " " + std::to_string(day) + ", " + year;
    return full;
}

// classes
class Person{
    private:
	int ID;
	std::string name;
	int age;
	char sex;
    public:
	Person(int givenID, std::string givenName, int givenAge, char givenSex){
	    ID = givenID;
	    name = givenName;
	    age = givenAge;
	    sex = givenSex;
	}

	int getID(){
	    return ID;
	}

	int getAge(){
	    return age;
	}

	std::string getName(){
	    return name;
	}

	char getSex(){
	    return sex;
	}
};

struct Appointment{
    private:
	int appID;
	int patID;
	int docID;
	int chosenHour;
	std::string appSched;
	bool isCancelled = false;
    public:
	Appointment(int givenAppID, int givenPatID, int givenDocID, std::string givenAppSched, int givenHour){
	    appID = givenAppID;
	    patID = givenPatID;
	    docID = givenDocID;
	    appSched = givenAppSched;
	    chosenHour = givenHour;
	}

	void appointmentCancel(){
	    isCancelled = true;
	    return;
	}

	std::string getSched(){
	    return appSched;
	}

	int getID(){
	    return appID;
	}

	int getPatID(){
	    return patID;
	}

	int getDocID(){
	    return docID;
	}

	int getHour(){
	    return chosenHour;
	}
};


class Patient : public Person {
    private:
	//// IDK
	// std::vector<std::string> symptoms;
	std::vector<Appointment> appointments;
    public:
	Patient(int givenID, std::string givenName, int givenAge, char givenGender) : Person(givenID, givenName, givenAge, givenGender){}
	void patientPrintInfo(){
	    std::cout << "Name: " << Person::getName() << ", Age: " << Person::getAge() << ", Sex: " << Person::getSex();
	}

	void addAppointment(Appointment app){
	    appointments.push_back(app);
	}

	void printAppointments(){
	    for(int i = 0; i < appointments.size(); ++i){
		std::cout << '(' << i << "): " << appointments[i].getSched() << '\n';
	    }
	}
};

class Doctor : public Person {
    private:
	std::string specialization;
	std::vector<std::string> availableTimes;
    public:
    // constructor
    Doctor(int givenID, std::string givenName, int givenAge, char givenSex, std::string givenSpecialization) : Person(givenID, givenName, givenAge, givenSex) {
	specialization = givenSpecialization;
    }
    // setters...
    void addSchedule(std::string fulldate) {
	availableTimes.push_back(fulldate);
    }

    void setSpecialization(std::string givenSpecialization) {
	specialization = givenSpecialization;
    }
    
    //getters
    std::string getSpecialization(){
	return specialization;
    }

    std::vector<std::string> getSchedules(){
	return availableTimes;
    }
};


// null objects
Doctor nullDoctor(-1, "_null", -1, '_', "null");
Patient nullPatient(-1, "_null", -1, '_');

//functions

std::vector<int> vecDate(std::string sched){
    std::stringstream ss(sched);
    int date, hs, he;
    char chr;
    ss >> date >> chr >> hs >> chr >> he;
    std::vector<int> vec = {date, hs, he};
    return vec;
}

// main 
class HospitalManager{
    private:
	std::vector<Patient> patients;
	std::vector<Doctor> doctors;
	std::vector<std::string> schedules;
	std::vector<Appointment> appointments;
	std::string patientSaveName;
	std::string doctorSaveName;
	std::string scheduleSaveName;
	std::string appointmentSaveName;
    public:
	HospitalManager(std::string givenPatientSaveName, std::string givenDoctorSaveName, std::string givenScheduleSaveName, std::string givenAppointmentSaveName) : patientSaveName(givenPatientSaveName), doctorSaveName(givenDoctorSaveName), scheduleSaveName(givenScheduleSaveName), appointmentSaveName(givenAppointmentSaveName) {
	    hospitalLoadPatients();
	    hospitalLoadDoctors();
	    hospitalLoadSchedules();
	    hospitalLoadAppointments();
	}
	
	// Saving
	void hospitalSavePatients(){
	    std::ofstream patFile(patientSaveName);
	    for(Patient& patient : patients){
		patFile << patient.getID() << (char)0x1F
			<< patient.getName() << (char)0x1F
			<< patient.getAge() << (char)0x1F
			<< patient.getSex() << (char)0x1F << '\n';
	    }
	    patFile.close();
	    return;
	}

	void hospitalSaveDoctors(){
	    std::ofstream docFile(doctorSaveName);
	    for(Doctor& doctor : doctors){
		docFile << doctor.getID() << (char)0x1F
			<< doctor.getName() << (char)0x1F
			<< doctor.getAge() << (char)0x1F
			<< doctor.getSex() << (char)0x1F
			<< doctor.getSpecialization() << (char)0x1F << '\n';
	    }
	    docFile.close();
	    return;
	}

	void hospitalSaveSchedules(){
	    std::ofstream schedFile(scheduleSaveName);
	    for(Doctor& doctor : doctors){
		if(doctor.getSchedules().size() <= 0)
		    continue;
		for(std::string sched : doctor.getSchedules()){
		    schedFile << doctor.getID() << (char)0x1F << sched << '\n';
		}
	    }
	    schedFile.close();
	    return;
	}
	
	void hospitalSaveAppointments(){
	    std::ofstream appFile(appointmentSaveName);
	    for(Appointment& app : appointments){
		appFile << app.getID() << ',' << app.getPatID() << ',' << app.getDocID() << ',' << app.getSched() << ';' << app.getHour() << '\n';
	    }
	    appFile.close();
	}

	// Loading
	void hospitalLoadPatients(){
	    patients.clear();
	    std::ifstream patFile(patientSaveName);
	    std::string line;
	    while(std::getline(patFile, line)){
		std::stringstream ss(line);
		std::string name;
		int id, age;
		char cma, sex;

		ss >> id >> cma;
		std::getline(ss, name, (char)0x1F);
		ss >> cma >> age >> cma >> sex;
		hospitalPatientAdd(name, age, sex, true);
	    }
	    return;
	}

	void hospitalLoadDoctors(){
	    doctors.clear();
	    std::ifstream docFile(doctorSaveName);
	    std::string line;
	    while(std::getline(docFile, line)){
		std::stringstream ss(line);
		std::string name, specialization;
		int id, age;
		char cma, sex;

		ss >> id >> cma;
		std::getline(ss, name, (char)0x1F);
		ss >> cma >> age >> cma >> sex >> cma >> specialization;
		hospitalDoctorAdd(name, age, sex, specialization, true);
	    }
	    return;
	}
	
	void hospitalLoadSchedules(){
	    schedules.clear();
	    std::ifstream schedFile(scheduleSaveName);
	    std::string line;
	    while(std::getline(schedFile, line)){
		std::stringstream ss(line);
		int docID;
		std::string fulldate;
		char cma;
		
		ss >> docID >> cma >> fulldate;
		hospitalSetDoctorSchedule(docID,  fulldate, true);
	    }
	    schedFile.close();
	}
	
	void hospitalLoadAppointments(){
	    appointments.clear();
	    std::ifstream appFile(appointmentSaveName);
	    std::string line;
	    while(std::getline(appFile, line)){
		std::stringstream ss(line);
		int appID, patID, docID, hour;
		std::string sched;
		char chr;

		ss >> appID >> chr >> patID >> chr >> docID >> chr;
		std::getline(ss, sched, ';');
		ss >> hour;

		Appointment app(appID, patID, docID, sched, hour);
		Patient* patient = hospitalGetPatient(patID);

		patient->addAppointment(app);
		hospitalSetAppointment(patID, docID, sched, hour, false);

	    }
	    appFile.close();
	    return;
	}
	// Setters
	void hospitalPatientAdd(std::string name, int age, char gender, bool isLoad=false){
	    int id = patients.size();
	    Patient newPatient(id, name, age, gender);
	    patients.push_back(newPatient);
	    if(!isLoad){
		hospitalSavePatients();
	    }
	}
	
	void hospitalDoctorAdd(std::string name, int age, char gender, std::string specialization, bool isLoad=false){
	    int id = doctors.size();
	    Doctor newDoctor(id, name, age, gender, specialization);
	    doctors.push_back(newDoctor);
	    if(!isLoad){
		hospitalSaveDoctors();
	    }
	    return;
	}

	void hospitalSetDoctorSchedule(int id, std::string fulldate, bool isLoad=false){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == id){
		    doctor.addSchedule(fulldate);
		    schedules.push_back(std::to_string(id)+(char)0x1F+fulldate);
		    if(!isLoad){
			hospitalSaveSchedules();
		    }
		    return;
		}
	    }
	}

	void hospitalSetAppointment(int patID, int docID, std::string chosenSched, int chosenHour, bool isLoad=false){
	    // Patient shit...
	    int appID = appointments.size();
	    Appointment app(appID, patID, docID, chosenSched, chosenHour);
	    appointments.push_back(app);
	    if(!isLoad){
		hospitalSaveAppointments();
	    }
	    return;
	}

	// Getters
	Patient* hospitalGetPatient(int id){
	    for(Patient& patient : patients){
		if(patient.getID() == id){
		    return &patient;
		}
	    }
	    return nullptr;
	}

	Doctor* hospitalGetDoctor(int id){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == id)
		    return &doctor;
	    }
	    return nullptr;
	}
	
	std::string hospitalGetSchedule(int docID, int schedID){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == docID){
		    std::string date = doctor.getSchedules()[schedID-1];
		    std::stringstream ssDate(date);
		    int id, datenum, hs, he;
		    char chr;
		    ssDate >> datenum >> chr >> hs >> chr >> he;
		    return parseDate(std::stoi(date)) + " From: " + std::to_string(hs) + ":00 to " + std::to_string(he) + ":00";
		}
	    }
	    return "NULL";
	}

	std::string hospitalGetRawSched(int docID, int chosenSched){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == docID){
		    return doctor.getSchedules()[chosenSched-1];
		}
	    }
	    return "NULL";
	}

	void hospitalPrintPatients(){
	    for(Patient& patient : patients){
		    std::cout << '(' << patient.getID() << ')' << patient.getName() << ", " << patient.getSex() << '\n';
	    }
	}

	void hospitalPrintDoctors(){
	    for(Doctor& doctor : doctors){
		    std::cout << '(' << doctor.getID() << ')' << doctor.getName() << ", " << doctor.getSex() << ", " << doctor.getSpecialization() << '\n';
	    }
	}

	void hospitalPrintDoctorSchedules(int id){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == id){
		    if(doctor.getSchedules().size() == 0)
			continue;
		    int i = 1;
		    for(std::string sched : doctor.getSchedules()){
			int date, hs, he;
			char chr;
			std::stringstream ss(sched);

			ss >> date >> chr >> hs >> chr >> he;
			std::cout << '(' << i << "): " << parseDate(date) << " " << hs << ":00 to " << he << ":00\n";
			i++;
		    }
		    return;
		}
	    }
	}
};

#include <bits/stdc++.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

// consts
const std::string months[12] = {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// functions
// YYYYMMDD 20250514:14,16
// 			May 14, 2025
std::string parseDate(int date){
    std::string fulldate = std::to_string(date);
    std::string year = fulldate.substr(0,4);
    std::string month = months[std::stoi(fulldate.substr(4,2))-1];
    int day = std::stoi(fulldate.substr(6));
    std::string full = month + " " + std::to_string(day) + ", " + year;
    return full;
}

std::string toLower(const std::string str){
    std::string lowered = "";
    for(char chr : str){
	if('A' <= chr && chr <= 'Z'){
	    lowered += (chr + 32);
	}else{
	    lowered += chr;
	}
    }
    return lowered;
}

int min(int a, int b){
    if(a>b)
	return b;
    return a;
}

bool isValidComp(const std::string str1, const std::string str2){
    if(str1.length() > str2.length()){
	return false;
    } 

    for(int i = 0; i < str1.length(); ++i){
		if(str1[i] != str2[i])
			return false;
    }
    return true;
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

	void setID(int id){
	    ID = id;
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

	bool checkCancelled(){
	    return isCancelled;
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

class Checkup{
    private:
	int recordID;
	int appID;
	std::string symptoms;
	std::string treatments;
    public:
	Checkup(int givenRecordID, int givenAppID, std::string givenSymptoms, std::string givenTreatments) : recordID(givenRecordID), appID(givenAppID), symptoms(givenSymptoms), treatments(givenTreatments) {}

	int getRecordID(){
	    return recordID;
	}

	int getAppID(){
	    return appID;
	}

	std::string getSymptoms(){
	    return symptoms;
	}

	std::string getTreatments(){
	    return treatments;
	}

	void removeCheckup(){
	    recordID = -1;
	    return;
	}
};

class Patient : public Person {
    private:
	//// IDK
	std::string symptoms;
	std::vector<Appointment> appointments;
    public:
	Patient(int givenID, std::string givenName, int givenAge, char givenGender) : Person(givenID, givenName, givenAge, givenGender){}
	// getter
	void patientPrintInfo(){
	    std::cout << "Name: " << Person::getName() << ", Age: " << Person::getAge() << ", Sex: " << Person::getSex();
	}

	void addAppointment(Appointment app){
	    appointments.push_back(app);
	}

	void printAppointments(){
	    for(int i = 0; i < appointments.size(); ++i){
		std::string appDate = appointments[i].getSched().substr(0,8);
		std::cout << '(' << i << "): " << parseDate(std::stoi(appDate)) << ", " << appointments[i].getHour() << ":00" << '\n';
	    }
	}
	
	void setSymptoms(std::string givenSymptoms){
	    symptoms = givenSymptoms;
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
	std::vector<Checkup> checkups;
	std::string patientSaveName;
	std::string doctorSaveName;
	std::string scheduleSaveName;
	std::string appointmentSaveName;
	std::string checkupSaveName;
    public:

	HospitalManager(std::string givenPatientSaveName, std::string givenDoctorSaveName, std::string givenScheduleSaveName, std::string givenAppointmentSaveName, std::string givenCheckupSaveName) : patientSaveName(givenPatientSaveName), doctorSaveName(givenDoctorSaveName), scheduleSaveName(givenScheduleSaveName), appointmentSaveName(givenAppointmentSaveName), checkupSaveName(givenCheckupSaveName) {
	    hospitalLoadPatients();
	    hospitalLoadDoctors();
	    hospitalLoadSchedules();
	    hospitalLoadAppointments();
	    hospitalLoadCheckups();
	}

	// Saving
	void hospitalSavePatients(){
	    std::ofstream patFile(patientSaveName);
	    for(Patient& patient : patients){
		if(patient.getID() == -1)
		    continue;
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
		if(doctor.getSchedules().size() <= 0 || doctor.getID() == -1)
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
		if(app.checkCancelled() == true){
		    continue;
		}
		appFile << app.getID() << ',' << app.getPatID() << ',' << app.getDocID() << ',' << app.getSched() << ';' << app.getHour() << '\n';
	    }
	    appFile.close();
	}

	void hospitalSaveCheckups(){
	    std::ofstream checkFile(checkupSaveName);
	    for(Checkup& checkup : checkups){
		if(checkup.getAppID() == -1){
		    continue;
		}
		checkFile << checkup.getRecordID() << ',' << checkup.getAppID() << ',' << checkup.getSymptoms() << (char)0x1F << checkup.getTreatments() << '\n';
	    }
	    checkFile.close();
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

	void hospitalLoadCheckups(){
	    checkups.clear();
	    std::ifstream checkFile(checkupSaveName);
	    std::string line;
	    while(std::getline(checkFile, line)){
		std::stringstream ss(line);
		int recordID, appID;
		std::string symptoms, treatments;
		char cma;

		ss >> recordID >> cma >> appID >> cma;
		std::getline(ss, symptoms, (char)0x1F);
		ss >> treatments;

		hospitalRecordCheckup(appID, symptoms, treatments, true);
	    }
	    checkFile.close();
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

	void hospitalSetDoctorSchedule(int docID, std::string fulldate, bool isLoad=false){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == docID){
		    doctor.addSchedule(fulldate);
		    schedules.push_back(std::to_string(docID)+(char)0x1F+fulldate);
		    if(!isLoad){
			hospitalSaveSchedules();
		    }
		    return;
		}
	    }
	}

	void hospitalSetAppointment(int patID, int docID, std::string chosenSched, int chosenHour, bool isLoad=false){
	    // Patient shit...
	    // TODO: add appointment to patient
	    int appID = appointments.size();
	    Appointment app(appID, patID, docID, chosenSched, chosenHour);
	    appointments.push_back(app);
	    if(!isLoad){
		hospitalSaveAppointments();
	    }
	    return;
	}

	void hospitalRecordCheckup(int appID, std::string symptoms, std::string treatments, bool isLoad=false){
	    int recordID = checkups.size();
	    Checkup record(recordID, appID, symptoms, treatments);
	    checkups.push_back(record);
	    if(!isLoad){
		hospitalSaveCheckups();
	    }
	}

	void hospitalGetDoctorsFromSpecialization(std::string specialization){
	    bool exists = false;
	    std::string loweredGiven = toLower(specialization);
	    std::vector<Doctor> validDoctors;
	    for(Doctor& doctor : doctors){
		std::string doctorSpec = toLower(doctor.getSpecialization());
		if(isValidComp(loweredGiven, doctorSpec)){
		    validDoctors.push_back(doctor);
		    exists = true;
		}
	    }
	    
	    if(!exists){
		std::cout << "No Doctors with that specialization found!\n";
		return;
	    }

	    for(Doctor& doc: validDoctors){
		std::cout << "(" << doc.getID() << "): " << doc.getName() << " || " << doc.getSpecialization() << '\n';
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

	Appointment* hospitalGetAppointment(int appID){
	    for(Appointment& app : appointments){
		if(app.getID() == appID){
		    return &app;
		}
	    }
	    return nullptr;
	}
	//20250515:10,15
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
		if(patient.getID() == -1)
		    continue;
		std::cout << '(' << patient.getID() << ')' << patient.getName() << ", " << patient.getSex() << '\n';
	    }
	}

	void hospitalPrintDoctors(){
	    for(Doctor& doctor : doctors){
		if(doctor.getID() == -1)
		    continue;
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
			bool isOccuppied = false;
			std::vector<int> occupiedHours;
			ss >> date >> chr >> hs >> chr >> he;

			// check occupied
			for(Appointment& app : appointments){
			    if(app.getDocID() == id){
				std::string converted = (std::to_string(date) + ":" + std::to_string(hs) + "," + std::to_string(he));
				std::string gottenSched = app.getSched();
				isOccuppied = (gottenSched == converted);
				occupiedHours.push_back(app.getHour());
			    }
			}
			std::cout << '(' << i << "): " << parseDate(date) << " " << hs << ":00 to " << he << ":00";
			if(isOccuppied){
			    for(int hour : occupiedHours){
				std::cout << "\n\t Hour Occupied: " << hour;
			    }
			}
			std::cout << '\n';
			i++;
		    }
		    return;
		}
	    }
	}

	std::vector<int> hospitalGetOccupiedHours(int docID, int schedID){
	    Doctor* doctor = hospitalGetDoctor(docID);
	    std::string schedule = doctor->getSchedules()[schedID];
	    std::stringstream ss(schedule);
	    int date, hs, he;
	    char chr;
	    ss >> date >> chr >> hs >> chr >> he;
	    std::vector<int> occupiedHours;
	    for(Appointment& app : appointments){
		if(app.getDocID() == docID){
		    std::string converted = (std::to_string(date) + ":" + std::to_string(hs) + "," + std::to_string(he));
		    std::string gottenSched = app.getSched();
		    occupiedHours.push_back(app.getHour());
		}
	    }
	    return occupiedHours;
	}

	bool hospitalValidateAppointment(std::vector<int> occupiedHours, int chosenHour){
	    for(int hour : occupiedHours){
		if(hour == chosenHour)
		    return false;
	    }
	    return true;
	}


	// Removing...
	void hospitalRemovePatient(int patID){
	    // Removing patient
	    Patient* patient = hospitalGetPatient(patID);
	    if(patient == nullptr){
		std::cout << "\nPatient with this ID doesn't exist!\n";
		return;
	    }

	    patient->setID(-1);
	    // Removing Appointments and Checkups with patID

	    for(Appointment& app : appointments){
			if(app.getPatID() == patID){
				// cancelling appointments
				app.appointmentCancel();
				// removing checkups
				for(Checkup& checkup : checkups){
				if(checkup.getAppID() == app.getID()){
					checkup.removeCheckup();
					break;
				}
				}
			}
	    }

	    hospitalSavePatients();
	    hospitalSaveAppointments();
	    hospitalSaveCheckups();
	    hospitalLoadPatients();
	    hospitalLoadAppointments();
	    hospitalLoadCheckups();
	    return;
	}

	void hospitalRemoveDoctor(int docID){
	    Doctor* doctor = hospitalGetDoctor(docID);
	    if(doctor == nullptr){
		std::cout << "\nDoctor with this ID doesn't exist!\n";
		return;
	    }
	    doctor->setID(-1);

	    // Remove Appointments, Checkups, Schedules
	    for(std::string sched : schedules){
		std::stringstream ss(sched);
		int dID;
		ss >> dID;
		if(dID == docID){
		    sched = "-1,000000000";
		}
	    }

	    for(Appointment& app : appointments){
		if(app.getDocID() == docID){
		    app.appointmentCancel();

		    for(Checkup& checkup : checkups){
			if(checkup.getAppID() == app.getID()){
			    checkup.removeCheckup();
			    break;
			}
		    }
		}
	    }

	    hospitalSaveDoctors();
	    hospitalSaveCheckups();
	    hospitalSaveAppointments();
	    hospitalSaveSchedules();
	    hospitalLoadSchedules();
	    hospitalLoadCheckups();
	    hospitalLoadAppointments();
	    hospitalLoadDoctors();
	    return;
	}
};

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

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

class Patient : public Person {
    private:
	//// IDK
	// std::vector<std::string> symptoms;
	// std::vector<Appointment> appointments;
    public:
	Patient(int givenID, std::string givenName, int givenAge, char givenGender) : Person(givenID, givenName, givenAge, givenGender){}
	void patientPrintInfo(){
	    std::cout << "Name: " << Person::getName() << ", Age: " << Person::getAge() << ", Sex: " << Person::getSex();
	}
};

class Doctor : public Person {
    // TODO
	private:
        	std::string specialization;
        	std::vector<std::string> availableTimes;
	public:
	// constructor
		Doctor(int givenID, std::string givenName, int givenAge, char givenSex, std::string givenSpecialization) : Person(givenID, givenName, givenAge, givenSex)
	{
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


// structs
struct Appointment{
    private:
	int appID;
	int patID;
	int docID;
	std::string appSched;
	int hour;
	bool isCancelled = false;
    public:
	Appointment(int givenAppID, int givenPatID, int givenDocID, std::string givenAppSched, int givenHour){
	    appID = givenAppID;
	    patID = givenPatID;
	    docID = givenDocID;
	    appSched = givenAppSched;
	    hour = givenHour;
	}

	void appointmentCancel(){
	    isCancelled = true;
	    return;
	}

	void appointmentGet(){
	    return;
	}
};
// null objects
Doctor nullDoctor(-1, "_null", -1, '_', "null");
Patient nullPatient(-1, "_null", -1, '_');

//functions

// main 
class HospitalManager{
    private:
	std::vector<Patient> patients;
	std::vector<Doctor> doctors;
	std::vector<std::string> schedules;
	std::string patientSaveName;
	std::string doctorSaveName;
	std::string scheduleSaveName;
    public:
	HospitalManager(std::string givenPatientSaveName, std::string givenDoctorSaveName, std::string givenScheduleSaveName) : patientSaveName(givenPatientSaveName), doctorSaveName(givenDoctorSaveName), scheduleSaveName(givenScheduleSaveName) {
	    hospitalLoadPatients();
	    hospitalLoadDoctors();
	    hospitalLoadSchedules();
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
		ss >> cma >> age >> cma >> sex;
		std::getline(ss, specialization, (char)0x1F);
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

	void hospitalSetAppointment(){
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
		    int i = 0;
		    for(std::string sched : doctor.getSchedules()){
			int date, hs, he;
			char chr;
			std::stringstream ss(sched);

			ss >> date >> chr >> hs >> chr >> he;
			std::cout << '(' << i << "): " << date << " " << hs << ":00 to " << he << ":00\n";
			i++;
		    }
		}
	    }
	}
};


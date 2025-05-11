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

class HospitalManager{
    private:
	std::vector<Patient> patients;
	std::vector<Doctor> doctors;
	std::string patientSaveName;
	std::string doctorSaveName;
    public:
	HospitalManager(std::string givenPatientSalveName, std::string givenDoctorSaveName) : patientSaveName(givenPatientSaveName), doctorSaveName(givenDoctorSaveName) {
	    hospitalLoadPatients();
	}
	
	// Saving
	void hospitalSavePatients(){
	    std::ofstream patFile(patientSaveName);
	    for(Patient& patient : patients){
		patFile << patient.getID() << ";;"
			<< patient.getName() << ";;"
			<< patient.getAge() << ";;"
			<< patient.getSex() << ";;" << '\n';
	    }
	    patFile.close();
	    return;
	}

	void hospitalSaveDoctors(){
	    std::ofstream docFile(doctorSaveName);
	    for(Doctor& doctor : doctors){
		docFile << doctor.getID() << ";;"
			<< doctor.getName() << ";;"
			<< doctor.getAge() << ";;"
			<< doctor.getSex() << ";;"
			<< doctor.getSpecialization() << ";;" << '\n';
	    }
	    docFile.close();
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

		ss >> id >> cma >> cma;
		std::getline(ss, name, ';');
		ss >> cma >> age >> cma >> cma >> sex;
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

		ss >> id >> cma >> cma;
		std::getline(ss, name, ';');
		ss >> cma >> age >> cma >> cma >> sex;
		std::getline(ss, specialization, ';');
		ss >> cma;
		hospitalDoctorrAdd(name, age, sex, specialization);
	    }
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
	    return;
	}
	// Getters
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
};


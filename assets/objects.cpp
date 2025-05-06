#include <string>
#include <vector>

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
    // TODO
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

	void cancelAppointment(){
	    isCancelled = true;
	    return;
	}

	void printAppointment(){
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
	HospitalManager(std::string givenPatientSaveName, std::string givenDoctorSaveName) : patientSaveName(givenPatientSaveName), doctorSaveName(givenDoctorSaveName) {}


};


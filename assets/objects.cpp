#include <string>

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
    // TODO
};

class Patient : public Person {
    // TODO
};

class Doctor : public Person {
    // TODO
};

class HospitalManager{
    // TODO
};


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
};

class HospitalManager{
    // TODO
};


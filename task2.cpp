#include <iostream>
#include <string>
using namespace std;

#define MAXDOC 10
#define totalPatient 100
#define MAXNURSE 10
#define MAXWARD 3

class Patient;
class Doctor;
class Nurse;
class Ward;

class Report
{
    int reportId;
    string diagnosis;
    string prescription;
    Patient *patient;
    Doctor *doctor;

public:
    Report();
    Report(int id, string diag, string presc, Patient *pat, Doctor *doc);
    Report(const Report &r);
    void setReportDetails(Patient *pat, Doctor *doc);
    void showReportDetails();
};

class Ward
{
    int wardId;

public:
    Ward();
    Ward(int id);
    Ward(Ward &w);
    void setWardDetails();
    void showWardDetails();
    void setWardId(int);
    int getWardId();
};

class Doctor
{
    int doctorId;
    string name;
    string specialty;
    int experience;
    Ward *ward;

public:
    Doctor();
    Doctor(int id, string n, string spec, int exp);
    Doctor(Doctor &doc);
    void setDoctorDetails();
    void showDoctorDetails();
    string getName();
    int getDoctorId();
};

class Patient
{
    int patientId;
    string name;
    int age;
    char gender;
    string diseases;
    Ward ward;
    Doctor *doc;
    int totalDoc;

public:
    Patient();
    Patient(int id, string n, int age, char gen, string d);
    Patient(Patient &pat);
    ~Patient();
    void setPatientDetails();
    void showPatientDetails();
    string getName();
    int getPatientId();
};

class Nurse
{
    int nurseId;
    string name;
    string shift;
    Ward *ward;

public:
    Nurse();
    Nurse(int id, string n, string s, Ward *w);
    Nurse(Nurse &n);
    void setNurseDetails();
    void showNurseDetails();
    string getName();
    int getNurseId();
};

class Hospital
{
    Patient patient[totalPatient];
    Doctor doctor[MAXDOC];
    Nurse nurse[MAXNURSE];
    Report reports[totalPatient];
    static int currPatient;
    static int currDoctor;
    static int currNurse;
    static int currReport;

public:
    void addPatient(const Patient &p);
    void viewAllPatients();
    void addDoctor(const Doctor &d);
    void viewAllDoctors();
    void addNurse(const Nurse &n);
    void viewAllNurses();
    void addReport();
    void viewAllReports();

    static int getCurrPatient()
    {
        return currPatient;
    }
    static int getCurrDoctor()
    {
        return currDoctor;
    }
    static int getCurrNurse()
    {
        return currNurse;
    }
    static int getcurrReport()
    {
        return currReport;
    }
    Patient getPatient(int index)
    {
        return patient[index];
    }
    Doctor getDoctor(int index)
    {
        return doctor[index];
    }
};

int Hospital::currPatient = 0;
int Hospital::currDoctor = 0;
int Hospital::currNurse = 0;
int Hospital::currReport = 0;
int inputNumber();
Ward::Ward()
{
    wardId = 0;
}

Ward::Ward(int id)
{
    wardId = id;
}

Ward::Ward(Ward &w)
{
    wardId = w.wardId;
}

void Ward::setWardDetails()
{
    cout << "Enter Ward ID: ";
    cin >> wardId;
    cin.ignore();
}

void Ward::showWardDetails()
{
    cout << "Ward ID: " << wardId << endl;
}

void Ward::setWardId(int wId)
{
    wardId = wId;
}

int Ward::getWardId()
{
    return wardId;
}

Patient::Patient()
{
    patientId = 0;
    name = "";
    age = 0;
    gender = ' ';
    diseases = "";
    ward.setWardId(0);
    totalDoc = 0;
    doc = new Doctor[MAXDOC];
}

Patient::Patient(int id, string n, int age, char gen, string d)
{
    patientId = id;
    name = n;
    this->age = age;
    gender = gen;
    diseases = d;
    totalDoc = 0;
    doc = new Doctor[MAXDOC];
}

Patient::Patient(Patient &pat)
{
    patientId = pat.patientId;
    name = pat.name;
    this->age = pat.age;
    gender = pat.gender;
    diseases = pat.diseases;
    totalDoc = pat.totalDoc;
    doc = new Doctor[MAXDOC];
    for (int i = 0; i < totalDoc; i++)
    {
        doc[i] = pat.doc[i];
    }
}

Patient::~Patient()
{
    delete[] doc;
}

void Patient::setPatientDetails()
{
    do
    {
        cout << "Enter Patient ID: ";
        patientId = inputNumber();
        if (patientId <= 0)
        {
            cout << "Patient ID should be positive integer(>0)!" << endl;
        }
    } while (patientId <= 0);
    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, name);
    do
    {
        cout << "Enter Patient Age: ";
        age = inputNumber();
        if (age <= 0)
        {
            cout << "Age should be positive integer(>0)!" << endl;
        }
    } while (age <= 0);
    cin.ignore();
    do
    {
        cout << "Enter Patient Gender (first character only): ";
        cin >> gender;
        if (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f')
        {
            cout << "Please Enter a valid character for gender!" << endl;
        }
    } while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f');

    cin.ignore();
    cout << "Enter Patient Diseases (comma-separated): ";
    getline(cin, diseases);

    int wId;
    do
    {
        cout << "Enter Ward ID: ";
        wId = inputNumber();
        if (wId < 0)
        {
            cout << "Ward ID should be positive integer!" << endl;
        }
        else if (wId > MAXWARD)
        {
            cout << "We have only 3 Ward(id 1 to 3)!Try Again" << endl;
        }
    } while (wId < 0 || wId > MAXWARD);
    ward.setWardId(wId);
    cin.ignore();
}

void Patient::showPatientDetails()
{
    cout << "Patient ID: " << patientId << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Disease: " << diseases << endl;
    cout << "Ward ID: " << ward.getWardId() << endl;
}

string Patient::getName()
{
    return name;
}

int Patient::getPatientId()
{
    return patientId;
}

Doctor::Doctor()
{
    doctorId = 0;
    name = "";
    specialty = "";
    experience = 0;
}

Doctor::Doctor(int id, string n, string spec, int exp)
{
    doctorId = id;
    name = n;
    specialty = spec;
    experience = exp;
}

Doctor::Doctor(Doctor &doc)
{
    doctorId = doc.doctorId;
    name = doc.name;
    specialty = doc.specialty;
    experience = doc.experience;
}

void Doctor::setDoctorDetails()
{
    do
    {
        cout << "Enter Doctor ID: ";
        doctorId = inputNumber();
        if (doctorId <= 0)
        {
            cout << "Doctor ID should be positive integer(>0)!" << endl;
        }
    } while (doctorId <= 0);
    cin.ignore();
    cout << "Enter Doctor Name: ";
    getline(cin, name);
    cout << "Enter Specialty: ";
    getline(cin, specialty);
    do
    {
        cout << "Enter Years of Experience: ";
        experience = inputNumber();
        if (experience < 0)
        {
            cout << "Experience can't be a negative value!" << endl;
        }
    } while (experience < 0);
    int wardId;
    do
    {
        cout << "Enter Assigned Ward ID (0 if none): ";
        wardId = inputNumber();
        if (wardId < 0)
        {
            cout << "Ward ID should be positive integer!" << endl;
        }
        else if (wardId > MAXWARD)
        {
            cout << "We have only 3 Ward(id 1 to 3)!Try Again" << endl;
        }
    } while (wardId < 0 || wardId > MAXWARD);
    if (wardId != 0)
    {
        ward = new Ward;
        ward->setWardId(wardId);
        cout << "Ward assigned to Doctor" << endl;
    }
    else
    {
        ward = nullptr;
        cout << "Doctor do not assign to any ward" << endl;
    }
}

void Doctor::showDoctorDetails()
{
    cout << "Doctor ID: " << doctorId << endl;
    cout << "Name: " << name << endl;
    cout << "Specialty: " << specialty << endl;
    cout << "Years of Experience: " << experience << endl;
    if (ward)
    {
        cout << "Assigned Ward ID: " << ward->getWardId() << endl;
    }
    else
    {
        cout << "No ward assigned to Doctor yet" << endl;
    }
}

string Doctor::getName()
{
    return name;
}

int Doctor::getDoctorId()
{
    return doctorId;
}

Nurse::Nurse()
{
    nurseId = 0;
    name = "";
    shift = "";
    ward = nullptr;
}

Nurse::Nurse(int id, string n, string s, Ward *w)
{
    nurseId = id;
    name = n;
    shift = s;
    ward = w;
}

Nurse::Nurse(Nurse &n)
{
    nurseId = n.nurseId;
    name = n.name;
    shift = n.shift;
    ward = n.ward;
}

void Nurse::setNurseDetails()
{
    do
    {
        cout << "Enter Nurse ID: ";
        nurseId = inputNumber();
        if (nurseId <= 0)
        {
            cout << "Nurse ID should be positive integer(>0)!" << endl;
        }
    } while (nurseId <= 0);
    cin.ignore();
    cout << "Enter Nurse Name: ";
    getline(cin, name);
    cout << "Enter Shift: ";
    getline(cin, shift);
    int wardId;
    do
    {
        cout << "Enter Assigned Ward ID (0 if none): ";
        wardId = inputNumber();
        if (wardId < 0)
        {
            cout << "Ward ID should be positive integer!" << endl;
        }
        else if (wardId > MAXWARD)
        {
            cout << "We have only 3 Ward(id 1 to 3)!Try Again" << endl;
        }
    } while (wardId < 0 || wardId > MAXWARD);
    if (wardId != 0)
    {
        ward = new Ward;
        ward->setWardId(wardId);
        cout << "Ward assigned to Nurse" << endl;
    }
    else
    {
        ward = nullptr;
        cout << "Nurse do not assign to any ward" << endl;
    }
}

void Nurse::showNurseDetails()
{
    cout << "Nurse ID: " << nurseId << endl;
    cout << "Name: " << name << endl;
    cout << "Shift: " << shift << endl;
    if (ward)
    {
        cout << "Assigned Ward ID: " << ward->getWardId() << endl;
    }
    else
    {
        cout << "No ward assigned to Nurse yet" << endl;
    }
}

string Nurse::getName()
{
    return name;
}

int Nurse::getNurseId()
{
    return nurseId;
}

Report::Report()
{
    reportId = 0;
    diagnosis = "";
    prescription = "";
    patient = nullptr;
    doctor = nullptr;
}

Report::Report(int id, string diag, string presc, Patient *pat, Doctor *doc)
{
    reportId = id;
    diagnosis = diag;
    prescription = presc;
    patient = pat;
    doctor = doc;
}

Report::Report(const Report &r)
{
    reportId = r.reportId;
    diagnosis = r.diagnosis;
    prescription = r.prescription;
    patient = r.patient;
    doctor = r.doctor;
}

void Report::setReportDetails(Patient *pat, Doctor *doc)
{
    patient = pat;
    doctor = doc;
    cout << "Enter Diagnosis: ";
    cin.ignore();
    getline(cin, diagnosis);
    cout << "Enter Prescription: ";
    getline(cin, prescription);
}

void Report::showReportDetails()
{
    cout << "Report ID: " << reportId << endl;
    cout << "Diagnosis: " << diagnosis << endl;
    cout << "Prescription: " << prescription << endl;
    cout << "Patient Name: " << patient->getName() << endl;
    cout << "Doctor Name: " << doctor->getName() << endl;
}

void Hospital::addPatient(const Patient &p)
{
    if (currPatient < totalPatient)
    {
        patient[currPatient] = p;
        currPatient++;
        cout << "Patient added to system" << endl;
    }
    else
    {
        cout << "Sorry!We have maximum limit for Patients" << endl;
    }
}

void Hospital::viewAllPatients()
{
    if (currPatient == 0)
    {
        cout << "Currently no patient exist in System" << endl;
    }
    else
    {
        cout << "List of Patients: " << endl;
        for (int i = 0; i < currPatient; i++)
        {
            patient[i].showPatientDetails();
            cout << "................" << endl;
        }
    }
}

void Hospital::addDoctor(const Doctor &d)
{
    if (currDoctor < MAXDOC)
    {
        doctor[currDoctor] = d;
        currDoctor++;
        cout << "Doctor added to a System" << endl;
    }
    else
    {
        cout << "Sorry!We have maximum limit for Doctors" << endl;
    }
}

void Hospital::viewAllDoctors()
{
    if (currDoctor == 0)
    {
        cout << "Currently no doctor exist in System" << endl;
    }
    else
    {
        cout << "List of Doctors: " << endl;
        for (int i = 0; i < currDoctor; i++)
        {
            doctor[i].showDoctorDetails();
            cout << "................" << endl;
        }
    }
}

void Hospital::addNurse(const Nurse &n)
{
    if (currNurse < MAXNURSE)
    {
        nurse[currNurse] = n;
        currNurse++;
        cout << "Nurse added to a System" << endl;
    }
    else
    {
        cout << "Sorry!We have maximum limit for Nurses" << endl;
    }
}

void Hospital::viewAllNurses()
{
    if (currNurse == 0)
    {
        cout << "Currently no Nurse exist in System" << endl;
    }
    else
    {
        cout << "List of Nurses:" << endl;
        for (int i = 0; i < currNurse; i++)
        {
            nurse[i].showNurseDetails();
            cout << "................" << endl;
        }
    }
}

void Hospital::addReport()
{
    if (currReport < totalPatient)
    {
        int patientId, doctorId;
        do
        {
            cout << "Enter Patient ID: ";
            patientId = inputNumber();
            if (patientId <= 0)
            {
                cout << "Patient ID should be positive integer(>0)!" << endl;
            }
        } while (patientId <= 0);
        do
        {
            cout << "Enter Doctor ID: ";
            doctorId = inputNumber();
            if (doctorId <= 0)
            {
                cout << "Doctor ID should be positive integer(>0)!" << endl;
            }
        } while (doctorId <= 0);
        Patient *pat = nullptr;
        Doctor *doc = nullptr;

        for (int i = 0; i < currPatient; i++)
        {
            if (patient[i].getPatientId() == patientId)
            {
                pat = &patient[i];
                break;
            }
        }

        for (int i = 0; i < currDoctor; i++)
        {
            if (doctor[i].getDoctorId() == doctorId)
            {
                doc = &doctor[i];
                break;
            }
        }

        if (pat && doc)
        {
            Report r(currReport + 1, "", "", pat, doc);
            r.setReportDetails(pat, doc);
            reports[currReport] = r;
            currReport++;
            cout << "Report added to a System" << endl;
        }
        else
        {
            cout << "Patient or Doctor not found!" << endl;
        }
    }
    else
    {
        cout << "Sorry!We have maximum limit for Reports." << endl;
    }
}

void Hospital::viewAllReports()
{
    if (currReport == 0)
    {
        cout << "Currently no Report exist in System" << endl;
    }
    else
    {
        cout << "List of Reports:" << endl;
        for (int i = 0; i < currReport; i++)
        {
            reports[i].showReportDetails();
            cout << "................" << endl;
        }
    }
}
int inputNumber()
{
    int number;
    while (!(cin >> number))
    {
        cout << "Invalid input. Please enter an number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return number;
}
int main()
{
    Hospital hospital;
    int choice;

    do
    {
        cout << "___Hospital Management System___" << endl
             << "1. Add Patient" << endl
             << "2. View All Patients" << endl
             << "3. Add Doctor" << endl
             << "4. View All Doctors" << endl
             << "5. Add Nurse" << endl
             << "6. View All Nurses" << endl
             << "7. Add Report" << endl
             << "8. View All Reports" << endl
             << "9. View total No. of Staff" << endl
             << "10. Exit" << endl
             << "Enter your choice: ";
        choice = inputNumber();
        cout << "-----------------------" << endl;
        switch (choice)
        {
        case 1:
        {
            Patient p;
            p.setPatientDetails();
            hospital.addPatient(p);
            break;
        }
        case 2:
            hospital.viewAllPatients();
            break;
        case 3:
        {
            Doctor d;
            d.setDoctorDetails();
            hospital.addDoctor(d);
            break;
        }
        case 4:
            hospital.viewAllDoctors();
            break;
        case 5:
        {
            Nurse n;
            n.setNurseDetails();
            hospital.addNurse(n);
            break;
        }
        case 6:
            hospital.viewAllNurses();
            break;
        case 7:
            hospital.addReport();
            break;
        case 8:
            hospital.viewAllReports();
            break;
        case 9:
            cout << "Total Staff:" << endl;
            cout << "Current  Patients: " << Hospital::getCurrPatient() << endl;
            cout << "Current Doctors: " << Hospital::getCurrDoctor() << endl;
            cout << "Current Nurses: " << Hospital::getCurrNurse() << endl;
            cout << "Current Reports: " << Hospital::getcurrReport() << endl;
            break;
        case 10:
            cout << "Terminating System......" << endl;
            break;
        default:
            cout << "Invalid choice!Try again." << endl;
        }
        cout << "-----------------------" << endl;
    } while (choice != 10);

    return 0;
}
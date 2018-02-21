#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;


double GetNormalLeave(string  LeaveType[], double & NLeaveDays, string EmployeeName,int index);
void GetSickLeave(string  LeaveType[], double & SLeaveDays, string EmployeeName);
void GetTodayDate ();
int GetNoLines (string EmployeeName, int & NumberOfLines);
void GetDatesLeave (int Day[], int  Month[], int  Year[], string LeaveType[],string EmployeeName, int NumberOfLines, char dot);
bool isValidDate (int Day, int  Month, int  Year);
bool isLeapYear ( int Year);
void GetDataBase(int & LDA, int & SLDT, int & NLDT, string & LA);
void ClaculateNLeaveDays(string LeaveType[], double & NLeaveDays, string EmployeeName,int & LDA, int & SLDT, int & NLDT, string & LA, int Day[], int  Month[], int  Year[], string Datestamp[], const string ArloJoinDate);

int main(){
	
int NumberOfLines =0;
const string ArloJoinDate = "24-01-2017";
string EmployeeName;
double NLeaveDays = 0;
double SLeaveDays = 0;
char dot;
int LDA =0;
int SLDT=0;
int NLDT=0;
string LA;

cout << "Please follow these instructions to use the Leave Calculator:"<< endl;
cout << "1.) Enter the name of the employee you wish to calculate the leave for:" << endl;
cin >>EmployeeName;

cout << "There are : " << GetNoLines (EmployeeName, NumberOfLines) << " records in the textfile" << endl;
cout << endl;

int Day[NumberOfLines];
int Month[NumberOfLines]; 
int Year[NumberOfLines];
string Datestamp[NumberOfLines];
string LeaveType[NumberOfLines];

GetDatesLeave(Day,  Month,  Year,  LeaveType,EmployeeName, NumberOfLines, dot);

//GetNormalLeave(LeaveType, NLeaveDays,EmployeeName);

GetSickLeave(LeaveType, SLeaveDays,EmployeeName);

GetTodayDate();

GetDataBase(LDA, SLDT, NLDT, LA);
cout << "Trigger" << NLDT << endl;
ClaculateNLeaveDays(LeaveType,NLeaveDays, EmployeeName,LDA, SLDT, NLDT, LA, Day, Month, Year, Datestamp, ArloJoinDate);


	return 0;
}






int GetNoLines (string EmployeeName,  int & NumberOfLines){
	
ifstream InputFile;
string line;
InputFile.open(EmployeeName+".txt");
if (!InputFile) {
    cerr << "Unable to open file " + EmployeeName+".txt"  + "\nAre you sure it was spelt correctly?";
    exit(1);   
}

while(getline(InputFile,line)) {
NumberOfLines ++;
 }
NumberOfLines =NumberOfLines-1;
InputFile.close();
	
	return NumberOfLines;
}




void GetDatesLeave (int Day[], int  Month[], int  Year[], string LeaveType[], string EmployeeName, int NumberOfLines, char dot){
	

ifstream InputFile;

InputFile.open(EmployeeName+".txt");


for(int i =0; i <NumberOfLines; i++) {

InputFile >> Day[i] >> dot >> Month[i] >> dot >> Year[i] >> dot >> LeaveType[i];

 if (!isValidDate(Day[i], Month[i] , Year[i])){

cout<< "The date : " <<Day[i] <<"-" << Month[i] <<"-" << Year[i]  << " Is not a valid date " << endl;
	
 }
if( LeaveType[i] != "NF" && LeaveType[i] != "NH" && LeaveType[i] != "SF" && LeaveType[i] != "SH"){
	 
cout << "The leave type selected '" <<LeaveType[i]  << "' is not a valid leave type" << endl;
 }

if (LeaveType[i] == "NF"){
	
 cout<< "On the " << Day[i]  <<"-" <<  Month[i]<<"-" <<  Year[i] << " " << EmployeeName << " took a full day of leave."<< endl;
 }
 
 if (LeaveType[i] == "NH"){
	
 cout<< "On the " << Day[i]  <<"-" <<  Month[i]<<"-" <<  Year[i] << " " << EmployeeName << " took a half day of leave."<< endl;
 }
 
if (LeaveType[i] == "SF"){
	
 cout<< "On the " << Day[i]  <<"-" <<  Month[i]<<"-" <<  Year[i] << " " << EmployeeName << " took a full day of sick leave."<< endl;
 }
 
if (LeaveType[i] == "SH"){
	
 cout<< "On the " << Day[i]  <<"-" <<  Month[i]<<"-" <<  Year[i] << " " << EmployeeName << " took a half day of sick leave."<< endl;
 }
 
}

InputFile.close();
	
}




double GetNormalLeave(string LeaveType[], double & NLeaveDays, string EmployeeName, int index){
	
for (int j=index; j<sizeof(LeaveType);j++){
	
	if (LeaveType[j]=="NF"){
		NLeaveDays +=1;
	}
	
		if (LeaveType[j]=="NH"){
		NLeaveDays +=0.5;
	}
}

cout << EmployeeName<< " has taken " <<NLeaveDays << " days of Normal leave" <<endl;
return NLeaveDays;
}




void GetSickLeave(string  LeaveType[], double & SLeaveDays, string EmployeeName){
	
for (int j=0; j<sizeof(LeaveType);j++){
	
	if (LeaveType[j]=="SF"){
		SLeaveDays +=1;
	}
			if (LeaveType[j]=="SH"){
		SLeaveDays +=0.5;
	}
}

cout << EmployeeName<< " has taken " <<SLeaveDays << " days of Sick leave" <<endl;
	
}

void GetTodayDate(){
	
time_t t = time(0);  
struct tm * now = localtime( & t );
cout <<  now->tm_mday<< '-'
		 << (now->tm_mon + 1) << '-'
		 <<(now->tm_year + 1900) 
         << endl;

}

bool isValidDate (int Day, int Month, int Year){
	
	if(Day<1 && Day>31){
			return false;
	}
		
		if ((Month ==4 || Month ==6|| Month==9|| Month ==11 ) && Day <=30){
			return true;
		}
		
		if ((Month ==1 || Month ==3|| Month==5|| Month ==7 || Month ==8|| Month ==10 ||Month ==12) && Day <=31){
			return true;
		}
			
		 if((Month ==2 && Day ==29) && (isLeapYear(Year) == true)){
			return true;
		}
		
		if((Month ==2 && Day >28) && (isLeapYear(Year) == false)){
			return false;
		}
	
}


bool isLeapYear ( int Year){
	
    if (((Year% 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0)){
        return true;
	}
	
    else {return false;}
	
}


void GetDataBase(int & LDA, int & SLDT, int & NLDT, string & LA){

string Line;
ifstream DataFile;
string temp;

DataFile.open("Data.txt");

while(getline(DataFile,Line)) {

if (Line.find("Leave_days_available:") != string::npos){
	
temp.clear();

for(int k =0; k <=Line.length(); k++){
	
if (isdigit(Line[k]))
  {
temp+=Line[k];


 }

}

 LDA =  stoi (temp);
cout << "LDA   " << LDA << endl;

}

if (Line.find("Last_accessed:") != string::npos){
	
temp.clear();

for(int k =0; k <=Line.length(); k++){
	
if (isdigit(Line[k]))
  {
temp+=Line[k];


 }

}

string LA =  temp;
cout << "LA   " << LA << endl;

}

if (Line.find("Normal_leave_days_then:") != string::npos){
	
temp.clear();

for(int k =0; k <=Line.length(); k++){
	
if (isdigit(Line[k]))
  {
temp+=Line[k];


 }

}

NLDT =  stoi(temp);
cout << "NLDT   " << NLDT << endl;

}

if (Line.find("Sick_leave_days_then:") != string::npos){
	
temp.clear();

for(int k =0; k <=Line.length(); k++){
	
if (isdigit(Line[k]))
  {
temp+=Line[k];


 }

}

 SLDT =  stoi(temp);
cout << "SLDT   " << SLDT << endl;

}

}
DataFile.close();
	
}


void ClaculateNLeaveDays(string LeaveType[], double & NLeaveDays, string EmployeeName,int & LDA, int & SLDT, int & NLDT, string & LA,int Day[], int  Month[], int  Year[], string Datestamp[],const string ArloJoinDate){
	
int index =0;

for(int j =0; j<sizeof(Day); j++){
	
	Datestamp[j] = to_string(Day[j]) + "-" + to_string(Month[j]) + "-" + to_string(Year[j]);
	cout << Datestamp[j]  << endl;
}

	
//if (LA>GetTodayDate()){
//	//write to th data file todays date of access
//add in renewed days leave 
//	
//}


for(int i =0; i < sizeof(Datestamp); i++){
	if (Datestamp[i]>LA){
		index = i;
		break;
	}
}

NLeaveDays=NLDT -GetNormalLeave(LeaveType, NLeaveDays,EmployeeName, index);


cout <<EmployeeName << " has " << NLeaveDays << " days of normal leave left until " <<endl;


}


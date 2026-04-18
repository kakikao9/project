#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Course{
    public:
      string sub;
      string grade;
      int credit;
};
class GradeStorage{
    protected:
      vector<Course> courses;
    
    public:
      void add();
      void add(string sub,string grade,int credit);
      void view();
      void calculateGPA();
      void loadFile();
      void loadFile(string filename);
      void saveFile();
    
    float gradeToPoint(string grade);
};
class GradeAnalyzer : public GradeStorage{
    public:
      void analyzeGrade();
};
class MenuSystem : public GradeAnalyzer{
    public:
      void mainMenu();
      void gradeMenu();
};
void GradeStorage::add(){
    string sub, grade;
    int credit;
    cout<<"name subject : ";
    cin>>sub;

    cout<<"credit : ";
    cin>>credit;

    cout<<"grade : ";
    cin>>grade;
    
    add(sub,grade,credit);

    cout<<"Course added successfully\n";

    saveFile();

    cout<<"Data saved to file\n";
}
void GradeStorage::add(string sub,string grade,int credit){
    
    Course c;
    c.sub=sub;
    c.grade=grade;
    c.credit=credit;

    courses.push_back(c);
}

void GradeStorage::view(){

    cout<<"\n----Course List----\n";
    cout<<left<<setw(5)<<"No"
        <<setw(15)<<"Course"
        <<setw(10)<<"Grade"
        <<setw(10)<<"Credit\n";
    cout<<"---------------------------------\n";
    for(int i=0;i<courses.size();i++){
        cout<<left<<setw(5)<<i+1
            <<setw(15)<<courses[i].sub
            <<setw(10)<<courses[i].grade
            <<setw(10)<<courses[i].credit<<endl;
    }

    cout<<"---------------------------------\n";
}

float GradeStorage::gradeToPoint(string grade){

    if(grade=="A") return 4;
    if(grade=="B+") return 3.5;
    if(grade=="B") return 3;
    if(grade=="C+") return 2.5;
    if(grade=="C") return 2;
    if(grade=="D+") return 1.5;
    if(grade=="D") return 1;
    return 0;
}

void GradeStorage::calculateGPA(){

    float totalPoint=0;
    int totalCredit=0;
    cout<<left<<setw(15)<<"Course"
        <<setw(10)<<"Grade"
        <<setw(10)<<"Credit\n";
    cout<<"---------------------------------\n";
    for(int i=0;i<courses.size();i++){
        cout<<left<<setw(15)<<courses[i].sub
            <<setw(10)<<courses[i].grade
            <<setw(10)<<courses[i].credit<<endl;
    }

    cout<<"---------------------------------\n";
    for(int i=0;i<courses.size();i++){

        float point = gradeToPoint(courses[i].grade);

        totalPoint += point * courses[i].credit;
        totalCredit += courses[i].credit;
    }

    if(totalCredit==0){
        cout<<"N/A\n";
        return;
    }

    cout<<"total cradit : "<<totalCredit<<endl;
    cout<<"GPA : "<<fixed<<setprecision(2)<<totalPoint/totalCredit<<endl;
}

void GradeStorage::saveFile(){

    ofstream file("grade.txt");

    for(int i=0;i<courses.size();i++){
        file<<courses[i].sub<<" "
            <<courses[i].grade<<" "
            <<courses[i].credit<<endl;
    }

    file.close();
}

void GradeStorage::loadFile(){
    loadFile("grade.txt");
}

void GradeStorage::loadFile(string filename){

    ifstream file(filename);
    
    if(!file){
        cout<<"Cannot open file\n";
        return;
    }
    
    Course c;

    courses.clear();

    while(file>>c.sub>>c.grade>>c.credit){
        courses.push_back(c);
    }

    cout<<"Loading data from grade.txt.....\n";
    cout<<"Data loaded successfully\n";
    cout<<"Total course loaded : "<<courses.size()<<endl;

    file.close();
}

void GradeAnalyzer::analyzeGrade(){

    string name;
    int hw,mid;
    int hwFull,midFull,finalFull;

    cout<<"\n--- grade analysis ---\n";

    cout<<"name subject : ";
    cin>>name;

    cout<<"accumulated score : ";
    cin>>hw;
    
    cout<<"full accumulated score : ";
    cin>>hwFull;

    cout<<"midterm scores : ";
    cin>>mid;

    cout<<"full midterm scores : ";
    cin>>midFull;

    cout<<"final score : ";
    cin>>finalFull;

    int current = hw + mid;

    cout<<"\n--- results of grade analysis ---\n";

    cout<<"วิชา : "<<name<<endl;

    cout<<"~ current score ~\n";
    cout<<"accumulated score : "<<hw<<endl;
    cout<<"midterm score : "<<mid<<endl;
    cout<<"total : "<<current<<endl;
    string target;
    cout<<"\nwhat grade do you want? : ";
    cin>>target;
    float targetScore;
    if(target=="A") targetScore=80;
    else if(target=="B+") targetScore=75;
    else if(target=="B") targetScore=70;
    else if(target=="C+") targetScore=65;
    else if(target=="C") targetScore=60;
    else if(target=="D+") targetScore=50;
    else if(target=="D") targetScore=40;
    else{
        cout<<"the grade is incorrect\n";
        return;
    }
    float need = targetScore - current;
    cout<<"the minimum score you should get on your final exam is : "<<need<<"/"<<finalFull<<endl;
    if(need <= 0){
        cout<<"suggest : pass"<<endl;
    }
    else if(need <= finalFull){
        cout<<"suggest : should go on"<<endl;
    }
    else{
        cout<<"suggest : should withdraw course"<<endl;
    }
}
void MenuSystem::gradeMenu(){

    int choice;

    do{

        cout<<"\n--record grade--\n";
        cout<<"1 add subject\n";
        cout<<"2 view subject\n";
        cout<<"3 calculate GPA\n";
        cout<<"4 load data from file\n";
        cout<<"5 back\n";
        cout<<"please select menu : ";
        cin>>choice;

        if(choice==1) add();
        if(choice==2) view();
        if(choice==3) calculateGPA();
        if(choice==4) loadFile();
        cout<<"---------------------\n";
    }while(choice!=5);
}

void MenuSystem::mainMenu(){
    int choice;
    do{
        cout<<"\n---- Grade Planner System ----\n";
        cout<<"1 collect grade information\n";
        cout<<"2 analysis grade\n";
        cout<<"3 leave\n";
        cout<<"please select menu : ";
        cin>>choice;
        if(choice==1) gradeMenu();
        if(choice==2) analyzeGrade();
    }while(choice!=3);
    cout<<"thank you\n";
}

int main(){
    MenuSystem system;
    system.mainMenu();
    return 0;
}
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score) {
    if(score >= 80) return 'A';
    if(score >= 70 && score <= 79) return 'B';
    if(score >= 60 && score <= 69) return 'C';
    if(score >= 50 && score <= 59) return 'D';
    else return 'F';
}

string toUpperStr(string x) {
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades) {
    ifstream source(filename);
    string text;
    char cname[100];
    string cppname;
    int score[3] = {};
    while(getline(source, text)) {
        sscanf(text.c_str(), "%[^:]: %d %d %d", cname, &score[0], &score[1], &score[2]);
        cppname = cname;
        names.push_back(cppname);
        scores.push_back(score[0]+score[1]+score[2]);
        if(score[0]+score[1]+score[2] >= 80) grades.push_back('A');
        else if(70 <= score[0]+score[1]+score[2] && score[0]+score[1]+score[2] <= 79) grades.push_back('B');
        else if(60 <= score[0]+score[1]+score[2] && score[0]+score[1]+score[2] <= 69) grades.push_back('C');
        else if(50 <= score[0]+score[1]+score[2] && score[0]+score[1]+score[2] <= 59) grades.push_back('D'); 
        else grades.push_back('F'); 
    }
}

void getCommand(string& command, string& key) {
    cout << "Please input your command:\n";
    string input;
    getline(cin, input);

    size_t spacePos = input.find(' ');
    if (spacePos != string::npos) {
        command = toUpperStr(input.substr(0, spacePos));
        key = input.substr(spacePos + 1);
    } else {
        command = toUpperStr(input);
        key = "";
    }
}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string key) {
    int match = 0;
    for(size_t i=0; i<names.size(); i++) {
        if(toUpperStr(names[i]) == key) {
            match++;
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
        }
    }
    if(match == 0) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    string grade;
    int match = 0;
    cout << "---------------------------------\n";
    for(size_t i=0; i<grades.size(); i++) {
        grade = grades[i];
        if(grade == key) {
            cout << names[i] << " (" << scores[i] << ")\n";
            match++;
        }
    }
    if(match == 0) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}

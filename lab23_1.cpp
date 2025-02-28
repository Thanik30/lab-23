#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string line;
    
    while(getline(file, line)){
        string name;
        int score1, score2, score3;
        size_t pos = line.find(":");
        
        if(pos != string::npos){
            name = line.substr(0, pos);
            size_t current = pos + 1;
            
            // อ่านคะแนนทั้ง 3 ตัว
            score1 = atoi(line.substr(current).c_str());
            while(current < line.length() && line[current] == ' ') current++;
            while(current < line.length() && line[current] != ' ') current++;
            
            score2 = atoi(line.substr(current).c_str());
            while(current < line.length() && line[current] == ' ') current++;
            while(current < line.length() && line[current] != ' ') current++;
            
            score3 = atoi(line.substr(current).c_str());
            
            names.push_back(name);
            scores.push_back(score1 + score2 + score3);
            grades.push_back(score2grade(score1 + score2 + score3));
        }
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    getline(cin, key);
    while(key[0] == ' ') key.erase(0,1);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "\n---------------------------------\n";
    int found = -1;
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == toUpperStr(key)) found = i;
    }
    
    if(found == -1) cout << "Cannot found.\n";
    else{
        cout << names[found] << "'s score = " << scores[found] << "\n";
        cout << names[found] << "'s grade = " << grades[found] << "\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "\n---------------------------------\n";
    bool found = false;
    for(unsigned int i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
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
            cout << "\n---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
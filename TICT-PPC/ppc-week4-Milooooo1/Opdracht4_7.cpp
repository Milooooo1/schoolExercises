#include <iostream>
#include <vector>
using namespace std;

struct student {
    string name;
    int age;
    vector<int> grades;
    bool pet;
};

struct klas {
    string name;
    vector<struct student> students;
    vector<string> teachers;
};

float averageGradeOfClass(klas k){
    float sumGrades = 0;
    float amountOfGrades = 0;
    for(int i = 0; i < k.students.size(); i++){
        for(int j = 0; j < k.students[i].grades.size(); j++){
            sumGrades += k.students[i].grades[j];
            amountOfGrades++;
        }
    }
    return sumGrades / amountOfGrades;
}

int main(){
    student s1 = {"Milo", 17, {7, 7, 8, 7, 6, 9}, true};
    student s2 = {"Lucas", 18, {9, 6, 6, 5, 7, 6}, true};
    student s3 = {"Sua", 21, {5, 8, 5, 6, 6, 6}, false};
    student s4 = {"Jelle", 19, {6, 6, 5, 7, 4, 9}, false};
    klas k1 = {"T1A", {s1, s2, s3, s4}, {"Jorn, Brian, Leo"}};
    cout << averageGradeOfClass(k1) << endl;
}
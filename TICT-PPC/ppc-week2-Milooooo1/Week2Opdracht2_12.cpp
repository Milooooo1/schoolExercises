#include <iostream>
#include <vector>
using namespace std;

string reverse(string s){
    char temp;
    for(int i = 0; i < int(s.length() >> 1); i++){
        temp = s[i];
        s[i] = s[s.length() - (i+1)];
        s[s.length() - (i+1)] = temp;
    }
    return s; 
}

bool isPalindroom(string s){
    for(int i = 0; i < int(s.length() >> 1); i++){
        if(s[i] != s[s.length() - i - 1]){
            return false;
        }
    }
    return true;
}

int main(){
    cout << reverse("lepel") << endl;
    string palindroom = "fiets";
    cout << isPalindroom(palindroom) << endl;
}

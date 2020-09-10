#include <fstream>
#include <string>
using namespace std;

void compress(string src_filename, string dest_filename){
    ifstream src(src_filename);
    string line;
    ofstream dest;
    dest.open(dest_filename);

    if(src.is_open()){
        while(getline(src, line)){
            for(unsigned i = 0; i < line.size(); i++){
                if(line[i] == '\t' || (line[i] == ' ' && !isalpha(line[i+1])) || (line[i] == ' ' && !isalpha(line[i-1])) || line[i] == EOF){
                    continue;
                }
                dest << line[i];
            }
            if(line.size() > 2){
                dest << '\n';
            }
        }
        src.close();
    }
    dest.close();
}

int main(){
    compress("opdracht4_5.txt","opdracht4_5-out.txt");
}

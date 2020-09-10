#include <iostream>
#include <string>

std::string translate(std::string line, std::string argument){
	std::string result = ""; // implementeer dit
	if(argument == "CAPITALIZE"){
		for(int i = 0; i < line.size(); i++){
		    if(line[i] == ' '){
			continue;
		    }
		    line[i] = line[i] - 32;
		}
		result = line;
	} else if (argument == "SHIFT"){
		for(int i = 0; line[i] != '\0'; i++){
		char ch = line[i];
		   if(ch >= 'a' && ch <= 'z'){
			ch = ch + 5;
			if(ch > 'z'){
			    ch = ch - 'z' + 'a' - 1;
			}
		   line[i] = ch;
		   } else if(ch >= 'A' && ch <= 'Z'){
		   	ch = ch + 5;
			if(ch > 'Z'){
			ch = ch - 'Z' + 'A' - 1;
			}
		   line[i] = ch;
		   }
		}
		result = line;
	} else {
		result = "Error invald argument.";
	}
	return result;
}

int main(int argc, char *argv[]){
	std::string line;

	if(argc != 2)
	{ std::cerr << "Deze functie heeft exact 1 argument nodig" << std::endl;
    		return -1; }

	while(std::getline(std::cin, line)){ 
		std::cout << translate(line, argv[1]) << std::endl; } 

  return 0;
}

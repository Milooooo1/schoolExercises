#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <string>

int main( int argc, char *argv[] ){
	
	std::map<std::string, int> top10words;
	std::vector<std::array<int, 2>> charCount;
	int numberOfLines = 0;
	std::string s = "";
	char c;
	
	for(int i = 0; i < 27; i++){
		charCount.push_back({0,0}); //Fill array with zeroes.
	}
	
	std::ifstream file("wilhelmus.txt", std::fstream::in);
	
	while( file >> std::noskipws >> c ){
		c = std::tolower(c);
		if(std::isalpha(c)){
			charCount[int(c) - 96][1]++; 				//Add one to the character which has been found
			charCount[int(c) - 96][0] = (int(c) - 97);  //Save the character itself
			s += c;
		} else {
			if(s == ""){
				
			} else {
				charCount[27][1]++; 						//Increase the special character counter
				top10words[s]++;				
				s="";
			}
		}
		if(c == '\n'){
			numberOfLines++;
		}
		// chars.push_back(c);								//Add the char to the chars vector
	}
	
	int sum = 0;
	char a = 'a';
	std::cout << "\nSorted by alphabetical order:\n";
	for(int i = 1; i < 27; i++){
		std::cout << charCount[i][1] << " \t" << char(charCount[i][0] + 97) << "'s found.\n";
		sum += charCount[i][1];
		a++;
	}
	
	std::sort(charCount.begin(), charCount.end(), [](std::array<int, 2> &x, std::array<int, 2> &y)-> bool{
		return x[1] > y[1];
	}); //Sort the array on amount of the characters have been found.
	
	std::cout << "\nSorted by number of occurance:\n";
	std::for_each(charCount.begin(), charCount.end() - 1, [](std::array<int, 2> &x)-> void{
		std::cout << x[1] << " \t" << char(x[0] + 97) << "'s found.\n";
	});
	std::cout << "\n\n";
	
	//Make a vector of all the pairs stored in the map
	std::vector<std::pair<std::string, int>> pairs;
	for(auto i = top10words.begin(); i != top10words.end(); i++){
		pairs.push_back(*i);
	}
	//Sort the vector of pairs.
	std::sort(pairs.begin(), pairs.end(), [](std::pair<std::string, int> &x, std::pair<std::string, int> &y)->bool{
		return x.second > y.second;
	});
	//Print the first 10 of the vector of pairs.
	int i = 1;
	for(auto ptr = pairs.begin(); ptr < (pairs.begin()+10); ptr++){
		std::cout << i << ".\t" << ptr->first << " \toccurs " << ptr->second << " amount of times.\n";
		i++;
	}	
	std::cout << "\n\nThe file contains: " << numberOfLines << " lines\n";
	std::cout << "Total amount of alphabetic characters: " << sum << "\n";
	std::cout << "Total amount of characters: " << (sum + charCount[27][1]) << "\n";
	std::cout << "\nTerminating application\n";
	file.close();
	return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

/**
Output Codes:
0 - Process was successfully executed.
1 - No configuration file provided / Configuration file not found.
2 - Error while processing the configuration file.
**/

std::string rewrite(std::string input, const std::map<char, std::string>& rules){
  std::string output = "";

    for(auto character : input){
      auto iterator = rules.find(character);

      if(iterator != rules.end()){
        output += iterator->second;
      }
      else{
        output += character;
      }
    }

  return output;
}

int main(int argc, char *argv[]){
  if(argc == 2){
    // Get path to JSON file.
    string path = argv[1];

    ifstream jFile(path);

    if(jFile.fail()){
      cout << "No file was found at \"" << path << "\".\n";
      return 1;
    }

    // TODO: I need to check if the cpp json library throws an error if the provided json file has any syntax errors.

    json lSystem;
    jFile >> lSystem;

    std::map<char, std::string> productionRules;

    // Taking the production rules from the JSON object and storing them in a map.
    for(json::iterator it = lSystem["language"]["prules"].begin(); it != lSystem["language"]["prules"].end(); ++it) {
      productionRules[( it.key() )[0]] = it.value();
    }

    // Retrieving the iteration count from the configuration file.
    try{
      // Setting output string to the axiom.
      std::string output = lSystem["language"]["axiom"].get<std::string>();

      if(output.length() == 0){
        std::cout << "L-systems cannot have an empty axiom.\n";
        return 2;
      }

      int iterations = lSystem["language"]["iterations"].get<int>();

      if(iterations <= 0){
        std::cout << "iterations = " << iterations << ". Iteration count cannot be less than 1.";
        return 2;
      }

      // Executing the rewrite rules.
      for(int i = 0; i < iterations; ++i){
        output = rewrite(output, productionRules);
      }

      std::cout << "Output:\n" << output << std::endl;
    }
    catch(nlohmann::detail::type_error exception){
      std::cout << "An error occured while processing the configuration file:\n" << exception.what() << std::endl;
      return 2;
    }
  }
  else{
    cout << "This program needs to be called as follows: lsystem <path to JSON file>.\n";
    return 1;
  }

  return 0;
}

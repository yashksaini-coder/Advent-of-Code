# include <iostream>
# include <fstream>
# include <vector>
# include <string>

int main(int argc, char* argv[]){
  /** 
  Input:- A text file with all the dials shit position noted.

  Key points:- 
  - Dial starts at 50 
  - Keep track of how many times we hit 0

  Approach:-
  - two positions of dial right and left
  - If dial moves right a number of dials it represented as `R4`
  - similarly if we it moves left a number of dials it's represented as `L6`.
  - The password for the safe is the number of times the L position shifts the dial to 0.
  
  Output:- Sum of all Number of times the dial was shifted to 0.
  **/
 
  if (argc !=2 ){
    std::cerr << "Input the file please: " << argv[0] << "\n";
    return 1;

  }
  std::ifstream in(argv[1]);

  if(!in){
    std::cerr << "Unable to open" << argv[1] << "\n";
    return 1;
  }

  /* ----- Reading all the files in a vector array ----- */

  std::vector<std::string> dials;
  std::string line;
  while (std::getline(in, line))
    if(!line.empty()) dials.push_back(line);

  /* ----- Using for loop to calculate the password -----*/
  int startAt = 50;
  int hits = 0;
  
  // const int n = sizeof(rotations)/sizeof(rotations[0]);
  
  for( std::size_t i = 0; i < dials.size(); i++) {

    char direction = dials[i][0];
    int dist = std::stoi(dials[i].substr(1));

    if(direction  == 'L'){
      startAt = (startAt - dist + 100) % 100;
    } else {
      startAt = (startAt + dist) % 100;
    }

    if (startAt == 0) ++hits;
  }

  std::cout << "Password is:- " << hits << "\n";
  return 0;
}

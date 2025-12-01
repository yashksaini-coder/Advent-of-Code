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
  - The password for the safe now is the number of times the dial touched 0 during rotation or stopped to 0.
  - Therefore now the answer will be the actual sum of times the dial was at definite 0 and when it touched the 0th position.
  - Checking the direction 
  Output:- Sum of all Number of times the dial points to 0 and then when it touched the 0.
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
  int currAt = 50;
  int hits = 0;
  
  // const int n = sizeof(rotations)/sizeof(rotations[0]);
  
  for( std::size_t i = 0; i < dials.size(); i++) {

    char direction = dials[i][0];
    int dist = std::stoi(dials[i].substr(1));

    int delta = (direction == 'L') ? -1 : 1;
    
    for( int step = 0; step < dist; ++step){
      // Parsing single step and checking if it lands at 0 and updated the sum
        currAt = (currAt + delta + 100 ) % 100;
        if (currAt == 0) ++hits;
      }
  }

  std::cout << "Password is:- " << hits << "\n";
  return 0;
}

//
//  extractMaze.cpp
//  CPP_EX1
//  Created by othman wattad on 26.03.19.
//

/*
 notes 3.4.19
 TODO:
 can't get current directory, other than that, everything is up to date
 */

#include "extractMaze.h"


void Extractor::createMaze(){
    if(!(MAX_STEPS && NUM_COLS && NUM_ROWS)){
        std::cerr<<"maze construction error"<<std::endl;
        everyThingIsOkay = false;
        return;
    }
    mazeMatrix = new char*[NUM_COLS];
    int counter = 0;
    for(int i=0; i<NUM_COLS;i++){
        mazeMatrix[i] = new char[NUM_ROWS];
        for(int j=0;j<NUM_ROWS;j++){
            mazeMatrix[i][j] = ' ';
            counter++;
        }
    }
    std::cout<<"created maze-matrix"<<std::endl;
}

void Extractor::readFile(const std::string& fileName){
    //with the given path create the matrix and extract relevant info.
    std::string line;
    if(fileName[0] == '/'){
        std::cout<<"abs path was given (intput)"<<std::endl;
    }else{
        std::cout<<"current path was given"<<std::endl;
        // change the fileName to include the current path ... can't find the right path atm
        std::cerr<<"haven't implemented this yet"<<std::endl;
        everyThingIsOkay = false;
        return;
    }
    
    std::ifstream fin(fileName);
    
    if (fin.is_open()){
        int lineCounter = 1;
        while(lineCounter < 5){    //first 4 lines (before reading the maze)
            std::getline(fin, line);
            switch(lineCounter){
                case 2:
                    checkLine(line, "maxsteps",lineCounter);
                    break;
                case 3:
                    checkLine(line, "rows",lineCounter);
                    break;
                case 4:
                    checkLine(line, "cols",lineCounter);
                    break;
            }
            lineCounter++;
        }
        if(!everyThingIsOkay)
            return;    // can't create a matrix, if the input file is corrupt
        
        createMaze();
        int rowCounter = 0, dollarCounter=0,atCounter=0,colCounter=0;
        char currentChar;
        while(std::getline(fin, line)){
            //iterate each line and insert it to the matrix (within it's bounds)
            for(size_t i = 0; i<line.length();i++){
                if((int)i >= NUM_COLS)
                    break;  //ignore chars beyond given cols
                currentChar = line[i];
                if((currentChar == '\r' && i==line.length()-1) || currentChar == '\n'){
                    continue;   //ignore new_line or \r at the end of the line
                }else if(currentChar == 9){
                    std::cerr<<"Wrong character in maze: TAB in row "<<lineCounter<<", col "<<i<<std::endl;
                    everyThingIsOkay=false;
                    //                    return;
                }else if(!(currentChar == '#'||currentChar == ' '||
                           currentChar == '@'||currentChar == '$')){
                    //forbiden chars
                    // \r would be catched here (if it's in the middle of the line)
                    std::cerr<<"Wrong character in maze: "<<currentChar<<" in row "<<lineCounter<<",  col "<<(i+1)<<std::endl;
                    everyThingIsOkay=false;
                    //                    return;
                }else{
                    if(currentChar == '@'){
                        atCounter++;
                        if(atCounter > 1){
                            std::cerr<<"More than one @ in maze"<<std::endl;
                            everyThingIsOkay=false;
                            //                            return;
                        }
                    }else if(currentChar == '$'){
                        dollarCounter++;
                        if(dollarCounter > 1){
                            std::cerr<<"More than one $ in maze"<<std::endl;
                            everyThingIsOkay=false;
                            //                            return;
                        }
                    }
                    // add to mazeMatrix
                    mazeMatrix[colCounter][rowCounter] = currentChar;
                    colCounter++;
                }
            }
            colCounter = 0;    //new line, start from the start
            rowCounter++;
            lineCounter++;
            if(rowCounter>=NUM_ROWS)
                break;  //ignore chars beyond given rows
        }
        fin.close();
        
        bool errorFound = false;
        
        if(atCounter == 0){
            std::cerr<<"Missing @ in maze"<<std::endl;
            errorFound = true;
        }
        if(dollarCounter == 0){
            std::cerr<<"Missing $ in maze"<<std::endl;
            errorFound = true;
        }
        if(errorFound){
            everyThingIsOkay=false;
            return;
        }
    }else
        std::cerr <<"Command line argument for maze: "<< fileName <<" doesn't lead to a maze file or leads to a file that cannot be opened"<<std::endl;
};

void Extractor::writeFile(const std::string& fileName){
    
    if(fileName[0] == '/'){
        std::cout<<"abs path was given (output)"<<std::endl;
    }else{
        std::cout<<"current path was given"<<std::endl;
        // change the fileName to include the current path ... can't find the right path atm
        std::cerr<<"haven't implemented this yet"<<std::endl;
        everyThingIsOkay = false;
        return;
    }
    
    if(fileExists(fileName)){
        std::cerr<<"Command line argument for output file: "<<fileName<<" points to a bad path or to a file that already exists"<<std::endl;
        everyThingIsOkay = false;
        return;
    }
    
    std::ofstream fin(fileName);  //create file
    
    if(fin.is_open()){}else{
        std::cerr<<"Command line argument for output file: "<<fileName<<" points to a bad path or to a file that already exists"<<std::endl;
    }
    
    
    //  std::ofstream fin(fileExists);
}

bool Extractor::checkLine(const std::string line, std::string compareWith, int lineNum){
    //check line's validity and extract the relevant information
    std::string tmpLine = line;
    int intValue = 0;
    //remove whitespace
    
    
    if(!checkWordSpaces(tmpLine)){  //stop if a word has a space within it
        mazeInputError(line, lineNum);
        everyThingIsOkay = false;
        std::cerr<<"error checkLine 3"<<std::endl;
        return false;
    }
    
    tmpLine.erase(remove_if(tmpLine.begin(), tmpLine.end(), isspace), tmpLine.end());
    
    std::string::size_type delimiter_pos = tmpLine.find('=');
    std::string name = tmpLine.substr(0,delimiter_pos);    //name=steps||rows||cols
    std::string value = tmpLine.substr(delimiter_pos+1);   //value has to be an int
    
    if(!is_number(value)){
        //check if value is a number
        mazeInputError(line, lineNum);
        everyThingIsOkay = false;
        std::cerr<<"error checkLine 1"<<std::endl;
        return false;
    }
    
    try{
        //convert value to int
        intValue = std::stoi(value);
    }
    catch (std::invalid_argument const &e){
        mazeInputError(line, lineNum);
        everyThingIsOkay = false;
        std::cerr<<"error checkLine 2"<<std::endl;
        return false;
    }
    
    std::transform(name.begin(), name.end(), name.begin(), tolower);    //convert name to lower case
    
    if(name.compare(compareWith)){
        mazeInputError(line, lineNum);
        everyThingIsOkay = false;
        std::cerr<<"error checkLine 3"<<std::endl;
        return false;
    }
    //everything checks out
    
    if(!name.compare("maxsteps"))
        MAX_STEPS = intValue;
    else if (!name.compare("rows"))
        NUM_ROWS = intValue;
    else if (!name.compare("cols"))
        NUM_COLS = intValue;
    return true;
}

void Extractor::printMAze(){
    if(!everyThingIsOkay)
        return;
    for(int j=0; j<NUM_ROWS;j++){
        for(int i=0; i<NUM_COLS;i++){
            std::cout<<mazeMatrix[i][j];
        }
        std::cout<<std::endl;
    }
}

void mazeInputError(const std::string line, int lineNum){
    std::string errorName;
    switch (lineNum) {
        case 2:
            errorName = "MaxSteps";
            break;
        case 3:
            errorName = "Rows";
            break;
        case 4:
            errorName = "Cols";
            break;
    }
    std::cerr << "expected in line "<<lineNum<<" - "<< errorName <<" = <num>" << '\n'<<
    "got: "<<line<<std::endl;
}

bool is_number(const std::string& s){
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool checkWordSpaces(std::string line){
    //check for any paces within words
    bool updateCounter = false;
    int counter = 0;  //count the number of occurunces where a new word starts.
    for(size_t i = 0; i< line.length();i++){
        if(counter == 3)
            return false;  // input is allowed to have a max length of 3
        if(line[i] == ' '){
            if(updateCounter){
                counter++;  // started new word
                updateCounter=false;
            }
            continue;
        }
        updateCounter = true;
    }
    return true;
}

bool fileExists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

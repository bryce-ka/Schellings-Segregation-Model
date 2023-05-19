/* Function producing output from Schelling's Segregation Model
 *
 * Time spent: 12 hours
 *
 * Authors: Paige Johnson, Bryce Anthony
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int* fileToArray(int row, int col){
    /* Helper function that takes file amd creates array
   Parameters:
       row - number of rows in array
       col - number of columns
   Returns:
       array2- array of size row * col
    */
    int* array2 = (int*) malloc(sizeof(int) * row * col);
    if (array2 == NULL) {
    printf("Bad malloc error\n");
    exit(3);
    }

    for (int i = 0; i < row; i++) {  // for each row i
        for (int j = 0; j < col; j++) { // iterate over each column element in row i
            *(array2 + i*col + j) = ' ';
    }
}
    return array2;
}

void printArray(int* array2, int row, int col){
    /* Helper function that prints the array
   Parameters:
        int* array2 - array with agents
       row - number of rows in array
       col - number of columns
   Returns:
       none
    */
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){

            if (*(array2 + i*col + j) == '.') {
             printf("%c", *(array2 + i*col + j));
            }
            else if (*(array2 + i*col + j) == '$') {
             printf("%c", *(array2 + i*col + j));
            }
            else {
             printf(" ");
            }
        }
        printf("\n");
    }
}

void placeAgents(int* array2, FILE* infile, int col, int counter){
    /* Helper function that places agents
   Parameters:
        int* array2 - array with agents
        infile- file to read from
       col - number of columns
       counter - tracks total agents in array
   Returns:
       none
    */
    //pass initMoney as counter
    int rowPlace = 0;
    int colPlace = 0;
    char character;
    int numRead = 2;
    if(counter > 0){
        character = '$';
    }
    else{
        character = '.';
    }
    numRead=fscanf(infile, "%d%d", &rowPlace, &colPlace);
    if(numRead != 2){
        printf("ERROR! User forgot to provide *two* arguements when running the program ./schelling small.txt");
        exit(2);
    }
    *(array2 + rowPlace*col + colPlace) = character;
}

float agentsToMove(int* array2, int x, int y, int col, int row){
    /* Helper function that moves agents
   Parameters:
        int* array2 - array with agents
        x - x coordinate of agent
        y - y coordinate of agent
        row - number of rows
       col - number of columns
   Returns:
       ratio - ratio of agents vs other type of agents
    */
   int rowCount = x-1;
   int colCount = y-1;
   float neighborsMoney = 0.0;
   float neighborsPeriod = 0.0;
   char curPos;
   for(int i = (x-1); i<= (x+1); i++){
        if((i>-1) & (i<row)){
        for(int j = (y-1); j<= (y+1); j++){
            if((j>-1)&(j<col)){
            curPos = *(array2 + i*col + j);

            if((i == x) & (j == y)){
                neighborsMoney = neighborsMoney;
            }
            else if( curPos == 36) {
                neighborsMoney++;
            }
            else if((curPos) == 46) {
                neighborsPeriod++;
            }
            }
            colCount++;

        }
        }
       rowCount++;

   }
    //calculate the satisfaction ratio
    float ratio = 1.0;
    if((neighborsMoney==0)&(neighborsPeriod==0)){
        return ratio;
    }
    if((*(array2 + x*col + y)) == '$'){
        ratio = neighborsMoney / (neighborsMoney + neighborsPeriod);
        return ratio;
    }
    else if((*(array2 + x*col + y)) == '.'){
        ratio = neighborsPeriod / (neighborsMoney + neighborsPeriod);

        return ratio;
    }
    return ratio;
}
int* checkRatio(float satisf, int* array2, int row, int col, int totalAgents){
    /* Helper function that creates flags array
    // and stores location of dissatisfied agents
   Parameters:
        satisf - ratio that agents must meet to be satisfied
        int* array2 - array with agents
        row- number of rows
       col - number of columns
       totalAgents - total number of agents in array
   Returns:
       flags- array with indexs of dissatisfied agents
    */
    int* flags = (int*) malloc(sizeof(int) * (totalAgents + 1));
    if (flags == NULL) {
        printf("Bad malloc error\n");
        exit(3);
    }
    int flagIndex = 0;
    float ratio = 1;
    for(int i=0; i < row; i++){
        for(int j=0; j< col; j++){
            ratio = agentsToMove(array2, i, j, col, row);

            if(ratio < satisf){
                // add agent to array of flags
                flags[flagIndex] = i*col + j;
                flagIndex++;
            }
        }
    }
    flags[flagIndex] = -1;
    return flags;
}
int movingAgents(int* ptr, int index, int sizeArray){
    /* Helper function that places agents
   Parameters:
        ptr- pointer to start of array2
        index- index of agent to be moved
        sizeArray - size of array2
   Returns:
       counter + index - location where agent should be moved
    */
    //move agents to new positions
    int* start = ptr;
    int count = index;
    ptr = (ptr + index);

    int var = *(ptr);

    *ptr = ' ';

    int counter = 0;
        //move this character to next empty space in array
    ptr = ptr + 1;

        for(int i=1; i<sizeArray; i++){
            count = count + 1;
            if(count > (sizeArray -1)){
                ptr = start;
                count = 0;

            }
            if((*ptr == '$') | (*ptr == '.')){

                ptr = ptr + 1;
            }
            else{

                break;
            }
        }

        *ptr = var;


    return counter + index;
}

void schellingModel(char array[], int verbosityLevel){
    /* Final function where all helpers are called
    //produces an array running the schelling model
   Parameters:
        array[] - arg with text file
        verbosityLevel - int determining print statements
   Returns:
       none
    */
    //initialize variables
    FILE* infile;
    int row;
    int col;
    int iterations = 0;
    float satisf = 0;
    int initMoney = 0;
    int initDot = 0;
    int totalAgents=0;
    int sizeArray = 0;
    int numRead;

    //read in file
    infile = fopen(array, "r");
    if(infile == NULL){
        printf("Error: unable to open file");
        exit(1);
    }

    for(int i =0; i<4;i++){
        //line = checkingFile(infile);
        if(i == 0){
            //dimensions read as a line- needs to be split
            numRead = fscanf(infile, "%d%d", &row, &col);
            if(numRead != 2){
                printf("ERROR! User forgot to provide *two* arguements when running the program ./schelling small.txt");
                exit(1);
            }
            sizeArray = (row*col);
        }
        if(i == 1){
            // iterations
            numRead = fscanf(infile, "%d", &iterations);
            if(numRead != 1){
                printf("ERROR! User forgot to provide *two* arguements when running the program ./schelling small.txt");
                exit(1);
            }
        }
        if(i == 2){
            // satisfaction threshold
            numRead = fscanf(infile, "%g", &satisf);
            if(numRead != 1){
                printf("ERROR! User forgot to provide *two* arguements when running the program ./schelling small.txt");
                exit(1);
            }
        }
        if(i == 3){
            //number of cells to be init as $
            numRead = fscanf(infile, "%d", &initMoney);
            if(numRead != 1){
                printf("ERROR! User forgot to provide *two* arguements when running the program ./schelling small.txt");
                exit(1);
            }
        }
            totalAgents = totalAgents+ initMoney;
    }


    //add to 2D array
    int* array2 = fileToArray(row, col);
    while(initMoney > 0){
        placeAgents(array2, infile, col, initMoney);
        initMoney = initMoney - 1;
    }
    numRead = fscanf(infile, "%d", &initDot);
    if(numRead != 1){
        printf("ERROR! User forgot to provide *two* arguements when running the program ./schelling small.txt");
        exit(1);
    }
    totalAgents = totalAgents+ initDot;
    initDot = -1*initDot;
    while(initDot < 0){
        placeAgents(array2, infile, col, initDot);
        initDot = initDot + 1;
    }
    if(verbosityLevel == 2){
        printArray(array2, row, col);
    }
    // run simunlation for given iterations
    for(int j=0; j<iterations;j++){
        int* flags;
        flags = checkRatio(satisf, array2, row, col, totalAgents);

        int index = 0;
        int test = 0;
        while(flags[index] != -1){
            test = movingAgents(&array2[0], flags[index], sizeArray);
            array2[test] = array2[flags[index]];
            array2[flags[index]] = ' ';
            index++;
        }

        if(verbosityLevel == 2){
            printArray(array2, row, col);
            //usleep(200000);
            if(j != iterations-1){
                usleep(200000);
                system("clear");
            }
        }
        free(flags);
    }
    if(verbosityLevel == 1){
        printArray(array2, row, col);
    }
    fclose(infile);
    free(array2);

}

int main(int argc, char* argv[]){
    //char* argv[1] = file name
    //argv[2] = verbosity level
    if(argc != 3){
        printf("too many arguments input");
        exit(1);
    }

    if((*argv[2] != '0') && (*argv[2] != '1') && (*argv[2] != '2')){
        printf("error in args");
        exit(1);
    }

    schellingModel(argv[1], atoi(argv[2]));
    return 0;
}
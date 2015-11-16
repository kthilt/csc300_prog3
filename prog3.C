/*************************************************************************//**
 * @file prog3.C
 *
 * @mainpage Assignment 3
 * 
 * @section course_section Course Information 
 *
 * @author Kevin Hilt
 * 
 * @date April 9, 2014
 * 
 * @par Professor: 
 *         Corwin, Edward
 * 
 * @par Course: 
 *         CSC300 - M001 -  MWTF 10:00AM
 * 
 * @par Location: 
 *         McLaury - 310
 *
 * @section program_section Program Information 
 * 
 * @details This program counts the number (n) of postivie, 32-bit integers 
 * in a text file and then reads them into an dynamically allocated array of
 * size n. Afterward, it dynamically allocates another array of n times the
 * largest specified constant value and uses that table to hash the n values
 * using the function number % table size. Each constant value (of which there
 * are currently 5) is used first with linear probing, and then the used spots
 * are reinitialized to 0 and the hashing is redone using quadratic probing.
 *
 * Since the insert function returns how many tries it took to insert the 
 * current number, this is added to the sum held in an averages array. Once
 * linear and quadratic probing for a given constant have been completed, the
 * average tries for each are computed and stored back in the averages array
 * and the table is reinitialized to 0s before proceeding to the next
 * constant. When all constants have been hashed using both probing methods,
 * a table comparing the averages to the theoretical 1 / (1 - alpha) is printed
 * to the screen before the program exits.
 * 
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      
 *	No special instructions for compiling. The program takes as a command line
 * argument the file that will be used for input.
 * 
 * @par Usage: 
   @verbatim  
   g++ prog3.C
   @endverbatim 
 *
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//Global Constants
//Used for different table sizes
///////////////////////////////////////////////////////////////////////////////

const int NUMBER_OF_CONSTANTS = 5;
const double C[NUMBER_OF_CONSTANTS] = {1.1,1.2,1.5,2,5};
//Put C[] in ascending order in order.
//This is used later when declaring the size of the table,
//since the maximum size needed will then be
//C[NUMBER_OF_CONSTANTS - 1] * n;

///////////////////////////////////////////////////////////////////////////////
//Prototypes
///////////////////////////////////////////////////////////////////////////////

int hash_value(int num, int size);
int insert(int num, int size, int *table, int hash_pos, bool is_linear);

///////////////////////////////////////////////////////////////////////////////
//main()
//This function takes in one additional command line argument after the
//executable: the name of the file that will be used for input. The input file
//should be unique, positive 32-bit integers separated by either spaces
//or newlines.
//
//Assuming there were no command line argument or file errors, main() opens
//the specificed input file and read through getting a count of valid 
//integers (n). It then closes the file and allocates an array of size n
//before reopening the file and putting the integers in this array. main()
//then closes the input file, as it is no longer needed.

//Next, an array of size C[NUMBER_OF_CONSTANTS - 1] is declared, which will
//be the largest array necessary proved that the constants were placed into
//C[] in ascending order as specified above. This array is then reused to
//insert all n numbers into their hash positions using both linear and
//quadratic probing. A count of the averages for each probing method for
//each constant is kept which allows main() to compute the averages
//and finally print these staistics in relation to 1 / (1 - alpha) before
//exiting successfully.
//
//Parameters:
//argc: Number of command line arguments
//argv[]: Array holding the command line arguments
//
//Returns:
//0: Program ran successfully.
//-1: Invalid number of command line arguments
//-2: Error opening input file
//-3: Quadratic probing encountered an infinite loop
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    double alpha;   //Used in priting statistics
    double average[2 * NUMBER_OF_CONSTANTS] = {0};
    ifstream fin;   //Input variable for the file
    int check_insert;   //Number of tries returned by insert (-1 = error)
    int c_size;     //Used for sizes associated with current constant
    int i = 0, j = 0, k = 0, l = 0;      //Iterators
    int n = 0;      //Count of valid numbers in the file
    int num = 0;    //Current number read from input
    int *original;  //Pointer to the array that will hold the file numbers
    int *table;     //Pointer to the array used for hashing  

    if(argc != 2)   //Invalid number of command line arguments
    {
        //Print usage
        cout << "USAGE:\nPlease provide the name of the input text file"
        " as a command line argument after your program name. \nExiting"
        " program.\n";
        return -1;  //Exit with -1 for invalid command line arguments
    }
    
    fin.open(argv[1]);  //Open the specificed input file
    
    if(!fin)
    {
        //Print file error
        cout << "Error opening specified input file " << argv[1] << "\n"
        "Exiting program.\n";
        return -2;  //Exit with -2 for error opening input file
    }
    
    while(fin >> num)   //Read until the end of the file
    {
        if(num > 0 && num < 2147483647) //If num is a valid integer
        {
            n++;    //Increment n
        }
    }
    
    fin.close();    //Close the input file
    
    if(n == 0)
    {
        cout << "Input file was empty.\n";
        return 0;   //Exit successfully
    }
    
    original = new int[n]; //Allocate array of size n to store the values
    fin.open(argv[1]);  //Open the specificed input file again
    
    while(fin >> num)   //Read until the end of the file
    {
        if(num > 0 && num < 2147483647) //If num is a valid integer
        {
            original[i] = num;  //Fill the appropriate spot in original
            i++;    //Increment i
        }
    }
    
    fin.close();    //Close the input file
    
    //Assuming the rules were followed above and C[] is in ascending order
    //Allocate as large of an array as needed
    c_size = C[NUMBER_OF_CONSTANTS - 1] * n;
    table = new int[c_size]();
    
    for(i = 0; i < NUMBER_OF_CONSTANTS; i++)
    {
        c_size = C[i] * n;  //Set the size to the current constant * n
        
        for(l = 1; l > -1; l--)
        {
            for(j = 0; j < n; j++)
            {
                num = hash_value(original[j], c_size); //Get hash value
                //Insert original[i] at the hash position
                check_insert = insert(original[j], c_size, table, num, l);
                
                if(check_insert == -1)
                {
                    cerr << "Infinite loop. Quadratic probing back at "
                         << "initial position.\nForce exiting program.\n";
                         return -3;     //Exit with -3 for failed quadratic
                }
                //Add the number of tries to average[k]
                average[k] += check_insert;       
            }
        
            for(j = 0; j < c_size; j++)
            {
                table[j] = 0;   //Reset the overwritten values to 0
            }
        
            average[k] = average[k] / n;    //Compute average
            k++;    //Increment k so we get the next spot in average[]
        }
    }
    
    delete [] table;    //Free up memory
    
    cout << "factor  linear   quadratic  1/(1-alpha)\n";
    j = 0;
    
    for(i = 0; i < NUMBER_OF_CONSTANTS; i++)
    {
        cout << " " << setprecision(3) << setw(8) << left << fixed << C[i];
        cout << setprecision(3) << setw(10) << left << fixed << average[j];
        j++;    //Go to quadratic average for current constant
        cout << setprecision(3) << setw(12) << left << fixed << average[j];
        c_size = C[i] * n;      //Compute size
        alpha = c_size - n;    //Compute number of open spots
        alpha = (c_size / alpha);   //Compue alpha
        cout << setprecision(3) << fixed << alpha << "\n";
        j++;    //Move to linear average for next constant
    }
         
    return 0;       //Exit sucessfully
}

///////////////////////////////////////////////////////////////////////////////
//hash_value()
//This function takes a passed number and mods it by the passed size, returning
//the result.
//
//Parameters:
//num: The passed number
//size: The size of the table, or C[i] * n
//
//Returns:
//num % size: The hash position in the given table
///////////////////////////////////////////////////////////////////////////////

int hash_value(int num, int size)
{
    return num % size;
}

///////////////////////////////////////////////////////////////////////////////
//insert()
//This function takes in the necessary parameters to put a passed number in
//the passed hash position of the table. If the spot is full, a passed flag
//indicates whether linear or quadratic probing should be used. Once the
//value of table[hash_pos] == 0, insert() writes num at hash_pos and returns
//a count of how many tires it took to insert the number.
//
//Paramters:
//num: The number to be inserted
//size: The size of the talble, or C[i] * n
//table: Pointer to the table where num will be stored
//hash_pos: The first desired input position, calculated by hash_value()
//is_linear: Flag to determine which probing method should be used
//
//Returns:
//count: Sucessful insert after count number of tries
//-1: Quadratic probing encountered an infinite loop. main() terminates.
///////////////////////////////////////////////////////////////////////////////

int insert(int num, int size, int *table, int hash_pos, bool is_linear)
{
    int count = 1;  //Count of how many tries it took to insert num
                    //Having no collision returns 1 try
    int initial_pos = hash_pos;     //Used for quadratic probing
    
    if(table[hash_pos] != 0)    //Collision
    {
        do
        {
            if(is_linear == 1)  //Linear probing
            {
                //Search the next spot, modded by the table size
                hash_pos = (hash_pos + 1) % size;
            }
            
            else    //Quadratic probing
            {
                //Search count^2 spots away, modded by the table size
                hash_pos = (initial_pos + (count * count)) % size;
                
                if(hash_pos == initial_pos)
                {
                    return -1;  //Error - infinite loop
                }
            }
            
            count++;    //Increment count
        }
        while(table[hash_pos] != 0);
    }
    
    table[hash_pos] = num;
    return count;
}


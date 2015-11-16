#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//Global Constants
//Used for different table sizes
///////////////////////////////////////////////////////////////////////////////
const double C1 = 1.5;
const double C2 = 2;
const double C3 = 5;
const double C[3] = {1.5,2,5};
const int NUMBER_OF_CONSTANTS = 3;

int hash_value(int num, int size);
int insert(int num, int size, int *table, int hash_pos, bool is_linear);

int main(int argc, char* argv[])
{
    ifstream fin;   //Input variable for the file
    int averages[6] = {0,0,0,0,0,0};  
    //Averages number of tries to insert In order:
    //c1_l, c1_q, c2_l, c2_q, c3_l, c3_q
    int *c1_l;
    int *c1_q;
    int *c2_l;
    int *c2_q;
    int *c3_l;
    int *c3_q;  //Pointers to the six different hash tables
    int i, j, k, l = 0;      //Iterators
    int n = 0;      //Count of valid numbers in the file
    int num = 0;    //Current number read from input
    int *original;  //Pointer to the array that will hold the file numbers
    //int table[5000000] = {0};   //Table used for hashing
    int *table;     //Pointer to array used for hashing
    double alpha;   //Used in priting statistics
    double average[6] = {0};
    int c_size;     //Current constant * n
    
    int c1_size = C[0] * n;
    int c2_size = C[1] * n;
    int c3_size = C[2] * n;    //Constant * n, typecast to an int
    

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
    
    table = new int[5000000](); //Allocate large table
    
    for(i = 0; i < NUMBER_OF_CONSTANTS; i++)
    {
        alpha = C[i] * n;   //Set the size to the current constant * n
        c_size = (int) alpha;
        
        for(l = 1; l > -1; l--)
        {
            for(j = 0; j < n; j++)
            {
                num = hash_value(original[j], c_size); //Get hash value
                //Insert original[i] at the hash position
                //Add the number of tries to average[k]
                average[k] += insert(original[j], c_size, table, num, l);       
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
    
    //Allocate hash tables, all initialized to 0
    //l is for linear probing and q is for quadratic
    /*c1_l = new int[c1_size]();
    c1_q = new int[c1_size]();
    c2_l = new int[c2_size]();
    c2_q = new int[c2_size]();
    c3_l = new int[c3_size](); 
    c3_q = new int[c3_size]();    
    
    for(i = 0; i < n; i++)  //Hash all the numbers in n
    {
        num = hash_value(original[i], c1_size);  //Get hash value for C1
        //Insert original[i] at the hash position using linear probing
        //Add the number of tries to the appropriate spot in averages[]
        averages[0] += insert(original[i], c1_size, c1_l, num, 1);
        //Do the same for quadratic
        averages[1] += insert(original[i], c1_size, c1_q, num, 0);
        
        //Do the same as above for C2
        num = hash_value(original[i], c2_size);
        averages[2] += insert(original[i], c2_size, c2_l, num, 1);
        averages[3] += insert(original[i], c2_size, c2_q, num, 0);
        
        //Do the same as above for C3
        num = hash_value(original[i], c3_size);
        averages[4] += insert(original[i], c3_size, c3_l, num, 1);
        averages[5] += insert(original[i], c3_size, c3_q, num, 0);
    }
    
    delete [] c1_l;
    delete [] c1_q;
    delete [] c2_l;
    delete [] c2_q;
    delete [] c3_l;
    delete [] c3_q;
    delete [] original; //Free up memory
    
    cout << "AVERAGE TRIES FOR INSERT:\n\n"
         << C1 << " * n, linear: " << (averages[0] / (double)n) << "\n"
         << C1 << " * n, quadratic: " << (averages[1] / (double)n) << "\n"
         << C2 << " * n, linear: " << (averages[2] / (double)n) << "\n"
         << C2 << " * n, quadratic: " << (averages[3] / (double)n) << "\n"
         << C3 << " * n, linear: " << (averages[4] / (double)n) << "\n"
         << C3 << " * n, quadratic: " << (averages[5] / (double)n) << "\n";
    */
    
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

int hash_value(int num, int size)
{
    return num % size;
}

int insert(int num, int size, int *table, int hash_pos, bool is_linear)
{
    int count = 1;  //Count of how many tries it took to insert num
                    //Having no collision returns 1 try
    
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
                hash_pos = (hash_pos + (count * count)) % size;
            }
            
            count++;    //Increment count
        }
        while(table[hash_pos] != 0);
    }
    //Since all tables are larger than the number of possible values
    //to be inserted, we never run into a full table
    
    table[hash_pos] = num;
    return count;
}


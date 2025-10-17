// Banker's Algorithm Implementation in C++
// This program reads the available resources, maximum demand, and allocation matrices from a file.
// Devon Morris

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    // Check for correct number of command line arguments
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    }

    ifstream infile(argv[1]); // open input file

    // Check if file opened successfully
    if (!infile)
    {
        cerr << "Error opening file: " << argv[1] << endl;
        return -1;
    }

    const int p = 5; // Number of processes
    const int r = 3; // Number of resources

    int avail[r];    // Available Resources
    int max[p][r];   // MAX Matrix
    int alloc[p][r]; // Allocation Matrix

    // Reading Allocation Matrix
    for (size_t i = 0; i < p; i++)
        for (size_t j = 0; j < r; j++)
            infile >> alloc[i][j];

    // Reading MAX Matrix
    for (size_t i = 0; i < p; i++)
        for (size_t j = 0; j < r; j++)
            infile >> max[i][j];

    // Reading Available Resources
    for (size_t i = 0; i < r; i++)
        infile >> avail[i];

    infile.close();

    int need[p][r]; // Need Matrix

    // Calculating Need of each P
    for (size_t i = 0; i < p; i++)
        for (size_t j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j]; // Need = MAX - Allocation

    bool finish[p] = {0}; // To track if process is finished
    int safeSeq[p];       // To store the safe sequence
    int work[r];          // Work array to simulate resource allocation

    // Initialize work as available
    for (size_t i = 0; i < r; i++)
        work[i] = avail[i];

    size_t count = 0; // Count of processes finished

    // Find a safe sequence
    while (count < p)
    {
        bool found = false; // To check if a process was found in this iteration

        // Check each process
        for (size_t i = 0; i < p; i++)
        {
            if (finish[i] == 0) // If process is not finished
            {
                int j;
                for (j = 0; j < r; j++)       // Check if needs can be met
                    if (need[i][j] > work[j]) // Break if need of p is more than work
                        break;
                if (j == r) // if all needs of p are meet
                {
                    for (size_t k = 0; k < r; k++) // Add allocated resources of p to work
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i; // Add process to safe sequence
                    finish[i] = 1;        // Mark process as finished
                    found = true;         // Mark process as found
                }
            }
        }

        // If no process was found in this iteration, system is not in safe state
        if (found == false)
        {
            cout << "System is not in safe state";
            return 0;
        }
    }

    cout << "System is in safe state.\nSafe sequence is: ";
    for (size_t i = 0; i < p; i++)
        cout << "P" << safeSeq[i] << (i < p - 1 ? " -> " : "\n");

    return 0;
}

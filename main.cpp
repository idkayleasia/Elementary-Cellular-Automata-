#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>
#include <limits>   // For clearing input buffer

using namespace std;



class CellularAutomaton{
private:
    static const int WIDTH = 10;
public:
    int cells[WIDTH] = {};
    int generation;

    //random ruleset, can make up any ruleset or use existing rules(ex.Wolfram's)
    int ruleset[8] = {0, 0, 1, 1, 0, 1, 0, 1};

    CellularAutomaton(){
        //initialize first generation
        for(int & cell : cells){
            cell = rand() % 2; //randomly assign each element 0's and 1's
        }
        generation = 0;
    }
    ~CellularAutomaton() = default;

    void PrintState() {
        cout << "Generation: " << generation << ": ";
        for(int & cell : cells){
            cout << cell << " ";
        }
        cout << endl;
    }

    void ClearInputBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //return specific index of ruleset based on combination of 3 bit number
    int rules(int ruleIndex){
        return ruleset[ruleIndex];
    }

    //generate next generation
    void Generate(){
        //create new array
        int nextGeneration[WIDTH] = {};

        //assign each cell in the next generation a value based on the 3 bit number states
        for(int i = 0; i < WIDTH; i ++){
            int leftNeighbor, currentCell, rightNeighbor;

            //account for first and last cell, which only has two neighbors
            if (i == 0 || i == WIDTH - 1){
                nextGeneration[i] = 0;
            }else{
                leftNeighbor = cells[i - 1];
                currentCell = cells[i];
                rightNeighbor = cells[i + 1];

                int ruleIndex = (leftNeighbor * 4) + (currentCell * 2) + (rightNeighbor); //convert using Positional Notation Method
                nextGeneration[i] = rules(ruleIndex);
            }
        }
        //make cells equal the new(current) generation
        for(int i = 0; i < WIDTH; i++){
            cells[i] = nextGeneration[i];
        }
        generation++;
    }
};

int main() {
    srand ( time(NULL) );
    CellularAutomaton OneDimensionalAutomaton;

    char userInput;

    do {
        OneDimensionalAutomaton.PrintState();

        cout << "Press enter to generate the next generation, or enter 'Q'/'q' to quit" << endl;
        cin.get(userInput);

        // Clear input buffer to handle Enter key press
        OneDimensionalAutomaton.ClearInputBuffer();

        if(userInput == '\n'){
            OneDimensionalAutomaton.Generate();
        }

    } while (userInput != 'q' && userInput != 'Q');

    return 0;
}

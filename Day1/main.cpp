#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <numeric>
#include <cstdint>

#define WINDOW_SIZE 3

int main(int argc, char **argv) {
    // Read the input file into a buffer
    std::ifstream file(argv[argc - 1]);
    uint32_t prev = INT_MAX; //Set this to be max possible value so comparison to check if the value increases is ok
    uint32_t current; // Set this to an integer
    uint32_t increases_indiv = 0; // Counter for if the individual depths increase (Part 1)
    uint32_t increases_window = 0; // Counter for if the window depths increase (Part 2)
    std::array<uint32_t, WINDOW_SIZE> window; // std::array to hold a window of values
    window.fill(-1); // fill with -1 to ensure that comparisons to check we have a valid window is ok
    auto window_old = window; // Create an object to hold the old version of the window so that comparisons can be done easily

    if(!file.is_open()){
        std::cout << "Error opening file." << std::endl;
        return EXIT_FAILURE;
    }

    // This for loop goes along the read file and pulls each line into a variable as a string
    for ( std::string line; std::getline(file, line); ) {
        // This converts the string to an integer and puts it into the variable
        current = std::stoi(line);
        // Check if the values have increases
        if (prev < current){
            increases_indiv++;
        }
        // Now that we have done our checks we can say that the old value is the current value in preperation for the next loop itteration
        prev = current;
        // This does a shift left of the array by 1 element (keeps the last value the same)
        std::shift_left(window.begin(), window.end(), 1);
        // This sets the last element in the array to be the value we read from the file
        window.back() = current;
        // This checks to see if -1 is in the old window, if it is, it means we have not read enough values and cannot do comparisons
        if (std::find(window_old.begin(), window_old.end(), -1) == std::end(window_old)){
            // This does a sum of all the elements in each of the arrays and checks the difference in them
            if (std::reduce(window.begin(), window.end()) > std::reduce(window_old.begin(), window_old.end())){
                increases_window++;
            }
        }
        // Now we have done our calculations, we set our old window to be the current one in preperation for the next loop itteraration
        window_old = window;
    }
    file.close();
    std::cout << "Number of increases is: " << increases_indiv << std::endl;
    std::cout << "Number of window increases is: " << increases_window << std::endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <cstdint>

int main(int argc, char **argv) {
    // Read the input file into a buffer
    std::ifstream file(argv[argc - 1]);

    // These values must all be initialised to 0, although it is possible for aim and depth to be negative
    int depth = 0;
    uint32_t horizontal_position = 0;
    int depth_p2 = 0;
    int aim = 0;

    //Check if the file has been opened successfully
    if(!file.is_open()){
        std::cout << "Error opening file." << std::endl;
        return EXIT_FAILURE;
    }

    //This reads the file
    for ( std::string line; std::getline(file, line); ) {
        // Extract the first part of the string (before the space) this is the direction
        auto direction = line.substr(0,line.find(' '));
        // Extract the second part of the string (after the space) and then convert that to an int
        auto value = std::stoi(line.substr(line.find(' ') + 1));
        // This ifchain checks the value of the direction and performs calculations based on that
        if (direction == "forward"){
            horizontal_position += value;
            depth_p2 += aim * value;
        }
        else if (direction == "up"){
            depth -= value;
            aim -= value;
        }
        else if (direction == "down"){
            depth += value;
            aim += value;
        }
        // If there is a junk value in the string, we should exit with unexpected results
        else {
            std::cout << "Invalid direction provided: " << direction << std::endl;
            return EXIT_FAILURE;
        }
    }

    // close the file as we are now done with it
    file.close();
    std::cout << "Total depth is: " << depth << std::endl;
    std::cout << "Total horizontal position is: " << horizontal_position << std::endl;
    std::cout << "The aim is: " << aim << std::endl;
    std::cout << "The part 2 depth is: " << depth_p2 << std::endl;
    std::cout << "The product of these values is: " << depth * horizontal_position << std::endl;
    std::cout << "The product of these values in p2 is: " << depth_p2 * horizontal_position << std::endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>

int main(int argc, char **argv) {
    // Read the input file into a buffer
    std::ifstream file(argv[argc - 1]);

    if(!file.is_open()){
        std::cout << "Error opening file." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<int> net_values;
    std::vector<std::string> data_oxygen;
    std::vector<std::string> data_co2;
    uint8_t vec_counter;

    for ( std::string line; std::getline(file, line); ) {
        vec_counter = 0;
        data_oxygen.push_back(line);
        data_co2.push_back(line);
        for (auto c : line) {
            int val = std::stoi(std::string(1, c));
            if (net_values.size() < vec_counter + 1){
                net_values.push_back(0);
            }
            if (val == 1) {
                net_values.at(vec_counter)++;
            }
            else {
                net_values.at(vec_counter)--;
            }
            vec_counter++;
        }
    }
    file.close();
    std::bitset<32> gamma;
    std::bitset<32> epsilon;
    for (auto val : net_values){
        if (val < 0) {
            gamma[vec_counter - 1] = 0;
            epsilon[vec_counter - 1] = 1;
        }
        else {
            gamma[vec_counter - 1] = 1;
            epsilon[vec_counter - 1] = 0;
        }
        vec_counter--;
    }

    for (int i = 0; i < data_oxygen.front().size(); i++){
        std::vector<int> zero_pos;
        std::vector<int> one_pos;
        int itter = 0;
        for (auto str : data_oxygen){
            if (str.at(i) == '1'){
                one_pos.push_back(itter);
            }
            else {
                zero_pos.push_back(itter);
            }
            itter++;
        }
        if (zero_pos.size() > one_pos.size()){
            while(!one_pos.empty()){
                data_oxygen.erase(data_oxygen.begin() + one_pos.back());
                one_pos.pop_back();
                if (data_oxygen.size() == 1){
                    break;
                }
            }
        }
        else{
            while(!zero_pos.empty()){
                data_oxygen.erase(data_oxygen.begin() + zero_pos.back());
                zero_pos.pop_back();
                if (data_oxygen.size() == 1){
                    break;
                }
            }
        }
        one_pos.clear();
        zero_pos.clear();
        itter = 0;
        for (auto str : data_co2){
            if (str.at(i) == '1'){
                one_pos.push_back(itter);
            }
            else {
                zero_pos.push_back(itter);
            }
            itter++;
        }
        if (zero_pos.size() <= one_pos.size()){
            while(!one_pos.empty()){
                data_co2.erase(data_co2.begin() + one_pos.back());
                one_pos.pop_back();
                if (data_co2.size() == 1){
                    break;
                }
            }
        }
        else{
            while(!zero_pos.empty()){
                data_co2.erase(data_co2.begin() + zero_pos.back());
                zero_pos.pop_back();
                if (data_co2.size() == 1){
                    break;
                }
            }
        }
    }

    std::cout << "The power consumption is: " << gamma.to_ulong() * epsilon.to_ulong() << std::endl;
    std::cout << "Gamma is: " << gamma.to_ulong() << " which is: " << gamma.to_string() << std::endl;
    std::cout << "Epsilon is: " << epsilon.to_ulong() << " which is: " << epsilon.to_string() << std::endl;
    std::cout << "Oxygen Value is: " << data_oxygen.front() << " which is: " << std::stoi(data_oxygen.front(), nullptr, 2) << std::endl;
    std::cout << "CO2 Value is: " << data_co2.front() << " which is: " << std::stoi(data_co2.front(), nullptr, 2) << std::endl;
    std::cout << "Life support rating is: " << std::stoi(data_oxygen.front(), nullptr, 2) * std::stoi(data_co2.front(), nullptr, 2) << std::endl;
    return 0;
}

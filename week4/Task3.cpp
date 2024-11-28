#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

int main() {
    // Step 1: Initialize the HMI control states
    std::vector<std::string> controlStates = {
        "visible", "invisible", "disabled", "visible", "visible", "invisible", "disabled"
    };
    
    std::cout << "Initial Control States:\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Step 2: Manipulate Control States
    
    // Create a backup of the control list using std::copy
    std::vector<std::string> backupControlStates(controlStates.size());
    std::copy(controlStates.begin(), controlStates.end(), backupControlStates.begin());
    
    std::cout << "Backup Control States:\n";
    for (const auto& state : backupControlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Use std::fill to set all states to "disabled" temporarily
    std::fill(controlStates.begin(), controlStates.end(), "disabled");
    
    std::cout << "After std::fill to disable all controls:\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Use std::generate to generate random states ("visible", "invisible", "disabled") for testing
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);  // Generates random number between 0 and 2

    auto randomState = [&dist, &gen]() {
        switch (dist(gen)) {
            case 0: return "visible";
            case 1: return "invisible";
            default: return "disabled";
        }
    };

    std::generate(controlStates.begin(), controlStates.end(), randomState);
    
    std::cout << "After std::generate with random states:\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Step 3: Apply Transformations
    
    // Use std::transform to change the state of all sliders to "invisible"
    std::transform(controlStates.begin(), controlStates.end(), controlStates.begin(),
                   [](const std::string& state) {
                       return state == "slider" ? "invisible" : state;
                   });
    
    std::cout << "After std::transform to set sliders to 'invisible':\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Use std::replace to replace "disabled" with "enabled" for testing
    // Use std::replace with std::string instead of C-string literals
    std::replace(controlStates.begin(), controlStates.end(), std::string("disabled"), std::string("enabled"));


    std::cout << "After std::replace to replace 'disabled' with 'enabled':\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Step 4: Other Operations
    
    // Use std::remove_if to filter out invisible controls from the list
    controlStates.erase(std::remove_if(controlStates.begin(), controlStates.end(),
                                       [](const std::string& state) {
                                           return state == "invisible";
                                       }),
                        controlStates.end());
    
    std::cout << "After std::remove_if to remove 'invisible' controls:\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Use std::reverse to reverse the control order (e.g., for a debug layout)
    std::reverse(controlStates.begin(), controlStates.end());
    
    std::cout << "After std::reverse to reverse control order:\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    // Use std::partition to group visible controls together
    auto partitionPoint = std::partition(controlStates.begin(), controlStates.end(),
                                         [](const std::string& state) {
                                             return state == "visible";
                                         });
    
    std::cout << "After std::partition to group 'visible' controls together:\n";
    for (const auto& state : controlStates) {
        std::cout << state << " ";
    }
    std::cout << "\n\n";

    return 0;
}

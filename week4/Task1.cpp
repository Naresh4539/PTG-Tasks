#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Control {
    int id;               // Unique ID
    std::string type;     // "button" or "slider"
    std::string state;    // "visible", "invisible", "disabled"
};

int main() {
    // Initialize controls
    std::vector<Control> controls = {
        {1, "button", "visible"},
        {2, "slider", "invisible"},
        {3, "button", "disabled"},
        {4, "slider", "visible"},
        {5, "button", "invisible"},
        {6, "slider", "disabled"},
        {7, "button", "visible"},
        {8, "slider", "visible"},
        {9, "button", "disabled"},
        {10, "slider", "invisible"}
    };

    // Step 3: Use STL Algorithms
    // 1. std::for_each: Iterate through all controls and print their details
    std::cout << "All Controls:\n";
    std::for_each(controls.begin(), controls.end(), [](const Control& ctrl) {
        std::cout << "ID: " << ctrl.id << ", Type: " << ctrl.type 
                  << ", State: " << ctrl.state << "\n";
    });

    // 2. std::find: Find a control with a specific ID (e.g., ID 3)
    auto it = std::find_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.id == 3;
    });
    if (it != controls.end()) {
        std::cout << "\nFound control with ID 3: " << it->type << " " << it->state << "\n";
    }

    // 3. std::find_if: Find the first invisible control
    auto invisibleControl = std::find_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "invisible";
    });
    if (invisibleControl != controls.end()) {
        std::cout << "\nFirst invisible control: ID " << invisibleControl->id
                  << ", Type: " << invisibleControl->type << "\n";
    }

    // 4. std::adjacent_find: Check for consecutive controls with the same state
    auto adjacent = std::adjacent_find(controls.begin(), controls.end(), [](const Control& a, const Control& b) {
        return a.state == b.state;
    });
    if (adjacent != controls.end()) {
        std::cout << "\nFound consecutive controls with the same state (ID " 
                  << adjacent->id << " and ID " << (adjacent + 1)->id << ")\n";
    }

    // 5. std::count: Count the number of visible controls
    int visibleCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.state == "visible";
    });
    std::cout << "\nNumber of visible controls: " << visibleCount << "\n";

    // 6. std::count_if: Count sliders that are disabled
    int disabledSlidersCount = std::count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
        return ctrl.type == "slider" && ctrl.state == "disabled";
    });
    std::cout << "\nNumber of disabled sliders: " << disabledSlidersCount << "\n";

    // 7. std::equal: Compare two subranges of controls to check if they are identical
    std::vector<Control> controlsSubset = {
        {1, "button", "visible"},
        {2, "slider", "invisible"}
    };
    bool areEqual = std::equal(controls.begin(), controlsSubset.end(), controlsSubset.begin(), controlsSubset.end(),
        [](const Control& a, const Control& b) {
            return a.id == b.id && a.type == b.type && a.state == b.state;
        });
    std::cout << "\nAre the first two controls identical to the subset? " << (areEqual ? "Yes" : "No") << "\n";

    return 0;
}

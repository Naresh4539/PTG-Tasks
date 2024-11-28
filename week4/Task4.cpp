#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

// Control structure to represent each control's ID and name
struct Control {
    int id;
    std::string name;

    // Default constructor (added to fix the error)
    Control() : id(0), name("") {}

    // Constructor for easy initialization
    Control(int id, const std::string& name) : id(id), name(name) {}

    // Comparator to enable sorting by ID (used in std::sort and std::stable_sort)
    bool operator<(const Control& other) const {
        return id < other.id;
    }
};

int main() {
    // Initialize two vectors of controls, each with IDs and names
    std::vector<Control> controls1 = {
        Control(3, "Speedometer"),
        Control(1, "Tachometer"),
        Control(4, "Fuel Gauge")
    };
    std::vector<Control> controls2 = {
        Control(5, "Temperature Control"),
        Control(2, "Odometer"),
        Control(4, "Fuel Gauge") // Duplicate with controls1
    };

    // Step 1: Sorting the controls by their ID using std::sort
    std::sort(controls1.begin(), controls1.end());
    std::sort(controls2.begin(), controls2.end());

    // Print sorted controls
    std::cout << "Sorted controls1:\n";
    for (const auto& control : controls1) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    std::cout << "\nSorted controls2:\n";
    for (const auto& control : controls2) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    // Step 2: Using std::stable_sort to maintain relative order of controls with the same ID
    std::stable_sort(controls1.begin(), controls1.end(), [](const Control& a, const Control& b) {
        return a.name < b.name;  // Sorting by name if IDs are the same
    });

    std::cout << "\nControls1 after stable_sort (maintain relative order for same IDs):\n";
    for (const auto& control : controls1) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    // Step 3: Binary Search (using lower_bound and upper_bound)
    auto it = std::lower_bound(controls1.begin(), controls1.end(), Control(2, ""), 
                               [](const Control& control, const Control& target) {
                                   return control.id < target.id;
                               });
    if (it != controls1.end()) {
        std::cout << "\nFound control with ID 2: " << it->name << "\n";
    } else {
        std::cout << "\nControl with ID 2 not found.\n";
    }

    // Step 4: Merging two sorted lists of controls
    std::vector<Control> mergedControls(controls1.size() + controls2.size());
    std::merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), mergedControls.begin());

    std::cout << "\nMerged controls (after std::merge):\n";
    for (const auto& control : mergedControls) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    // Step 5: Using std::inplace_merge to merge controls within the same vector
    std::vector<Control> inplaceMergedControls = controls1;
    inplaceMergedControls.insert(inplaceMergedControls.end(), controls2.begin(), controls2.end());
    std::inplace_merge(inplaceMergedControls.begin(), inplaceMergedControls.begin() + controls1.size(), inplaceMergedControls.end());

    std::cout << "\nInplace merged controls:\n";
    for (const auto& control : inplaceMergedControls) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    // Step 6: Set Operations (std::set_union and std::set_intersection)
    std::set<Control> set1(controls1.begin(), controls1.end());
    std::set<Control> set2(controls2.begin(), controls2.end());

    // Find the union of both sets (unique controls from both sets)
    std::vector<Control> unionControls;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(unionControls));

    std::cout << "\nUnion of controls (unique controls from both sets):\n";
    for (const auto& control : unionControls) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    // Find the intersection of both sets (controls common to both sets)
    std::vector<Control> intersectionControls;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(intersectionControls));

    std::cout << "\nIntersection of controls (common controls between both sets):\n";
    for (const auto& control : intersectionControls) {
        std::cout << "ID: " << control.id << ", Name: " << control.name << "\n";
    }

    return 0;
}

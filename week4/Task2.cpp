#include <iostream>
#include <vector>
#include <set>
#include <algorithm>  // For std::copy and std::find

int main() {
    // Step 1: Populate Containers

    // Initialize dynamic widgets as a std::vector (since it's dynamic, it can change during runtime)
    std::vector<std::string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge", "GPS"};
    
    // Initialize static widgets as a std::set (static widgets won't change during runtime)
    std::set<std::string> staticWidgets = {"Logo", "WarningLights"};

    // Step 2: Use Iterators to print dynamic widgets
    std::cout << "Dynamic Widgets: \n";
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Step 3: Check if a specific widget is in the static widgets set
    std::string widgetToFind = "WarningLights";
    auto search = staticWidgets.find(widgetToFind);
    if (search != staticWidgets.end()) {
        std::cout << widgetToFind << " is found in the static widgets set." << std::endl;
    } else {
        std::cout << widgetToFind << " is NOT found in the static widgets set." << std::endl;
    }

    // Step 4: Advanced Iteration - Combine both containers into a new vector
    std::vector<std::string> combinedWidgets;
    
    // Copy dynamic widgets into combinedWidgets vector
    std::copy(dynamicWidgets.begin(), dynamicWidgets.end(), std::back_inserter(combinedWidgets));
    
    // Copy static widgets into combinedWidgets vector
    combinedWidgets.insert(combinedWidgets.end(), staticWidgets.begin(), staticWidgets.end());
    
    // Step 5: Use std::find to locate a specific widget in the combined container
    std::string combinedSearch = "Tachometer";
    auto combinedSearchResult = std::find(combinedWidgets.begin(), combinedWidgets.end(), combinedSearch);
    
    if (combinedSearchResult != combinedWidgets.end()) {
        std::cout << combinedSearch << " is found in the combined widget list." << std::endl;
    } else {
        std::cout << combinedSearch << " is NOT found in the combined widget list." << std::endl;
    }

    // Step 6: Output Results - Print the combined list of widgets
    std::cout << "\nCombined Widgets List: \n";
    for (const auto& widget : combinedWidgets) {
        std::cout << widget << std::endl;
    }

    return 0;
}

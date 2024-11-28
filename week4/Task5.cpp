#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// 1. Singleton Design Pattern
class HMISystem {
private:
    static HMISystem* instance;  // Static pointer to hold the single instance

    // Private constructor to prevent instantiation
    HMISystem() {}

public:
    // Static method to get the instance of the class
    static HMISystem* getInstance() {
        if (instance == nullptr) {
            instance = new HMISystem();
        }
        return instance;
    }

    // Method to display current system mode (Day/Night)
    void displayMode(const std::string& mode) {
        std::cout << "Current Mode: " << mode << std::endl;
    }
};

// Initialize the static pointer to nullptr
HMISystem* HMISystem::instance = nullptr;

// 2. Factory Design Pattern
// Abstract Product
class Control {
public:
    virtual void render() = 0;
    virtual ~Control() {}
};

// Concrete Products
class Button : public Control {
public:
    void render() override {
        std::cout << "Rendering a Button." << std::endl;
    }
};

class Slider : public Control {
public:
    void render() override {
        std::cout << "Rendering a Slider." << std::endl;
    }
};

// Factory class
class ControlFactory {
public:
    static Control* createControl(const std::string& type) {
        if (type == "Button") {
            return new Button();
        } else if (type == "Slider") {
            return new Slider();
        }
        return nullptr;
    }
};

// 3. Observer Design Pattern
// Observer interface
class ModeObserver {
public:
    virtual void update(const std::string& mode) = 0;
    virtual ~ModeObserver() {}
};

// Concrete Observers
class ButtonObserver : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Button visibility adjusted for Night mode." << std::endl;
        } else {
            std::cout << "Button visibility adjusted for Day mode." << std::endl;
        }
    }
};

class SliderObserver : public ModeObserver {
public:
    void update(const std::string& mode) override {
        if (mode == "Night") {
            std::cout << "Slider visibility adjusted for Night mode." << std::endl;
        } else {
            std::cout << "Slider visibility adjusted for Day mode." << std::endl;
        }
    }
};

// Subject class (HMI System)
class HMISystemObserver {
private:
    std::vector<ModeObserver*> observers;
    std::string mode;

public:
    void addObserver(ModeObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(ModeObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setMode(const std::string& newMode) {
        mode = newMode;
        notifyObservers();
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->update(mode);
        }
    }
};

// 4. Strategy Design Pattern
// Strategy interface
class RenderingStrategy {
public:
    virtual void render() = 0;
    virtual ~RenderingStrategy() {}
};

// Concrete Strategies
class TwoDRendering : public RenderingStrategy {
public:
    void render() override {
        std::cout << "Rendering in 2D." << std::endl;
    }
};

class ThreeDRendering : public RenderingStrategy {
public:
    void render() override {
        std::cout << "Rendering in 3D." << std::endl;
    }
};

// Context class
class ControlWithRendering {
private:
    RenderingStrategy* strategy;

public:
    ControlWithRendering(RenderingStrategy* strategy) : strategy(strategy) {}

    void setRenderingStrategy(RenderingStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void render() {
        strategy->render();
    }
};

// Main function
int main() {
    // 1. Singleton Pattern Usage
    HMISystem* hmi = HMISystem::getInstance();
    hmi->displayMode("Day");

    // 2. Factory Pattern Usage
    Control* button = ControlFactory::createControl("Button");
    button->render();  // Rendering a Button

    Control* slider = ControlFactory::createControl("Slider");
    slider->render();  // Rendering a Slider

    // 3. Observer Pattern Usage
    HMISystemObserver system;
    ButtonObserver buttonObserver;
    SliderObserver sliderObserver;

    system.addObserver(&buttonObserver);
    system.addObserver(&sliderObserver);

    system.setMode("Night");  // All observers will be notified and adjust their visibility
    system.setMode("Day");    // All observers will be notified again

    // 4. Strategy Pattern Usage
    TwoDRendering twoD;
    ThreeDRendering threeD;

    ControlWithRendering control(&twoD);
    control.render();  // Rendering in 2D

    control.setRenderingStrategy(&threeD);
    control.render();  // Rendering in 3D

    // Clean up
    delete button;
    delete slider;
    return 0;
}

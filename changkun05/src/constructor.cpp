#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <string>
#include <vector>

class ConstructorNode : public rclcpp::Node {
public:
    ConstructorNode() : Node("ConstructorNode") {
        
        // =====================================================================
        // AXIS A: WHERE TO ALLOCATE (Stack vs Heap)
        // =====================================================================
        std::cout << "--- 1. Allocation Location ---" << std::endl;
        
        int a = 42; // Direct Allocation (Lives 100% on the Stack)
        std::cout << "Stack Variable 'a' Address: " << &a << std::endl;

        // Indirect Allocation (Smart pointer lives on Stack, targets Heap)
        auto b = std::make_shared<int>(42); 
        std::cout << "SmartPtr 'b' on Stack: " << &b << " | Target on Heap: " << b.get() << std::endl;
        std::cout << std::endl;

        // =====================================================================
        // AXIS B: SYNTAX STYLE (How data is packed)
        // =====================================================================
        std::cout << "--- 2. Syntax Styles ---" << std::endl;
        
        int c(42); // Traditional syntax (Stack allocation)
        int d{42}; // Uniform List initialization (Stack allocation)
        
        // This class variable lives on the STACK, but internally handles its own heap buffer!
        std::string uniform_stack_string{"I am a stack variable object!"}; 
        std::cout << "String Object 'uniform_stack_string' lives on STACK: " << &uniform_stack_string << std::endl;
        std::cout << std::endl;

        // =====================================================================
        // AXIS C: SEMANTICS (Copy vs Move vs Reference)
        // =====================================================================
        std::cout << "--- 3. Copy vs Move vs Reference ---" << std::endl;
        
        std::string original = "Lidar_Frame_Data"; // Value initialization on Stack
        
        std::string copy_constructed = original; // COPY: Creates a duplicate clone in a new stack space
        std::cout << "Original address: " << &original << " | Copy address: " << &copy_constructed << std::endl;

        std::string move_constructed = std::move(original); // MOVE: Steals heap resources, original is now empty!
        std::cout << "Moved string address: " << &move_constructed << " | Value: " << move_constructed << std::endl;
        std::cout << std::endl;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ConstructorNode>();
    rclcpp::shutdown();
    return 0;
}

/*take home message 27.May 2026:
- The Rule: If you don't use new, make_shared, or make_unique, the object is born on the Stack regardless of whether it's a built-in int or a heavy custom class!
*/
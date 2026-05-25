#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

class MemoryExplorerNode : public rclcpp::Node {
public:
    MemoryExplorerNode() : Node("MemoryExplorerNode") {
        int stack_int1 = 42; // Stack allocation
        int stack_int2 = 84; // Stack allocation
        std::cout << "Stack Int 1 Adress" << &stack_int1 << std::endl;
        std::cout << "Stack Int 2 Adress" << &stack_int2 << std::endl;
        std::cout << "They should be 4 addresses away from each other" << std::endl;

        auto heap_int1 = std::make_shared<int>(42); // Heap allocation
        int* heap_int2 = new int(84); // Heap allocation
        std::cout << "Heap Int 1 Adress" << heap_int1.get() << "But the Pointer is on the STACK" << &heap_int1 << std::endl;
        std::cout << "Heap Int 2 Adress" << heap_int2.get() << "But the Pointer is on the STACK" << &heap_int2 << std::endl;

        //Growing, std::vector are usually on the heap, but the pointer to it is on the stack
        std::vector<int> robot_path;
        std::cout << "Initial Vector size: " << robot_path.size() << "size in bytes" << sizeof(robot_path) << ", capacity: " << robot_path.capacity() << ", pointer address: " << &robot_path << ", heap address: " << robot_path.data() << std::endl;
        for (auto i = 0; i < 10; ++i) {
            robot_path.push_back(i);
            std::cout << "Vector number of elements: " << robot_path.size() << "size in bytes" << sizeof(robot_path) << ", capacity: " << robot_path.capacity() << ", pointer address: " << &robot_path << ", heap address: " << robot_path.data() << std::endl;
        }
    }

    print_virtual_memory_map();

private:
    // Helper to read the Linux kernel's memory map for this exact process
    void print_virtual_memory_map() {
        std::cout << "=== LINUX KERNEL VIRTUAL MEMORY MAP FOR THIS PROCESS ===\n";
        std::ifstream maps_file("/proc/self/maps");
        std::string line;
        
        int lines_printed = 0;
        while (std::getline(maps_file, line)) {
            // Only print lines showing Heap, Stack, or Code to keep it readable
            if (line.find("[heap]") != std::string::npos || 
                line.find("[stack]") != std::string::npos || 
                line.find("memory_explorer_node") != std::string::npos) {
                std::cout << "  " << line << "\n";
                lines_printed++;
            }
        }
        std::cout << "========================================================\n";
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MemoryExplorerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
/*
take home message 18. Mai 2026:
- Stack: LIFO, used for function calls, local variables, and control flow. $8\text{ MB}$ per thread (Default) => stack overflow
- Heap: used for dynamic memory allocation.
- in OS there are many programs, each program assumes it is the only one running => works inside its VIRTUAL MEMORY 2^64
- each program has its own VIRTUAL MEMORY stack and heap, ISOLATED !!! can never touch each other
- BUT IN REALITY, stacks and heaps across different programs are COMPLETELY MIXED!!!
- KASLR (Kernel Address Space Layout Randomization) everytime it boots
- array: continuous in VIRTUAL MEMORY -> Page Table -> scattered in PHYSICAL MEMORY
- Heap allocation: size as big as it needs in stack
- But what if it grows? 
    - std::string and std::vector will rellocate (remember reserve?)
    - std::map, std::set, std::list are linkedlist
    - EVERYTHING IS VIRTUAL ADDRESS!!! VIRTUAL MEMORY
    - C++ CAN NEVER SEE PHYSICAL MEMORY, ONLY VIRTUAL MEMORY
    - Linux NEVER EXPOSE PHYSICAL MEMORY TO USER SPACE, ONLY MMU & Kernel
    - Custom CLASSES NEVER GROW, only its instances like std::list can grow
- 0x7fffff80 from ROS can also be the same 0x7fffff80 from another program, but different physical memory
- MMU looks at the CR3 register to see Process ID and looks at its page table.
- E.g: Segmentation Fault (SIGSEGV) when access a not allocated jet memory like a nullptr
- Questions:
    - can something starts from 0x0000? -> virtual no, auto starts at 0x10000, the bottom reserved for other things, but physical yes maybe
    - can C++ developer decide address? -> no, OS does that
    - are virtual address really next to each other? -> yes, but downward
    - how many bits are two consecutive address away? -> modern computer ALWAYS BYTE (8bit) addressed => an integer takes up 4 addresses, the next one is 4 addresses away
*/
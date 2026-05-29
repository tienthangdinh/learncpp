#include <memory>
#include <fstream>
#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <string>


class MemConceptNode : public rclcpp::Node{
    public:
    MemConceptNode() : Node("MemConceptNode") {
        

        std::cout << "===============second test with just an int================" << std::endl;
        std::shared_ptr<int> randomint = std::make_shared<int>(42);
        std::cout << "[REF-COUNT] Count: " << randomint.use_count() 
                  << " | SmartPtr Stack Pos: " << &randomint 
                  << " | Heap Target Address: " << randomint.get() 
                  << " | Value: " << *randomint << std::endl;

        {
            std::shared_ptr<int> secondintptr = randomint;
            std::cout << "[REF-COUNT] Count inside scope: " << randomint.use_count() 
                      << " | SecondIntPtr Stack Pos: " << &secondintptr 
                      << " | Heap Target Address: " << secondintptr.get() 
                      << " | Value: " << *secondintptr << std::endl;
        }
        std::cout << "[REF-COUNT] Count after scope closed: " << randomint.use_count() 
                  << " | SmartPtr Stack Pos: " << &randomint 
                  << " | Heap Target Address: " << randomint.get() 
                  << " | Value: " << *randomint << std::endl;

        std::cout << "===============third test with old C style int pointer================" << std::endl;
        int* oldstyleint = new int(42);
        std::cout << "Pointer position on stack: " << &oldstyleint << " | Old Style Int Pointer Address in Heap: " << oldstyleint << " | Value in that Heap position: " << *oldstyleint << std::endl;
        delete oldstyleint; // we have to manually delete it, otherwise it will cause memory leak, and we have
    }
    //after construction function even the count back to 0 but idk how to visualize it
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MemConceptNode>();
    rclcpp::shutdown();
    return 0;
}

/* take home message 25. Mai 2026:
- RAII is a general concept about construction and destruction and the pointer also die together with it
- reference counting is an implementation of RAII
- old C-syle pointer: &ptr, ptr, *ptr
- new smart pointer: &ptr, ptr.get(), *ptr
- uint8_t is really important for images, it saves massive storage by 75%
- passing (const Type& var) means please do not change this
*/
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <iostream>

class PointerExplorerNode :public rclcpp::Node {
    public:
    PointerExplorerNode() : Node("PointerExplorerNode") {
        std::shared_ptr<int> old_style_ptr(new int(100));
        std::shared_ptr<int> new_style_ptr = std::make_shared<int>(102);
        std::cout << "[INIT] Old Style Pointer Address on Stack " << &old_style_ptr << " Target Address on Heap: " << old_style_ptr.get() << " | Value: " << *old_style_ptr << std::endl;
        std::cout << "[INIT] New Style Pointer Address on Stack " << &new_style_ptr << " Target Address on Heap: " << new_style_ptr.get() << " | Value: " << *new_style_ptr << std::endl;
        std::cout << std::endl;

        std::shared_ptr<int> smartpointer2 = new_style_ptr;
        int* oldpointer2 = new_style_ptr.get();
        std::cout << "SmartPointer 2 on Stack at " << &smartpointer2 << " Target Address on Heap: " << smartpointer2.get() << " With value " << *smartpointer2 << " Count of pointer " << smartpointer2.use_count() << std::endl;
        std::cout << "C-Style Old Pointer 2 on Stack at " << &oldpointer2 << " Target Address on Heap " << oldpointer2 << " With value " << *oldpointer2 << " and no counter because it is C-style" << std::endl;
        std::cout << std::endl;
        smartpointer2.reset();
        std::cout << "After smartpointer2 resetted" << std::endl;
        std::cout << "SmartPointer 2 on Stack at " << &smartpointer2 << " Target Address on Heap: " << smartpointer2.get() << " With value " << "SEGMENTATION FAULT" << " Count of pointer " << smartpointer2.use_count() << std::endl;
        std::cout << "Original pointer on Stack " << &new_style_ptr << " Target Address on Heap: " << new_style_ptr.get() << " With value " << *new_style_ptr << " Count of pointer " << new_style_ptr.use_count() << std::endl;
        std::cout << std::endl;

        new_style_ptr.reset();
        std::cout << "Now let's try to reset original pointer" << std::endl;
        std::cout << "Original pointer on Stack " << &new_style_ptr << " Target Address on Heap: " << new_style_ptr.get() << " With value " << "SEGMENTATION FAULT" << " Count of pointer " << new_style_ptr.use_count() << std::endl;
        std::cout << "C-Style Old Pointer 2 on Stack at " << &oldpointer2 << " Target Address on Heap " << oldpointer2 << " With value " << *oldpointer2 << " and no counter because it is C-style" << std::endl;
        std::cout << std::endl;

    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PointerExplorerNode>();
    rclcpp::shutdown();
    return 0;
}
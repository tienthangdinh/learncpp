#include "virtual_mem_inspector.hpp"
#include <iomanip>

// 1. DATA / BSS SEGMENT: Global and static variables
// Initialized data goes to .data; zero-initialized goes to .bss
int g_robot_system_status = 1;              // .data segment (initialized global)
static double g_global_kinematic_scale = 1.0; // .data segment (initialized static)
int g_uninitialized_error_code;             // .bss segment (uninitialized/zero-filled)

// 2. TEXT SEGMENT: A normal standalone function (compiled CPU machine instructions)
void sample_control_loop_function() {
    // Machine instructions residing in .text
}

MemoryInspectorNode::MemoryInspectorNode() {
    // Open a dummy file/device to acquire a file descriptor from the Kernel PCB
    // STDIN = 0, STDOUT = 1, STDERR = 2 -> The next opened file gets FD = 3
    lidar_device_fd_ = open("/dev/null", O_RDONLY);
}

MemoryInspectorNode::~MemoryInspectorNode() {
    if (lidar_device_fd_ >= 0) {
        close(lidar_device_fd_);
    }
}

void MemoryInspectorNode::inspect_all_segments(int recursion_depth) {
    // 3. STACK SEGMENT: Local variables inside this stack frame
    int stack_local_var = 42;

    if (recursion_depth > 0) {
        // Recurse once to visually show the stack growing DOWNWARD
        std::cout << "[STACK FRAME " << recursion_depth << "] Local variable at:  " 
                  << static_cast<void*>(&stack_local_var) << std::endl;
        inspect_all_segments(recursion_depth - 1);
        return;
    }

    std::cout << "[STACK FRAME 0] Local variable at:  " 
              << static_cast<void*>(&stack_local_var) << std::endl;

    // 4. HEAP SEGMENTS
    // A. Standard dynamic heap allocation via new / malloc
    int* heap_dynamic_var = new int(100);

    // B. Direct Virtual Page Allocation via mmap
    void* mmap_region = mmap(nullptr, 4096, PROT_READ | PROT_WRITE, 
                             MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    // -------------------------------------------------------------
    // PRINTING THE FULL VIRTUAL MEMORY LAYOUT (Low -> High)
    // -------------------------------------------------------------
    std::cout << "\n================ PROCESS VIRTUAL MEMORY LAYOUT ================\n";
    std::cout << std::left;

    // TEXT (Machine Code)
    std::cout << "\n--- [1] TEXT SEGMENT (Code / Machine Instructions - Low Memory) ---" << std::endl;
    std::cout << "  Free Function Address:            " 
              << reinterpret_cast<void*>(&sample_control_loop_function) << std::endl;
    std::cout << "  Current Object (this) Address:          "
              << reinterpret_cast<void*>(this) << std::endl;

    // DATA / BSS
    std::cout << "\n--- [2] DATA & BSS SEGMENTS (Globals & Static Data) ---" << std::endl;
    std::cout << "  Initialized Global (.data):       " 
              << static_cast<void*>(&g_robot_system_status) << std::endl;
    std::cout << "  Initialized Static Global (.data):" 
              << static_cast<void*>(&g_global_kinematic_scale) << std::endl;
    std::cout << "  Uninitialized Global (.bss):      " 
              << static_cast<void*>(&g_uninitialized_error_code) << std::endl;

    // HEAP (Grows UP)
    std::cout << "\n--- [3] HEAP & MMAP SEGMENTS (Dynamic Allocations) ---" << std::endl;
    std::cout << "  Heap Variable (via new):          " 
              << static_cast<void*>(heap_dynamic_var) << std::endl;
    std::cout << "  mmap Virtual Page:                " 
              << mmap_region << std::endl;

    // STACK (Grows DOWN from High Memory)
    std::cout << "\n--- [4] STACK SEGMENT (Local Frames - High User Memory) ---" << std::endl;
    std::cout << "  Stack Local Variable:             " 
              << static_cast<void*>(&stack_local_var) << std::endl;

    // KERNEL SPACE (PCB & File Descriptor Table)
    std::cout << "\n--- [5] KERNEL SPACE (Protected OS Memory) ---" << std::endl;
    std::cout << "  Current Process ID (PID):         " << getpid() << std::endl;
    std::cout << "  Lidar File Descriptor (FD index): " << lidar_device_fd_ 
              << " (Index in the Kernel's private FD table)\n" << std::endl;

    // Clean up heap and mmap allocations
    delete heap_dynamic_var;
    munmap(mmap_region, 4096);
}

/*
+-------------------------------------------------------+ High Addresses

|                                                       |
|  KERNEL SPACE (Protected OS Memory)                   |
|  -> Process Control Block (PCB)                       |
|     * Process ID (PID)                                |
|     * CPU Register states                             |
|     * FILE DESCRIPTOR TABLE [0, 1, 2, 3...]  <-- HERE!|
+-------------------------------------------------------+ (Strict Wall)

|                                                       |
|  USER SPACE (Your C++ Program's Memory)               |
|                                                       |
|  ▼ STACK (Local variables, function frames)           |
|                                                       |
|                     ( Free Space )                    |
|                                                       |
|  ▲ HEAP (Dynamic memory: malloc, new, mmap locations) |
|                                                       |
|  - DATA SEGMENT (Global & static variables)           |
|                                                       |
|  - TEXT SEGMENT (Your compiled machine code instructions)|
+-------------------------------------------------------+ Low Addresses



Each stack frame
A Stack Frame (or Activation Record) is simply a contiguous block of bytes on the stack allocated automatically by the CPU every time a function is called.
1 Function Call = 1 Stack Frame
When a function is called, its frame is pushed onto the top of the stack.
When the function returns, its frame is popped (instantly discarded) by moving the CPU's Stack Pointer register.
High Address
+------------------------------------+  0x16bdb61a0 -> &stack_local_var (Frame 10)
| stack_local_var (int)              |  4 bytes  (0x16bdb61a0 - 0x16bdb61a3)
| recursion_depth argument (int)     |  4 bytes
| Hidden 'this' pointer (Node*)      |  8 bytes
| Saved Return Address (LR / x30)    |  8 bytes  (where to jump back when function finishes)
| Saved Frame Pointer (FP / x29)     |  8 bytes  (points to previous stack frame)
| Saved CPU Registers                |  16 bytes
| ABI Alignment Padding              |  48 bytes (enforces 16-byte CPU alignment)
+------------------------------------+  0x16bdb6140 -> &stack_local_var (Frame 9)
Low Address



High Virtual Addresses
+-------------------------------------------------------+
| KERNEL SPACE (Protected OS Memory)                   |
+-------------------------------------------------------+
| STACK REGION (Virtual Memory)                         |
|                                                       |
|  +-------------------------------------------------+  |
|  | Stack Frame 2: main()                           |  |
|  |  - Local variables of main                      |  |
|  +-------------------------------------------------+  |
|  | Stack Frame 1: inspect_all_segments(depth=1)    |  |
|  |  - Return address back to main                  |  |
|  |  - Local variables (stack_local_var)            |  |
|  +-------------------------------------------------+  |
|  | Stack Frame 0: inspect_all_segments(depth=0)    |  | <-- Current active frame
|  |  - Return address back to depth=1               |  |     (Top of Stack / SP)
|  |  - Local variables (stack_local_var)            |  |
|  +-------------------------------------------------+  |
|                          |                            |
|                          v (Grows DOWNWARD)           |
|                                                       |
|                     ( Free Space )                    |
|                                                       |
|                          ^ (Grows UPWARD)             |
|                          |                            |
| HEAP REGION (malloc, new, dynamic memory)             |
| DATA / BSS SEGMENTS (Globals & statics)               |
| TEXT SEGMENT (Compiled CPU instructions)              |
+-------------------------------------------------------+
Low Virtual Addresses



Each function call creates a new Stack Frame on that thread's stack. But never for structs, classes, objects or other data structures.
Why the CPU Treats Functions Specially?????
At the hardware level, a CPU is an execution engine. It doesn't know what a "struct" or a "class" is—to the CPU, data is just a sequence of bytes.
A function, however, alters the flow of control. Calling a function requires the CPU to:
- Jump to a new instruction address in the .text segment.
- Remember where it came from (saving the Return Address into a register or on the stack).
- Isolate local variables so the called function doesn't overwrite the caller's variables.
- Jump back to the caller when finished.


======================= PROCESS VIRTUAL MEMORY =======================

  [ TEXT SEGMENT ]    -> Shared by all threads (the compiled code)
  [ DATA / BSS ]      -> Shared by all threads (globals & static variables)
  [ HEAP ]            -> Shared by all threads (malloc, new, dynamic memory)
  [ FILE DESCRIPTORS] -> Shared by all threads (sockets, serial ports, files)

  ---------------------------------------------------------------------
  
  [ THREAD 1 ]        -> Private Stack 1 (Stack Frames for Thread 1)
  [ THREAD 2 ]        -> Private Stack 2 (Stack Frames for Thread 2)
  [ THREAD 3 ]        -> Private Stack 3 (Stack Frames for Thread 3)

======================================================================
// Lives on the SHARED HEAP
int* shared_counter = new int(0); 

// Thread 1's Stack Frame (Private)           // Thread 2's Stack Frame (Private)
void worker1() {                              void worker2() {
    int local_a = 5; // On Stack 1                int local_b = 10; // On Stack 2
    
    // BOTH access the SAME Heap Address:
    *shared_counter += local_a;                   *shared_counter += local_b;
    // ^ RACE CONDITION without a mutex!           ^ RACE CONDITION without a mutex!
}                                             }
*/
#include <virtual_mem_buffer.hpp>

VirtualMemoryBuffer::VirtualMemoryBuffer(std::size_t num_pages) {
    page_size_ = static_cast<std::size_t>(sysconf(_SC_PAGESIZE));
    total_size_ = num_pages * page_size_;
    std::cout << "Creating VirtualMemoryBuffer with " << num_pages << " pages (" << total_size_ << " bytes). OS Page size: " << page_size_ << " bytes." << std::endl;
    mapped_region_ = mmap(
        nullptr, //kernel chooses the virtual address
        total_size_,  //number of bytes to map, must be a multiple of the system page size
        PROT_READ | PROT_WRITE, //memory region can be read and written
        MAP_PRIVATE | MAP_ANONYMOUS, //mapping is private and not backed by any file
        -1, //file descriptor, -1 means no file is associated with the mapping
        0); //offset in the file, 0 means start of the file
    if (mapped_region_ == MAP_FAILED) {
        std::cerr << "Failed to map memory region." << std::endl;
        throw std::bad_alloc();
    }
}

VirtualMemoryBuffer::~VirtualMemoryBuffer() {
    if (mapped_region_ && mapped_region_ != MAP_FAILED) {
        munmap(mapped_region_, total_size_);
        std::cout << "Unmapped memory region of size " << total_size_ << " bytes at " << mapped_region_ << std::endl;
    }
}

bool VirtualMemoryBuffer::set_read_only() {
    if (mprotect(mapped_region_, total_size_, PROT_READ) == 0) {
        std::cout << "Set memory region to read-only." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to set memory region to read-only." << std::endl;
        return false;
    }
}

bool VirtualMemoryBuffer::set_read_write() {
    if (mprotect(mapped_region_, total_size_, PROT_READ | PROT_WRITE) == 0) {
        std::cout << "Set memory region to read-write." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to set memory region to read-write." << std::endl;
        return false;
    }
}

/*
+-------------------------------------------------------------------------+
|                              User Space                                 |
|  [ Program / Process ] (Code, Stack, Heap, std::vector, etc.)          |
|         |                                                               |
|         v                                                               |
|  [ Virtual Memory ] Divided into fixed-size "Pages" (e.g., 4KB / 16KB)  |
+---------|---------------------------------------------------------------+
          | (Virtual Address)
          v
+-------------------------------------------------------------------------+
|                   Operating System Kernel & CPU MMU                     |
|  - Page Tables (Translates Virtual Page -> Physical Frame)              |
|  - Page Fault Handler (Intercepts missing or swapped-out pages)         |
+---------|---------------------------------------------------------------+
          |
          +-----------------------------+---------------------------------+
          | (Mapped via Page Table)     | (Kernel File I/O subsystem)     |
          v                             v                                 v
+-------------------------------------------------------------------------+
|                         Physical Memory (RAM)                           |
|  +-----------------------+  +-------------------+  +-----------------+  |
|  |    Anonymous Pages    |  |    Page Cache     |  |  Buffer Cache   |  |
|  | (Heap, Stack, BSS)    |  | (Cached Files,    |  | (Raw Disk Block |  |
|  |                       |  |  mmap file pages) |  |  Metadata/Inodes|  |
|  +-----------------------+  +-------------------+  +-----------------+  |
+-------------|-------------------------|-----------------------|---------+
              | (Memory pressure)       | (Sync / Writeback)    |
              v                         v                       v
+-------------------------------------------------------------------------+
|                       Secondary Storage (Disk / SSD)                   |
|  [ Swap Partition/File ]    [ File System Data ]   [ Raw Block Storage ]|
+-------------------------------------------------------------------------+





The OS executes a single assembly instruction to rewrite the CR3/TTBR0 register with the physical address of Page Table B.
Process A (PID 101)                 Process B (PID 202)
Virtual Address: 0x00400000         Virtual Address: 0x00400000
       |                                   |
       v                                   v
[ Page Table A ]                    [ Page Table B ]
(Pointed to by CR3 when             (Pointed to by CR3 when 
 Process A is running)               Process B is running)
       |                                   |
       v                                   v
Physical Frame: 0x1A000             Physical Frame: 0x8F000 (somewhere totally different in RAM)






The Page Cache is the OS kernel's mechanism for keeping recently read or written disk file pages stored in unused physical RAM.
Process A (Node 1)                Process B (Node 2)
Virtual Page 0x7FFF1000           Virtual Page 0x5AAA3000
        \                                /
         \                              /
          v                            v
    +----------------------------------------+
    |       Shared Page Cache in RAM         |
    |  Physical Frame 0x4C000: "map.yaml"    |
    +----------------------------------------+
                        ^
                        | (Loaded once from disk)
               [ NVMe SSD / Disk ]




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


No, your source code files (main.cpp, CMakeLists.txt, something.hpp) are NOT the files in the File Descriptor Table.
They are build code, not run code. Run code only like: asset files, configuration files, network sockets, or database files that your program interacts with live while it runs.
like when you play game you load map and play music yo load .mp3 or something
 +-----------------------------------+

                  |      Your Running Program         |
                  |                                   |
                  |  [Your Stack Variable]: int fd = 3|
                  +-----------------------------------+
                                    |
                                    | (Sends the number 3)
                                    v
+-------------------------------------------------------------------------+

| KERNEL SPACE                                                            |
|                                                                         |
|  File Descriptor Table:                                                 |
|  [0] -> Keyboard Stream                                                 |
|  [1] -> Screen Stream                                                   |
|  [2] -> Screen Stream                                                   |
|  [3] -> [ Wire connected to "background_music.mp3" on your SSD ] <----+ |
|                                                                       | |
+-----------------------------------------------------------------------|-+
                                                                        |
                                                                        v
                                                             +------------------+

                                                             | Physical Storage |
                                                             |  (Hard Drive)    |
                                                             +------------------+
*/
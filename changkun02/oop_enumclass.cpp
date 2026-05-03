#include <cstdint>
#include <iostream>

// define uint8_t so that we only use 1 byte to save these number representation
// of this enumeration class
enum class RobotState : uint8_t {
  IDLE,   // saved as 0
  MOVING, // saved as 1
  ERROR   // saved as 2 in memory
};

enum class GripperState : uint8_t {
  OPEN,
  CLOSED,
  ERROR // of course not the same as RobotState::ERROR
};

int main() {
  RobotState robotstate = RobotState::ERROR;
  GripperState gripperstate = GripperState::ERROR;
  std::cout << "Robot State: " << static_cast<int>(robotstate) << std::endl;
  std::cout << "Gripper State: " << static_cast<int>(gripperstate) << std::endl;
  return 0;
}

/*take home message 03. Mai 2026:
- enum class save values internally as integer and we can choose how many values
would that be
- e.g. uint8_t is 1 byte type, normal int is 4 byte type
*/

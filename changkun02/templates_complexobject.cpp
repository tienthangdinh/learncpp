#include <iostream>

struct MotorCommand {
  int motor_id;
  float throttle;
};

template <typename T, int BufferSize> class CommandBuffer {
private:
  T commands[BufferSize];

public:
  T &get_first_value() { return commands[0]; }
};

int main() {
  CommandBuffer<MotorCommand, 10> commandbuffer;
  MotorCommand &commandref = commandbuffer.get_first_value();
  std::cout << "Motor ID:" << commandref.motor_id
            << " Throttle: " << commandref.throttle
            << " Position: " << &commandref << std::endl;
  return 0;
}

/*take home message 02. Mai 2026:
- use more reference
- using template to construct more complext things, not just about type
*/
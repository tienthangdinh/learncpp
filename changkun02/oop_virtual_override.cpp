#include <iostream>

class Motor {
public:
  virtual void set_connection() {
    std::cout << "Connection setup" << std::endl;
  }
  virtual void close_connection() {
    std::cout << "Connection close" << std::endl;
  }
  virtual ~Motor() = default;
};

class SerialMotor : public Motor {
public:
  std::string port;
  void set_connection() override { port = "/dev/ttyUSB0"; }
  void close_connection() override final { port = "0"; }
  ~SerialMotor() { std::cout << port << " closed" << std::endl; }
};

int main() {
  SerialMotor usb;
  usb.set_connection();
  return 0;
}
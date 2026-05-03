#import <iostream>

float get_next_lidar_distance() { return 5.65f; };

int main() {
  auto current_reading = get_next_lidar_distance();
  decltype(current_reading) previous_reading;
  previous_reading = current_reading;
  current_reading = get_next_lidar_distance();

  std::cout << "previous reading: " << previous_reading << std::endl;
  std::cout << "current reading: " << current_reading << std::endl;

  return 0;
}

/*take home message 01. Mai 2026
- f in 5.65f means treats this number as a float (32bit) not doouble (64bit)
- auto(value) and the value need to be run!
- decltype(expression) is just to take the type, but NOT RUN!!!
*/

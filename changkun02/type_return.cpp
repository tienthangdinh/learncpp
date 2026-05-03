#include <iostream>

template <typename SensorT, typename ScaleT>
auto scale_sensor_value(SensorT raw, ScaleT factor) {
  return raw * factor;
};

decltype(auto) call_sensor() { return scale_sensor_value(6.1, 1); }

int main() {
  auto direct_lidar_value = scale_sensor_value(5.3, 0.94);
  std::cout << "Direct Lidar sensor: " << direct_lidar_value << std::endl;

  auto indirect_lidar_value = call_sensor();
  std::cout << "Indirect Lidar sensor: " << indirect_lidar_value << std::endl;

  return 0;
}

/*take home message 01. Mai 2026
- decltype(auto) is at function forwarding
- template<typename, typename>
*/
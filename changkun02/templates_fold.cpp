#include <iostream>
#include <string>

void log_sensor() { std::cout << "end of report" << std::endl; }

template <typename Sensor1, typename... restSensors>
void log_sensor(Sensor1 sensordata1, restSensors... restsensordata) {
  std::cout << sensordata1 << std::endl;
  log_sensor(restsensordata...);
}

template <typename... SensorT> auto sum_all_sensordata(SensorT... sensordata) {
  return (sensordata + ...);
}

int main() {
  int motor_encoder = 0x423;
  double lidar_value = 5.213;
  std::string lidar_status = "Active";
  float camera_fx = 1.032;

  log_sensor(motor_encoder, lidar_value, lidar_status, camera_fx);

  std::cout << sum_all_sensordata(motor_encoder, lidar_value, camera_fx)
            << std::endl;
}

/*take home message 02. Mai 2026:
- the use of template typename ...
*/
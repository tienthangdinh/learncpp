#include <string>
#include <vector>

// generic class base
template <typename DataT, typename ProtocolT> class SensorHub {
public:
  std::vector<DataT> sensor_data;
  ProtocolT connection_info;
};

// create new class based on the class base, changing in type
template <typename T>
using SerialSensor = SensorHub<T, std::string>; // for example GPS

template <typename T> using CANSensor = SensorHub<T, int>; // for motor encoder

int main() {
  SerialSensor<double> gps_sensor;
  CANSensor<float> motor_encoder;
  gps_sensor.sensor_data.push_back(4.542);
  motor_encoder.connection_info = 0x433;
}

/*take home message 02. Mai 2026
- 0x433 is hexadecimal-16-4bits
- memory address is in this 4bits system, e.g. 0x433, 0x434, 0x435
-template using
*/

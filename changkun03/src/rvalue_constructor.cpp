#include <cstddef>
#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <utility>
#include <vector>

class LidarScan {
public:
  float *points;
  size_t counts;

  // normal constructor
  LidarScan(size_t n) : counts(n) {
    points = new float[counts];
    std::cout << "Original lidar scan at " << (void *)points << std::endl;
  }

  // move constructor (handover)
  LidarScan(LidarScan &&oldscan) noexcept
      : points(oldscan.points), counts(oldscan.counts) {
    oldscan.points = nullptr;
    oldscan.counts = 0;
    std::cout << "Handle data to new object at " << (void *)points << std::endl;
  }

  ~LidarScan() {
    if (points != NULL) {
      std::cout << "Delete data at " << (void *)points << std::endl;
      delete[] points;
    }
  }
};

class LidarFilterNode : public rclcpp::Node {
public:
  LidarFilterNode() : Node("LidarFilterNode") {
    LidarScan newscan(500);

    apply_filter(std::move(newscan));
  }

private:
  LidarScan *filtered_storage_ = nullptr;

  void apply_filter(LidarScan &&old_scan) {
    this->filtered_storage_ = new LidarScan(std::move(old_scan));
    RCLCPP_INFO(this->get_logger(), "incoming data now stored at %p",
                (void *)filtered_storage_->points);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<LidarFilterNode>();
  rclcpp::shutdown();
  return 0;
}

/*take home message 07. Mai 2026:
- once again, if we have LidarScan float *points, which means it is a pointer:
- &points is the address that saves it
- points is the address of where the values are
- new int(5) has type int* => data always in the heap
- int* b = &a also has type int*, already knew in AuD
- *b only has type int
- regarding to new[] and delete[]: When you use new[], the computer hides a
small piece of information next to the array telling it how many items are
there. delete[] looks for that hidden number so it knows how many "houses" to
tear down. and thats also how we get acces to points[i] too

For example, each float takes 4 bytes:
points = new float[4];
length 4 saved at addr 992 (8 byte - 64 bit) for the header status and length
points[0] -- addr: 1000
points[1] -- addr: 1004
points[2] -- addr: 1008
points[3] -- addr: 1012
*/
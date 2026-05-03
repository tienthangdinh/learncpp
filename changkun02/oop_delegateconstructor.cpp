class LaserScanner {
public:
  int range;
  bool is_active;

  // default constructor
  LaserScanner() {
    is_active = true;
    range = 0;
  }

  LaserScanner(int range)
      : LaserScanner() { // call default constructor with is_active first, then
                         // overwrite range, this is called delegating
                         // constructor
    range = range;
  }
};

class SubLaserScanner : public LaserScanner { // subclass using :
public:
  using LaserScanner::LaserScanner; // inheriting constructor
};

int main() {
  LaserScanner lidar(12);
  return 0;
}
/*
 */
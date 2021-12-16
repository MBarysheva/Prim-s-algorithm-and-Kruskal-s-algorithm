#include <chrono> //интервалы времени Ц duration
#include <iostream>
using namespace std;
namespace GrafTest {

class time {
  using clock_t = chrono::high_resolution_clock;
  using second_t = chrono::duration<double, ratio<1> >;

  chrono::time_point<clock_t> startTime;

 public:
  time() : startTime(clock_t::now()) {}
  ~time() = default;
  void resetTime();
  double getTime() const;
};
}  // namespace GrafTest

void GrafTest::time::resetTime() { startTime = clock_t::now(); }

double GrafTest::time::getTime() const {
  return chrono::duration_cast<second_t>(clock_t::now() - startTime)
      .count();
}

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <vector>

const std::string SKIP_4LINES = "\n\n\n\n";

int main() {
  // ==================== Preliminaries ====================
  std::random_device rd;
  std::mt19937 tornado(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::vector<int> nums(20);
  std::generate(nums.begin(), nums.end(),
                [&dist, &tornado]() { return dist(tornado); });

  std::ofstream output("output.txt");
  std::stringstream ss;

  // ==================== Min and Max elements ====================
  auto [mn_it, mx_it] = std::minmax_element(nums.begin(), nums.end());
  ss << "Min: " << *mn_it << "; " << "Max: " << *mx_it << SKIP_4LINES;

  // ==================== Sort ====================
  std::stable_sort(nums.begin(), nums.end());
  ss << "[ ";
  std::copy(nums.begin(), nums.end() - 1, std::ostream_iterator<int>(ss, ", "));
  ss << nums.back() << " ]" << SKIP_4LINES;

  // ==================== Amount of [+, -, 0] elements ====================
  int pos = 0, neg = 0, zer = 0;
  auto cur = nums.begin();
  auto end = nums.end();

it_is_not_a_loop:
  if (cur == end) {
    goto end_not_a_loop;
  }
  if (*cur > 0) {
    pos++;
  } else if (*cur == 0) {
    zer++;
  } else {
    neg++;
  }
  cur++;
  goto it_is_not_a_loop;
end_not_a_loop:

  ss << "Positive: " << pos << "; Negative: " << neg << "; Zeros: " << zer
     << SKIP_4LINES;

  // ==================== Average number ====================
  int sm = std::accumulate(nums.begin(), nums.end(), 0);
  int av = (float)sm / (float)(pos + neg + zer);
  ss << "Average number: " << av << SKIP_4LINES;

  // ==================== Deletion elements which less than average number
  // ====================
  nums.erase(
      std::remove_if(nums.begin(), nums.end(), [av](int n) { return n < av; }),
      nums.end());
  ss << "Vector after deletion: [ ";
  std::copy(nums.begin(), nums.end() - 1, std::ostream_iterator<int>(ss, ", "));
  ss << nums.back() << " ]" << SKIP_4LINES;

  // ==================== Sort vector after deletion and creation of new vector
  // of unique numbers ====================
  std::stable_sort(nums.begin(), nums.end());

  std::vector<int> nvec;
  std::unique_copy(nums.begin(), nums.end(), std::back_inserter(nvec));

  ss << "Sort vector after deletion and creation of new vector of unique "
        "numbers: [";
  std::copy(nvec.begin(), nvec.end() - 1, std::ostream_iterator<int>(ss, ", "));
  ss << nvec.back() << " ]" << SKIP_4LINES;

  // ==================== Output ====================
  output << ss.str();
  output.close();
}

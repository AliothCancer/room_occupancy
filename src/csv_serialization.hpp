
#ifndef RO_CSV_SER
#define RO_CSV_SER

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include "local_utils.cpp"
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

struct CsvLineError {
  std::size_t row_number;
  std::vector<std::string> fields_errors;
};

inline constexpr std::array<std::string_view, 19> CSV_HEADER{
    "Date",
    "Time",
    "S1_Temp",
    "S2_Temp",
    "S3_Temp",
    "S4_Temp",
    "S1_Light",
    "S2_Light",
    "S3_Light",
    "S4_Light",
    "S1_Sound",
    "S2_Sound",
    "S3_Sound",
    "S4_Sound",
    "S5_CO2",
    "S5_CO2_Slope",
    "S6_PIR",
    "S7_PIR",
    "Room_Occupancy_Count",
};

enum class DiscreteLevel : std::uint8_t {
  NaN,
  Zero,
  One,
  Two,
  Three,
};

struct CsvRecord {
  static constexpr char SEP = ',';
  CsvLineError errors;
  // Do not touch the order, it's 1 to 1 with the expected csv header
  std::string_view Date;
  std::string_view Time;
  double S1_Temp{};
  double S2_Temp{};
  double S3_Temp{};
  double S4_Temp{};
  double S1_Light{};
  double S2_Light{};
  double S3_Light{};
  double S4_Light{};
  double S1_Sound{};
  double S2_Sound{};
  double S3_Sound{};
  double S4_Sound{};
  double S5_CO2{};
  double S5_CO2_Slope{};
  DiscreteLevel S6_PIR{};
  DiscreteLevel S7_PIR{};
  DiscreteLevel Room_Occupancy_Count{};

  /**
   * @brief build a record
   * @param path  the csv file path
   * @param sep   the specific separator char "," only for explicit declaration
   */
  CsvRecord(std::size_t row_, std::string line)
      : errors{
            .row_number = row_,
            .fields_errors = {},
        } {

    auto comma_split = std::views::split(line, SEP);
    auto it = comma_split.begin();


    auto if_err_log = [&](bool predicate, std::string_view msg) {
      if (predicate) {
        errors.fields_errors.emplace_back(msg);
      }
    };

    auto next = [&]() {
      assert(it != comma_split.end());
      auto sub = *it++;
      return std::string_view(sub.begin(), sub.end());
    };

    Date = trim(next());
    if_err_log(Date.empty(), "field `Date` is empty");

    Time = trim(next());
    if_err_log(Time.empty(), "field `Time` is empty");
  }
};

struct DataFrame{

};

#endif

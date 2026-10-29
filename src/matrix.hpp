#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>


template <std::size_t COLS, std::size_t ROWS> class Matrix {
  std::vector<double> values;

public:
  Matrix() : values(COLS * ROWS, 0.0) {}

  void print_values() const {
    for (auto i : values) {
      std::cout << i << '\n';
    }
  }

  template<std::size_t COLS2>
  Matrix<COLS, COLS2> mat_mul(const Matrix<ROWS, COLS2>& rhs) const;

};


/*
 * 1 2 3
 * 4 5 6
 *                0 1 2 3 4 5
 * Row major:    [1,2,3,4,5,6]
 * Column major: [1,4,2,5,3,6]
 *
 * ROWS = 2
 * COLS = 3
 *
 * values.get(col=2, row=0)
 * row * COLS + col
 *
 */

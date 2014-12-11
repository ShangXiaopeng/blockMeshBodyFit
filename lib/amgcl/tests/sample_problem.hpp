#ifndef TESTS_SAMPLE_PROBLEM_HPP
#define TESTS_SAMPLE_PROBLEM_HPP

// Generates matrix for poisson problem in a unit cube.
template <typename real, typename index>
int sample_problem(
        ptrdiff_t           n,
        std::vector<real>  &val,
        std::vector<index> &col,
        std::vector<index> &ptr,
        std::vector<real>  &rhs
        )
{
    ptrdiff_t n3  = n * n * n;
    real h2i = static_cast<real>((n - 1) * (n - 1));

    ptr.clear();
    col.clear();
    val.clear();
    rhs.clear();

    ptr.reserve(n3 + 1);
    col.reserve(n3 * 7);
    val.reserve(n3 * 7);
    rhs.reserve(n3);

    ptr.push_back(0);
    for(ptrdiff_t k = 0, idx = 0; k < n; ++k) {
        for(ptrdiff_t j = 0; j < n; ++j) {
            for (ptrdiff_t i = 0; i < n; ++i, ++idx) {
                if (
                        i == 0 || i == n - 1 ||
                        j == 0 || j == n - 1 ||
                        k == 0 || k == n - 1
                   )
                {
                    col.push_back(idx);
                    val.push_back(1);

                    rhs.push_back(0);
                } else {
                    col.push_back(idx - n * n);
                    val.push_back(-h2i);

                    col.push_back(idx - n);
                    val.push_back(-h2i);

                    col.push_back(idx - 1);
                    val.push_back(-h2i);

                    col.push_back(idx);
                    val.push_back(6 * h2i);

                    col.push_back(idx + 1);
                    val.push_back(-h2i);

                    col.push_back(idx + n);
                    val.push_back(-h2i);

                    col.push_back(idx + n * n);
                    val.push_back(-h2i);

                    rhs.push_back(1);
                }

                ptr.push_back( static_cast<index>(col.size()) );
            }
        }
    }

    return n3;
}

#endif

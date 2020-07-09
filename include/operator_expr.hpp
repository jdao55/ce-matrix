#ifndef OPERATOR_EXP_H
#define OPERATOR_EXP_H
#include "matrix_expr.hpp"
#include "numeric_trait.hpp"
namespace ce {
    template<typename E1, typename E2>
    struct matrixSum :public matrix_expr<matrixSum<E1, E2>>{
        E1 const & _u;
        E2 const & _v;

        constexpr matrixSum(E1 const&u, E2 const&v):_u(u), _v(v){}
        constexpr size_t size() const { return _u.size();}
        constexpr size_t row_count()  const { return _u.row_count(); }
        constexpr size_t col_count()  const { return _v.col_count(); }
        constexpr auto operator()(const size_t i, const size_t j) const
        {
            return _u(i,j) + _v(i,j);
        }

    };

    template <typename E1, typename E2>
    matrixSum<E1, E2>
    operator+(matrix_expr<E1> const& u, matrix_expr<E2> const& v) {

        return matrixSum<E1, E2>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
    }
}
#endif

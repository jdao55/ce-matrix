#include <iostream>
#include <algorithm>
#include <array>

namespace ce{

template<typename T, size_t n, size_t m>
struct ctmatrix {
    std::array<T, n*m> data;

    constexpr ctmatrix():data() {};
    constexpr ctmatrix(std::initializer_list<T> l){
        std::copy(l.begin(), l.end(), data.begin());
    }
    constexpr ctmatrix(const ctmatrix<T,n,m> &cp) = default;
    constexpr ctmatrix(ctmatrix<T,n,m> &&cp) = default;

    constexpr ctmatrix<T,n,m>& operator=(const ctmatrix<T,n,m>& cp) = default;
    constexpr ctmatrix<T,n,m>& operator=(ctmatrix<T,n,m>&& cp) = default;

    template<size_t s>
    [[nodiscard]] constexpr ctmatrix<T,n,s> operator*(const ctmatrix<T, m ,s>& rhs) const{
        ctmatrix<T,n,s> ret;
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < s; ++j){
                for (auto k = 0; k < m; ++k){
                    ret.at(i,j)+= this->at(i,k)*rhs.at(k,j);
                }
            }
        }
        return ret;
    }
    
    [[nodiscard]]constexpr ctmatrix<T,n,m> operator*(const T& rhs) const
    {
         ctmatrix<T,n,m> ret;
         for (auto i=0; i < n*m; i++)
         {
             ret.data[i]= data[i] * rhs;
         }
         return ret;
    }

    [[nodiscard]]friend constexpr ctmatrix<T,n,m> operator*(const T& lhs, const ctmatrix<T,n,m>& rhs)
    {
        return rhs*lhs;
    }


   [[nodiscard]] constexpr ctmatrix<T,n,m> operator+(const ctmatrix<T,n,m>& rhs) const
    {
        ctmatrix<T,n,m> ret;
        for (auto i=0; i < n*m; i++)
        {
             ret.data[i]= data[i] + rhs.data[i];
        }
        return ret;
    }

    [[nodiscard]]constexpr ctmatrix<T,n,m> operator-(const ctmatrix<T,n,m>& rhs) const
    {
        ctmatrix<T,n,m> ret;
        for (auto i=0; i < n*m; i++)
        {
             ret.data[i]= data[i] - rhs.data[i];
        }
        return ret;
    }

    constexpr const T& at(const size_t i, const size_t j) const
    {
        return data[i*m+j];
    }
    constexpr T& at(const size_t i, const size_t j)
    {
        return data[i*m+j];
    }

    constexpr T& operator[](size_t i)
    {
        return data[i];
    }
    constexpr const T& operator[](size_t i) const
    {
        return data[i];
    }

    //template<typename Tn, size_t r, size_t c>
    constexpr ctmatrix<T,m,n> transpose () const
    {
        ctmatrix<T,m,n> ret;
        for(auto i = 0; i< m; i++)
        {
            for(auto j = 0; j< n; j++)
                {
                    ret.at(i,j) = this->at(j,i);
                }
        }
        return ret;
    }
};
};

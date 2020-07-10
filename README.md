# ce-matrix
c++20 compile time (constexpr), header only and expression template matrix library (WIP Expect api to change)
```c++
/*
0 1 2   1 1 1
3 4 5 * 1 1 1  
6 7 8   1 1 1
*/
int main()
{
    constexpr ce::ctmatrix<int, 3, 3> A{ 0, 1, 2,
                                         3, 4, 5, 
                                         6, 7, 8};
    constexpr ce::ctmatrix<int, 3, 3> B{ 1, 1, 1,
                                         1, 1, 1, 
                                         1, 1, 1};;
    constexpr auto C = A*B;
    return C[0];
}

```
The matrix mulitplication of A*B is evaluated at compile time   
The above program is compiled to:(using gcc10.1 with flags: ```-S -std=c++2a -masm=intel```)
```asm
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 144
	mov	DWORD PTR [rbp-48], 0
	mov	DWORD PTR [rbp-44], 1
	mov	DWORD PTR [rbp-40], 2
	mov	DWORD PTR [rbp-36], 3
	mov	DWORD PTR [rbp-32], 4
	mov	DWORD PTR [rbp-28], 5
	mov	DWORD PTR [rbp-24], 6
	mov	DWORD PTR [rbp-20], 7
	mov	DWORD PTR [rbp-16], 8
	mov	DWORD PTR [rbp-96], 1
	mov	DWORD PTR [rbp-92], 1
	mov	DWORD PTR [rbp-88], 1
	mov	DWORD PTR [rbp-84], 1
	mov	DWORD PTR [rbp-80], 1
	mov	DWORD PTR [rbp-76], 1
	mov	DWORD PTR [rbp-72], 1
	mov	DWORD PTR [rbp-68], 1
	mov	DWORD PTR [rbp-64], 1
	mov	DWORD PTR [rbp-144], 3
	mov	DWORD PTR [rbp-140], 3
	mov	DWORD PTR [rbp-136], 3
	mov	DWORD PTR [rbp-132], 12
	mov	DWORD PTR [rbp-128], 12
	mov	DWORD PTR [rbp-124], 12
	mov	DWORD PTR [rbp-120], 21
	mov	DWORD PTR [rbp-116], 21
	mov	DWORD PTR [rbp-112], 21
	lea	rax, [rbp-144]
	mov	esi, 0
	mov	rdi, rax
	call	_ZNK2ce8ctmatrixIiLm3ELm3EEixEm
	mov	eax, DWORD PTR [rax]
	leave
	ret
```
# Dependancies
- c++20 compliant compiler
     - currently working on gcc-10.1, more compilers will be supported as they get better c++20 supportDependancies
# DOCUMENTATION
TODO updat
## Matrix Class
### Contructors
```c++
template<numeric T, size_t N, size_T> constexpr ctmatrix()
```
- default construct a N by M matrix

```c++
template<numeric T, size_t N, size_T> constexpr ctmatrix(T init)
```
- construct a N by M matrix, with each elemeent initialized to init

```c++
template<numeric T, size_t N, size_T>  constexpr ctmatrix(std::initializer_list<T> l)
```
- initialize N by M matrix with initializer_list
``` c++
static constexpr ctmatrix<T, n, m> identity()
```
- returns N by N identity matrix (compile time error if n!=m)

### Operator overloads
#### Mulitplication overloads
```c++
template<size_t s>
[[nodiscard]] constexpr ctmatrix<T, n, s> operator*(const ctmatrix<T, m, s> &rhs) const;
```

```c++
[[nodiscard]] constexpr ctmatrix<T, n, m> operator*(const T &rhs) const;
```
```c++
[[nodiscard]] friend constexpr ctmatrix<T, n, m> operator*(const T &lhs, const ctmatrix<T, n, m> &rhs)
```
#### addition/subtraction overloads
```
[[nodiscard]] constexpr ctmatrix<T, n, m> operator+(const ctmatrix<T, n, m> &rhs) const;
```
```
[[nodiscard]] constexpr ctmatrix<T, n, m> operator-(const ctmatrix<T, n, m> &rhs) const;
```
#### Container access overloads and functions
```c++
constexpr T &operator[](size_t i) { return data[i]; }
```
```c++
constexpr const T &operator[](size_t i) const { return data[i]; }
```
```c++
constexpr const T &operator()(const size_t i, const size_t j) const;
```
- return const reference to element in ith row and ith column
```
constexpr const T &operator()(const size_t i, const size_t j);
```

```c++
constexpr const T &at(const size_t i, const size_t j) const ;
```
```c++
constexpr T &at(const size_t i, const size_t j);
```
```c++
constexpr bool operator==(const ctmatrix<T, n, m> &rhs) const;
```
#### other functions
```c++
constexpr ctmatrix<T, m, n> transpose() const;
```
- return transpose of matrix
### Vector fuctions
```c++
using vector = ctmatrix<T, N, 1>;
```
- definition of vector ie N by 1 matrix
```c++
template<numeric T, size_t N>
constexpr T dot_product(const vector<T, N> &lhs, const vector<T, N> &rhs)
```
- Dot product between 2 vectors
```c++
template<numeric T>
constexpr vector<T, 3> cross_product(const vector<T, 3> &lhs, const vector<T, 3> &rhs)
```
- Cross product between 3 by 1 vectors
 
# Examples
```c++
constexpr ce::ctmatrix<int, 3, 3> A{ 0, 1, 2,
                                     3, 4, 5, 
                                     6, 7, 8};
//create 3x3 matrix of ones
constexpr ce::ctmatrix<int, 3, 3> B(1);

//create 4x4 identity matrix
constexpr auto i4 = ce::matrix<double, 4>::identity();
    
//matrix binary operators
constexpr auto C1 = A*B;
constexpr auto C2 = A*4; //element wise multiplication
constexpr auto C2 = 4*A; //element wise multiplication
constexpr auto C3 = A+B;
constexpr auto C4= A-B;

//construct vector
constexpr ce::vector<std::complex, 4> cmplx4;

//vector dot prouct
constexpr ce::vector<int, 2> vec1{1,2};
constexpr ce::vector<int, 2> vec2{3,4};
constexpr auto dot_res = ce::vector::dot(vec1, vec2);
//vector cross
constexpr auto cross_res = ce::vector::cross(vec1, vec2);


```




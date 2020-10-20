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
    constexpr ce::vari::matrix_t<int, 3, 3> A{ 0, 1, 2,
                                               3, 4, 5, 
                                               6, 7, 8};
    constexpr ce::vari::matrix_t<int, 3, 3> B{ 1, 1, 1,
                                               1, 1, 1, 
                                               1, 1, 1};
    constexpr ce::vari::matrix_t<int, 3, 3> C = A*B;
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
- for benchmarks and examples
	- [nanobench](https://nanobench.ankerl.com/index.html)
 
# Examples
```c++
using namespace ce::vari;
constexpr matrix_t<float, 3, 3> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
constexpr matrix_t<float, 3, 3> B{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
constexpr matrix_t<float, 3, 3> C{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

//binary operators
constexpr matrix_t<float, 3, 3> D = A + B + C;
constexpr matrix_t<float, 3, 3> E = A * B - C;
constexpr matrix_t<float, 3, 3> E2 = A * 2;

//
constexpr vector_t<int, 3> v1{ 1, 2, 3 };
constexpr vector_t<int, 3> v2{ 2, 3, 4 };
constexpr auto v3 = ce::vari::dot_product(v1, v2);
static_assert(v3 == 20, "error wrong dot product value");

```




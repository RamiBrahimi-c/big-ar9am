# BigRa9m - Arbitary Length Numbers Library in C 

A self-contained arbitrary-precision arithmetic library written in C. Supports large integer operations including addition, subtraction, multiplication, division, modular arithmetic, GCD, primality testing, and more.

it only depends on standard C lib . 

## Table of Contents
- [Important Note](#important-note-)
- [Is It Valid](#is-it-valid-)
- [Features](#features)
- [Algorithms](#algorithms-)
- [Requirements](#requirements)
- [Building](#building)
- [Usage](#usage)
- [Testing](#testing-)
- [Known Issues](#known-issues)
- [Future Improvements](#future-improvements)


## Important Note : 

this lib is made just for fun or primaly to help with arbitary length numbers in asymmetric crypto in my own [crypto lib](https://github.com/RamiBrahimi-c/cryptography-library) .

Therefore it is **not intended** for professional use (if so you should be looking at [this](https://gmplib.org/))

also there is perhaps some bugs or perhaps memory leaks (this will be discussed in the next section)

## Is It Valid ?

* **Computationally** : I used differential testing *Python 3.12.3* --thank you python-- , means i tested results from both python and my big num side to side for the thousands of times on randomized input like `$SRANDOM` , you can check `script.sh` for that or read this section **[differential testing](#differential-testing-)** !!!!!


* **Memory leaks and traditional C issues** : the lib allocates and frees memory dynamically in continuous way , i used [valgrind](https://valgrind.org/) to make sure each functions doesn't leak any memory


## Features

- Arbitrary precision integer arithmetic
- Addition, subtraction, multiplication, division
- Modular arithmetic and exponentiation
- GCD calculation
- Primality testing (Miller-Rabin, Fermat)
- Random number generation
- No external dependencies (self-contained)

# Algorithms : 
 based on the current version of this library : 

- **addition** : Standard grade‑school addition .
- **subtraction** : Standard grade‑school subtraction .
- **multiplication** : standard long multiplication .
- **division** : long division or call it knuth's algorithm d . 

- **Modular inverse** : Extended Euclidean Algorithm .
- **Modular Exponentiation** : Binary exponentiation (square‑and‑multiply) .

- **GCD** : Euclidean algorithm .

- **Primality Testing** : Miller–Rabin , fermat (not reliable due to Carmichael numbers) 

- **Random Number Generation** : OS‑provided , (was built upon this [my cross-platform RNG](https://github.com/RamiBrahimi-c/RandomLib---Cross-Platform-Random-Number-Generator) )


## Requirements
the project uses just the standard C lib , if you compile on windows make sure to include the `-lbcrypt` flag 

### Compiler
- GCC (GNU Compiler Collection) 4.9 or later
- Clang 3.5 or later (should work, but GCC is recommended)

### Build Tools
- `make` (GNU Make 3.81 or later)
- `ar` (for static library creation, comes with binutils)
- Standard C library (libc)

### Optional
- Git (for cloning the repository)

**No external libraries required!** The library is completely self-contained.


## Building

well for **windows users** specifically if you want to make you life easier just check [the releases](https://github.com/RamiBrahimi-c/big-ar9am/releases) you can find the static lib for windows-86_64 . 
also that contains static lib for linux fellas .

### Build Everything (Library + Main)
```bash
make all
```
This creates:
- `lib/libbigra9m.a` - Static library
- `bin/main` - Main executable (useless for now)

### Build Only the Library
```bash
make lib
```
Creates `lib/libbigra9m.a`

### Build Only the Main Program
```bash
make main
```

## Usage

### Linking Against the Library

```bash
# Basic usage 
gcc -I/path/to/bigra9m/include your_program.c -L/path/to/bigra9m/lib -lbigra9m -o your_program

# Example (from within the project directory)
gcc -I../include my_program.c -L../lib -lbigra9m -o my_program
```

### Example Program

```c
#include <stdio.h>
#include "bigra9m.h"

int main()
{

    BigRa9m a , b , c ; // or BigInt BigRa9m a , b , c ;  
    

    // make sure to initilize it first !!!
    // (use one of the 'inits' functions )
    bigra9m_inits(&a , &b , NULL) ;
    bigra9m_init_str(&c , "123456789987654321") ;
    
    
    // lets assign some HUGE numbers !!!
    bigra9m_assign_str(&a , "-123456876432654321351000650100000") ; 
    bigra9m_assign_uint64_t(&b , 0x123456789 ) ; 
    
    // now we print numbers to check 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ;

    // do some operation on it 
    bigra9m_add(a , b , &c) ;
    

    // print results : 
    printf("a : ") ; 
    bigra9m_print(a) ; 
    printf("b : ") ; 
    bigra9m_print(b) ; 
    printf("c : ") ; 
    bigra9m_print(c) ; 

    // please clean your memory when you finish working !!!!!!
    bigra9m_clears(&a , &b , &c , NULL) ; 


}
```

## Project Structure

```
.
├── include/          # Header files
│   ├── bigra9m.h    # Main library header
│   ├── test.h       # important macros for `tests/test_main.c`
│   └── utils.h      # some useful utils/macros/functions used to help with dynamically allocating 
├── src/             # Source files
│   ├── main.c       # Main program (useless)
│   └── brz/         # Library implementation
├── lib/             # Static library (generated)
├── bin/             # Executables (generated)
├── obj/             # Object files (generated)
└── tests/           # Test files
    ├── fun/         # fun programs (calculating : factorial or fibonocci numbers up to 1000 !!! ...)
    ├── output/      # where the testing executables are stored  
    ├── test_*.c     # Unit tests for individual operations
    ├── script.sh    # bash file responsible for running the differential testing 
    ├── main.py      # important for differential testing 
    └── test_main.c  # Main interactive test program , used for differential testing too
```

## Cleaning

```bash
# Clean everything
make clean

# Clean only main binaries
make clean-main

# Clean only library
make clean-lib

# Clean only test binaries
make clean-tests
```


## Testing : 

### a whole main test : 
which is `tests/test_main.c`
```
# compile it with : make test-main
make test-main 

# run it 
./tests/output/bin/run_tests_main [OPERATION] [num1] [num2] [num3] ...
```
**NOTE** : number of numbers or arguments differ from operation to another , so make sure you check the table down before running your test ...

examples : 
```bash

# addition
$  ./tests/output/bin/run_tests_main add 51515151515151 320032148186541651 
51515151515151 add 320032148186541651 = 320083663338056802

# multiplication
$  ./tests/output/bin/run_tests_main mul 54155415415 123456789987654321
54155415415 mul 123456789987654321 = 6685853747583832475174758215

# division
$  ./tests/output/bin/run_tests_main div 5415541541556565651516515156 123456789987654321
5415541541556565651516515156 div 123456789987654321 = 43865886534


# generate a random number in range 0 .. 10000000000
$  ./tests/output/bin/run_tests_main rng 10000000000
5785107225


# check if number is prime 
$  ./tests/output/bin/run_tests_main prime_mr 778177574988945185577791728819
prime
$  ./tests/output/bin/run_tests_main prime_mr 455454544444444442112232153654
composite


# generate a prime in the range of 0 .. 10000000000
$  ./tests/output/bin/run_tests_main rng_prime 10000000000
9164038229

# generate a prime in the range of 0 .. 2^(256)-1
$  ./tests/output/bin/run_tests_main rng_prime_bits 256
bits : 256 
31024956291324549512809092473497486619527665424938344891865858460781360719627

# generate a prime with exactly 256-bits
$  ./tests/output/bin/run_tests_main rng_prime_bits2 256
bits : 256 
90671637999748794998145908032471757153928019144514771379102616782791123821279


```

[OPERATION] : 
|    **operation**   |                                            **what it does**                                            | **Mathematical expression** | **number of arguments** |
|:------------------:|:------------------------------------------------------------------------------------------------------:|-----------------------------|:-----------------------:|
|       **add**      | addition of 2 big nums                                                                                 |         num1 + num2         |            2            |
|       **sub**      | subtraction of 2 big nums                                                                              |         num1 - num2         |            2            |
|       **div**      | division of 2 big nums                                                                                 |         num1 / num2         |            2            |
|       **mul**      | multiplication of 2 big nums                                                                           |         num1 * num2         |            2            |
|     **mul_u64**    | multiplication of bigra9m and uint64_t num                                                             |         num1 * num2         |            2            |
|       **pow**      | exponentiation of 2 bignums                                                                            |         num1 ^ num2         |            2            |
|       **mod**      | modulo operation                                                                                       |         num1 % num2         |            2            |
|     **mod_exp**    | modulo exponentiation                                                                                  |     (num1 ^ num2) % num3    |            3            |
|     **mod_inv**    | modulo inverse                                                                                         |       num1^(-1) % num2      |            2            |
|       **eq**       | check equality                                                                                         |         num1 == num2        |            2            |
|       **bg**       | check if first number is strictly greater than the second                                              |         num1 > num2         |            2            |
|       **beq**      | check if first number is greater or equal than the second                                              |         num1 >= num2        |            2            |
|       **lw**       | check if first number is strictly lower than the second                                                |         num1 < num2         |            2            |
|       **leq**      | check if first number is lower or equal than the second                                                |         num1 <= num2        |            2            |
|    **prime_fr**    | check if the number is prime using fermat test                                                         |              /              |            1            |
|   **prime_fr_f**   | check if the number is prime using fermat test ( but with modulo exponentiation which make it faster ) |              /              |            1            |
|    **prime_mr**    | check if the number is prime using miller-rabin test                                                   |              /              |            1            |
|       **gcd**      | calculated the GCD (Greatest Common Divisor)                                                           |       gcd(num1 , num2)      |            2            |
|      **even**      | checks if number is even                                                                               |        num1 % 2 == 0        |            1            |
|       **odd**      | checks if number is odd                                                                                |        num1 % 2 == 1        |            1            |
|       **rng**      | generate random number in the range 0 to ( max -1 )                                                    |              /              |            1            |
|    **rng_bits**    | generate random number in the range 0 to 2^(max) - 1                                                   |              /              |            1            |
|    **rng_bits2**   | generate random number with exactly bits length                                                        |              /              |            1            |
|    **rng_prime**   | generate random prime number in the range 0 to ( max -1 )                                              |              /              |            1            |
| **rng_prime_bits** | generate random prime number in the range 0 to 2^(max) - 1                                             |              /              |            1            |


### uni-tests : 
or kind of , they are found in `tests/` in this format exactly : `tests/test_*` : 
where each functions is tested

```bash
# to compile and run a uni-test in tests/test_example.c : 

make test-example

```

### differential testing :

first it requires at least *Python 3.12.3* plus : 
- `tests/script.sh` 
- `tests/main.py` : our main python program 
- `tests/test_main.c` : it needs its executable actually which i suppose it would be `tests/output/bin/run_tests_main` or `tests/output/bin/run_tests_main.exe`

so if you want to run `N` test side to side with py : 
- check `line 19` in `tests/script.sh` and edit `NUMBER_OF_TESTS` for the number you want .
- check `line 20` in `tests/script.sh` and edit `operation` for the operation you want to test (**NOTE** : the operation should be one of the ones mentioned in the table plus it should be in `tests/main.py` , right now there are not a lot of operations in the py file ~~) .

**NOTE** it also worth mentioning that right now if we encounter a difference in results the test is stopped immediately ! (maybe i need to figure out smth better) .    


## Known Issues

i wont be hard on it but 

- [ ] Multiplication algorithm is O(n²) - slow for very large numbers
- [ ] Division could be optimized further ?
- [ ] Some edge cases with negative numbers might not be fully tested
- [ ] Fermat primality test can be fooled by Carmichael numbers
- [ ] No constant-time operations (not suitable for cryptographic use against side-channel attacks)
- [x] ~~the base choice is not really wise~~ 
- [x] ~~the bigra9m_print just works with the current *BASE* which is *100*~~ 


## Future Improvements

- [ ] Implement Karatsuba multiplication for better performance
- [ ] Add elliptic curve operations
- [ ] Implement Barrett reduction for faster modular arithmetic
- [ ] Add constant-time operations for cryptographic safety
- [ ] Optimize division algorithm
- [ ] Add more primality tests (Solovay-Strassen, Baillie-PSW)
- [ ] Create proper API documentation
- [ ] Add benchmarks


## Acknowledgments
-  knuth's art of computer programming volume 2 . (especially section 4.3.1 page 272 about the algorithm d )

- [Python](https://www.python.org/) for differential testing
- [Valgrind](https://valgrind.org/) for memory checking


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
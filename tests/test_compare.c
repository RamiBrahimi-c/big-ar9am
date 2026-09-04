#include <stdio.h>
#include <stdlib.h>
#include "../include/bigra9m.h"

static int failures = 0;
static int checks = 0;

#define EXPECT_INT(desc, expr, expected) do { \
    checks++; \
    int _got = (expr); \
    if (_got != (expected)) { \
        failures++; \
        printf("FAIL: %s -> got %d, expected %d\n", (desc), _got, (expected)); \
    } \
} while (0)

#define EQ(a_str, b_str, expected) do { \
    BigInt _a, _b; \
    bigra9m_init_str(&_a, (a_str)); \
    bigra9m_init_str(&_b, (b_str)); \
    EXPECT_INT("eq(" a_str "," b_str ")", bigra9m_isEqualNum(_a, _b), (expected)); \
    bigra9m_clears(&_a, &_b, NULL); \
} while (0)

#define GE(a_str, b_str, expected) do { \
    BigInt _a, _b; \
    bigra9m_init_str(&_a, (a_str)); \
    bigra9m_init_str(&_b, (b_str)); \
    EXPECT_INT("ge(" a_str "," b_str ")", bigra9m_isBiggerThanNum(_a, _b), (expected)); \
    bigra9m_clears(&_a, &_b, NULL); \
} while (0)

#define GT(a_str, b_str, expected) do { \
    BigInt _a, _b; \
    bigra9m_init_str(&_a, (a_str)); \
    bigra9m_init_str(&_b, (b_str)); \
    EXPECT_INT("gt(" a_str "," b_str ")", bigra9m_isStrictlyBiggerThanNum(_a, _b), (expected)); \
    bigra9m_clears(&_a, &_b, NULL); \
} while (0)

#define LE(a_str, b_str, expected) do { \
    BigInt _a, _b; \
    bigra9m_init_str(&_a, (a_str)); \
    bigra9m_init_str(&_b, (b_str)); \
    EXPECT_INT("le(" a_str "," b_str ")", bigra9m_isLowerThanNum(_a, _b), (expected)); \
    bigra9m_clears(&_a, &_b, NULL); \
} while (0)

#define LT(a_str, b_str, expected) do { \
    BigInt _a, _b; \
    bigra9m_init_str(&_a, (a_str)); \
    bigra9m_init_str(&_b, (b_str)); \
    EXPECT_INT("lt(" a_str "," b_str ")", bigra9m_isStrictlyLowerThanNum(_a, _b), (expected)); \
    bigra9m_clears(&_a, &_b, NULL); \
} while (0)

int main(void) {
    EQ("5", "5", 1);
    EQ("-5", "-5", 1);
    EQ("5", "-5", 0);
    EQ("-5", "5", 0);
    EQ("0", "0", 1);
    EQ("0", "1", 0);
    EQ("0", "-1", 0);
    EQ("1", "0", 0);
    EQ("-1", "0", 0);
    EQ("-1", "-1", 1);
    EQ("-4294967295", "-4294967295", 1);
    EQ("-4294967296", "-4294967296", 1);
    EQ("-4294967297", "-4294967297", 1);
    EQ("4294967296", "4294967296", 1);
    EQ("-4294967296", "4294967296", 0);

    GE("5", "3", 1);
    GE("3", "5", 0);
    GE("5", "5", 1);
    GE("-3", "-5", 1);
    GE("-5", "-3", 0);
    GE("-5", "-5", 1);
    GE("5", "-5", 1);
    GE("-5", "5", 0);
    GE("-5", "0", 0);
    GE("0", "-5", 1);
    GE("0", "5", 0);
    GE("5", "0", 1);
    GE("0", "0", 1);
    GE("-4294967296", "-4294967297", 1);
    GE("-4294967297", "-4294967296", 0);

    GT("5", "3", 1);
    GT("3", "5", 0);
    GT("5", "5", 0);
    GT("-3", "-5", 1);
    GT("-5", "-3", 0);
    GT("-5", "-5", 0);
    GT("5", "-5", 1);
    GT("-5", "5", 0);
    GT("0", "-5", 1);
    GT("-5", "0", 0);
    GT("0", "0", 0);

    LE("3", "5", 1);
    LE("5", "3", 0);
    LE("5", "5", 1);
    LE("-5", "-3", 1);
    LE("-3", "-5", 0);
    LE("-5", "-5", 1);
    LE("-5", "5", 1);
    LE("5", "-5", 0);
    LE("-5", "0", 1);
    LE("0", "-5", 0);
    LE("0", "5", 1);
    LE("5", "0", 0);
    LE("0", "0", 1);
    LE("-4294967297", "-4294967296", 1);
    LE("-4294967296", "-4294967297", 0);

    LT("3", "5", 1);
    LT("5", "3", 0);
    LT("5", "5", 0);
    LT("-5", "-3", 1);
    LT("-3", "-5", 0);
    LT("-5", "-5", 0);
    LT("-5", "5", 1);
    LT("5", "-5", 0);
    LT("-5", "0", 1);
    LT("0", "-5", 0);
    LT("0", "0", 0);

    printf("compare: %d checks, %d failures\n", checks, failures);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

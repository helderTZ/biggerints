#include "gtest/gtest.h"
#include "biggerints.h"

#include <iostream>
#include <string>
#include <algorithm>

std::string to_string(const uint128_t& t) {
    std::string str;

    for (int64_t i = 63; i >= 0; --i) {
        str += std::to_string( (t.hi & (1 << i)) >> i );
    }

    for (int64_t i = 63; i >= 0; --i) {
        str += std::to_string( (t.lo & (1 << i)) >> i );
    }

    return str;
}

std::string to_string(const uint256_t& t) {
    std::string str;
    str += to_string(t.hi);
    str += to_string(t.lo);
    return str;
}

TEST(biggerints, uint128_t_add) {
    uint128_t num1 = {0xFFFF0000ULL, 0xFFFFULL}; // 18446462598732906495
    uint128_t num2 = {0x0000FFFFULL, 0xFFFFULL}; // 281470681808895

    std::cout << "num1: " << to_string(num1) << "\n";
    std::cout << "num2: " << to_string(num2) << "\n";
    num1 = num1 + num2;
    std::cout << "num1: " << to_string(num1) << "\n";

    EXPECT_EQ(num1.lo, 0x1FFFEULL);
    EXPECT_EQ(num1.hi, 0xFFFFFFFFULL);
}

TEST(biggerints, uint128_t_add_with_overflow) {
    uint128_t num1 = {0xFFFF0000ULL, 0xFFFFFFFFULL};
    uint128_t num2 = {0x0ULL,        0x1ULL};

    std::cout << "num1: " << to_string(num1) << "\n";
    std::cout << "num2: " << to_string(num2) << "\n";
    num1 = num1 + num2;
    std::cout << "num1: " << to_string(num1) << "\n";

    EXPECT_EQ(num1.lo, 0x0ULL);
    EXPECT_EQ(num1.hi, 0xFFFF0001ULL);
}

TEST(biggerints, uint128_t_sub) {
    uint128_t num1 = {0xFFFF0000ULL, 0xFFFFULL}; // 18446462598732906495
    uint128_t num2 = {0x0ULL,        0xFFFFULL}; // 65535

    std::cout << "num1: " << to_string(num1) << "\n";
    std::cout << "num2: " << to_string(num2) << "\n";
    num1 = num1 - num2;
    std::cout << "num1: " << to_string(num1) << "\n";

    EXPECT_EQ(num1.lo, 0x0ULL);
    EXPECT_EQ(num1.hi, 0xFFFF0000ULL);
}

TEST(biggerints, uint128_t_sub_with_underflow) {
    uint128_t num1 = {0xFFFF0000ULL, 0x00FFULL};
    uint128_t num2 = {0x0ULL,        0xFFFFULL};

    std::cout << "num1: " << to_string(num1) << "\n";
    std::cout << "num2: " << to_string(num2) << "\n";
    num1 = num1 - num2;
    std::cout << "num1: " << to_string(num1) << "\n";

    EXPECT_EQ(num1.lo, 0x0ULL);
    EXPECT_EQ(num1.hi, 0xFFFF0000ULL);
}
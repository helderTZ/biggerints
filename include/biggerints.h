#ifndef BIGGER_INTS_H_
#define BIGGER_INTS_H_

#include <cstdint>
#include <limits>

struct uint128_t {
    uint64_t hi;
    uint64_t lo;

    uint128_t operator+(const uint128_t& other) const {
        uint128_t result;
        uint64_t carry = overflow_add(this->lo, other.lo) ? 1 : 0;
        result.lo = this->lo + other.lo;
        result.hi = this->hi + other.hi + carry;
        return result;
    }

    uint128_t operator+=(const uint128_t& other) {
        uint64_t carry = overflow_add(this->lo, other.lo) ? 1 : 0;
        this->lo += other.lo;
        this->hi += other.hi + carry;
        return *this;
    }

    uint128_t operator-(const uint128_t& other) const {
        uint128_t result;
        uint64_t carry = underflow_sub(this->lo, other.lo) ? 1 : 0;
        if (other.lo > this->lo) {
            result.lo = other.lo - this->lo;
        } else {
            result.lo = this->lo - other.lo;
        }
        result.hi = this->hi - other.hi - carry;
        return result;
    }

    uint128_t operator-=(const uint128_t& other) {
        uint64_t carry = underflow_sub(this->lo, other.lo) ? 1 : 0;
        if (other.lo > this->lo) {
            this->lo = other.lo - this->lo;
        } else {
            this->lo = this->lo - other.lo;
        }
        this->hi -= other.hi - carry;
        return *this;
    }

    uint128_t operator*(const uint128_t& other) const {
        uint128_t result;
        uint64_t carry = overflow_mul(this->lo, other.lo) ? 1 : 0;
        result.lo = this->lo * other.lo;
        result.hi = this->hi * other.hi + carry;
        return result;
    }

    uint128_t operator*=(const uint128_t& other) {
        uint64_t carry = overflow_mul(this->lo, other.lo) ? 1 : 0;
        this->lo *= other.lo;
        this->hi *= other.hi + carry;
        return *this;
    }

    uint128_t operator^(const uint128_t& other) const {
        uint128_t result;
        result.lo = this->lo ^ other.lo;
        result.hi = this->hi ^ other.hi;
        return result;
    }

    uint128_t operator^=(const uint128_t& other) {
        this->lo ^= other.lo;
        this->hi ^= other.hi;
        return *this;
    }

    bool operator>(const uint128_t& other) const {
        return (this->hi > other.hi) || ( (this->hi == other.hi) && (this->lo > other.lo) );
    }

    bool operator<(const uint128_t& other) const {
        return (this->hi < other.hi) || ( (this->hi == other.lo) && (this->lo < other.lo) );
    }

    bool operator>=(const uint128_t& other) const {
        return (this->hi >= other.hi) || ( (this->hi == other.hi) && (this->lo >= other.lo) );
    }

    bool operator<=(const uint128_t& other) const {
        return (this->hi <= other.hi) || ( (this->hi == other.lo) && (this->lo <= other.lo) );
    }

    bool operator==(const uint128_t& other) const {
        return (this->hi == other.hi) && (this->lo == other.lo);
    }

    bool underflow_sub(uint64_t a, uint64_t b) const {
        return b > a;
    }

    bool overflow_add(uint64_t a, uint64_t b) const {
        if ( (b != 0 && a > static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) - b) ||
             (a != 0 && b > static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) - a)
        ) {
            return true;
        }
        return false;
    }

    bool overflow_mul(uint64_t a, uint64_t b) const {
        if ( (b != 0 && a > static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) / b) ||
             (a != 0 && b > static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) / a)
        ) {
            return true;
        }
        return false;
    }
};

struct uint256_t {
    uint128_t hi;
    uint128_t lo;

    uint256_t operator+(const uint256_t& other) const {
        uint256_t result;
        bool carry = overflow_add(this->lo, other.lo) ? 1 : 0;
        result.lo = this->lo + other.lo;
        result.hi = this->hi + other.hi + uint128_t{carry, 0};
        return result;
    }

    uint256_t operator+=(const uint256_t& other) {
        uint128_t carry = overflow_add(this->lo, other.lo) ? uint128_t{0, 1} : uint128_t{0, 0};
        this->lo += other.lo;
        this->hi += other.hi;
        this->hi += carry;
        return *this;
    }

    uint256_t operator-(const uint256_t& other) const {
        uint256_t result;
        uint128_t carry = underflow_sub(this->lo, other.lo) ? uint128_t{0, 1} : uint128_t{0, 0};
        if (other.lo > this->lo) {
            result.lo = other.lo - this->lo;
        } else {
            result.lo = this->lo - other.lo;
        }
        result.hi = this->hi - other.hi - carry;
        return result;
    }

    uint256_t operator-=(const uint256_t& other) {
        uint128_t carry = underflow_sub(this->lo, other.lo) ? uint128_t{0, 1} : uint128_t{0, 0};
        if (other.lo > this->lo) {
            this->lo = other.lo - this->lo;
        } else {
            this->lo -= other.lo;
        }
        this->hi = (this->hi - other.hi) - carry;
        return *this;
    }

    uint256_t operator*(const uint256_t& other) const {
        uint256_t result;
        uint128_t carry = overflow_mul(this->lo, other.lo) ? uint128_t{0, 1} : uint128_t{0, 0};
        result.lo = this->lo * other.lo;
        result.hi = (this->hi * other.hi) + carry;
        return result;
    }

    uint256_t operator*=(const uint256_t& other) {
        uint128_t carry = overflow_mul(this->lo, other.lo) ? uint128_t{0, 1} : uint128_t{0, 0};
        this->lo *= other.lo;
        this->hi *= other.hi;
        this->hi += carry;
        return *this;
    }

    uint256_t operator^(const uint256_t& other) const {
        uint256_t result;
        result.lo = this->lo ^ other.lo;
        result.hi = this->hi ^ other.hi;
        return result;
    }

    uint256_t operator^=(const uint256_t& other) {
        this->lo ^= other.lo;
        this->hi ^= other.hi;
        return *this;
    }

    bool operator>(const uint256_t& other) const {
        return (this->hi > other.hi) || ( (this->hi == other.hi) && (this->lo > other.lo) );
    }

    bool operator<(const uint256_t& other) const {
        return (this->hi < other.hi) || ( (this->hi == other.lo) && (this->lo < other.lo) );
    }

    bool operator>=(const uint256_t& other) const {
        return (this->hi >= other.hi) || ( (this->hi == other.hi) && (this->lo >= other.lo) );
    }

    bool operator<=(const uint256_t& other) const {
        return (this->hi <= other.hi) || ( (this->hi == other.lo) && (this->lo <= other.lo) );
    }

    bool operator==(const uint256_t& other) const {
        return (this->hi == other.hi) && (this->lo == other.lo);
    }

    bool underflow_sub(uint128_t a, uint128_t b) const {
        return b > a;
    }

    bool overflow_mul(const uint128_t& a, const uint128_t& b) const {
        if (a.overflow_mul(a.lo, b.lo) || a.overflow_mul(a.hi, b.hi)) {
            return true;
        }
        return false;
    }

    bool overflow_add(const uint128_t& a, const uint128_t& b) const {
        if (a.overflow_add(a.lo, b.lo) || a.overflow_add(a.hi, b.hi)) {
            return true;
        }
        return false;
    }
};

#endif  // BIGGER_INTS_H_

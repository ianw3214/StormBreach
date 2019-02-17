#pragma once

#include <vector>

constexpr unsigned int BIT_PER_UINT = static_cast<unsigned int>(sizeof(unsigned int));

class BitArray {
public:
    BitArray();
    BitArray(unsigned int size);

    BitArray& operator&=(const BitArray& other);
    BitArray& operator|=(const BitArray& other);
    BitArray& operator|=(unsigned int bit);

    bool operator|(unsigned int bit);
private:
    std::vector<unsigned int> bits;
};
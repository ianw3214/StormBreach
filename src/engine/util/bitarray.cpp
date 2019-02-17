#include "bitarray.hpp"

BitArray::BitArray() {
    // Initialize with just one bit field of 0
    bits.push_back(0);
}
BitArray::BitArray(unsigned int size) {
    unsigned int num_zeros = (size / BIT_PER_UINT) + (size % BIT_PER_UINT == 0 ? 0 : 1);
    bits = std::vector<unsigned int>(num_zeros,0);
}

BitArray& BitArray::operator&=(const BitArray& other) {
    while(bits.size() < other.bits.size()) {
        bits.push_back(0);
    }
    for(unsigned int i : bits) {
        if (bits[i] == other.bits[i]) continue;
        for (unsigned int j = 0; j < BIT_PER_UINT; ++j) {
            if ((other.bits[i] & 1 << j) == 0) {
                bits[i] &= ~(1 << j);
            }
        }
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& other) {
    while(bits.size() < other.bits.size()) {
        bits.push_back(0);
    }
    for(unsigned int i : bits) {
        if (bits[i] == other.bits[i]) continue;
        for (unsigned int j = 0; j < BIT_PER_UINT; ++j) {
            if ((other.bits[i] & 1 << j) > 0) {
                bits[i] |= 1 << j;
            }
        }
    }
    return *this;
}

#include <iostream>
BitArray& BitArray::operator|=(unsigned int bit) {
    unsigned int size = (bit / BIT_PER_UINT) + (bit % BIT_PER_UINT == 0 ? 0 : 1);
    while(bits.size() < size) {
        bits.push_back(0);
    }
    unsigned int index = 0;
    while(bit >= BIT_PER_UINT) {
        bit -= BIT_PER_UINT;
        index++;
    }
    bits[index] |= 1 << bit;
    return *this;
}

bool BitArray::operator|(unsigned int bit) {
    unsigned int size = (bit / BIT_PER_UINT) + (bit % BIT_PER_UINT == 0 ? 0 : 1);
    if (bits.size() < size) return false;
    unsigned int index = 0;
    while(bit >= BIT_PER_UINT) {
        bit -= BIT_PER_UINT;
        index++;
    }

    return (bits[index] & (1 << bit)) > 0;
}
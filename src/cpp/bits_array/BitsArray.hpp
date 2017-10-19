/*
 * Bitarray.hpp
 *
 *  Created on: Oct 2, 2017
 *      Author: Or Nagar
 */

#ifndef BITARRAY_HPP_
#define BITARRAY_HPP_

#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include <cstdio>

namespace ilrd {

template<size_t N>
class BitsArray {
private:
    class Bit;
public:
    explicit BitsArray() noexcept;
    ~BitsArray() noexcept = default ;
    BitsArray(const BitsArray&) noexcept = default;
    BitsArray& operator=(const BitsArray&) noexcept = default;

    void flip_bit(size_t idx) throw(std::out_of_range);
    void flip_all() noexcept;
    std::size_t count_bits() noexcept;
    void set(size_t idx, bool val) throw(std::out_of_range);
    bool get(size_t idx) throw(std::out_of_range);

    bool operator==(const BitsArray&) const noexcept;
    bool operator!=(const BitsArray&) const noexcept;

    BitsArray& operator|=(const BitsArray&) noexcept;
    BitsArray& operator&=(const BitsArray&) noexcept;
    BitsArray& operator^=(const BitsArray&) noexcept;
    BitsArray& operator>>=(std::size_t n) noexcept;
    BitsArray& operator<<=(std::size_t n) noexcept;

    Bit operator[](size_t idx) noexcept;
    bool operator[](size_t idx) const noexcept;
#ifdef _DEBUG
    void print() const noexcept;
#endif
private:
    typedef size_t WordT;
    static const size_t BITS_IN_IDX = sizeof(WordT) * 8;
    static const size_t ARR_SIZE = N;
    static const WordT MS_BIT = static_cast<WordT>(1) << (BITS_IN_IDX - 1);
    static const WordT LS_BIT = static_cast<WordT>(1);
    std::array<WordT, (N / BITS_IN_IDX) + (N % BITS_IN_IDX != 0)> m_array;

    class Bit {
    public:
        explicit Bit(BitsArray* bitarr, size_t idx) noexcept;
        ~Bit() noexcept = default;
        Bit(const Bit&) noexcept = default;
        Bit& operator=(bool) noexcept;
        Bit& operator=(const Bit&) noexcept;
        operator bool() const noexcept;

    private:
        BitsArray& m_bitarr;
        size_t m_idx;
    };
};

template<size_t N>
inline BitsArray<N>::BitsArray() noexcept : m_array {0} {}

template<size_t N>
void BitsArray<N>::flip_bit(size_t idx) throw(std::out_of_range)
{
    if (idx >= ARR_SIZE) {
        throw std::out_of_range("out of range");
    }

    size_t ch_idx = idx / BITS_IN_IDX;
    size_t bit_idx = idx % BITS_IN_IDX;

    WordT mask = MS_BIT >> bit_idx;
    m_array[ch_idx] ^= mask;
}

template<size_t N>
void BitsArray<N>::flip_all() noexcept
{
    WordT mask = ~0;

    for (auto& i : m_array) {
        i ^= mask;
    }

    size_t bits_in_last_byte = ARR_SIZE % BITS_IN_IDX;
    mask <<= BITS_IN_IDX - bits_in_last_byte;
    m_array[m_array.size() - 1] &= mask;
}

template<size_t N>
size_t BitsArray<N>::count_bits() noexcept
{
    WordT mask = MS_BIT;
    size_t count = 0;

    for (auto& i : m_array) {
        for (size_t j = 0; j < BITS_IN_IDX; ++j) {
            count += ((i & mask) != 0);
            mask >>= 1;
        }
        mask = MS_BIT;
    }

    return count;
}

template<size_t N>
void BitsArray<N>::set(size_t idx, bool val)  throw(std::out_of_range)
{
    if (idx >= ARR_SIZE) {
        throw std::out_of_range("out of range");
    }

    (*this)[idx] = val;
}

template<size_t N>
bool BitsArray<N>::get(size_t idx)  throw(std::out_of_range)
{
    if (idx >= ARR_SIZE) {
        throw std::out_of_range("out of range");
    }

    return (*this)[idx];
}

template<size_t N>
bool BitsArray<N>::operator==(const BitsArray<N>& other) const noexcept
{
    for (int i = 0; i < m_array.size(); ++i) {
        if (m_array[i] != other.m_array[i]) {
            return false;
        }
    }

    return true;
}

template<size_t N>
bool BitsArray<N>::operator!=(const BitsArray<N>& other) const noexcept
{
    return !operator==(other);
}

template<size_t N>
typename BitsArray<N>::Bit BitsArray<N>::operator[](size_t idx) noexcept
{
    return Bit(this, idx);
}

template<size_t N>
bool BitsArray<N>::operator[](size_t idx) const noexcept
{
    return Bit(const_cast<BitsArray<N>*>(this), idx);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator|=(const BitsArray<N>& other) noexcept
{
    for (int i = 0; i < m_array.size(); ++i) {
        m_array[i] |= other.m_array[i];
    }

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator&=(const BitsArray<N>& other) noexcept
{
    for (int i = 0; i < m_array.size(); ++i) {
        m_array[i] &= other.m_array[i];
    }

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator^=(const BitsArray<N>& other) noexcept
{
    for (int i = 0; i < m_array.size(); ++i) {
        m_array[i] ^= other.m_array[i];
    }

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator>>=(std::size_t n) noexcept
{
    size_t i = n, j = 0;
    for (; i < ARR_SIZE; ++j, ++i) {
        (*this)[j] = (*this)[i];
    }

    for (; j < ARR_SIZE; ++j) {
        (*this)[j] = false;
    }

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator<<=(std::size_t n) noexcept
{
    size_t i = ARR_SIZE - n, j = ARR_SIZE;
    for (; i > n; --j, --i) {
        (*this)[j-1] = (*this)[i-1];
    }

    for (; i > 0; --j, --i) {
        (*this)[j-1] = (*this)[i-1];
        (*this)[i-1] = false;
    }

    return *this;
}

/*****************************BIT**************************************/
template<size_t N>
BitsArray<N>::Bit::Bit(BitsArray<N>* bitarr, size_t idx) noexcept :
                m_bitarr(*bitarr), m_idx(idx) {}

template<size_t N>
typename BitsArray<N>::Bit& BitsArray<N>::Bit::operator=(bool val) noexcept
{
    size_t ch_idx = m_idx / BITS_IN_IDX;
    size_t bit_idx = m_idx % BITS_IN_IDX;

    WordT mask = MS_BIT;
    mask >>= bit_idx;

    if (val) {
        m_bitarr.m_array[ch_idx] |= mask;
    } else {
        m_bitarr.m_array[ch_idx] &= ~mask;
    }

    return *this;
}

template<size_t N>
typename BitsArray<N>::Bit& BitsArray<N>::Bit::operator=(const Bit& other) noexcept
{
    size_t ch_idx = other.m_idx / BITS_IN_IDX;
    size_t bit_idx = other.m_idx % BITS_IN_IDX;

    WordT mask = MS_BIT;
    mask >>= bit_idx;

    if (other.m_bitarr.m_array[ch_idx] & mask) {
        operator=(true);
    } else {
        operator=(false);
    }

    return *this;
}

template<size_t N>
BitsArray<N>::Bit::operator bool() const noexcept
{

    size_t ch_idx = m_idx / BITS_IN_IDX;
    size_t bit_idx = m_idx % BITS_IN_IDX;

    WordT mask = MS_BIT;
    mask >>= bit_idx;

    return (m_bitarr.m_array[ch_idx] & mask);
}

/*********************************************************************/
#ifdef _DEBUG
template<size_t N>
void BitsArray<N>::print() const noexcept
{
    WordT mask = MS_BIT;
    size_t i = 0;
    size_t k = 0;
    int arr[N];

    for (i = 0; i < m_array.size() - 1; ++i) {
        for (size_t j = 0; j < BITS_IN_IDX; ++j, ++k) {
            if ((m_array[i] & mask) != 0) {
                arr[k] = 1;
            } else {
                arr[k] = 0;
            }
            mask >>= 1;
        }
        mask = MS_BIT;
    }

    size_t left_over = ARR_SIZE % BITS_IN_IDX;
    for (size_t j = 0; j < left_over; ++j, ++k) {
        if ((m_array[i] & mask) != 0) {
            arr[k] = 1;
        } else {
            arr[k] = 0;
        }
        mask >>= 1;
    }

    for (k = ARR_SIZE; k > 0; --k) {
        std::cout << " " << arr[k - 1] << " ";
    }

    std::cout << std::endl;
}

} // namespace ilrd
#endif //_DEBUG

#endif /* BITARRAY_HPP_ */

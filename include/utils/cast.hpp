#pragma once

#include <cstdint>
#include <deque>
#include <stdexcept>
#include <type_traits>

namespace utils {
template <class T, uint8_t size>
std::deque<bool> Cast(T value) {
	if(!std::is_arithmetic<T>::value) {
		throw std::invalid_argument("The type can't be cast");
	}

	std::deque<bool> result;
	for(size_t shift{}; shift < size; ++shift) {
		result.push_front((value >> shift) & 0x1);
	}

	return result;
}
} // namespace utils
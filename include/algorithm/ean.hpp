/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

#include <array>
#include <cstdint>
#include <deque>
#include <map>
#include <stdexcept>
#include <string>

#include "utils/cast.hpp"

namespace algorithm {
const std::map<char, std::deque<uint8_t>> symbol_table{{'G',
														{0b0100111,
														 0b0110011,
														 0b0011011,
														 0b0100001,
														 0b0011101,
														 0b0111001,
														 0b0000101,
														 0b0010001,
														 0b0001001,
														 0b0010111}},

													   {'R',
														{0b1110010,
														 0b1100110,
														 0b1101100,
														 0b1000010,
														 0b1011100,
														 0b1001110,
														 0b1010000,
														 0b1000100,
														 0b1001000,
														 0b1110100}},

													   {'L',
														{0b0001101,
														 0b0011001,
														 0b0010011,
														 0b0111101,
														 0b0100011,
														 0b0110001,
														 0b0101111,
														 0b0111011,
														 0b0110111,
														 0b0001011}}};

template <uint8_t size>
class EAN;

template <>
class EAN<13> {
public:
	static const int kCodeSize		= 12;
	static const int kBarZoneAmount = 95;

	static const std::deque<std::string> structure_table;

public:
	using Code	  = std::array<uint8_t, kCodeSize>;
	using BarCode = std::deque<bool>;

public:
	/**
	 * @brief Construct a new EAN object
	 * 
	 * @param code the code to encode into EAN13
	 */
	EAN(Code code) : code_{code} {}

public:
	/**
	 * @brief Encode the code to EAN13
	 * 
	 * @return BarCode the bar code indicating, which bars should be black or white
	 */
	BarCode Encode() const {
		BarCode result{};

		const auto edge_marker	 = utils::Cast<uint8_t, 3>(0b101);
		const auto center_marker = utils::Cast<uint8_t, 5>(0b01010);

		// Start the code with the edge markers
		std::copy(edge_marker.begin(), edge_marker.end(), back_inserter(result));

		// Append the first section of the code
		for(uint8_t index{1}; index <= kCodeSize / 2; ++index) {
			const auto value = code_.at(index);
			const auto encoded_value =
				EncodeValue(value, index - 1); // The first symbol is not coded, so it's
			const auto barcode = utils::Cast<uint8_t, 7>(encoded_value);

			std::copy(barcode.begin(), barcode.end(), back_inserter(result));
		}

		// Add the separator
		std::copy(center_marker.begin(), center_marker.end(), back_inserter(result));

		// Append the last section of the code
		for(uint8_t index{(kCodeSize / 2) + 1}; index < kCodeSize; ++index) {
			const auto value		 = code_.at(index);
			const auto encoded_value = EncodeValue(value, index);
			const auto barcode		 = utils::Cast<uint8_t, 7>(encoded_value);

			std::copy(barcode.begin(), barcode.end(), back_inserter(result));
		}

		// Here goes the checksum...
		const auto encoded_value = EncodeValue(CalculateChecksum(), kCodeSize + 1);
		const auto barcode		 = utils::Cast<uint8_t, 7>(encoded_value);
		std::copy(barcode.begin(), barcode.end(), back_inserter(result));

		// Add the checksum to the end of the code
		std::copy(edge_marker.begin(), edge_marker.end(), back_inserter(result));

		return result;
	}

protected:
	/**
	 * @brief Calculate the checksum of the given code
	 * 
	 * @return uint8_t the checksum
	 */
	uint8_t CalculateChecksum() const {
		uint8_t checksum{};
		for(uint8_t index{}; index < code_.size(); ++index) {
			checksum += code_.at(index) * ((index % 2 == 0) ? 3 : 1);
		}
		return checksum % 10;
	}

	/**
	 * @brief Encode a single symbol using one of the three EAN13 tables 
	 * 
	 * @param value the symbol to encode
	 * @param index the index of the symbol
	 * @return uint8_t the symbol, but encoded in EAN13 system
	 */
	uint8_t EncodeValue(uint8_t value, uint8_t index) const {
		// Including the checksum
		if(index > kCodeSize + 1) {
			throw std::out_of_range("The position of the value is incorect. Abort.");
		}

		// Find the right table to get the encoded symbol
		const uint8_t& type_index	 = code_.at(0);
		const std::string& structure = structure_table.at(type_index);
		const char code_type =
			(index < (kCodeSize / 2))
				? structure.at(index)
				: 'R'; // If the position is high enough, then the value should be coded using the R-code table
		const std::deque<uint8_t>& code_table = symbol_table.at(code_type);

		return code_table.at(value);
	}

protected:
	Code code_;
};

const std::deque<std::string> EAN<13>::structure_table{"LLLLLL",
													   "LLGLGG",
													   "LLGGLG",
													   "LLGGGL",
													   "LGLLGG",
													   "LGGLLG",
													   "LGGGLL",
													   "LGLGLG",
													   "LGLGGL",
													   "LGGLGL"};
} // namespace algorithm
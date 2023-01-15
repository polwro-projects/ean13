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

#include "algorithm/ean.hpp"
#include "image/svg.hpp"
#include "image/svg/rectangle.hpp"

namespace image {
template <class T>
class BarCodeImage;

template <>
class BarCodeImage<algorithm::EAN<13>> : public SVG {
	const double kSmallBarPrescaller = 0.9;

public:
	/**
	 * @brief Construct a new BarCodeImage object
	 * 
	 * @param width the width of the resulting image
	 * @param height the height of the resulting image
	 */
	BarCodeImage(double width, double height)
		: SVG{width, height}, kLineWidth{width / algorithm::EAN<13>::kBarZoneAmount} {}

public:
	/**
	 * @brief Generate the image out of the given EAN13 code
	 * 
	 * @param value the EAN13 code for which image will be generated
	 */
	void Generate(const algorithm::EAN<13>& value) {
		const auto& bar_values = value.Encode();
		for(uint32_t index{}; index < bar_values.size(); ++index) {
			// Check if the bar should be drawn at all
			const auto bar = bar_values.at(index);
			if(!bar) {
				continue;
			}

			// Create a bar
			auto rectangle = std::make_shared<svg::Rectangle>(
				index * kLineWidth,
				0,
				kLineWidth,
				height_ * (IsBarSmall(index) ? kSmallBarPrescaller : 1.0));
			rectangle->SetColor("black");

			// Add the bar to the image
			Add(rectangle);
		}

		// Fill the background
		auto background = std::make_shared<svg::Rectangle>(0, 0, width_, height_);
		background->SetColor("white");
		Add(background);
	}

	/**
	 * @brief Check if the bar should be small
	 * 
	 * @param index the index of the bar
	 * @return true if the bar should be small
	 * @return false otherwise
	 */
	inline static bool IsBarSmall(uint32_t index) {
		switch(index) {
		case 0:
		case 1:
		case 2:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 92:
		case 93:
		case 94:
			return false;
		}

		return true;
	}

protected:
	const double kLineWidth;
};
} // namespace image
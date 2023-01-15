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

#include <string>

namespace image {
namespace svg {
class Shape {
public:
	/**
	 * @brief Construct a new Shape object
	 * 
	 * @param x the X coordinate of the given shape
	 * @param y the Y coordinate of the given shape
	 */
	Shape(double x, double y);

public:
	/**
	 * @brief Set the color of the shape
	 * 
	 * @param value the color's name
	 */
	void SetColor(std::string value);

	/**
	 * @brief The stream where to put the SVG blocks for the shape
	 * 
	 * @param stream the stream to use
	 * @return std::ostream& the same stream
	 */
	virtual std::ostream& operator<<(std::ostream& stream) const = 0;

protected:
	double x_;
	double y_;

	std::string color_{"white"};
};
} // namespace svg
} // namespace image
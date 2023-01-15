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

#include "image/svg/shape.hpp"

namespace image {
namespace svg {
class Rectangle : virtual public Shape {
public:
	/**
	 * @brief Construct a new Rectangle object
	 * 
	 * @param x the X coordinate of the given rectangle
	 * @param y the Y coordinate of the given rectangle
	 * @param width the width of the rectangle
	 * @param height the height of the current rectangle
	 */
	Rectangle(double x, double y, double width, double height);

public:
	/**
	 * @brief The stream where to put the SVG blocks for the shape
	 * 
	 * @param stream the stream to use
	 * @return std::ostream& the same stream
	 */
	std::ostream& operator<<(std::ostream& stream) const override;

protected:
	double width_;
	double height_;
};
} // namespace svg
} // namespace image
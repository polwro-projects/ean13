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

#include "image/svg/rectangle.hpp"

#include <sstream>

namespace image {
namespace svg {
Rectangle::Rectangle(double x, double y, double width, double height)
	: Shape{x, y}, width_{width}, height_{height} {}

std::ostream& Rectangle::operator<<(std::ostream& stream) const {
	stream << "<rect x=\"" << x_ << "\" y=\"" << y_ << "\" width=\"" << width_ << "\" height=\""
		   << height_ << "\" fill=\"" << color_ << "\" />";
	return stream;
}
} // namespace svg
} // namespace image
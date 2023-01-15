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

#include "image/svg.hpp"

namespace image {
SVG::SVG(double width, double height) : width_{width}, height_{height} {}

void SVG::Add(std::shared_ptr<svg::Shape> value) {
	// TODO : add checks for the shape

	shapes_.push_front(value);
}

std::ostream& SVG::operator<<(std::ostream& stream) {
	// Add the header of the file
	stream << "<svg version=\"1.1\" width =\"" << width_ << "\" height=\"" << height_
		   << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

	// Add the shapes to the output
	for(const auto& shape : shapes_) {
		shape->operator<<(stream);
		stream << std::endl;
	}

	// Close the SVG block
	stream << "</svg>";

	return stream;
}
} // namespace image
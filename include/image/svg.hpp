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

#include <forward_list>
#include <memory>
#include <ostream>
#include <string>

#include "image/svg/shape.hpp"

namespace image {
class SVG {
public:
	/**
	 * @brief Construct a new SVG object
	 * 
	 * @param width the width of the resulting image
	 * @param height the height of the resulting image
	 */
	SVG(double width, double height);

public:
	/**
	 * @brief Add the shape into the image
	 * 
	 * @param value the shape to add
	 */
	void Add(std::shared_ptr<svg::Shape> value);

public:
	/**
	 * @brief Output the content of the file to the stream
	 * 
	 * @param stream the stream to output the file to
	 * @return std::ostream& the same stream from the input
	 */
	std::ostream& operator<<(std::ostream& stream);

protected:
	double width_;
	double height_;
	std::forward_list<std::shared_ptr<svg::Shape>> shapes_;
};
} // namespace image
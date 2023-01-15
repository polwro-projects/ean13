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

#include <fstream>
#include <string>

#include "algorithm/ean.hpp"
#include "image/barcodeimage.hpp"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		throw std::runtime_error("There are not enough arguments");
	}

	uint8_t index{};
	char* input = argv[1];
	algorithm::EAN<13>::Code code{};
	while(input[index] != '\0' && index <= code.size()) {
		code.at(index) = input[index] - '0';
		++index;
	}

	algorithm::EAN<13> ean(code);
	image::BarCodeImage<algorithm::EAN<13>> image(800, 480);
	image.Generate(ean);

	std::ofstream stream{"output.svg"};
	image.operator<<(stream);

	return 0;
}
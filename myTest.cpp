#include "Halide.h"

// We'll also include stdio for printf.
#include <stdio.h>

int mytest() {

	/*
	Halide::Func gradient;


	Halide::Var x, y;


	Halide::Expr e = x + y;

	gradient(x, y) = e;


	Halide::Buffer<int32_t> output = gradient.realize(5, 5);

	for (int j = 0; j < output.height(); j++) {
		for (int i = 0; i < output.width(); i++) {
			// We can access a pixel of an Buffer object using similar
			// syntax to defining and using functions.
				printf(" %d ",output(i, j));
		}
		printf(" \n");
	}
	printf(" \n");
	printf(" \n");
	printf(" \n");

	Halide::Func brighter;

	Halide::Expr value = output(x, y);

	value = Halide::cast<float>(value);


	value = value * 2.f;

	value = Halide::cast<int32_t>(value);
	brighter(x, y) = value;

	Halide::Buffer<int32_t> output2 =
		brighter.realize(5, 5);

	for (int j = 0; j < output.height(); j++) {
		for (int i = 0; i < output.width(); i++) {
			// We can access a pixel of an Buffer object using similar
			// syntax to defining and using functions.
			printf(" %d ", output2(i, j));
		}
		printf(" \n");
	}

	printf(" \n");
	printf(" \n");
	printf(" \n");
	Halide::Buffer<uint8_t> planar_input(5, 5, 3);
	std::cout << planar_input.height() << std::endl;
	std::cout << planar_input.width() << std::endl;
	for (int j = 0; j < planar_input.height(); j++) {
		for (int i = 0; i < planar_input.width(); i++) {
			for (int k = 0; k < 3; k++) {
				planar_input(i, j, k) = 0;
			}
		}
	}

	for (int j = 0; j < planar_input.height(); j++) {
		for (int i = 0; i < planar_input.width(); i++) {
			
			// We can access a pixel of an Buffer object using similar
			// syntax to defining and using functions.
			printf(" %d ", planar_input(i, j, 2));
		}
		printf(" \n");
	}
	*/

	// radar code
	Halide::Buffer<float> input(10, 1, 3); // w * h * 3
	for (int j = 0; j < input.height(); j++) {
		for (int i = 0; i < input.width(); i++) {
			for (int k = 0; k < 3; k++) {
				input(i, j, k) = 1;
			}
		}
	}

	for (int j = 0; j < input.height(); j++) {
		for (int i = 0; i < input.width(); i++) {
			for (int k = 0; k < 3; k++) {
				printf(" %d ", input(i, j, k));
			}
			printf(" \n");
		}
		printf(" \n");
	}

	Halide::Func transformColod;


	Halide::Var x, y;

	Halide::Var c;
	Halide::Expr xCoor = input(x, y, 0);
	Halide::Expr yCoor = input(x, y, 1);
	Halide::Expr zCoor = input(x, y, 2);

	xCoor = Halide::cast<float>(xCoor);
	yCoor = Halide::cast<float>(yCoor);
	zCoor = Halide::cast<float>(zCoor);

	std::cout << "aa\n";
	std::cout << " input.channels() " << input.channels() << std::endl;
	xCoor += 10;
	yCoor += 20;
	zCoor += 30;

	//xCoor = Halide::cast<float>(xCoor);
	//yCoor = Halide::cast<float>(yCoor);
	//zCoor = Halide::cast<float>(zCoor);

	//transformColod(x, y, 0) = xCoor;
	//transformColod(x, y, 1) = yCoor;
	//transformColod(x, y, 2) = zCoor;
	// 2) It requires a select, which can impact performance if not
	// bounded and unrolled:
	// brighter.bound(c, 0, 3).unroll(c);
	
	// 参考 lesson 13
	// TODO: 这个操作要求循环展开！
	transformColod(x, y, c) = mux(c, { xCoor , yCoor, zCoor });

	// For each pixel of the input image.

	/*
	Halide::Var x, y, c;
	Halide::Expr value = input(x, y, c);

	// Cast it to a floating point value.
	value = Halide::cast<float>(value);

	// Multiply it by 1.5 to brighten it. Halide represents real
	// numbers as floats, not doubles, so we stick an 'f' on the end
	// of our constant.
	value = value * 3;

	// Clamp it to be less than 255, so we don't get overflow when we
	// cast it back to an 8-bit unsigned int.
	value = Halide::min(value, 255.0f);

	// Cast it back to an 8-bit unsigned integer.
	value = Halide::cast<uint8_t>(value);

	// Define the function.
	transformColod(x, y, c) = value;
	*/
	//Halide::Buffer<float> output2(10, 1, 3);

	Halide::Buffer<float> output2 =
		transformColod.realize(input.width(), input.height(), 3);
	//transformColod.realize(output2);

	std::cout << "bb\n";
	for (int j = 0; j < output2.height(); j++) {
		for (int i = 0; i < output2.width(); i++) {
			for (int k = 0; k < output2.channels(); k++) {
				printf(" %f ", output2(i, j, k));
			}
			printf(" \n");
		}
		printf(" \n");
	}
	return 0;
}

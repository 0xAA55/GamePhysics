#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/common.hpp>

namespace GamePhysics
{
	using namespace glm;

	// Vector int
	
	extern template vec<1, int, lowp>;
	extern template vec<2, int, lowp>;
	extern template vec<3, int, lowp>;
	extern template vec<4, int, lowp>;

	extern template vec<1, int, mediump>;
	extern template vec<2, int, mediump>;
	extern template vec<3, int, mediump>;
	extern template vec<4, int, mediump>;

	extern template vec<1, int, highp>;
	extern template vec<2, int, highp>;
	extern template vec<3, int, highp>;
	extern template vec<4, int, highp>;

	extern template vec<1, int, defaultp>;
	extern template vec<2, int, defaultp>;
	extern template vec<3, int, defaultp>;
	extern template vec<4, int, defaultp>;

	extern template vec<1, i8, lowp>;
	extern template vec<2, i8, lowp>;
	extern template vec<3, i8, lowp>;
	extern template vec<4, i8, lowp>;

	extern template vec<1, i8, mediump>;
	extern template vec<2, i8, mediump>;
	extern template vec<3, i8, mediump>;
	extern template vec<4, i8, mediump>;

	extern template vec<1, i8, highp>;
	extern template vec<2, i8, highp>;
	extern template vec<3, i8, highp>;
	extern template vec<4, i8, highp>;

	extern template vec<1, i8, defaultp>;
	extern template vec<2, i8, defaultp>;
	extern template vec<3, i8, defaultp>;
	extern template vec<4, i8, defaultp>;

	extern template vec<1, i16, lowp>;
	extern template vec<2, i16, lowp>;
	extern template vec<3, i16, lowp>;
	extern template vec<4, i16, lowp>;

	extern template vec<1, i16, mediump>;
	extern template vec<2, i16, mediump>;
	extern template vec<3, i16, mediump>;
	extern template vec<4, i16, mediump>;

	extern template vec<1, i16, highp>;
	extern template vec<2, i16, highp>;
	extern template vec<3, i16, highp>;
	extern template vec<4, i16, highp>;

	extern template vec<1, i16, defaultp>;
	extern template vec<2, i16, defaultp>;
	extern template vec<3, i16, defaultp>;
	extern template vec<4, i16, defaultp>;

	extern template vec<1, i32, lowp>;
	extern template vec<2, i32, lowp>;
	extern template vec<3, i32, lowp>;
	extern template vec<4, i32, lowp>;

	extern template vec<1, i32, mediump>;
	extern template vec<2, i32, mediump>;
	extern template vec<3, i32, mediump>;
	extern template vec<4, i32, mediump>;

	extern template vec<1, i32, highp>;
	extern template vec<2, i32, highp>;
	extern template vec<3, i32, highp>;
	extern template vec<4, i32, highp>;

	extern template vec<1, i32, defaultp>;
	extern template vec<2, i32, defaultp>;
	extern template vec<3, i32, defaultp>;
	extern template vec<4, i32, defaultp>;

	extern template vec<1, i64, lowp>;
	extern template vec<2, i64, lowp>;
	extern template vec<3, i64, lowp>;
	extern template vec<4, i64, lowp>;

	extern template vec<1, i64, mediump>;
	extern template vec<2, i64, mediump>;
	extern template vec<3, i64, mediump>;
	extern template vec<4, i64, mediump>;

	extern template vec<1, i64, highp>;
	extern template vec<2, i64, highp>;
	extern template vec<3, i64, highp>;
	extern template vec<4, i64, highp>;

	extern template vec<1, i64, defaultp>;
	extern template vec<2, i64, defaultp>;
	extern template vec<3, i64, defaultp>;
	extern template vec<4, i64, defaultp>;

	// Vector uint

	extern template vec<1, uint, lowp>;
	extern template vec<2, uint, lowp>;
	extern template vec<3, uint, lowp>;
	extern template vec<4, uint, lowp>;

	extern template vec<1, uint, mediump>;
	extern template vec<2, uint, mediump>;
	extern template vec<3, uint, mediump>;
	extern template vec<4, uint, mediump>;

	extern template vec<1, uint, highp>;
	extern template vec<2, uint, highp>;
	extern template vec<3, uint, highp>;
	extern template vec<4, uint, highp>;

	extern template vec<1, uint, defaultp>;
	extern template vec<2, uint, defaultp>;
	extern template vec<3, uint, defaultp>;
	extern template vec<4, uint, defaultp>;

	extern template vec<1, u8, lowp>;
	extern template vec<2, u8, lowp>;
	extern template vec<3, u8, lowp>;
	extern template vec<4, u8, lowp>;

	extern template vec<1, u8, mediump>;
	extern template vec<2, u8, mediump>;
	extern template vec<3, u8, mediump>;
	extern template vec<4, u8, mediump>;

	extern template vec<1, u8, highp>;
	extern template vec<2, u8, highp>;
	extern template vec<3, u8, highp>;
	extern template vec<4, u8, highp>;

	extern template vec<1, u8, defaultp>;
	extern template vec<2, u8, defaultp>;
	extern template vec<3, u8, defaultp>;
	extern template vec<4, u8, defaultp>;

	extern template vec<1, u16, lowp>;
	extern template vec<2, u16, lowp>;
	extern template vec<3, u16, lowp>;
	extern template vec<4, u16, lowp>;

	extern template vec<1, u16, mediump>;
	extern template vec<2, u16, mediump>;
	extern template vec<3, u16, mediump>;
	extern template vec<4, u16, mediump>;

	extern template vec<1, u16, highp>;
	extern template vec<2, u16, highp>;
	extern template vec<3, u16, highp>;
	extern template vec<4, u16, highp>;

	extern template vec<1, u16, defaultp>;
	extern template vec<2, u16, defaultp>;
	extern template vec<3, u16, defaultp>;
	extern template vec<4, u16, defaultp>;

	extern template vec<1, u32, lowp>;
	extern template vec<2, u32, lowp>;
	extern template vec<3, u32, lowp>;
	extern template vec<4, u32, lowp>;

	extern template vec<1, u32, mediump>;
	extern template vec<2, u32, mediump>;
	extern template vec<3, u32, mediump>;
	extern template vec<4, u32, mediump>;

	extern template vec<1, u32, highp>;
	extern template vec<2, u32, highp>;
	extern template vec<3, u32, highp>;
	extern template vec<4, u32, highp>;

	extern template vec<1, u32, defaultp>;
	extern template vec<2, u32, defaultp>;
	extern template vec<3, u32, defaultp>;
	extern template vec<4, u32, defaultp>;

	extern template vec<1, u64, lowp>;
	extern template vec<2, u64, lowp>;
	extern template vec<3, u64, lowp>;
	extern template vec<4, u64, lowp>;

	extern template vec<1, u64, mediump>;
	extern template vec<2, u64, mediump>;
	extern template vec<3, u64, mediump>;
	extern template vec<4, u64, mediump>;

	extern template vec<1, u64, highp>;
	extern template vec<2, u64, highp>;
	extern template vec<3, u64, highp>;
	extern template vec<4, u64, highp>;

	extern template vec<1, u64, defaultp>;
	extern template vec<2, u64, defaultp>;
	extern template vec<3, u64, defaultp>;
	extern template vec<4, u64, defaultp>;

	// Vector float

	extern template vec<1, float, lowp>;
	extern template vec<2, float, lowp>;
	extern template vec<3, float, lowp>;
	extern template vec<4, float, lowp>;

	extern template vec<1, float, mediump>;
	extern template vec<2, float, mediump>;
	extern template vec<3, float, mediump>;
	extern template vec<4, float, mediump>;

	extern template vec<1, float, highp>;
	extern template vec<2, float, highp>;
	extern template vec<3, float, highp>;
	extern template vec<4, float, highp>;

	extern template vec<1, float, defaultp>;
	extern template vec<2, float, defaultp>;
	extern template vec<3, float, defaultp>;
	extern template vec<4, float, defaultp>;

	extern template vec<1, float, lowp>;
	extern template vec<2, float, lowp>;
	extern template vec<3, float, lowp>;
	extern template vec<4, float, lowp>;

	extern template vec<1, float, mediump>;
	extern template vec<2, float, mediump>;
	extern template vec<3, float, mediump>;
	extern template vec<4, float, mediump>;

	extern template vec<1, float, highp>;
	extern template vec<2, float, highp>;
	extern template vec<3, float, highp>;
	extern template vec<4, float, highp>;

	extern template vec<1, f32, defaultp>;
	extern template vec<2, f32, defaultp>;
	extern template vec<3, f32, defaultp>;
	extern template vec<4, f32, defaultp>;

	extern template vec<1, f32, lowp>;
	extern template vec<2, f32, lowp>;
	extern template vec<3, f32, lowp>;
	extern template vec<4, f32, lowp>;

	extern template vec<1, f32, mediump>;
	extern template vec<2, f32, mediump>;
	extern template vec<3, f32, mediump>;
	extern template vec<4, f32, mediump>;

	extern template vec<1, f32, highp>;
	extern template vec<2, f32, highp>;
	extern template vec<3, f32, highp>;
	extern template vec<4, f32, highp>;

	extern template vec<1, f32, defaultp>;
	extern template vec<2, f32, defaultp>;
	extern template vec<3, f32, defaultp>;
	extern template vec<4, f32, defaultp>;

	extern template vec<1, f64, lowp>;
	extern template vec<2, f64, lowp>;
	extern template vec<3, f64, lowp>;
	extern template vec<4, f64, lowp>;

	extern template vec<1, f64, mediump>;
	extern template vec<2, f64, mediump>;
	extern template vec<3, f64, mediump>;
	extern template vec<4, f64, mediump>;

	extern template vec<1, f64, highp>;
	extern template vec<2, f64, highp>;
	extern template vec<3, f64, highp>;
	extern template vec<4, f64, highp>;

	extern template vec<1, f64, defaultp>;
	extern template vec<2, f64, defaultp>;
	extern template vec<3, f64, defaultp>;
	extern template vec<4, f64, defaultp>;

	extern template vec<1, f64, lowp>;
	extern template vec<2, f64, lowp>;
	extern template vec<3, f64, lowp>;
	extern template vec<4, f64, lowp>;

	extern template vec<1, f64, mediump>;
	extern template vec<2, f64, mediump>;
	extern template vec<3, f64, mediump>;
	extern template vec<4, f64, mediump>;

	extern template vec<1, f64, highp>;
	extern template vec<2, f64, highp>;
	extern template vec<3, f64, highp>;
	extern template vec<4, f64, highp>;

	extern template vec<1, f64, defaultp>;
	extern template vec<2, f64, defaultp>;
	extern template vec<3, f64, defaultp>;
	extern template vec<4, f64, defaultp>;

	// Matrix NxN

	extern template mat<2, 2, f32, lowp>;
	extern template mat<3, 3, f32, lowp>;
	extern template mat<4, 4, f32, lowp>;

	extern template mat<2, 2, f32, mediump>;
	extern template mat<3, 3, f32, mediump>;
	extern template mat<4, 4, f32, mediump>;

	extern template mat<2, 2, f32, highp>;
	extern template mat<3, 3, f32, highp>;
	extern template mat<4, 4, f32, highp>;

	extern template mat<2, 2, f32, defaultp>;
	extern template mat<3, 3, f32, defaultp>;
	extern template mat<4, 4, f32, defaultp>;

	extern template mat<2, 2, f32, lowp>;
	extern template mat<3, 3, f32, lowp>;
	extern template mat<4, 4, f32, lowp>;

	extern template mat<2, 2, f32, mediump>;
	extern template mat<3, 3, f32, mediump>;
	extern template mat<4, 4, f32, mediump>;

	extern template mat<2, 2, f32, highp>;
	extern template mat<3, 3, f32, highp>;
	extern template mat<4, 4, f32, highp>;

	extern template mat<2, 2, f32, defaultp>;
	extern template mat<3, 3, f32, defaultp>;
	extern template mat<4, 4, f32, defaultp>;

	extern template mat<2, 2, f32, lowp>;
	extern template mat<3, 3, f32, lowp>;
	extern template mat<4, 4, f32, lowp>;

	extern template mat<2, 2, f32, mediump>;
	extern template mat<3, 3, f32, mediump>;
	extern template mat<4, 4, f32, mediump>;

	extern template mat<2, 2, f32, highp>;
	extern template mat<3, 3, f32, highp>;
	extern template mat<4, 4, f32, highp>;

	extern template mat<2, 2, f32, defaultp>;
	extern template mat<3, 3, f32, defaultp>;
	extern template mat<4, 4, f32, defaultp>;

	extern template mat<2, 2, f64, lowp>;
	extern template mat<3, 3, f64, lowp>;
	extern template mat<4, 4, f64, lowp>;

	extern template mat<2, 2, f64, mediump>;
	extern template mat<3, 3, f64, mediump>;
	extern template mat<4, 4, f64, mediump>;

	extern template mat<2, 2, f64, highp>;
	extern template mat<3, 3, f64, highp>;
	extern template mat<4, 4, f64, highp>;

	extern template mat<2, 2, f64, defaultp>;
	extern template mat<3, 3, f64, defaultp>;
	extern template mat<4, 4, f64, defaultp>;

	extern template mat<2, 2, f64, lowp>;
	extern template mat<3, 3, f64, lowp>;
	extern template mat<4, 4, f64, lowp>;

	extern template mat<2, 2, f64, mediump>;
	extern template mat<3, 3, f64, mediump>;
	extern template mat<4, 4, f64, mediump>;

	extern template mat<2, 2, f64, highp>;
	extern template mat<3, 3, f64, highp>;
	extern template mat<4, 4, f64, highp>;

	extern template mat<2, 2, f64, defaultp>;
	extern template mat<3, 3, f64, defaultp>;
	extern template mat<4, 4, f64, defaultp>;

	// Matrix MxN

	extern template mat<2, 2, f32, lowp>;
	extern template mat<2, 3, f32, lowp>;
	extern template mat<2, 4, f32, lowp>;
	extern template mat<3, 2, f32, lowp>;
	extern template mat<3, 3, f32, lowp>;
	extern template mat<3, 4, f32, lowp>;
	extern template mat<4, 2, f32, lowp>;
	extern template mat<4, 3, f32, lowp>;
	extern template mat<4, 4, f32, lowp>;

	extern template mat<2, 2, f32, mediump>;
	extern template mat<2, 3, f32, mediump>;
	extern template mat<2, 4, f32, mediump>;
	extern template mat<3, 2, f32, mediump>;
	extern template mat<3, 3, f32, mediump>;
	extern template mat<3, 4, f32, mediump>;
	extern template mat<4, 2, f32, mediump>;
	extern template mat<4, 3, f32, mediump>;
	extern template mat<4, 4, f32, mediump>;

	extern template mat<2, 2, f32, highp>;
	extern template mat<2, 3, f32, highp>;
	extern template mat<2, 4, f32, highp>;
	extern template mat<3, 2, f32, highp>;
	extern template mat<3, 3, f32, highp>;
	extern template mat<3, 4, f32, highp>;
	extern template mat<4, 2, f32, highp>;
	extern template mat<4, 3, f32, highp>;
	extern template mat<4, 4, f32, highp>;

	extern template mat<2, 2, f32, defaultp>;
	extern template mat<3, 2, f32, defaultp>;
	extern template mat<4, 2, f32, defaultp>;
	extern template mat<2, 3, f32, defaultp>;
	extern template mat<3, 3, f32, defaultp>;
	extern template mat<4, 3, f32, defaultp>;
	extern template mat<2, 4, f32, defaultp>;
	extern template mat<3, 4, f32, defaultp>;
	extern template mat<4, 4, f32, defaultp>;

	extern template mat<2, 2, f32, lowp>;
	extern template mat<2, 3, f32, lowp>;
	extern template mat<2, 4, f32, lowp>;
	extern template mat<3, 2, f32, lowp>;
	extern template mat<3, 3, f32, lowp>;
	extern template mat<3, 4, f32, lowp>;
	extern template mat<4, 2, f32, lowp>;
	extern template mat<4, 3, f32, lowp>;
	extern template mat<4, 4, f32, lowp>;

	extern template mat<2, 2, f32, mediump>;
	extern template mat<2, 3, f32, mediump>;
	extern template mat<2, 4, f32, mediump>;
	extern template mat<3, 2, f32, mediump>;
	extern template mat<3, 3, f32, mediump>;
	extern template mat<3, 4, f32, mediump>;
	extern template mat<4, 2, f32, mediump>;
	extern template mat<4, 3, f32, mediump>;
	extern template mat<4, 4, f32, mediump>;

	extern template mat<2, 2, f32, highp>;
	extern template mat<2, 3, f32, highp>;
	extern template mat<2, 4, f32, highp>;
	extern template mat<3, 2, f32, highp>;
	extern template mat<3, 3, f32, highp>;
	extern template mat<3, 4, f32, highp>;
	extern template mat<4, 2, f32, highp>;
	extern template mat<4, 3, f32, highp>;
	extern template mat<4, 4, f32, highp>;

	extern template mat<2, 2, f32, defaultp>;
	extern template mat<3, 2, f32, defaultp>;
	extern template mat<4, 2, f32, defaultp>;
	extern template mat<2, 3, f32, defaultp>;
	extern template mat<3, 3, f32, defaultp>;
	extern template mat<4, 3, f32, defaultp>;
	extern template mat<2, 4, f32, defaultp>;
	extern template mat<3, 4, f32, defaultp>;
	extern template mat<4, 4, f32, defaultp>;

	extern template mat<2, 2, f32, lowp>;
	extern template mat<2, 3, f32, lowp>;
	extern template mat<2, 4, f32, lowp>;
	extern template mat<3, 2, f32, lowp>;
	extern template mat<3, 3, f32, lowp>;
	extern template mat<3, 4, f32, lowp>;
	extern template mat<4, 2, f32, lowp>;
	extern template mat<4, 3, f32, lowp>;
	extern template mat<4, 4, f32, lowp>;

	extern template mat<2, 2, f32, mediump>;
	extern template mat<2, 3, f32, mediump>;
	extern template mat<2, 4, f32, mediump>;
	extern template mat<3, 2, f32, mediump>;
	extern template mat<3, 3, f32, mediump>;
	extern template mat<3, 4, f32, mediump>;
	extern template mat<4, 2, f32, mediump>;
	extern template mat<4, 3, f32, mediump>;
	extern template mat<4, 4, f32, mediump>;

	extern template mat<2, 2, f32, highp>;
	extern template mat<2, 3, f32, highp>;
	extern template mat<2, 4, f32, highp>;
	extern template mat<3, 2, f32, highp>;
	extern template mat<3, 3, f32, highp>;
	extern template mat<3, 4, f32, highp>;
	extern template mat<4, 2, f32, highp>;
	extern template mat<4, 3, f32, highp>;
	extern template mat<4, 4, f32, highp>;

	extern template mat<2, 2, f32, defaultp>;
	extern template mat<3, 2, f32, defaultp>;
	extern template mat<4, 2, f32, defaultp>;
	extern template mat<2, 3, f32, defaultp>;
	extern template mat<3, 3, f32, defaultp>;
	extern template mat<4, 3, f32, defaultp>;
	extern template mat<2, 4, f32, defaultp>;
	extern template mat<3, 4, f32, defaultp>;
	extern template mat<4, 4, f32, defaultp>;

	extern template mat<2, 2, double, lowp>;
	extern template mat<2, 3, double, lowp>;
	extern template mat<2, 4, double, lowp>;
	extern template mat<3, 2, double, lowp>;
	extern template mat<3, 3, double, lowp>;
	extern template mat<3, 4, double, lowp>;
	extern template mat<4, 2, double, lowp>;
	extern template mat<4, 3, double, lowp>;
	extern template mat<4, 4, double, lowp>;

	extern template mat<2, 2, double, mediump>;
	extern template mat<2, 3, double, mediump>;
	extern template mat<2, 4, double, mediump>;
	extern template mat<3, 2, double, mediump>;
	extern template mat<3, 3, double, mediump>;
	extern template mat<3, 4, double, mediump>;
	extern template mat<4, 2, double, mediump>;
	extern template mat<4, 3, double, mediump>;
	extern template mat<4, 4, double, mediump>;

	extern template mat<2, 2, double, highp>;
	extern template mat<2, 3, double, highp>;
	extern template mat<2, 4, double, highp>;
	extern template mat<3, 2, double, highp>;
	extern template mat<3, 3, double, highp>;
	extern template mat<3, 4, double, highp>;
	extern template mat<4, 2, double, highp>;
	extern template mat<4, 3, double, highp>;
	extern template mat<4, 4, double, highp>;

	extern template mat<2, 2, double, defaultp>;
	extern template mat<3, 2, double, defaultp>;
	extern template mat<4, 2, double, defaultp>;
	extern template mat<2, 3, double, defaultp>;
	extern template mat<3, 3, double, defaultp>;
	extern template mat<4, 3, double, defaultp>;
	extern template mat<2, 4, double, defaultp>;
	extern template mat<3, 4, double, defaultp>;
	extern template mat<4, 4, double, defaultp>;

	extern template mat<2, 2, f64, lowp>;
	extern template mat<2, 3, f64, lowp>;
	extern template mat<2, 4, f64, lowp>;
	extern template mat<3, 2, f64, lowp>;
	extern template mat<3, 3, f64, lowp>;
	extern template mat<3, 4, f64, lowp>;
	extern template mat<4, 2, f64, lowp>;
	extern template mat<4, 3, f64, lowp>;
	extern template mat<4, 4, f64, lowp>;

	extern template mat<2, 2, f64, mediump>;
	extern template mat<2, 3, f64, mediump>;
	extern template mat<2, 4, f64, mediump>;
	extern template mat<3, 2, f64, mediump>;
	extern template mat<3, 3, f64, mediump>;
	extern template mat<3, 4, f64, mediump>;
	extern template mat<4, 2, f64, mediump>;
	extern template mat<4, 3, f64, mediump>;
	extern template mat<4, 4, f64, mediump>;

	extern template mat<2, 2, f64, highp>;
	extern template mat<2, 3, f64, highp>;
	extern template mat<2, 4, f64, highp>;
	extern template mat<3, 2, f64, highp>;
	extern template mat<3, 3, f64, highp>;
	extern template mat<3, 4, f64, highp>;
	extern template mat<4, 2, f64, highp>;
	extern template mat<4, 3, f64, highp>;
	extern template mat<4, 4, f64, highp>;

	extern template mat<2, 2, f64, defaultp>;
	extern template mat<3, 2, f64, defaultp>;
	extern template mat<4, 2, f64, defaultp>;
	extern template mat<2, 3, f64, defaultp>;
	extern template mat<3, 3, f64, defaultp>;
	extern template mat<4, 3, f64, defaultp>;
	extern template mat<2, 4, f64, defaultp>;
	extern template mat<3, 4, f64, defaultp>;
	extern template mat<4, 4, f64, defaultp>;

	// Signed integer matrix MxN

	extern template mat<2, 2, int, lowp>;
	extern template mat<2, 3, int, lowp>;
	extern template mat<2, 4, int, lowp>;
	extern template mat<3, 2, int, lowp>;
	extern template mat<3, 3, int, lowp>;
	extern template mat<3, 4, int, lowp>;
	extern template mat<4, 2, int, lowp>;
	extern template mat<4, 3, int, lowp>;
	extern template mat<4, 4, int, lowp>;

	extern template mat<2, 2, int, mediump>;
	extern template mat<2, 3, int, mediump>;
	extern template mat<2, 4, int, mediump>;
	extern template mat<3, 2, int, mediump>;
	extern template mat<3, 3, int, mediump>;
	extern template mat<3, 4, int, mediump>;
	extern template mat<4, 2, int, mediump>;
	extern template mat<4, 3, int, mediump>;
	extern template mat<4, 4, int, mediump>;

	extern template mat<2, 2, int, highp>;
	extern template mat<2, 3, int, highp>;
	extern template mat<2, 4, int, highp>;
	extern template mat<3, 2, int, highp>;
	extern template mat<3, 3, int, highp>;
	extern template mat<3, 4, int, highp>;
	extern template mat<4, 2, int, highp>;
	extern template mat<4, 3, int, highp>;
	extern template mat<4, 4, int, highp>;

	extern template mat<2, 2, int, defaultp>;
	extern template mat<3, 2, int, defaultp>;
	extern template mat<4, 2, int, defaultp>;
	extern template mat<2, 3, int, defaultp>;
	extern template mat<3, 3, int, defaultp>;
	extern template mat<4, 3, int, defaultp>;
	extern template mat<2, 4, int, defaultp>;
	extern template mat<3, 4, int, defaultp>;
	extern template mat<4, 4, int, defaultp>;


	extern template mat<2, 2, int8, lowp>;
	extern template mat<2, 3, int8, lowp>;
	extern template mat<2, 4, int8, lowp>;
	extern template mat<3, 2, int8, lowp>;
	extern template mat<3, 3, int8, lowp>;
	extern template mat<3, 4, int8, lowp>;
	extern template mat<4, 2, int8, lowp>;
	extern template mat<4, 3, int8, lowp>;
	extern template mat<4, 4, int8, lowp>;

	extern template mat<2, 2, int8, mediump>;
	extern template mat<2, 3, int8, mediump>;
	extern template mat<2, 4, int8, mediump>;
	extern template mat<3, 2, int8, mediump>;
	extern template mat<3, 3, int8, mediump>;
	extern template mat<3, 4, int8, mediump>;
	extern template mat<4, 2, int8, mediump>;
	extern template mat<4, 3, int8, mediump>;
	extern template mat<4, 4, int8, mediump>;

	extern template mat<2, 2, int8, highp>;
	extern template mat<2, 3, int8, highp>;
	extern template mat<2, 4, int8, highp>;
	extern template mat<3, 2, int8, highp>;
	extern template mat<3, 3, int8, highp>;
	extern template mat<3, 4, int8, highp>;
	extern template mat<4, 2, int8, highp>;
	extern template mat<4, 3, int8, highp>;
	extern template mat<4, 4, int8, highp>;

	extern template mat<2, 2, int8, defaultp>;
	extern template mat<3, 2, int8, defaultp>;
	extern template mat<4, 2, int8, defaultp>;
	extern template mat<2, 3, int8, defaultp>;
	extern template mat<3, 3, int8, defaultp>;
	extern template mat<4, 3, int8, defaultp>;
	extern template mat<2, 4, int8, defaultp>;
	extern template mat<3, 4, int8, defaultp>;
	extern template mat<4, 4, int8, defaultp>;


	extern template mat<2, 2, int16, lowp>;
	extern template mat<2, 3, int16, lowp>;
	extern template mat<2, 4, int16, lowp>;
	extern template mat<3, 2, int16, lowp>;
	extern template mat<3, 3, int16, lowp>;
	extern template mat<3, 4, int16, lowp>;
	extern template mat<4, 2, int16, lowp>;
	extern template mat<4, 3, int16, lowp>;
	extern template mat<4, 4, int16, lowp>;

	extern template mat<2, 2, int16, mediump>;
	extern template mat<2, 3, int16, mediump>;
	extern template mat<2, 4, int16, mediump>;
	extern template mat<3, 2, int16, mediump>;
	extern template mat<3, 3, int16, mediump>;
	extern template mat<3, 4, int16, mediump>;
	extern template mat<4, 2, int16, mediump>;
	extern template mat<4, 3, int16, mediump>;
	extern template mat<4, 4, int16, mediump>;

	extern template mat<2, 2, int16, highp>;
	extern template mat<2, 3, int16, highp>;
	extern template mat<2, 4, int16, highp>;
	extern template mat<3, 2, int16, highp>;
	extern template mat<3, 3, int16, highp>;
	extern template mat<3, 4, int16, highp>;
	extern template mat<4, 2, int16, highp>;
	extern template mat<4, 3, int16, highp>;
	extern template mat<4, 4, int16, highp>;

	extern template mat<2, 2, int16, defaultp>;
	extern template mat<3, 2, int16, defaultp>;
	extern template mat<4, 2, int16, defaultp>;
	extern template mat<2, 3, int16, defaultp>;
	extern template mat<3, 3, int16, defaultp>;
	extern template mat<4, 3, int16, defaultp>;
	extern template mat<2, 4, int16, defaultp>;
	extern template mat<3, 4, int16, defaultp>;
	extern template mat<4, 4, int16, defaultp>;


	extern template mat<2, 2, int32, lowp>;
	extern template mat<2, 3, int32, lowp>;
	extern template mat<2, 4, int32, lowp>;
	extern template mat<3, 2, int32, lowp>;
	extern template mat<3, 3, int32, lowp>;
	extern template mat<3, 4, int32, lowp>;
	extern template mat<4, 2, int32, lowp>;
	extern template mat<4, 3, int32, lowp>;
	extern template mat<4, 4, int32, lowp>;

	extern template mat<2, 2, int32, mediump>;
	extern template mat<2, 3, int32, mediump>;
	extern template mat<2, 4, int32, mediump>;
	extern template mat<3, 2, int32, mediump>;
	extern template mat<3, 3, int32, mediump>;
	extern template mat<3, 4, int32, mediump>;
	extern template mat<4, 2, int32, mediump>;
	extern template mat<4, 3, int32, mediump>;
	extern template mat<4, 4, int32, mediump>;

	extern template mat<2, 2, int32, highp>;
	extern template mat<2, 3, int32, highp>;
	extern template mat<2, 4, int32, highp>;
	extern template mat<3, 2, int32, highp>;
	extern template mat<3, 3, int32, highp>;
	extern template mat<3, 4, int32, highp>;
	extern template mat<4, 2, int32, highp>;
	extern template mat<4, 3, int32, highp>;
	extern template mat<4, 4, int32, highp>;

	extern template mat<2, 2, int32, defaultp>;
	extern template mat<3, 2, int32, defaultp>;
	extern template mat<4, 2, int32, defaultp>;
	extern template mat<2, 3, int32, defaultp>;
	extern template mat<3, 3, int32, defaultp>;
	extern template mat<4, 3, int32, defaultp>;
	extern template mat<2, 4, int32, defaultp>;
	extern template mat<3, 4, int32, defaultp>;
	extern template mat<4, 4, int32, defaultp>;


	extern template mat<2, 2, int64, lowp>;
	extern template mat<2, 3, int64, lowp>;
	extern template mat<2, 4, int64, lowp>;
	extern template mat<3, 2, int64, lowp>;
	extern template mat<3, 3, int64, lowp>;
	extern template mat<3, 4, int64, lowp>;
	extern template mat<4, 2, int64, lowp>;
	extern template mat<4, 3, int64, lowp>;
	extern template mat<4, 4, int64, lowp>;

	extern template mat<2, 2, int64, mediump>;
	extern template mat<2, 3, int64, mediump>;
	extern template mat<2, 4, int64, mediump>;
	extern template mat<3, 2, int64, mediump>;
	extern template mat<3, 3, int64, mediump>;
	extern template mat<3, 4, int64, mediump>;
	extern template mat<4, 2, int64, mediump>;
	extern template mat<4, 3, int64, mediump>;
	extern template mat<4, 4, int64, mediump>;

	extern template mat<2, 2, int64, highp>;
	extern template mat<2, 3, int64, highp>;
	extern template mat<2, 4, int64, highp>;
	extern template mat<3, 2, int64, highp>;
	extern template mat<3, 3, int64, highp>;
	extern template mat<3, 4, int64, highp>;
	extern template mat<4, 2, int64, highp>;
	extern template mat<4, 3, int64, highp>;
	extern template mat<4, 4, int64, highp>;

	extern template mat<2, 2, int64, defaultp>;
	extern template mat<3, 2, int64, defaultp>;
	extern template mat<4, 2, int64, defaultp>;
	extern template mat<2, 3, int64, defaultp>;
	extern template mat<3, 3, int64, defaultp>;
	extern template mat<4, 3, int64, defaultp>;
	extern template mat<2, 4, int64, defaultp>;
	extern template mat<3, 4, int64, defaultp>;
	extern template mat<4, 4, int64, defaultp>;


	// Unsigned integer matrix MxN

	extern template mat<2, 2, uint, lowp>;
	extern template mat<2, 3, uint, lowp>;
	extern template mat<2, 4, uint, lowp>;
	extern template mat<3, 2, uint, lowp>;
	extern template mat<3, 3, uint, lowp>;
	extern template mat<3, 4, uint, lowp>;
	extern template mat<4, 2, uint, lowp>;
	extern template mat<4, 3, uint, lowp>;
	extern template mat<4, 4, uint, lowp>;

	extern template mat<2, 2, uint, mediump>;
	extern template mat<2, 3, uint, mediump>;
	extern template mat<2, 4, uint, mediump>;
	extern template mat<3, 2, uint, mediump>;
	extern template mat<3, 3, uint, mediump>;
	extern template mat<3, 4, uint, mediump>;
	extern template mat<4, 2, uint, mediump>;
	extern template mat<4, 3, uint, mediump>;
	extern template mat<4, 4, uint, mediump>;

	extern template mat<2, 2, uint, highp>;
	extern template mat<2, 3, uint, highp>;
	extern template mat<2, 4, uint, highp>;
	extern template mat<3, 2, uint, highp>;
	extern template mat<3, 3, uint, highp>;
	extern template mat<3, 4, uint, highp>;
	extern template mat<4, 2, uint, highp>;
	extern template mat<4, 3, uint, highp>;
	extern template mat<4, 4, uint, highp>;

	extern template mat<2, 2, uint, defaultp>;
	extern template mat<3, 2, uint, defaultp>;
	extern template mat<4, 2, uint, defaultp>;
	extern template mat<2, 3, uint, defaultp>;
	extern template mat<3, 3, uint, defaultp>;
	extern template mat<4, 3, uint, defaultp>;
	extern template mat<2, 4, uint, defaultp>;
	extern template mat<3, 4, uint, defaultp>;
	extern template mat<4, 4, uint, defaultp>;


	extern template mat<2, 2, uint8, lowp>;
	extern template mat<2, 3, uint8, lowp>;
	extern template mat<2, 4, uint8, lowp>;
	extern template mat<3, 2, uint8, lowp>;
	extern template mat<3, 3, uint8, lowp>;
	extern template mat<3, 4, uint8, lowp>;
	extern template mat<4, 2, uint8, lowp>;
	extern template mat<4, 3, uint8, lowp>;
	extern template mat<4, 4, uint8, lowp>;

	extern template mat<2, 2, uint8, mediump>;
	extern template mat<2, 3, uint8, mediump>;
	extern template mat<2, 4, uint8, mediump>;
	extern template mat<3, 2, uint8, mediump>;
	extern template mat<3, 3, uint8, mediump>;
	extern template mat<3, 4, uint8, mediump>;
	extern template mat<4, 2, uint8, mediump>;
	extern template mat<4, 3, uint8, mediump>;
	extern template mat<4, 4, uint8, mediump>;

	extern template mat<2, 2, uint8, highp>;
	extern template mat<2, 3, uint8, highp>;
	extern template mat<2, 4, uint8, highp>;
	extern template mat<3, 2, uint8, highp>;
	extern template mat<3, 3, uint8, highp>;
	extern template mat<3, 4, uint8, highp>;
	extern template mat<4, 2, uint8, highp>;
	extern template mat<4, 3, uint8, highp>;
	extern template mat<4, 4, uint8, highp>;

	extern template mat<2, 2, uint8, defaultp>;
	extern template mat<3, 2, uint8, defaultp>;
	extern template mat<4, 2, uint8, defaultp>;
	extern template mat<2, 3, uint8, defaultp>;
	extern template mat<3, 3, uint8, defaultp>;
	extern template mat<4, 3, uint8, defaultp>;
	extern template mat<2, 4, uint8, defaultp>;
	extern template mat<3, 4, uint8, defaultp>;
	extern template mat<4, 4, uint8, defaultp>;


	extern template mat<2, 2, uint16, lowp>;
	extern template mat<2, 3, uint16, lowp>;
	extern template mat<2, 4, uint16, lowp>;
	extern template mat<3, 2, uint16, lowp>;
	extern template mat<3, 3, uint16, lowp>;
	extern template mat<3, 4, uint16, lowp>;
	extern template mat<4, 2, uint16, lowp>;
	extern template mat<4, 3, uint16, lowp>;
	extern template mat<4, 4, uint16, lowp>;

	extern template mat<2, 2, uint16, mediump>;
	extern template mat<2, 3, uint16, mediump>;
	extern template mat<2, 4, uint16, mediump>;
	extern template mat<3, 2, uint16, mediump>;
	extern template mat<3, 3, uint16, mediump>;
	extern template mat<3, 4, uint16, mediump>;
	extern template mat<4, 2, uint16, mediump>;
	extern template mat<4, 3, uint16, mediump>;
	extern template mat<4, 4, uint16, mediump>;

	extern template mat<2, 2, uint16, highp>;
	extern template mat<2, 3, uint16, highp>;
	extern template mat<2, 4, uint16, highp>;
	extern template mat<3, 2, uint16, highp>;
	extern template mat<3, 3, uint16, highp>;
	extern template mat<3, 4, uint16, highp>;
	extern template mat<4, 2, uint16, highp>;
	extern template mat<4, 3, uint16, highp>;
	extern template mat<4, 4, uint16, highp>;

	extern template mat<2, 2, uint16, defaultp>;
	extern template mat<3, 2, uint16, defaultp>;
	extern template mat<4, 2, uint16, defaultp>;
	extern template mat<2, 3, uint16, defaultp>;
	extern template mat<3, 3, uint16, defaultp>;
	extern template mat<4, 3, uint16, defaultp>;
	extern template mat<2, 4, uint16, defaultp>;
	extern template mat<3, 4, uint16, defaultp>;
	extern template mat<4, 4, uint16, defaultp>;


	extern template mat<2, 2, uint32, lowp>;
	extern template mat<2, 3, uint32, lowp>;
	extern template mat<2, 4, uint32, lowp>;
	extern template mat<3, 2, uint32, lowp>;
	extern template mat<3, 3, uint32, lowp>;
	extern template mat<3, 4, uint32, lowp>;
	extern template mat<4, 2, uint32, lowp>;
	extern template mat<4, 3, uint32, lowp>;
	extern template mat<4, 4, uint32, lowp>;

	extern template mat<2, 2, uint32, mediump>;
	extern template mat<2, 3, uint32, mediump>;
	extern template mat<2, 4, uint32, mediump>;
	extern template mat<3, 2, uint32, mediump>;
	extern template mat<3, 3, uint32, mediump>;
	extern template mat<3, 4, uint32, mediump>;
	extern template mat<4, 2, uint32, mediump>;
	extern template mat<4, 3, uint32, mediump>;
	extern template mat<4, 4, uint32, mediump>;

	extern template mat<2, 2, uint32, highp>;
	extern template mat<2, 3, uint32, highp>;
	extern template mat<2, 4, uint32, highp>;
	extern template mat<3, 2, uint32, highp>;
	extern template mat<3, 3, uint32, highp>;
	extern template mat<3, 4, uint32, highp>;
	extern template mat<4, 2, uint32, highp>;
	extern template mat<4, 3, uint32, highp>;
	extern template mat<4, 4, uint32, highp>;

	extern template mat<2, 2, uint32, defaultp>;
	extern template mat<3, 2, uint32, defaultp>;
	extern template mat<4, 2, uint32, defaultp>;
	extern template mat<2, 3, uint32, defaultp>;
	extern template mat<3, 3, uint32, defaultp>;
	extern template mat<4, 3, uint32, defaultp>;
	extern template mat<2, 4, uint32, defaultp>;
	extern template mat<3, 4, uint32, defaultp>;
	extern template mat<4, 4, uint32, defaultp>;


	extern template mat<2, 2, uint64, lowp>;
	extern template mat<2, 3, uint64, lowp>;
	extern template mat<2, 4, uint64, lowp>;
	extern template mat<3, 2, uint64, lowp>;
	extern template mat<3, 3, uint64, lowp>;
	extern template mat<3, 4, uint64, lowp>;
	extern template mat<4, 2, uint64, lowp>;
	extern template mat<4, 3, uint64, lowp>;
	extern template mat<4, 4, uint64, lowp>;

	extern template mat<2, 2, uint64, mediump>;
	extern template mat<2, 3, uint64, mediump>;
	extern template mat<2, 4, uint64, mediump>;
	extern template mat<3, 2, uint64, mediump>;
	extern template mat<3, 3, uint64, mediump>;
	extern template mat<3, 4, uint64, mediump>;
	extern template mat<4, 2, uint64, mediump>;
	extern template mat<4, 3, uint64, mediump>;
	extern template mat<4, 4, uint64, mediump>;

	extern template mat<2, 2, uint64, highp>;
	extern template mat<2, 3, uint64, highp>;
	extern template mat<2, 4, uint64, highp>;
	extern template mat<3, 2, uint64, highp>;
	extern template mat<3, 3, uint64, highp>;
	extern template mat<3, 4, uint64, highp>;
	extern template mat<4, 2, uint64, highp>;
	extern template mat<4, 3, uint64, highp>;
	extern template mat<4, 4, uint64, highp>;

	extern template mat<2, 2, uint64, defaultp>;
	extern template mat<3, 2, uint64, defaultp>;
	extern template mat<4, 2, uint64, defaultp>;
	extern template mat<2, 3, uint64, defaultp>;
	extern template mat<3, 3, uint64, defaultp>;
	extern template mat<4, 3, uint64, defaultp>;
	extern template mat<2, 4, uint64, defaultp>;
	extern template mat<3, 4, uint64, defaultp>;
	extern template mat<4, 4, uint64, defaultp>;

	// Quaternion

	extern template qua<float, lowp>;
	extern template qua<float, mediump>;
	extern template qua<float, highp>;
	extern template qua<float, defaultp>;

	extern template qua<float, lowp>;
	extern template qua<float, mediump>;
	extern template qua<float, highp>;
	extern template qua<float, defaultp>;

	extern template qua<f32, lowp>;
	extern template qua<f32, mediump>;
	extern template qua<f32, highp>;
	extern template qua<f32, defaultp>;

	extern template qua<double, lowp>;
	extern template qua<double, mediump>;
	extern template qua<double, highp>;
	extern template qua<double, defaultp>;

	extern template qua<f64, lowp>;
	extern template qua<f64, mediump>;
	extern template qua<f64, highp>;
	extern template qua<f64, defaultp>;
}



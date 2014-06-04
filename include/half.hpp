// half - IEEE 754-based half-precision floating point library.
//
// Copyright (c) 2012-2014 Christian Rau <rauy@users.sourceforge.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, 
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// Version 1.11.0

/// \file
/// Main header file for half precision functionality.

#ifndef HALF_HALF_HPP
#define HALF_HALF_HPP

/// Combined gcc version number.
#define HALF_GNUC_VERSION (__GNUC__*100+__GNUC_MINOR__)

//check C++11 language features
#if defined(__clang__)										//clang
	#if __has_feature(cxx_static_assert) && !defined(HALF_ENABLE_CPP11_STATIC_ASSERT)
		#define HALF_ENABLE_CPP11_STATIC_ASSERT 1
	#endif
	#if __has_feature(cxx_constexpr) && !defined(HALF_ENABLE_CPP11_CONSTEXPR)
		#define HALF_ENABLE_CPP11_CONSTEXPR 1
	#endif
	#if __has_feature(cxx_noexcept) && !defined(HALF_ENABLE_CPP11_NOEXCEPT)
		#define HALF_ENABLE_CPP11_NOEXCEPT 1
	#endif
	#if __has_feature(cxx_user_literals) && !defined(HALF_ENABLE_CPP11_USER_LITERALS)
		#define HALF_ENABLE_CPP11_USER_LITERALS 1
	#endif
	#if (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L) && !defined(HALF_ENABLE_CPP11_LONG_LONG)
		#define HALF_ENABLE_CPP11_LONG_LONG 1
	#endif
/*#elif defined(__INTEL_COMPILER)								//Intel C++
	#if __INTEL_COMPILER >= 1100 && !defined(HALF_ENABLE_CPP11_STATIC_ASSERT)		????????
		#define HALF_ENABLE_CPP11_STATIC_ASSERT 1
	#endif
	#if __INTEL_COMPILER >= 1300 && !defined(HALF_ENABLE_CPP11_CONSTEXPR)			????????
		#define HALF_ENABLE_CPP11_CONSTEXPR 1
	#endif
	#if __INTEL_COMPILER >= 1300 && !defined(HALF_ENABLE_CPP11_NOEXCEPT)			????????
		#define HALF_ENABLE_CPP11_NOEXCEPT 1
	#endif
	#if __INTEL_COMPILER >= 1100 && !defined(HALF_ENABLE_CPP11_LONG_LONG)			????????
		#define HALF_ENABLE_CPP11_LONG_LONG 1
	#endif*/
#elif defined(__GNUC__)										//gcc
	#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
		#if HALF_GNUC_VERSION >= 403 && !defined(HALF_ENABLE_CPP11_STATIC_ASSERT)
			#define HALF_ENABLE_CPP11_STATIC_ASSERT 1
		#endif
		#if HALF_GNUC_VERSION >= 406 && !defined(HALF_ENABLE_CPP11_CONSTEXPR)
			#define HALF_ENABLE_CPP11_CONSTEXPR 1
		#endif
		#if HALF_GNUC_VERSION >= 406 && !defined(HALF_ENABLE_CPP11_NOEXCEPT)
			#define HALF_ENABLE_CPP11_NOEXCEPT 1
		#endif
		#if HALF_GNUC_VERSION >= 407 && !defined(HALF_ENABLE_CPP11_USER_LITERALS)
			#define HALF_ENABLE_CPP11_USER_LITERALS 1
		#endif
		#if !defined(HALF_ENABLE_CPP11_LONG_LONG)
			#define HALF_ENABLE_CPP11_LONG_LONG 1
		#endif
	#endif
#elif defined(_MSC_VER)										//Visual C++
	#if _MSC_VER >= 1600 && !defined(HALF_ENABLE_CPP11_STATIC_ASSERT)
		#define HALF_ENABLE_CPP11_STATIC_ASSERT 1
	#endif
	#if _MSC_VER >= 1310 && !defined(HALF_ENABLE_CPP11_LONG_LONG)
		#define HALF_ENABLE_CPP11_LONG_LONG 1
	#endif
	#define HALF_POP_WARNINGS 1
	#pragma warning(push)
	#pragma warning(disable : 4099 4127 4146)	//struct vs class, constant in if, negative unsigned
#endif

//check C++11 library features
#include <utility>
#if defined(_LIBCPP_VERSION)								//libc++
	#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103
		#ifndef HALF_ENABLE_CPP11_TYPE_TRAITS
			#define HALF_ENABLE_CPP11_TYPE_TRAITS 1
		#endif
		#ifndef HALF_ENABLE_CPP11_CSTDINT
			#define HALF_ENABLE_CPP11_CSTDINT 1
		#endif
		#ifndef HALF_ENABLE_CPP11_CMATH
			#define HALF_ENABLE_CPP11_CMATH 1
		#endif
		#ifndef HALF_ENABLE_CPP11_HASH
			#define HALF_ENABLE_CPP11_HASH 1
		#endif
	#endif
#elif defined(__GLIBCXX__)									//libstdc++
	#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103
		#ifdef __clang__
			#if __GLIBCXX__ >= 20080606 && !defined(HALF_ENABLE_CPP11_TYPE_TRAITS)
				#define HALF_ENABLE_CPP11_TYPE_TRAITS 1
			#endif
			#if __GLIBCXX__ >= 20080606 && !defined(HALF_ENABLE_CPP11_CSTDINT)
				#define HALF_ENABLE_CPP11_CSTDINT 1
			#endif
			#if __GLIBCXX__ >= 20080606 && !defined(HALF_ENABLE_CPP11_CMATH)
				#define HALF_ENABLE_CPP11_CMATH 1
			#endif
			#if __GLIBCXX__ >= 20080606 && !defined(HALF_ENABLE_CPP11_HASH)
				#define HALF_ENABLE_CPP11_HASH 1
			#endif
		#else
			#if HALF_GNUC_VERSION >= 403 && !defined(HALF_ENABLE_CPP11_CSTDINT)
				#define HALF_ENABLE_CPP11_CSTDINT 1
			#endif
			#if HALF_GNUC_VERSION >= 403 && !defined(HALF_ENABLE_CPP11_CMATH)
				#define HALF_ENABLE_CPP11_CMATH 1
			#endif
			#if HALF_GNUC_VERSION >= 403 && !defined(HALF_ENABLE_CPP11_HASH)
				#define HALF_ENABLE_CPP11_HASH 1
			#endif
		#endif
	#endif
#elif defined(_CPPLIB_VER)									//Dinkumware/Visual C++
	#if _CPPLIB_VER >= 520
		#ifndef HALF_ENABLE_CPP11_TYPE_TRAITS
			#define HALF_ENABLE_CPP11_TYPE_TRAITS 1
		#endif
		#ifndef HALF_ENABLE_CPP11_CSTDINT
			#define HALF_ENABLE_CPP11_CSTDINT 1
		#endif
		#ifndef HALF_ENABLE_CPP11_HASH
			#define HALF_ENABLE_CPP11_HASH 1
		#endif
	#endif
	#if _CPPLIB_VER >= 610
		#ifndef HALF_ENABLE_CPP11_CMATH
			#define HALF_ENABLE_CPP11_CMATH 1
		#endif
	#endif
#endif
#undef HALF_GNUC_VERSION

//support constexpr
#if HALF_ENABLE_CPP11_CONSTEXPR
	#define HALF_CONSTEXPR			constexpr
	#define HALF_CONSTEXPR_CONST	constexpr
#else
	#define HALF_CONSTEXPR
	#define HALF_CONSTEXPR_CONST	const
#endif

//support noexcept
#if HALF_ENABLE_CPP11_NOEXCEPT
	#define HALF_NOEXCEPT	noexcept
	#define HALF_NOTHROW	noexcept
#else
	#define HALF_NOEXCEPT
	#define HALF_NOTHROW	throw()
#endif

#include <algorithm>
#include <iostream>
#include <limits>
#include <climits>
#include <cmath>
#include <cstring>
#if HALF_ENABLE_CPP11_TYPE_TRAITS
	#include <type_traits>
#endif
#if HALF_ENABLE_CPP11_CSTDINT
	#include <cstdint>
#endif
#if HALF_ENABLE_CPP11_HASH
	#include <functional>
#endif


/// Default rounding mode.
/// This specifies the rounding mode used for all conversions between [half](\ref half_float::half)s and `float`s as well as 
/// for the half_cast() if not specifying a rounding mode explicitly. It can be redefined (before including half.hpp) to one 
/// of the standard rounding modes using their respective constants or the equivalent values of `std::float_round_style`:
///
/// `std::float_round_style`         | value | rounding
/// ---------------------------------|-------|-------------------------
/// `std::round_indeterminate`       | -1    | fastest (default)
/// `std::round_toward_zero`         | 0     | toward zero
/// `std::round_to_nearest`          | 1     | to nearest
/// `std::round_toward_infinity`     | 2     | toward positive infinity
/// `std::round_toward_neg_infinity` | 3     | toward negative infinity
///
/// By default this is set to `-1` (`std::round_indeterminate`), which uses truncation (round toward zero, but with overflows 
/// set to infinity) and is the fastest rounding mode possible. It can even be set to `std::numeric_limits<float>::round_style` 
/// to synchronize the rounding mode with that of the underlying single-precision implementation.
#ifndef HALF_ROUND_STYLE
	#define HALF_ROUND_STYLE	-1			// = std::round_indeterminate
#endif

/// Tie-breaking behaviour for round to nearest.
/// This specifies if ties in round to nearest should be resolved by rounding to the nearest even value. By default this is 
/// defined to `0` resulting in the faster but slightly more biased behaviour of rounding away from zero in half-way cases (and 
/// thus equal to the round() function), but can be redefined to `1` (before including half.hpp) if more IEEE-conformant 
/// behaviour is needed.
#ifndef HALF_ROUND_TIES_TO_EVEN
	#define HALF_ROUND_TIES_TO_EVEN	0		// ties away from zero
#endif

/// Value signaling overflow.
/// In correspondence with `HUGE_VAL[F|L]` from `<cmath>` this symbol expands to a positive value signaling the overflow of an 
/// operation, in particular it just evaluates to positive infinity.
#define HUGE_VALH	std::numeric_limits<half_float::half>::infinity()

/// Fast half-precision fma function.
/// This symbol is only defined if the fma() function generally executes as fast as, or faster than, a separate 
/// half-precision multiplication followed by an addition. Due to the internal single-precision implementation of all 
/// arithmetic operations, this is in fact always the case.
#define FP_FAST_FMAH	1

#ifndef FP_ILOGB0
	#define FP_ILOGB0		INT_MIN
#endif
#ifndef FP_ILOGBNAN
	#define FP_ILOGBNAN		INT_MAX
#endif
#ifndef FP_SUBNORMAL
	#define FP_SUBNORMAL	0
#endif
#ifndef FP_ZERO
	#define FP_ZERO			1
#endif
#ifndef FP_NAN
	#define FP_NAN			2
#endif
#ifndef FP_INFINITE
	#define FP_INFINITE		3
#endif
#ifndef FP_NORMAL
	#define FP_NORMAL		4
#endif


/// Main namespace for half precision functionality.
/// This namespace contains all the functionality provided by the library.
namespace half_float
{
	class half;

	/// \internal
	/// \brief Implementation details.
	namespace detail
	{
	#if HALF_ENABLE_CPP11_TYPE_TRAITS
		/// Conditional type.
		template<bool B,typename T,typename F> struct conditional : std::conditional<B,T,F> {};

		/// Helper for tag dispatching.
		template<bool B> struct bool_type : std::integral_constant<bool,B> {};
		using std::true_type;
		using std::false_type;

		/// Type traits for floating point types.
		template<typename T> struct is_float : std::is_floating_point<T> {};
	#else
		/// Conditional type.
		template<bool,typename T,typename> struct conditional { typedef T type; };
		template<typename T,typename F> struct conditional<false,T,F> { typedef F type; };

		/// Helper for tag dispatching.
		template<bool> struct bool_type {};
		typedef bool_type<true> true_type;
		typedef bool_type<false> false_type;

		/// Type traits for floating point types.
		template<typename> struct is_float : false_type {};
		template<typename T> struct is_float<const T> : is_float<T> {};
		template<typename T> struct is_float<volatile T> : is_float<T> {};
		template<typename T> struct is_float<const volatile T> : is_float<T> {};
		template<> struct is_float<float> : true_type {};
		template<> struct is_float<double> : true_type {};
		template<> struct is_float<long double> : true_type {};
	#endif

	#if HALF_ENABLE_CPP11_CSTDINT
		/// Unsigned integer of (at least) 16 bits width.
		typedef std::uint_least16_t uint16;

		/// Unsigned integer of (at least) 32 bits width.
		typedef std::uint_least32_t uint32;
	#else
		/// Unsigned integer of (at least) 16 bits width.
		typedef unsigned short uint16;

		/// Unsigned integer of (at least) 32 bits width.
		typedef conditional<std::numeric_limits<unsigned int>::digits>=32,unsigned int,unsigned long>::type uint32;
	#endif

		/// Tag type for binary construction.
		struct binary_t {};

		/// Tag for binary construction.
		HALF_CONSTEXPR_CONST binary_t binary = binary_t();

		/// \name Classification helpers
		/// \{

		/// Check for infinity.
		/// \tparam T argument type (builtin floating point type)
		/// \param arg value to query
		/// \retval true if infinity
		/// \retval false else
		template<typename T> bool builtin_isinf(T arg)
		{
		#if HALF_ENABLE_CPP11_CMATH
			return std::isinf(arg);
		#elif defined(_MSC_VER)
			return !_finite(static_cast<double>(arg)) && !_isnan(static_cast<double>(arg));
		#else
			return arg == std::numeric_limits<T>::infinity() || arg == -std::numeric_limits<T>::infinity();
		#endif
		}

		/// Check for NaN.
		/// \tparam T argument type (builtin floating point type)
		/// \param arg value to query
		/// \retval true if not a number
		/// \retval false else
		template<typename T> bool builtin_isnan(T arg)
		{
		#if HALF_ENABLE_CPP11_CMATH
			return std::isnan(arg);
		#elif defined(_MSC_VER)
			return _isnan(static_cast<double>(arg)) != 0;
		#else
			return arg != arg;
		#endif
		}

		/// Check sign.
		/// \tparam T argument type (builtin floating point type)
		/// \param arg value to query
		/// \retval true if signbit set
		/// \retval false else
		template<typename T> bool builtin_signbit(T arg)
		{
		#if HALF_ENABLE_CPP11_CMATH
			return std::signbit(arg);
		#else
			return arg < T() || (arg == T() && T(1)/arg < T());
		#endif
		}

		/// \}
		/// \name Conversion
		/// \{

		/// Convert IEEE single-precision to half-precision.
		/// Credit for this goes to [Jeroen van der Zijp](ftp://ftp.fox-toolkit.org/pub/fasthalffloatconversion.pdf).
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \param value single-precision value
		/// \return binary representation of half-precision value
		template<std::float_round_style R> uint16 float2half_impl(float value, true_type)
		{
		#if HALF_ENABLE_CPP11_STATIC_ASSERT
			static_assert(std::numeric_limits<float>::is_iec559, "float to half conversion needs IEEE 754 conformant 'float' type");
			static_assert(sizeof(uint32)==sizeof(float), "float to half conversion needs unsigned integer type of exactly the size of a 'float'");
		#endif
			static const uint16 base_table[512] = { 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 
				0x0200, 0x0400, 0x0800, 0x0C00, 0x1000, 0x1400, 0x1800, 0x1C00, 0x2000, 0x2400, 0x2800, 0x2C00, 0x3000, 0x3400, 0x3800, 0x3C00, 
				0x4000, 0x4400, 0x4800, 0x4C00, 0x5000, 0x5400, 0x5800, 0x5C00, 0x6000, 0x6400, 0x6800, 0x6C00, 0x7000, 0x7400, 0x7800, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 0x7C00, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
				0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8001, 0x8002, 0x8004, 0x8008, 0x8010, 0x8020, 0x8040, 0x8080, 0x8100, 
				0x8200, 0x8400, 0x8800, 0x8C00, 0x9000, 0x9400, 0x9800, 0x9C00, 0xA000, 0xA400, 0xA800, 0xAC00, 0xB000, 0xB400, 0xB800, 0xBC00, 
				0xC000, 0xC400, 0xC800, 0xCC00, 0xD000, 0xD400, 0xD800, 0xDC00, 0xE000, 0xE400, 0xE800, 0xEC00, 0xF000, 0xF400, 0xF800, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 
				0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00 };
			static const unsigned char shift_table[512] = { 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 
				13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 13, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 
				13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
				24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 13 };
			uint32 bits;// = *reinterpret_cast<uint32*>(&value);		//violating strict aliasing!
			std::memcpy(&bits, &value, sizeof(float));
			uint16 hbits = base_table[bits>>23] + static_cast<uint16>((bits&0x7FFFFF)>>shift_table[bits>>23]);
			if(R == std::round_to_nearest)
				hbits += (((bits&0x7FFFFF)>>(shift_table[bits>>23]-1))|(((bits>>23)&0xFF)==102)) & ((hbits&0x7C00)!=0x7C00)
				#if HALF_ROUND_TIES_TO_EVEN
					& (((((static_cast<uint32>(1)<<(shift_table[bits>>23]-1))-1)&bits)!=0)|hbits)
				#endif
				;
			else if(R == std::round_toward_zero)
				hbits -= ((hbits&0x7FFF)==0x7C00) & ~shift_table[bits>>23];
			else if(R == std::round_toward_infinity)
				hbits += ((((bits&0x7FFFFF&((static_cast<uint32>(1)<<(shift_table[bits>>23]))-1))!=0)|(((bits>>23)<=102)&
					((bits>>23)!=0)))&(hbits<0x7C00)) - ((hbits==0xFC00)&((bits>>23)!=511));
			else if(R == std::round_toward_neg_infinity)
				hbits += ((((bits&0x7FFFFF&((static_cast<uint32>(1)<<(shift_table[bits>>23]))-1))!=0)|(((bits>>23)<=358)&
					((bits>>23)!=256)))&(hbits<0xFC00)&(hbits>>15)) - ((hbits==0x7C00)&((bits>>23)!=255));
			return hbits;
		}

		/// Convert non-IEEE single-precision to half-precision.
		/// \param value single-precision value
		/// \return binary representation of half-precision value
		template<std::float_round_style R> uint16 float2half_impl(float value, false_type)
		{
			uint16 hbits = builtin_signbit(value) << 15;
			if(value == 0.0f)
				return hbits;
			if(builtin_isnan(value))
				return hbits | 0x7FFF;
			if(builtin_isinf(value))
				return hbits | 0x7C00;
			int exp;
			std::frexp(value, &exp);
			if(exp > 16)
			{
				if(R == std::round_toward_infinity)
					return hbits | 0x7C00 - (hbits>>15);
				else if(R == std::round_toward_neg_infinity)
					return hbits | 0x7BFF + (hbits>>15);
				return hbits | 0x7BFF + (R!=std::round_toward_zero);
			}
			if(exp < -13)
				value = std::ldexp(value, 24);
			else
			{
				value = std::ldexp(value, 11-exp);
				hbits |= ((exp+13)<<10);
			}
			int ival = static_cast<int>(value);
			hbits += static_cast<uint16>(std::abs(ival));
			if(R == std::round_to_nearest)
			{
				float diff = std::abs(value-static_cast<float>(ival));
				#if HALF_ROUND_TIES_TO_EVEN
					hbits += (diff>0.5f) | ((diff==0.5f)&hbits);
				#else
					hbits += diff >= 0.5f;
				#endif
			}
			else if(R == std::round_toward_infinity)
				hbits += value > static_cast<float>(ival);
			else if(R == std::round_toward_neg_infinity)
				hbits += value < static_cast<float>(ival);
			return hbits;
		}

		/// Convert single-precision to half-precision.
		/// \param value single-precision value
		/// \return binary representation of half-precision value
		template<std::float_round_style R> uint16 float2half(float value)
		{
			return float2half_impl<R>(value, bool_type<std::numeric_limits<float>::is_iec559&&sizeof(uint32)==sizeof(float)>());
		}

		/// Convert integer to half-precision floating point.
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \tparam S `true` if value negative, `false` else
		/// \tparam T type to convert (builtin integer type)
		/// \param value non-negative integral value
		/// \return binary representation of half-precision value
		template<std::float_round_style R,bool S,typename T> uint16 int2half_impl(T value)
		{
		#if HALF_ENABLE_CPP11_STATIC_ASSERT && HALF_ENABLE_CPP11_TYPE_TRAITS
			static_assert(std::is_integral<T>::value, "int to half conversion only supports builtin integer types");
		#endif
			if(S)
				value = -value;
			uint16 bits = S << 15;
			if(value > 0xFFFF)
			{
				if(R == std::round_toward_infinity)
					bits |= 0x7C00 - S;
				else if(R == std::round_toward_neg_infinity)
					bits |= 0x7BFF + S;
				else
					bits |= 0x7BFF + (R!=std::round_toward_zero);
			}
			else if(value)
			{
				unsigned int m = value, exp = 24;
				for(; m<0x400; m<<=1,--exp) ;
				for(; m>0x7FF; m>>=1,++exp) ;
				bits |= (exp<<10) + m;
				if(exp > 24)
				{
					if(R == std::round_to_nearest)
						bits += (value>>(exp-25)) & 1
						#if HALF_ROUND_TIES_TO_EVEN
							& (((((1<<(exp-25))-1)&value)!=0)|bits)
						#endif
						;
					else if(R == std::round_toward_infinity)
						bits += ((value&((1<<(exp-24))-1))!=0) & !S;
					else if(R == std::round_toward_neg_infinity)
						bits += ((value&((1<<(exp-24))-1))!=0) & S;
				}
			}
			return bits;
		}

		/// Convert integer to half-precision floating point.
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \tparam T type to convert (builtin integer type)
		/// \param value integral value
		/// \return binary representation of half-precision value
		template<std::float_round_style R,typename T> uint16 int2half(T value)
		{
			return (value<0) ? int2half_impl<R,true>(value) : int2half_impl<R,false>(value);
		}

		/// Convert half-precision to IEEE single-precision.
		/// Credit for this goes to [Jeroen van der Zijp](ftp://ftp.fox-toolkit.org/pub/fasthalffloatconversion.pdf).
		/// \param value binary representation of half-precision value
		/// \return single-precision value
		inline float half2float_impl(uint16 value, true_type)
		{
		#if HALF_ENABLE_CPP11_STATIC_ASSERT
			static_assert(std::numeric_limits<float>::is_iec559, "half to float conversion needs IEEE 754 conformant 'float' type");
			static_assert(sizeof(uint32)==sizeof(float), "half to float conversion needs unsigned integer type of exactly the size of a 'float'");
		#endif
			static const uint32 mantissa_table[2048] = { 
				0x00000000, 0x33800000, 0x34000000, 0x34400000, 0x34800000, 0x34A00000, 0x34C00000, 0x34E00000, 0x35000000, 0x35100000, 0x35200000, 0x35300000, 0x35400000, 0x35500000, 0x35600000, 0x35700000, 
				0x35800000, 0x35880000, 0x35900000, 0x35980000, 0x35A00000, 0x35A80000, 0x35B00000, 0x35B80000, 0x35C00000, 0x35C80000, 0x35D00000, 0x35D80000, 0x35E00000, 0x35E80000, 0x35F00000, 0x35F80000, 
				0x36000000, 0x36040000, 0x36080000, 0x360C0000, 0x36100000, 0x36140000, 0x36180000, 0x361C0000, 0x36200000, 0x36240000, 0x36280000, 0x362C0000, 0x36300000, 0x36340000, 0x36380000, 0x363C0000, 
				0x36400000, 0x36440000, 0x36480000, 0x364C0000, 0x36500000, 0x36540000, 0x36580000, 0x365C0000, 0x36600000, 0x36640000, 0x36680000, 0x366C0000, 0x36700000, 0x36740000, 0x36780000, 0x367C0000, 
				0x36800000, 0x36820000, 0x36840000, 0x36860000, 0x36880000, 0x368A0000, 0x368C0000, 0x368E0000, 0x36900000, 0x36920000, 0x36940000, 0x36960000, 0x36980000, 0x369A0000, 0x369C0000, 0x369E0000, 
				0x36A00000, 0x36A20000, 0x36A40000, 0x36A60000, 0x36A80000, 0x36AA0000, 0x36AC0000, 0x36AE0000, 0x36B00000, 0x36B20000, 0x36B40000, 0x36B60000, 0x36B80000, 0x36BA0000, 0x36BC0000, 0x36BE0000, 
				0x36C00000, 0x36C20000, 0x36C40000, 0x36C60000, 0x36C80000, 0x36CA0000, 0x36CC0000, 0x36CE0000, 0x36D00000, 0x36D20000, 0x36D40000, 0x36D60000, 0x36D80000, 0x36DA0000, 0x36DC0000, 0x36DE0000, 
				0x36E00000, 0x36E20000, 0x36E40000, 0x36E60000, 0x36E80000, 0x36EA0000, 0x36EC0000, 0x36EE0000, 0x36F00000, 0x36F20000, 0x36F40000, 0x36F60000, 0x36F80000, 0x36FA0000, 0x36FC0000, 0x36FE0000, 
				0x37000000, 0x37010000, 0x37020000, 0x37030000, 0x37040000, 0x37050000, 0x37060000, 0x37070000, 0x37080000, 0x37090000, 0x370A0000, 0x370B0000, 0x370C0000, 0x370D0000, 0x370E0000, 0x370F0000, 
				0x37100000, 0x37110000, 0x37120000, 0x37130000, 0x37140000, 0x37150000, 0x37160000, 0x37170000, 0x37180000, 0x37190000, 0x371A0000, 0x371B0000, 0x371C0000, 0x371D0000, 0x371E0000, 0x371F0000, 
				0x37200000, 0x37210000, 0x37220000, 0x37230000, 0x37240000, 0x37250000, 0x37260000, 0x37270000, 0x37280000, 0x37290000, 0x372A0000, 0x372B0000, 0x372C0000, 0x372D0000, 0x372E0000, 0x372F0000, 
				0x37300000, 0x37310000, 0x37320000, 0x37330000, 0x37340000, 0x37350000, 0x37360000, 0x37370000, 0x37380000, 0x37390000, 0x373A0000, 0x373B0000, 0x373C0000, 0x373D0000, 0x373E0000, 0x373F0000, 
				0x37400000, 0x37410000, 0x37420000, 0x37430000, 0x37440000, 0x37450000, 0x37460000, 0x37470000, 0x37480000, 0x37490000, 0x374A0000, 0x374B0000, 0x374C0000, 0x374D0000, 0x374E0000, 0x374F0000, 
				0x37500000, 0x37510000, 0x37520000, 0x37530000, 0x37540000, 0x37550000, 0x37560000, 0x37570000, 0x37580000, 0x37590000, 0x375A0000, 0x375B0000, 0x375C0000, 0x375D0000, 0x375E0000, 0x375F0000, 
				0x37600000, 0x37610000, 0x37620000, 0x37630000, 0x37640000, 0x37650000, 0x37660000, 0x37670000, 0x37680000, 0x37690000, 0x376A0000, 0x376B0000, 0x376C0000, 0x376D0000, 0x376E0000, 0x376F0000, 
				0x37700000, 0x37710000, 0x37720000, 0x37730000, 0x37740000, 0x37750000, 0x37760000, 0x37770000, 0x37780000, 0x37790000, 0x377A0000, 0x377B0000, 0x377C0000, 0x377D0000, 0x377E0000, 0x377F0000, 
				0x37800000, 0x37808000, 0x37810000, 0x37818000, 0x37820000, 0x37828000, 0x37830000, 0x37838000, 0x37840000, 0x37848000, 0x37850000, 0x37858000, 0x37860000, 0x37868000, 0x37870000, 0x37878000, 
				0x37880000, 0x37888000, 0x37890000, 0x37898000, 0x378A0000, 0x378A8000, 0x378B0000, 0x378B8000, 0x378C0000, 0x378C8000, 0x378D0000, 0x378D8000, 0x378E0000, 0x378E8000, 0x378F0000, 0x378F8000, 
				0x37900000, 0x37908000, 0x37910000, 0x37918000, 0x37920000, 0x37928000, 0x37930000, 0x37938000, 0x37940000, 0x37948000, 0x37950000, 0x37958000, 0x37960000, 0x37968000, 0x37970000, 0x37978000, 
				0x37980000, 0x37988000, 0x37990000, 0x37998000, 0x379A0000, 0x379A8000, 0x379B0000, 0x379B8000, 0x379C0000, 0x379C8000, 0x379D0000, 0x379D8000, 0x379E0000, 0x379E8000, 0x379F0000, 0x379F8000, 
				0x37A00000, 0x37A08000, 0x37A10000, 0x37A18000, 0x37A20000, 0x37A28000, 0x37A30000, 0x37A38000, 0x37A40000, 0x37A48000, 0x37A50000, 0x37A58000, 0x37A60000, 0x37A68000, 0x37A70000, 0x37A78000, 
				0x37A80000, 0x37A88000, 0x37A90000, 0x37A98000, 0x37AA0000, 0x37AA8000, 0x37AB0000, 0x37AB8000, 0x37AC0000, 0x37AC8000, 0x37AD0000, 0x37AD8000, 0x37AE0000, 0x37AE8000, 0x37AF0000, 0x37AF8000, 
				0x37B00000, 0x37B08000, 0x37B10000, 0x37B18000, 0x37B20000, 0x37B28000, 0x37B30000, 0x37B38000, 0x37B40000, 0x37B48000, 0x37B50000, 0x37B58000, 0x37B60000, 0x37B68000, 0x37B70000, 0x37B78000, 
				0x37B80000, 0x37B88000, 0x37B90000, 0x37B98000, 0x37BA0000, 0x37BA8000, 0x37BB0000, 0x37BB8000, 0x37BC0000, 0x37BC8000, 0x37BD0000, 0x37BD8000, 0x37BE0000, 0x37BE8000, 0x37BF0000, 0x37BF8000, 
				0x37C00000, 0x37C08000, 0x37C10000, 0x37C18000, 0x37C20000, 0x37C28000, 0x37C30000, 0x37C38000, 0x37C40000, 0x37C48000, 0x37C50000, 0x37C58000, 0x37C60000, 0x37C68000, 0x37C70000, 0x37C78000, 
				0x37C80000, 0x37C88000, 0x37C90000, 0x37C98000, 0x37CA0000, 0x37CA8000, 0x37CB0000, 0x37CB8000, 0x37CC0000, 0x37CC8000, 0x37CD0000, 0x37CD8000, 0x37CE0000, 0x37CE8000, 0x37CF0000, 0x37CF8000, 
				0x37D00000, 0x37D08000, 0x37D10000, 0x37D18000, 0x37D20000, 0x37D28000, 0x37D30000, 0x37D38000, 0x37D40000, 0x37D48000, 0x37D50000, 0x37D58000, 0x37D60000, 0x37D68000, 0x37D70000, 0x37D78000, 
				0x37D80000, 0x37D88000, 0x37D90000, 0x37D98000, 0x37DA0000, 0x37DA8000, 0x37DB0000, 0x37DB8000, 0x37DC0000, 0x37DC8000, 0x37DD0000, 0x37DD8000, 0x37DE0000, 0x37DE8000, 0x37DF0000, 0x37DF8000, 
				0x37E00000, 0x37E08000, 0x37E10000, 0x37E18000, 0x37E20000, 0x37E28000, 0x37E30000, 0x37E38000, 0x37E40000, 0x37E48000, 0x37E50000, 0x37E58000, 0x37E60000, 0x37E68000, 0x37E70000, 0x37E78000, 
				0x37E80000, 0x37E88000, 0x37E90000, 0x37E98000, 0x37EA0000, 0x37EA8000, 0x37EB0000, 0x37EB8000, 0x37EC0000, 0x37EC8000, 0x37ED0000, 0x37ED8000, 0x37EE0000, 0x37EE8000, 0x37EF0000, 0x37EF8000, 
				0x37F00000, 0x37F08000, 0x37F10000, 0x37F18000, 0x37F20000, 0x37F28000, 0x37F30000, 0x37F38000, 0x37F40000, 0x37F48000, 0x37F50000, 0x37F58000, 0x37F60000, 0x37F68000, 0x37F70000, 0x37F78000, 
				0x37F80000, 0x37F88000, 0x37F90000, 0x37F98000, 0x37FA0000, 0x37FA8000, 0x37FB0000, 0x37FB8000, 0x37FC0000, 0x37FC8000, 0x37FD0000, 0x37FD8000, 0x37FE0000, 0x37FE8000, 0x37FF0000, 0x37FF8000, 
				0x38000000, 0x38004000, 0x38008000, 0x3800C000, 0x38010000, 0x38014000, 0x38018000, 0x3801C000, 0x38020000, 0x38024000, 0x38028000, 0x3802C000, 0x38030000, 0x38034000, 0x38038000, 0x3803C000, 
				0x38040000, 0x38044000, 0x38048000, 0x3804C000, 0x38050000, 0x38054000, 0x38058000, 0x3805C000, 0x38060000, 0x38064000, 0x38068000, 0x3806C000, 0x38070000, 0x38074000, 0x38078000, 0x3807C000, 
				0x38080000, 0x38084000, 0x38088000, 0x3808C000, 0x38090000, 0x38094000, 0x38098000, 0x3809C000, 0x380A0000, 0x380A4000, 0x380A8000, 0x380AC000, 0x380B0000, 0x380B4000, 0x380B8000, 0x380BC000, 
				0x380C0000, 0x380C4000, 0x380C8000, 0x380CC000, 0x380D0000, 0x380D4000, 0x380D8000, 0x380DC000, 0x380E0000, 0x380E4000, 0x380E8000, 0x380EC000, 0x380F0000, 0x380F4000, 0x380F8000, 0x380FC000, 
				0x38100000, 0x38104000, 0x38108000, 0x3810C000, 0x38110000, 0x38114000, 0x38118000, 0x3811C000, 0x38120000, 0x38124000, 0x38128000, 0x3812C000, 0x38130000, 0x38134000, 0x38138000, 0x3813C000, 
				0x38140000, 0x38144000, 0x38148000, 0x3814C000, 0x38150000, 0x38154000, 0x38158000, 0x3815C000, 0x38160000, 0x38164000, 0x38168000, 0x3816C000, 0x38170000, 0x38174000, 0x38178000, 0x3817C000, 
				0x38180000, 0x38184000, 0x38188000, 0x3818C000, 0x38190000, 0x38194000, 0x38198000, 0x3819C000, 0x381A0000, 0x381A4000, 0x381A8000, 0x381AC000, 0x381B0000, 0x381B4000, 0x381B8000, 0x381BC000, 
				0x381C0000, 0x381C4000, 0x381C8000, 0x381CC000, 0x381D0000, 0x381D4000, 0x381D8000, 0x381DC000, 0x381E0000, 0x381E4000, 0x381E8000, 0x381EC000, 0x381F0000, 0x381F4000, 0x381F8000, 0x381FC000, 
				0x38200000, 0x38204000, 0x38208000, 0x3820C000, 0x38210000, 0x38214000, 0x38218000, 0x3821C000, 0x38220000, 0x38224000, 0x38228000, 0x3822C000, 0x38230000, 0x38234000, 0x38238000, 0x3823C000, 
				0x38240000, 0x38244000, 0x38248000, 0x3824C000, 0x38250000, 0x38254000, 0x38258000, 0x3825C000, 0x38260000, 0x38264000, 0x38268000, 0x3826C000, 0x38270000, 0x38274000, 0x38278000, 0x3827C000, 
				0x38280000, 0x38284000, 0x38288000, 0x3828C000, 0x38290000, 0x38294000, 0x38298000, 0x3829C000, 0x382A0000, 0x382A4000, 0x382A8000, 0x382AC000, 0x382B0000, 0x382B4000, 0x382B8000, 0x382BC000, 
				0x382C0000, 0x382C4000, 0x382C8000, 0x382CC000, 0x382D0000, 0x382D4000, 0x382D8000, 0x382DC000, 0x382E0000, 0x382E4000, 0x382E8000, 0x382EC000, 0x382F0000, 0x382F4000, 0x382F8000, 0x382FC000, 
				0x38300000, 0x38304000, 0x38308000, 0x3830C000, 0x38310000, 0x38314000, 0x38318000, 0x3831C000, 0x38320000, 0x38324000, 0x38328000, 0x3832C000, 0x38330000, 0x38334000, 0x38338000, 0x3833C000, 
				0x38340000, 0x38344000, 0x38348000, 0x3834C000, 0x38350000, 0x38354000, 0x38358000, 0x3835C000, 0x38360000, 0x38364000, 0x38368000, 0x3836C000, 0x38370000, 0x38374000, 0x38378000, 0x3837C000, 
				0x38380000, 0x38384000, 0x38388000, 0x3838C000, 0x38390000, 0x38394000, 0x38398000, 0x3839C000, 0x383A0000, 0x383A4000, 0x383A8000, 0x383AC000, 0x383B0000, 0x383B4000, 0x383B8000, 0x383BC000, 
				0x383C0000, 0x383C4000, 0x383C8000, 0x383CC000, 0x383D0000, 0x383D4000, 0x383D8000, 0x383DC000, 0x383E0000, 0x383E4000, 0x383E8000, 0x383EC000, 0x383F0000, 0x383F4000, 0x383F8000, 0x383FC000, 
				0x38400000, 0x38404000, 0x38408000, 0x3840C000, 0x38410000, 0x38414000, 0x38418000, 0x3841C000, 0x38420000, 0x38424000, 0x38428000, 0x3842C000, 0x38430000, 0x38434000, 0x38438000, 0x3843C000, 
				0x38440000, 0x38444000, 0x38448000, 0x3844C000, 0x38450000, 0x38454000, 0x38458000, 0x3845C000, 0x38460000, 0x38464000, 0x38468000, 0x3846C000, 0x38470000, 0x38474000, 0x38478000, 0x3847C000, 
				0x38480000, 0x38484000, 0x38488000, 0x3848C000, 0x38490000, 0x38494000, 0x38498000, 0x3849C000, 0x384A0000, 0x384A4000, 0x384A8000, 0x384AC000, 0x384B0000, 0x384B4000, 0x384B8000, 0x384BC000, 
				0x384C0000, 0x384C4000, 0x384C8000, 0x384CC000, 0x384D0000, 0x384D4000, 0x384D8000, 0x384DC000, 0x384E0000, 0x384E4000, 0x384E8000, 0x384EC000, 0x384F0000, 0x384F4000, 0x384F8000, 0x384FC000, 
				0x38500000, 0x38504000, 0x38508000, 0x3850C000, 0x38510000, 0x38514000, 0x38518000, 0x3851C000, 0x38520000, 0x38524000, 0x38528000, 0x3852C000, 0x38530000, 0x38534000, 0x38538000, 0x3853C000, 
				0x38540000, 0x38544000, 0x38548000, 0x3854C000, 0x38550000, 0x38554000, 0x38558000, 0x3855C000, 0x38560000, 0x38564000, 0x38568000, 0x3856C000, 0x38570000, 0x38574000, 0x38578000, 0x3857C000, 
				0x38580000, 0x38584000, 0x38588000, 0x3858C000, 0x38590000, 0x38594000, 0x38598000, 0x3859C000, 0x385A0000, 0x385A4000, 0x385A8000, 0x385AC000, 0x385B0000, 0x385B4000, 0x385B8000, 0x385BC000, 
				0x385C0000, 0x385C4000, 0x385C8000, 0x385CC000, 0x385D0000, 0x385D4000, 0x385D8000, 0x385DC000, 0x385E0000, 0x385E4000, 0x385E8000, 0x385EC000, 0x385F0000, 0x385F4000, 0x385F8000, 0x385FC000, 
				0x38600000, 0x38604000, 0x38608000, 0x3860C000, 0x38610000, 0x38614000, 0x38618000, 0x3861C000, 0x38620000, 0x38624000, 0x38628000, 0x3862C000, 0x38630000, 0x38634000, 0x38638000, 0x3863C000, 
				0x38640000, 0x38644000, 0x38648000, 0x3864C000, 0x38650000, 0x38654000, 0x38658000, 0x3865C000, 0x38660000, 0x38664000, 0x38668000, 0x3866C000, 0x38670000, 0x38674000, 0x38678000, 0x3867C000, 
				0x38680000, 0x38684000, 0x38688000, 0x3868C000, 0x38690000, 0x38694000, 0x38698000, 0x3869C000, 0x386A0000, 0x386A4000, 0x386A8000, 0x386AC000, 0x386B0000, 0x386B4000, 0x386B8000, 0x386BC000, 
				0x386C0000, 0x386C4000, 0x386C8000, 0x386CC000, 0x386D0000, 0x386D4000, 0x386D8000, 0x386DC000, 0x386E0000, 0x386E4000, 0x386E8000, 0x386EC000, 0x386F0000, 0x386F4000, 0x386F8000, 0x386FC000, 
				0x38700000, 0x38704000, 0x38708000, 0x3870C000, 0x38710000, 0x38714000, 0x38718000, 0x3871C000, 0x38720000, 0x38724000, 0x38728000, 0x3872C000, 0x38730000, 0x38734000, 0x38738000, 0x3873C000, 
				0x38740000, 0x38744000, 0x38748000, 0x3874C000, 0x38750000, 0x38754000, 0x38758000, 0x3875C000, 0x38760000, 0x38764000, 0x38768000, 0x3876C000, 0x38770000, 0x38774000, 0x38778000, 0x3877C000, 
				0x38780000, 0x38784000, 0x38788000, 0x3878C000, 0x38790000, 0x38794000, 0x38798000, 0x3879C000, 0x387A0000, 0x387A4000, 0x387A8000, 0x387AC000, 0x387B0000, 0x387B4000, 0x387B8000, 0x387BC000, 
				0x387C0000, 0x387C4000, 0x387C8000, 0x387CC000, 0x387D0000, 0x387D4000, 0x387D8000, 0x387DC000, 0x387E0000, 0x387E4000, 0x387E8000, 0x387EC000, 0x387F0000, 0x387F4000, 0x387F8000, 0x387FC000, 
				0x38000000, 0x38002000, 0x38004000, 0x38006000, 0x38008000, 0x3800A000, 0x3800C000, 0x3800E000, 0x38010000, 0x38012000, 0x38014000, 0x38016000, 0x38018000, 0x3801A000, 0x3801C000, 0x3801E000, 
				0x38020000, 0x38022000, 0x38024000, 0x38026000, 0x38028000, 0x3802A000, 0x3802C000, 0x3802E000, 0x38030000, 0x38032000, 0x38034000, 0x38036000, 0x38038000, 0x3803A000, 0x3803C000, 0x3803E000, 
				0x38040000, 0x38042000, 0x38044000, 0x38046000, 0x38048000, 0x3804A000, 0x3804C000, 0x3804E000, 0x38050000, 0x38052000, 0x38054000, 0x38056000, 0x38058000, 0x3805A000, 0x3805C000, 0x3805E000, 
				0x38060000, 0x38062000, 0x38064000, 0x38066000, 0x38068000, 0x3806A000, 0x3806C000, 0x3806E000, 0x38070000, 0x38072000, 0x38074000, 0x38076000, 0x38078000, 0x3807A000, 0x3807C000, 0x3807E000, 
				0x38080000, 0x38082000, 0x38084000, 0x38086000, 0x38088000, 0x3808A000, 0x3808C000, 0x3808E000, 0x38090000, 0x38092000, 0x38094000, 0x38096000, 0x38098000, 0x3809A000, 0x3809C000, 0x3809E000, 
				0x380A0000, 0x380A2000, 0x380A4000, 0x380A6000, 0x380A8000, 0x380AA000, 0x380AC000, 0x380AE000, 0x380B0000, 0x380B2000, 0x380B4000, 0x380B6000, 0x380B8000, 0x380BA000, 0x380BC000, 0x380BE000, 
				0x380C0000, 0x380C2000, 0x380C4000, 0x380C6000, 0x380C8000, 0x380CA000, 0x380CC000, 0x380CE000, 0x380D0000, 0x380D2000, 0x380D4000, 0x380D6000, 0x380D8000, 0x380DA000, 0x380DC000, 0x380DE000, 
				0x380E0000, 0x380E2000, 0x380E4000, 0x380E6000, 0x380E8000, 0x380EA000, 0x380EC000, 0x380EE000, 0x380F0000, 0x380F2000, 0x380F4000, 0x380F6000, 0x380F8000, 0x380FA000, 0x380FC000, 0x380FE000, 
				0x38100000, 0x38102000, 0x38104000, 0x38106000, 0x38108000, 0x3810A000, 0x3810C000, 0x3810E000, 0x38110000, 0x38112000, 0x38114000, 0x38116000, 0x38118000, 0x3811A000, 0x3811C000, 0x3811E000, 
				0x38120000, 0x38122000, 0x38124000, 0x38126000, 0x38128000, 0x3812A000, 0x3812C000, 0x3812E000, 0x38130000, 0x38132000, 0x38134000, 0x38136000, 0x38138000, 0x3813A000, 0x3813C000, 0x3813E000, 
				0x38140000, 0x38142000, 0x38144000, 0x38146000, 0x38148000, 0x3814A000, 0x3814C000, 0x3814E000, 0x38150000, 0x38152000, 0x38154000, 0x38156000, 0x38158000, 0x3815A000, 0x3815C000, 0x3815E000, 
				0x38160000, 0x38162000, 0x38164000, 0x38166000, 0x38168000, 0x3816A000, 0x3816C000, 0x3816E000, 0x38170000, 0x38172000, 0x38174000, 0x38176000, 0x38178000, 0x3817A000, 0x3817C000, 0x3817E000, 
				0x38180000, 0x38182000, 0x38184000, 0x38186000, 0x38188000, 0x3818A000, 0x3818C000, 0x3818E000, 0x38190000, 0x38192000, 0x38194000, 0x38196000, 0x38198000, 0x3819A000, 0x3819C000, 0x3819E000, 
				0x381A0000, 0x381A2000, 0x381A4000, 0x381A6000, 0x381A8000, 0x381AA000, 0x381AC000, 0x381AE000, 0x381B0000, 0x381B2000, 0x381B4000, 0x381B6000, 0x381B8000, 0x381BA000, 0x381BC000, 0x381BE000, 
				0x381C0000, 0x381C2000, 0x381C4000, 0x381C6000, 0x381C8000, 0x381CA000, 0x381CC000, 0x381CE000, 0x381D0000, 0x381D2000, 0x381D4000, 0x381D6000, 0x381D8000, 0x381DA000, 0x381DC000, 0x381DE000, 
				0x381E0000, 0x381E2000, 0x381E4000, 0x381E6000, 0x381E8000, 0x381EA000, 0x381EC000, 0x381EE000, 0x381F0000, 0x381F2000, 0x381F4000, 0x381F6000, 0x381F8000, 0x381FA000, 0x381FC000, 0x381FE000, 
				0x38200000, 0x38202000, 0x38204000, 0x38206000, 0x38208000, 0x3820A000, 0x3820C000, 0x3820E000, 0x38210000, 0x38212000, 0x38214000, 0x38216000, 0x38218000, 0x3821A000, 0x3821C000, 0x3821E000, 
				0x38220000, 0x38222000, 0x38224000, 0x38226000, 0x38228000, 0x3822A000, 0x3822C000, 0x3822E000, 0x38230000, 0x38232000, 0x38234000, 0x38236000, 0x38238000, 0x3823A000, 0x3823C000, 0x3823E000, 
				0x38240000, 0x38242000, 0x38244000, 0x38246000, 0x38248000, 0x3824A000, 0x3824C000, 0x3824E000, 0x38250000, 0x38252000, 0x38254000, 0x38256000, 0x38258000, 0x3825A000, 0x3825C000, 0x3825E000, 
				0x38260000, 0x38262000, 0x38264000, 0x38266000, 0x38268000, 0x3826A000, 0x3826C000, 0x3826E000, 0x38270000, 0x38272000, 0x38274000, 0x38276000, 0x38278000, 0x3827A000, 0x3827C000, 0x3827E000, 
				0x38280000, 0x38282000, 0x38284000, 0x38286000, 0x38288000, 0x3828A000, 0x3828C000, 0x3828E000, 0x38290000, 0x38292000, 0x38294000, 0x38296000, 0x38298000, 0x3829A000, 0x3829C000, 0x3829E000, 
				0x382A0000, 0x382A2000, 0x382A4000, 0x382A6000, 0x382A8000, 0x382AA000, 0x382AC000, 0x382AE000, 0x382B0000, 0x382B2000, 0x382B4000, 0x382B6000, 0x382B8000, 0x382BA000, 0x382BC000, 0x382BE000, 
				0x382C0000, 0x382C2000, 0x382C4000, 0x382C6000, 0x382C8000, 0x382CA000, 0x382CC000, 0x382CE000, 0x382D0000, 0x382D2000, 0x382D4000, 0x382D6000, 0x382D8000, 0x382DA000, 0x382DC000, 0x382DE000, 
				0x382E0000, 0x382E2000, 0x382E4000, 0x382E6000, 0x382E8000, 0x382EA000, 0x382EC000, 0x382EE000, 0x382F0000, 0x382F2000, 0x382F4000, 0x382F6000, 0x382F8000, 0x382FA000, 0x382FC000, 0x382FE000, 
				0x38300000, 0x38302000, 0x38304000, 0x38306000, 0x38308000, 0x3830A000, 0x3830C000, 0x3830E000, 0x38310000, 0x38312000, 0x38314000, 0x38316000, 0x38318000, 0x3831A000, 0x3831C000, 0x3831E000, 
				0x38320000, 0x38322000, 0x38324000, 0x38326000, 0x38328000, 0x3832A000, 0x3832C000, 0x3832E000, 0x38330000, 0x38332000, 0x38334000, 0x38336000, 0x38338000, 0x3833A000, 0x3833C000, 0x3833E000, 
				0x38340000, 0x38342000, 0x38344000, 0x38346000, 0x38348000, 0x3834A000, 0x3834C000, 0x3834E000, 0x38350000, 0x38352000, 0x38354000, 0x38356000, 0x38358000, 0x3835A000, 0x3835C000, 0x3835E000, 
				0x38360000, 0x38362000, 0x38364000, 0x38366000, 0x38368000, 0x3836A000, 0x3836C000, 0x3836E000, 0x38370000, 0x38372000, 0x38374000, 0x38376000, 0x38378000, 0x3837A000, 0x3837C000, 0x3837E000, 
				0x38380000, 0x38382000, 0x38384000, 0x38386000, 0x38388000, 0x3838A000, 0x3838C000, 0x3838E000, 0x38390000, 0x38392000, 0x38394000, 0x38396000, 0x38398000, 0x3839A000, 0x3839C000, 0x3839E000, 
				0x383A0000, 0x383A2000, 0x383A4000, 0x383A6000, 0x383A8000, 0x383AA000, 0x383AC000, 0x383AE000, 0x383B0000, 0x383B2000, 0x383B4000, 0x383B6000, 0x383B8000, 0x383BA000, 0x383BC000, 0x383BE000, 
				0x383C0000, 0x383C2000, 0x383C4000, 0x383C6000, 0x383C8000, 0x383CA000, 0x383CC000, 0x383CE000, 0x383D0000, 0x383D2000, 0x383D4000, 0x383D6000, 0x383D8000, 0x383DA000, 0x383DC000, 0x383DE000, 
				0x383E0000, 0x383E2000, 0x383E4000, 0x383E6000, 0x383E8000, 0x383EA000, 0x383EC000, 0x383EE000, 0x383F0000, 0x383F2000, 0x383F4000, 0x383F6000, 0x383F8000, 0x383FA000, 0x383FC000, 0x383FE000, 
				0x38400000, 0x38402000, 0x38404000, 0x38406000, 0x38408000, 0x3840A000, 0x3840C000, 0x3840E000, 0x38410000, 0x38412000, 0x38414000, 0x38416000, 0x38418000, 0x3841A000, 0x3841C000, 0x3841E000, 
				0x38420000, 0x38422000, 0x38424000, 0x38426000, 0x38428000, 0x3842A000, 0x3842C000, 0x3842E000, 0x38430000, 0x38432000, 0x38434000, 0x38436000, 0x38438000, 0x3843A000, 0x3843C000, 0x3843E000, 
				0x38440000, 0x38442000, 0x38444000, 0x38446000, 0x38448000, 0x3844A000, 0x3844C000, 0x3844E000, 0x38450000, 0x38452000, 0x38454000, 0x38456000, 0x38458000, 0x3845A000, 0x3845C000, 0x3845E000, 
				0x38460000, 0x38462000, 0x38464000, 0x38466000, 0x38468000, 0x3846A000, 0x3846C000, 0x3846E000, 0x38470000, 0x38472000, 0x38474000, 0x38476000, 0x38478000, 0x3847A000, 0x3847C000, 0x3847E000, 
				0x38480000, 0x38482000, 0x38484000, 0x38486000, 0x38488000, 0x3848A000, 0x3848C000, 0x3848E000, 0x38490000, 0x38492000, 0x38494000, 0x38496000, 0x38498000, 0x3849A000, 0x3849C000, 0x3849E000, 
				0x384A0000, 0x384A2000, 0x384A4000, 0x384A6000, 0x384A8000, 0x384AA000, 0x384AC000, 0x384AE000, 0x384B0000, 0x384B2000, 0x384B4000, 0x384B6000, 0x384B8000, 0x384BA000, 0x384BC000, 0x384BE000, 
				0x384C0000, 0x384C2000, 0x384C4000, 0x384C6000, 0x384C8000, 0x384CA000, 0x384CC000, 0x384CE000, 0x384D0000, 0x384D2000, 0x384D4000, 0x384D6000, 0x384D8000, 0x384DA000, 0x384DC000, 0x384DE000, 
				0x384E0000, 0x384E2000, 0x384E4000, 0x384E6000, 0x384E8000, 0x384EA000, 0x384EC000, 0x384EE000, 0x384F0000, 0x384F2000, 0x384F4000, 0x384F6000, 0x384F8000, 0x384FA000, 0x384FC000, 0x384FE000, 
				0x38500000, 0x38502000, 0x38504000, 0x38506000, 0x38508000, 0x3850A000, 0x3850C000, 0x3850E000, 0x38510000, 0x38512000, 0x38514000, 0x38516000, 0x38518000, 0x3851A000, 0x3851C000, 0x3851E000, 
				0x38520000, 0x38522000, 0x38524000, 0x38526000, 0x38528000, 0x3852A000, 0x3852C000, 0x3852E000, 0x38530000, 0x38532000, 0x38534000, 0x38536000, 0x38538000, 0x3853A000, 0x3853C000, 0x3853E000, 
				0x38540000, 0x38542000, 0x38544000, 0x38546000, 0x38548000, 0x3854A000, 0x3854C000, 0x3854E000, 0x38550000, 0x38552000, 0x38554000, 0x38556000, 0x38558000, 0x3855A000, 0x3855C000, 0x3855E000, 
				0x38560000, 0x38562000, 0x38564000, 0x38566000, 0x38568000, 0x3856A000, 0x3856C000, 0x3856E000, 0x38570000, 0x38572000, 0x38574000, 0x38576000, 0x38578000, 0x3857A000, 0x3857C000, 0x3857E000, 
				0x38580000, 0x38582000, 0x38584000, 0x38586000, 0x38588000, 0x3858A000, 0x3858C000, 0x3858E000, 0x38590000, 0x38592000, 0x38594000, 0x38596000, 0x38598000, 0x3859A000, 0x3859C000, 0x3859E000, 
				0x385A0000, 0x385A2000, 0x385A4000, 0x385A6000, 0x385A8000, 0x385AA000, 0x385AC000, 0x385AE000, 0x385B0000, 0x385B2000, 0x385B4000, 0x385B6000, 0x385B8000, 0x385BA000, 0x385BC000, 0x385BE000, 
				0x385C0000, 0x385C2000, 0x385C4000, 0x385C6000, 0x385C8000, 0x385CA000, 0x385CC000, 0x385CE000, 0x385D0000, 0x385D2000, 0x385D4000, 0x385D6000, 0x385D8000, 0x385DA000, 0x385DC000, 0x385DE000, 
				0x385E0000, 0x385E2000, 0x385E4000, 0x385E6000, 0x385E8000, 0x385EA000, 0x385EC000, 0x385EE000, 0x385F0000, 0x385F2000, 0x385F4000, 0x385F6000, 0x385F8000, 0x385FA000, 0x385FC000, 0x385FE000, 
				0x38600000, 0x38602000, 0x38604000, 0x38606000, 0x38608000, 0x3860A000, 0x3860C000, 0x3860E000, 0x38610000, 0x38612000, 0x38614000, 0x38616000, 0x38618000, 0x3861A000, 0x3861C000, 0x3861E000, 
				0x38620000, 0x38622000, 0x38624000, 0x38626000, 0x38628000, 0x3862A000, 0x3862C000, 0x3862E000, 0x38630000, 0x38632000, 0x38634000, 0x38636000, 0x38638000, 0x3863A000, 0x3863C000, 0x3863E000, 
				0x38640000, 0x38642000, 0x38644000, 0x38646000, 0x38648000, 0x3864A000, 0x3864C000, 0x3864E000, 0x38650000, 0x38652000, 0x38654000, 0x38656000, 0x38658000, 0x3865A000, 0x3865C000, 0x3865E000, 
				0x38660000, 0x38662000, 0x38664000, 0x38666000, 0x38668000, 0x3866A000, 0x3866C000, 0x3866E000, 0x38670000, 0x38672000, 0x38674000, 0x38676000, 0x38678000, 0x3867A000, 0x3867C000, 0x3867E000, 
				0x38680000, 0x38682000, 0x38684000, 0x38686000, 0x38688000, 0x3868A000, 0x3868C000, 0x3868E000, 0x38690000, 0x38692000, 0x38694000, 0x38696000, 0x38698000, 0x3869A000, 0x3869C000, 0x3869E000, 
				0x386A0000, 0x386A2000, 0x386A4000, 0x386A6000, 0x386A8000, 0x386AA000, 0x386AC000, 0x386AE000, 0x386B0000, 0x386B2000, 0x386B4000, 0x386B6000, 0x386B8000, 0x386BA000, 0x386BC000, 0x386BE000, 
				0x386C0000, 0x386C2000, 0x386C4000, 0x386C6000, 0x386C8000, 0x386CA000, 0x386CC000, 0x386CE000, 0x386D0000, 0x386D2000, 0x386D4000, 0x386D6000, 0x386D8000, 0x386DA000, 0x386DC000, 0x386DE000, 
				0x386E0000, 0x386E2000, 0x386E4000, 0x386E6000, 0x386E8000, 0x386EA000, 0x386EC000, 0x386EE000, 0x386F0000, 0x386F2000, 0x386F4000, 0x386F6000, 0x386F8000, 0x386FA000, 0x386FC000, 0x386FE000, 
				0x38700000, 0x38702000, 0x38704000, 0x38706000, 0x38708000, 0x3870A000, 0x3870C000, 0x3870E000, 0x38710000, 0x38712000, 0x38714000, 0x38716000, 0x38718000, 0x3871A000, 0x3871C000, 0x3871E000, 
				0x38720000, 0x38722000, 0x38724000, 0x38726000, 0x38728000, 0x3872A000, 0x3872C000, 0x3872E000, 0x38730000, 0x38732000, 0x38734000, 0x38736000, 0x38738000, 0x3873A000, 0x3873C000, 0x3873E000, 
				0x38740000, 0x38742000, 0x38744000, 0x38746000, 0x38748000, 0x3874A000, 0x3874C000, 0x3874E000, 0x38750000, 0x38752000, 0x38754000, 0x38756000, 0x38758000, 0x3875A000, 0x3875C000, 0x3875E000, 
				0x38760000, 0x38762000, 0x38764000, 0x38766000, 0x38768000, 0x3876A000, 0x3876C000, 0x3876E000, 0x38770000, 0x38772000, 0x38774000, 0x38776000, 0x38778000, 0x3877A000, 0x3877C000, 0x3877E000, 
				0x38780000, 0x38782000, 0x38784000, 0x38786000, 0x38788000, 0x3878A000, 0x3878C000, 0x3878E000, 0x38790000, 0x38792000, 0x38794000, 0x38796000, 0x38798000, 0x3879A000, 0x3879C000, 0x3879E000, 
				0x387A0000, 0x387A2000, 0x387A4000, 0x387A6000, 0x387A8000, 0x387AA000, 0x387AC000, 0x387AE000, 0x387B0000, 0x387B2000, 0x387B4000, 0x387B6000, 0x387B8000, 0x387BA000, 0x387BC000, 0x387BE000, 
				0x387C0000, 0x387C2000, 0x387C4000, 0x387C6000, 0x387C8000, 0x387CA000, 0x387CC000, 0x387CE000, 0x387D0000, 0x387D2000, 0x387D4000, 0x387D6000, 0x387D8000, 0x387DA000, 0x387DC000, 0x387DE000, 
				0x387E0000, 0x387E2000, 0x387E4000, 0x387E6000, 0x387E8000, 0x387EA000, 0x387EC000, 0x387EE000, 0x387F0000, 0x387F2000, 0x387F4000, 0x387F6000, 0x387F8000, 0x387FA000, 0x387FC000, 0x387FE000 };
			static const uint32 exponent_table[64] = { 
				0x00000000, 0x00800000, 0x01000000, 0x01800000, 0x02000000, 0x02800000, 0x03000000, 0x03800000, 0x04000000, 0x04800000, 0x05000000, 0x05800000, 0x06000000, 0x06800000, 0x07000000, 0x07800000, 
				0x08000000, 0x08800000, 0x09000000, 0x09800000, 0x0A000000, 0x0A800000, 0x0B000000, 0x0B800000, 0x0C000000, 0x0C800000, 0x0D000000, 0x0D800000, 0x0E000000, 0x0E800000, 0x0F000000, 0x47800000, 
				0x80000000, 0x80800000, 0x81000000, 0x81800000, 0x82000000, 0x82800000, 0x83000000, 0x83800000, 0x84000000, 0x84800000, 0x85000000, 0x85800000, 0x86000000, 0x86800000, 0x87000000, 0x87800000, 
				0x88000000, 0x88800000, 0x89000000, 0x89800000, 0x8A000000, 0x8A800000, 0x8B000000, 0x8B800000, 0x8C000000, 0x8C800000, 0x8D000000, 0x8D800000, 0x8E000000, 0x8E800000, 0x8F000000, 0xC7800000 };
			static const unsigned short offset_table[64] = { 
				   0, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 
				   0, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024 };
			uint32 bits = mantissa_table[offset_table[value>>10]+(value&0x3FF)] + exponent_table[value>>10];
//			uint32 bits = mantissa_table[(((value&0x7C00)!=0)<<10)+(value&0x3FF)] + exponent_table[value>>10];
//			return *reinterpret_cast<float*>(&bits);			//violating strict aliasing!
			float out;
			std::memcpy(&out, &bits, sizeof(float));
			return out;
		}

		/// Convert half-precision to non-IEEE single-precision.
		/// \param value binary representation of half-precision value
		/// \return single-precision value
		inline float half2float_impl(uint16 value, false_type)
		{
			float out;
			int abs = value & 0x7FFF;
			if(abs > 0x7C00)
				out = std::numeric_limits<float>::has_quiet_NaN ? std::numeric_limits<float>::quiet_NaN() : 0.0f;
			else if(abs == 0x7C00)
				out = std::numeric_limits<float>::has_infinity ? std::numeric_limits<float>::infinity() : std::numeric_limits<float>::max();
			else if(abs > 0x3FF)
				out = std::ldexp(static_cast<float>((value&0x3FF)|0x400), (abs>>10)-25);
			else
				out = std::ldexp(static_cast<float>(abs), -24);
			return (value&0x8000) ? -out : out;
		}

		/// Convert half-precision to single-precision.
		/// \param value binary representation of half-precision value
		/// \return single-precision value
		inline float half2float(uint16 value)
		{
			return half2float_impl(value, bool_type<std::numeric_limits<float>::is_iec559&&sizeof(uint32)==sizeof(float)>());
		}

		/// Convert half-precision floating point to integer.
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \tparam E `true` for round to even, `false` for round away from zero
		/// \tparam T type to convert to (buitlin integer type with at least 16 bits precision, excluding any implicit sign bits)
		/// \param value binary representation of half-precision value
		/// \return integral value
		template<std::float_round_style R,bool E,typename T> T half2int_impl(uint16 value)
		{
		#if HALF_ENABLE_CPP11_STATIC_ASSERT && HALF_ENABLE_CPP11_TYPE_TRAITS
			static_assert(std::is_integral<T>::value, "half to int conversion only supports builtin integer types");
		#endif
			unsigned int e = value & 0x7FFF;
			if(e >= 0x7C00)
				return (value&0x8000) ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max();
			if(e < 0x3800)
			{
				if(R == std::round_toward_infinity)
					return T(~(value>>15)&(e!=0));
				else if(R == std::round_toward_neg_infinity)
					return -T(value>0x8000);
				return T();
			}
			unsigned int m = (value&0x3FF) | 0x400;
			e >>= 10;
			if(e < 25)
			{
				if(R == std::round_to_nearest)
					m += (1<<(24-e)) - (~(m>>(25-e))&E);
				else if(R == std::round_toward_infinity)
					m += ((value>>15)-1) & ((1<<(25-e))-1U);
				else if(R == std::round_toward_neg_infinity)
					m += -(value>>15) & ((1<<(25-e))-1U);
				m >>= 25 - e;
			}
			else
				m <<= e - 25;
			return (value&0x8000) ? -static_cast<T>(m) : static_cast<T>(m);
		}

		/// Convert half-precision floating point to integer.
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \tparam T type to convert to (buitlin integer type with at least 16 bits precision, excluding any implicit sign bits)
		/// \param value binary representation of half-precision value
		/// \return integral value
		template<std::float_round_style R,typename T> T half2int(uint16 value) { return half2int_impl<R,HALF_ROUND_TIES_TO_EVEN,T>(value); }

		/// Convert half-precision floating point to integer using round-to-nearest-away-from-zero.
		/// \tparam T type to convert to (buitlin integer type with at least 16 bits precision, excluding any implicit sign bits)
		/// \param value binary representation of half-precision value
		/// \return integral value
		template<typename T> T half2int_up(uint16 value) { return half2int_impl<std::round_to_nearest,0,T>(value); }

		/// Round half-precision number to nearest integer value.
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \tparam E `true` for round to even, `false` for round away from zero
		/// \param value binary representation of half-precision value
		/// \return half-precision bits for nearest integral value
		template<std::float_round_style R,bool E> uint16 round_half_impl(uint16 value)
		{
			unsigned int e = value & 0x7FFF;
			uint16 result = value;
			if(e < 0x3C00)
			{
				result &= 0x8000;
				if(R == std::round_to_nearest)
					result |= 0x3C00U & -(e>=(0x3800+E));
				else if(R == std::round_toward_infinity)
					result |= 0x3C00U & -(~(value>>15)&(e!=0));
				else if(R == std::round_toward_neg_infinity)
					result |= 0x3C00U & -(value>0x8000);
			}
			else if(e < 0x6400)
			{
				e = 25 - (e>>10);
				unsigned int mask = (1<<e) - 1;
				if(R == std::round_to_nearest)
					result += (1<<(e-1)) - (~(result>>e)&E);
				else if(R == std::round_toward_infinity)
					result += mask & ((value>>15)-1);
				else if(R == std::round_toward_neg_infinity)
					result += mask & -(value>>15);
				result &= ~mask;
			}
			return result;
		}

		/// Round half-precision number to nearest integer value.
		/// \tparam R rounding mode to use, `std::round_indeterminate` for fastest rounding
		/// \param value binary representation of half-precision value
		/// \return half-precision bits for nearest integral value
		template<std::float_round_style R> uint16 round_half(uint16 value) { return round_half_impl<R,HALF_ROUND_TIES_TO_EVEN>(value); }

		/// Round half-precision number to nearest integer value using round-to-nearest-away-from-zero.
		/// \param value binary representation of half-precision value
		/// \return half-precision bits for nearest integral value
		inline uint16 round_half_up(uint16 value) { return round_half_impl<std::round_to_nearest,0>(value); }
		/// \}

		struct functions;
		template<typename,typename,std::float_round_style> struct half_caster;
	}

	/// Half-precision floating point type.
	/// This class implements an IEEE-conformant half-precision floating point type with the usual arithmetic operators and 
	/// conversions. It is implicitly convertible to single-precision floating point, which makes artihmetic expressions and 
	/// functions with mixed-type operands to be of the most precise operand type. Additionally all arithmetic operations 
	/// (and many mathematical functions) are carried out in single-precision internally. All conversions from single- to 
	/// half-precision are done using truncation (round towards zero), but temporary results inside chained arithmetic 
	/// expressions are kept in single-precision as long as possible (while of course still maintaining a strong half-precision type).
	///
	/// According to the C++98/03 definition, the half type is not a POD type. But according to C++11's less strict and 
	/// extended definitions it is both a standard layout type and a trivially copyable type (even if not a POD type), which 
	/// means it can be standard-conformantly copied using raw binary copies. But in this context some more words about the 
	/// actual size of the type. Although the half is representing an IEEE 16-bit type, it does not neccessarily have to be of 
	/// exactly 16-bits size. But on any reasonable implementation the actual binary representation of this type will most 
	/// probably not ivolve any additional "magic" or padding beyond the simple binary representation of the underlying 16-bit 
	/// IEEE number, even if not strictly guaranteed by the standard. But even then it only has an actual size of 16 bits if 
	/// your C++ implementation supports an unsigned integer type of exactly 16 bits width. But this should be the case on 
	/// nearly any reasonable platform.
	///
	/// So if your C++ implementation is not totally exotic or imposes special alignment requirements, it is a reasonable 
	/// assumption that the data of a half is just comprised of the 2 bytes of the underlying IEEE representation.
	class half
	{
		friend struct detail::functions;
		template<typename,typename,std::float_round_style> friend struct detail::half_caster;
		friend class std::numeric_limits<half>;
	#if HALF_ENABLE_CPP11_HASH
		friend struct std::hash<half>;
	#endif

	public:
		/// Default constructor.
		/// This initializes the half to 0. Although this does not match the builtin types' default-initialization semantics 
		/// and may be less efficient than no initialization, it is needed to provide proper value-initialization semantics.
		HALF_CONSTEXPR half() /*HALF_NOEXCEPT*/ : data_() {}

		/// Conversion constructor.
		/// \param rhs float to convert
		explicit half(float rhs) : data_(detail::float2half<round_style>(rhs)) {}
	
		/// Conversion to single-precision.
		/// \return single precision value representing expression value
		operator float() const { return detail::half2float(data_); }

		/// Arithmetic assignment.
		/// \tparam T type of concrete half expression
		/// \param rhs half expression to add
		/// \return reference to this half
		half& operator+=(half rhs) { return *this += static_cast<float>(rhs); }

		/// Arithmetic assignment.
		/// \tparam T type of concrete half expression
		/// \param rhs half expression to subtract
		/// \return reference to this half
		half& operator-=(half rhs) { return *this -= static_cast<float>(rhs); }

		/// Arithmetic assignment.
		/// \tparam T type of concrete half expression
		/// \param rhs half expression to multiply with
		/// \return reference to this half
		half& operator*=(half rhs) { return *this *= static_cast<float>(rhs); }

		/// Arithmetic assignment.
		/// \tparam T type of concrete half expression
		/// \param rhs half expression to divide by
		/// \return reference to this half
		half& operator/=(half rhs) { return *this /= static_cast<float>(rhs); }

		/// Assignment operator.
		/// \param rhs single-precision value to copy from
		/// \return reference to this half
		half& operator=(float rhs) { data_ = detail::float2half<round_style>(rhs); return *this; }

		/// Arithmetic assignment.
		/// \param rhs single-precision value to add
		/// \return reference to this half
		half& operator+=(float rhs) { data_ = detail::float2half<round_style>(detail::half2float(data_)+rhs); return *this; }

		/// Arithmetic assignment.
		/// \param rhs single-precision value to subtract
		/// \return reference to this half
		half& operator-=(float rhs) { data_ = detail::float2half<round_style>(detail::half2float(data_)-rhs); return *this; }

		/// Arithmetic assignment.
		/// \param rhs single-precision value to multiply with
		/// \return reference to this half
		half& operator*=(float rhs) { data_ = detail::float2half<round_style>(detail::half2float(data_)*rhs); return *this; }

		/// Arithmetic assignment.
		/// \param rhs single-precision value to divide by
		/// \return reference to this half
		half& operator/=(float rhs) { data_ = detail::float2half<round_style>(detail::half2float(data_)/rhs); return *this; }

		/// Prefix increment.
		/// \return incremented half value
		half& operator++() { return *this += 1.0f; }

		/// Prefix decrement.
		/// \return decremented half value
		half& operator--() { return *this -= 1.0f; }

		/// Postfix increment.
		/// \return non-incremented half value
		half operator++(int) { half out(*this); ++*this; return out; }

		/// Postfix decrement.
		/// \return non-decremented half value
		half operator--(int) { half out(*this); --*this; return out; }
	
	private:
		/// Rounding mode to use
		static const std::float_round_style round_style = (std::float_round_style)(HALF_ROUND_STYLE);

		/// Constructor.
		/// \param bits binary representation to set half to
		HALF_CONSTEXPR half(detail::binary_t, detail::uint16 bits) /*HALF_NOEXCEPT*/ : data_(bits) {}

		/// Internal binary representation
		detail::uint16 data_;
	};

#if HALF_ENABLE_CPP11_USER_LITERALS
	/// Library-defined half-precision literals.
	/// Import this namespace to enable half-precision floating point literals:
	/// ~~~~{.cpp}
	/// using namespace half_float::literal;
	/// half_float::half = 4.2_h;
	/// ~~~~
	namespace literal
	{
		/// Half literal.
		/// While this returns an actual half-precision value, half literals can unfortunately not be constant expressions due 
		/// to rather involved single-to-half conversion.
		/// \param value literal value
		/// \return half with given value (if representable)
		inline half operator "" _h(long double value) { return half(static_cast<float>(value)); }
	}
#endif

	namespace detail
	{
		/// Wrapper implementing unspecialized half-precision functions.
		struct functions
		{
			static half plus(half x, half y)
			{
				int absx = x.data_ & 0x7FFF, absy = y.data_ & 0x7FFF;
				if(absx > 0x7C00)
					return x;
				if(absy > 0x7C00)
					return y;
				bool sub = (x.data_^y.data_) >> 15;
				if(absx == 0x7C00)
					return (sub && absy==0x7C00) ? half(binary, 0x7FFF) : x;
				if(absy == 0x7C00)
					return y;
				if(!absx)
					return y;
				if(!absy)
					return x;
				uint16 value = ((sub && absy>absx) ? y.data_ : x.data_) & 0x8000;
				if(absy > absx)
					std::swap(absx, absy);
				int exp = (absx>>10) + (absx<=0x3FF), d = exp - (absy>>10) - (absy<=0x3FF);
				int mx = ((absx&0x3FF)|((absx>0x3FF)<<10)) << 3, my;
				if(d < 13)
				{
					my = ((absy&0x3FF)|((absy>0x3FF)<<10)) << 2;
					int s = 0;
					for(; d; --d,my>>=1)
						s |= my & 1;
					my = (my<<1) | s;
				}
				else
					my = 1;
				int m, s = 0;
				if(sub)
				{
					m = mx - my;
					for(; m<0x2000 && exp>1; m<<=1,--exp) ;
				}
				else
				{
					m = mx + my;
					if(m > 0x3FFF)
					{
						s = m & 1;
						m >>= 1;
						if(++exp > 30)
						{
							if(half::round_style == std::round_toward_infinity)
								return half(binary, value|0x7C00-(value>>15));
							else if(half::round_style == std::round_toward_neg_infinity)
								return half(binary, value|0x7BFF+(value>>15));
							return half(binary, value|0x7BFF+(half::round_style!=std::round_toward_zero));
						}
					}
				}
				s |= (m|(m>>1)) & 1;
				int g = (m>>2) & 1;
				value |= ((exp-1)<<10) + (m>>3);
				if(half::round_style == std::round_to_nearest)
					#if HALF_ROUND_TIES_TO_EVEN
						value += g & (s|value);
					#else
						value += g;
					#endif
				else if(half::round_style == std::round_toward_infinity)
					value += ~(value>>15) & (g|s);
				else if(half::round_style == std::round_toward_neg_infinity)
					value += (value>>15) & (g|s);
				return half(binary, value);
			}

			static half minus(half x, half y) { return plus(x, half(binary, y.data_^0x8000)); }

			static half multiplies(half x, half y)
			{
				int absx = x.data_ & 0x7FFF, absy = y.data_ & 0x7FFF;
				if(absx > 0x7C00)
					return x;
				if(absy > 0x7C00)
					return y;
				uint16 value = (x.data_^y.data_) & 0x8000;
				if(absx == 0x7C00)
					return half(binary, !absy ? 0x7FFF : (value|0x7C00));
				if(absy == 0x7C00)
					return half(binary, !absx ? 0x7FFF : (value|0x7C00));
				if(!absx || !absy)
					return half(binary, value);
				int exp = -15;
				for(; absx<0x400; absx<<=1,--exp) ;
				for(; absy<0x400; absy<<=1,--exp) ;
				long m = ((absx&0x3FF)|0x400L) * ((absy&0x3FF)|0x400L);
				int i = m >> 21;
				exp += (absx>>10) + (absy>>10) + i;
				if(exp > 30)
				{
					if(half::round_style == std::round_toward_infinity)
						value |= 0x7C00 - (value>>15);
					else if(half::round_style == std::round_toward_neg_infinity)
						value |= 0x7BFF + (value>>15);
					else
						value |= 0x7BFF + (half::round_style!=std::round_toward_zero);
				}
				else if(exp > -11)
				{
					int s = m & i;
					m >>= i;
					s |= (m&0x1FF) != 0;
					int g = (m>>9) & 1;
					if(exp > 0)
						value |= (exp<<10) | ((m>>10)&0x3FF);
					else if(half::round_style != std::round_indeterminate && half::round_style != std::round_toward_zero)
					{
						m >>= 10;
						s |= g;
						for(; exp; ++exp,m>>=1)
							s |= m & 1;
						g = m & 1;
						value |= m >> 1;
					}
					else
						value |= m >> (11-exp);
					if(half::round_style == std::round_to_nearest)
						#if HALF_ROUND_TIES_TO_EVEN
							value += g & (s|value);
						#else
							value += g;
						#endif
					else if(half::round_style == std::round_toward_infinity)
						value += ~(value>>15) & (g|s);
					else if(half::round_style == std::round_toward_neg_infinity)
						value += (value>>15) & (g|s);
				}
				else if(half::round_style == std::round_toward_infinity)
					value -= (value>>15) - 1;
				else if(half::round_style == std::round_toward_neg_infinity)
					value += value >> 15;
				return half(binary, value);
			}

			static half divides(half x, half y)
			{
				int absx = x.data_ & 0x7FFF, absy = y.data_ & 0x7FFF;
				if(absx > 0x7C00)
					return x;
				if(absy > 0x7C00)
					return y;
				uint16 value = (x.data_^y.data_) & 0x8000;
				if(absx == 0x7C00 || !absy)
					return half(binary, (absx==absy) ? 0x7FFF : (value|0x7C00));
				if(absy == 0x7C00 || !absx)
					return half(binary, (absx==absy) ? 0x7FFF : value);
				int exp = 15;
				for(; absx<0x400; absx<<=1,--exp) ;
				for(; absy<0x400; absy<<=1,++exp) ;
				long mx = ((absx&0x3FF)|0x400L) << 1, my = ((absy&0x3FF)|0x400L) << 1;
				int i = mx < my;
				mx <<= i;
				exp += (absx>>10) - (absy>>10) - i;
				if(exp > 30)
				{
					if(half::round_style == std::round_toward_infinity)
						value |= 0x7C00 - (value>>15);
					else if(half::round_style == std::round_toward_neg_infinity)
						value |= 0x7BFF + (value>>15);
					else
						value |= 0x7BFF + (half::round_style!=std::round_toward_zero);
				}
				else if(exp > -11)
				{
					std::ldiv_t div = std::div(mx<<11, my);
					int m = div.quot, g = m & 1, s = div.rem != 0;
					m >>= 1;
					if(exp > 0)
						value |= (exp<<10) | (m&0x3FF);
					else if(half::round_style != std::round_indeterminate && half::round_style != std::round_toward_zero)
					{
						s |= g;
						for(; exp; ++exp,m>>=1)
							s |= m & 1;
						g = m & 1;
						value |= m >> 1;
					}
					else
						value |= m >> (1-exp);
					if(half::round_style == std::round_to_nearest)
						#if HALF_ROUND_TIES_TO_EVEN
							value += g & (s|value);
						#else
							value += g;
						#endif
					else if(half::round_style == std::round_toward_infinity)
						value += ~(value>>15) & (g|s);
					else if(half::round_style == std::round_toward_neg_infinity)
						value += (value>>15) & (g|s);
				}
				else if(half::round_style == std::round_toward_infinity)
					value -= (value>>15) - 1;
				else if(half::round_style == std::round_toward_neg_infinity)
					value += value >> 15;
				return half(binary, value);
			}

			/// Negation implementation.
			/// \param arg value to negate
			/// \return negated value
			static HALF_CONSTEXPR half negate(half arg) { return half(binary, arg.data_^0x8000); }

			/// Output implementation.
			/// \param out stream to write to
			/// \param arg value to write
			/// \return reference to stream
			template<typename charT,typename traits> static std::basic_ostream<charT,traits>& write(std::basic_ostream<charT,traits> &out, float arg) { return out << arg; }

			/// Input implementation.
			/// \param in stream to read from
			/// \param arg half to read into
			/// \return reference to stream
			template<typename charT,typename traits> static std::basic_istream<charT,traits>& read(std::basic_istream<charT,traits> &in, half &arg)
			{
				float f;
				if(in >> f)
					arg = f;
				return in;
			}

			/// Absolute value implementation.
			/// \param arg function argument
			/// \return absolute value
			static half fabs(half arg) { return half(binary, arg.data_&0x7FFF); }

			/// Modulo implementation.
			/// \param x first operand
			/// \param y second operand
			/// \return Half-precision division remainder
			static half fmod(half x, half y)
			{
				int absx = x.data_ & 0x7FFF, absy = y.data_ & 0x7FFF;
				if(absx >= 0x7C00 || absy >= 0x7C00 || !absy)
					return half(binary, 0x7FFF);
				if(absx < absy)
					return x;
				uint16 sign = x.data_ & 0x8000;
				if(absx == absy)
					return half(binary, sign);
				int expx = 0, expy = 0;
				for(; absx<0x400; absx<<=1,--expx) ;
				for(; absy<0x400; absy<<=1,--expy) ;
				expx += absx >> 10;
				expy += absy >> 10;
				int mx = (absx&0x3FF) | 0x400L, my = (absy&0x3FF) | 0x400L;
				for(int d=expx-expy; d; --d)
				{
					if(mx == my)
						return half(binary, sign);
					if(mx > my)
						mx -= my;
					mx <<= 1;
				}
				if(mx == my)
					return half(binary, sign);
				if(mx > my)
					mx -= my;
				for(; mx<0x400; mx<<=1,--expy) ;
				return half(binary, sign | ((expy>0) ? ((expy<<10)|(mx&0x3FF)) : (mx>>(1-expy))));
			}

			/// Remainder implementation.
			/// \param x first operand
			/// \param y second operand
			/// \return Half-precision division remainder
			static half remainder(half x, half y)
			{
/*			#if HALF_ENABLE_CPP11_CMATH
				return half(std::remainder(x, y));
			#else
				uint16 sign = x.data_ & 0x8000;
				x.data_ &= 0x7FFF;
				y.data_ &= 0x7FFF;
				if(x.data_ >= 0x7C00 || y.data_ > 0x7C00 || !y.data_)
					return half(binary, 0x7FFF);
				if(y.data_ == 0x7C00)
					return half(binary, sign|x.data_);
				if(!x.data_ || x.data_ == y.data_)
					return half(binary, sign);
				float ax = static_cast<float>(x), ay = static_cast<float>(y);
				ax = std::fmod(ax, ay+ay);
				float y2 = 0.5f * ay;
				if(ax > y2)
				{
					ax -= ay;
					if(ax >= y2)
						ax -= ay;
				}
				return half(binary, half(ax).data_^sign);
			#endif
*/				int absx = x.data_ & 0x7FFF, absy = y.data_ &= 0x7FFF, q = 0;
				if(absx >= 0x7C00 || absy > 0x7C00 || !absy)
					return half(binary, 0x7FFF);
				if(absy == 0x7C00)
					return x;
				uint16 sign = x.data_ & 0x8000;
				if(absx == absy)
					return half(binary, sign);
				if(absx > absy)
				{
					int expx = 0, expy = 0;
					for(; absx<0x400; absx<<=1, --expx);
					for(; absy<0x400; absy<<=1, --expy);
					expx += absx >> 10;
					expy += absy >> 10;
					int mx = (absx&0x3FF) | 0x400L, my = (absy&0x3FF) | 0x400L;
					for(int d=expx-expy; d; --d)
					{
						if(mx == my)
							return half(binary, sign);
						if(mx > my)
						{
							mx -= my;
							++q;
						}
						mx <<= 1;
						q <<= 1;
					}
					if(mx == my)
						return half(binary, sign);
					if(mx > my)
					{
						mx -= my;
						++q;
					}
					for(; mx<0x400; mx<<=1, --expy);
					x.data_ = (expy>0) ? ((expy<<10)|(mx&0x3FF)) : (mx>>(1-expy));
				}
				else
					x.data_ = absx;
				if(y.data_ < 0x800)
				{
					uint16 x2 = (x.data_<0x400) ? (x.data_<<1) : (x.data_+0x400);
					if(x2 > y.data_ || (x2 == y.data_ && (q&1)))
						x = mod_sub(x, y);
				}
				else
				{
					uint16 y_half = y.data_ - 0x400;
					if(x.data_ > y_half || (x.data_ == y_half && (q&1)))
						x = mod_sub(x, y);
				}
				return half(binary, x.data_^sign);
			}

			/// Remainder implementation.
			/// \param x first operand
			/// \param y second operand
			/// \param quo address to store quotient bits at
			/// \return Half-precision division remainder
			static half remquo(half x, half y, int *quo)
			{
/*			#if HALF_ENABLE_CPP11_CMATH
				return half(std::remquo(x, y, quo));
			#else
				uint16 sign = x.data_ & 0x8000;
				bool qsign = (sign^y.data_) >> 15;
				x.data_ &= 0x7FFF;
				y.data_ &= 0x7FFF;
				if(x.data_ >= 0x7C00 || y.data_ > 0x7C00 || !y.data_)
					return half(binary, 0x7FFF);
				if(y.data_ == 0x7C00)
					return *quo = 0, half(binary, sign|x.data_);
				if(x.data_ == y.data_)
					return *quo = qsign ? -1 : 1, half(binary, sign);
				float ax = static_cast<float>(x), ay = static_cast<float>(y);
				ax = std::fmod(ax, 8.0f*ay);
				int cquo = 0;
				if(ax >= 4.0f * ay)
				{
					ax -= 4.0f * ay;
					cquo += 4;
				}
				if(ax >= 2.0f * ay)
				{
					ax -= 2.0f * ay;
					cquo += 2;
				}
				float y2 = 0.5f * ay;
				if(ax > y2)
				{
					ax -= ay;
					++cquo;
					if(ax >= y2)
					{
						ax -= ay;
						++cquo;
					}
				}
				return *quo = qsign ? -cquo : cquo, half(sign ? -ax : ax);
			#endif
*/				uint16 sign = x.data_ & 0x8000;
				bool qsign = (sign^y.data_) >> 15;
				int absx = x.data_ & 0x7FFF, absy = y.data_ &= 0x7FFF, q = 0;
				if(absx >= 0x7C00 || absy > 0x7C00 || !absy)
					return half(binary, 0x7FFF);
				if(absy == 0x7C00)
					return *quo = 0, x;
				if(absx == absy)
					return *quo = qsign ? -1 : 1, half(binary, sign);
				if(absx > absy)
				{
					int expx = 0, expy = 0;
					for(; absx<0x400; absx<<=1, --expx);
					for(; absy<0x400; absy<<=1, --expy);
					expx += absx >> 10;
					expy += absy >> 10;
					int mx = (absx&0x3FF) | 0x400L, my = (absy&0x3FF) | 0x400L;
					for(int d=expx-expy; d; --d)
					{
						if(mx >= my)
						{
							mx -= my;
							++q;
						}
						mx <<= 1;
						q <<= 1;
					}
					if(mx >= my)
					{
						mx -= my;
						++q;
					}
					if(!mx)
						return *quo = qsign ? -q : q, half(binary, sign);
					for(; mx<0x400; mx<<=1, --expy);
					x.data_ = (expy>0) ? ((expy<<10)|(mx&0x3FF)) : (mx>>(1-expy));
				}
				else
					x.data_ = absx;
				if(y.data_ < 0x800)
				{
					uint16 x2 = (x.data_<0x400) ? (x.data_<<1) : (x.data_+0x400);
					if(x2 > y.data_ || (x2 == y.data_ && (q&1)))
					{
						x = mod_sub(x, y);
						++q;
					}
				}
				else
				{
					uint16 y_half = y.data_ - 0x400;
					if(x.data_ > y_half || (x.data_ == y_half && (q&1)))
					{
						x = mod_sub(x, y);
						++q;
					}
				}
				return *quo = qsign ? -q : q, half(binary, x.data_^sign);
			}

			static half fmin(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				if(xabs > 0x7C00)
					return y;
				if(yabs > 0x7C00)
					return x;
				return (((xabs==x.data_) ? xabs : -xabs) > ((yabs==y.data_) ? yabs : -yabs)) ? y : x;
			}

			static half fmax(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				if(xabs > 0x7C00)
					return y;
				if(yabs > 0x7C00)
					return x;
				return (((xabs==x.data_) ? xabs : -xabs) < ((yabs==y.data_) ? yabs : -yabs)) ? y : x;
			}

			/// Positive difference implementation.
			/// \param x first operand
			/// \param y second operand
			/// \return Positive difference
			static half fdim(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				if(xabs > 0x7C00)
					return x;
				if(yabs > 0x7C00)
					return y;
				return (((xabs==x.data_) ? xabs : -xabs)<=((yabs==y.data_) ? yabs : -yabs)) ? half(binary, 0) : minus(x, y);
			}

			/// Fused multiply-add implementation.
			/// \param x first operand
			/// \param y second operand
			/// \param z third operand
			/// \return \a x * \a y + \a z
			static half fma(half x, half y, half z)
			{
				int absx = x.data_ & 0x7FFF, absy = y.data_ & 0x7FFF, absz = z.data_ & 0x7FFF;
				if(absx > 0x7C00)
					return x;
				if(absy > 0x7C00)
					return y;
				if(absz > 0x7C00)
					return z;
				uint16 value = (x.data_^y.data_) & 0x8000;
				bool sub = (value^z.data_) >> 15;
				if(absx == 0x7C00)
					return half(binary, (!absy || (sub && absz==0x7C00)) ? 0x7FFF : (value|0x7C00));
				if(absy == 0x7C00)
					return half(binary, (!absx || (sub && absz==0x7C00)) ? 0x7FFF : (value|0x7C00));
				if(absz == 0x7C00 || !absx || !absy)
					return z;
				int exp = -15;
				for(; absx<0x400; absx<<=1,--exp) ;
				for(; absy<0x400; absy<<=1,--exp) ;
				long m = ((absx&0x3FF)|0x400L) * ((absy&0x3FF)|0x400L);
				int i = m >> 21, s = 0;
				exp += (absx>>10) + (absy>>10) + i;
				m <<= 2 - i;
				if(absz)
				{
					int expz = 0;
					for(; absz<0x400; absz<<=1,--expz) ;
					expz += absz >> 10;
					long mz = ((absz&0x3FF)|0x400L) << 12;
					if(expz > exp || (expz == exp && mz > m))
					{
						std::swap(m, mz);
						std::swap(exp, expz);
						if(sub)
							value = z.data_ & 0x8000;
					}
					m <<= 1;
					int d = exp - expz;
					if(d < 23)
					{
						int s = 0;
						for(; d; --d,mz>>=1)
							s |= mz & 1;
						mz = (mz<<1) | s;
					}
					else
						mz = 1;
					if(sub)
					{
						m = std::abs(m-mz);
						if(!m)
							return half(binary, value);
						for(; m<0x800000; m<<=1,--exp) ;
					}
					else
					{
						m += mz;
						if(m > 0xFFFFFF)
						{
							s = m & 1;
							m >>= 1;
							++exp;
						}
					}
				}
				else
					m <<= 1;
				if(exp > 30)
				{
					if(half::round_style == std::round_toward_infinity)
						value |= 0x7C00 - (value>>15);
					else if(half::round_style == std::round_toward_neg_infinity)
						value |= 0x7BFF + (value>>15);
					else
						value |= 0x7BFF + (half::round_style!=std::round_toward_zero);
				}
				else if(exp > -11)
				{
					int g = (m>>12) & 1;
					s |= (m&0xFFF) != 0;
					if(exp > 0)
						value |= (exp<<10) | ((m>>13)&0x3FF);
					else if(half::round_style != std::round_indeterminate && half::round_style != std::round_toward_zero)
					{
						m >>= 13;
						s |= g;
						for(; exp; ++exp,m>>=1)
							s |= m & 1;
						g = m & 1;
						value |= m >> 1;
					}
					else
						value |= m >> (14-exp);
					if(half::round_style == std::round_to_nearest)
						#if HALF_ROUND_TIES_TO_EVEN
							value += g & (s|value);
						#else
							value += g;
						#endif
					else if(half::round_style == std::round_toward_infinity)
						value += ~(value>>15) & (g|s);
					else if(half::round_style == std::round_toward_neg_infinity)
						value += (value>>15) & (g|s);
				}
				else if(half::round_style == std::round_toward_infinity)
					value -= (value>>15) - 1;
				else if(half::round_style == std::round_toward_neg_infinity)
					value += value >> 15;
				return half(binary, value);
			}

			/// Get NaN.
			/// \return Half-precision quiet NaN
			static half nanh(const char*) { return half(binary, 0x7FFF); }

			/// Exponential implementation.
			/// \param arg function argument
			/// \return function value
			static half exp(float arg) { return half(std::exp(arg)); }

			/// Exponential implementation.
			/// \param arg function argument
			/// \return function value
			static half expm1(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::expm1(arg));
			#else
				return half(static_cast<float>(std::exp(static_cast<double>(arg))-1.0));
			#endif
			}

			/// Binary exponential implementation.
			/// \param arg function argument
			/// \return function value
			static half exp2(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::exp2(arg));
			#else
				return half(static_cast<float>(std::exp(arg*0.69314718055994530941723212145818)));
			#endif
			}

			/// Logarithm implementation.
			/// \param arg function argument
			/// \return function value
			static half log(float arg) { return half(std::log(arg)); }

			/// Common logarithm implementation.
			/// \param arg function argument
			/// \return function value
			static half log10(float arg) { return half(std::log10(arg)); }

			/// Logarithm implementation.
			/// \param arg function argument
			/// \return function value
			static half log1p(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::log1p(arg));
			#else
				return half(static_cast<float>(std::log(1.0+arg)));
			#endif
			}

			/// Binary logarithm implementation.
			/// \param arg function argument
			/// \return function value
			static half log2(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::log2(arg));
			#else
				return half(static_cast<float>(std::log(static_cast<double>(arg))*1.4426950408889634073599246810019));
			#endif
			}

			/// Square root implementation.
			/// \param arg function argument
			/// \return square root of argument
			static half sqrt(half arg)
			{
				if(arg.data_ & 0x8000 && arg.data_ != 0x8000)
					arg.data_ |= 0x7FFF;
				int abs = arg.data_ & 0x7FFF;
				if(!abs || abs >= 0x7C00)
					return arg;
				int exp = 15;
				for(; abs<0x400; abs<<=1,--exp) ;
				exp += abs >> 10;
				long m = 0, r = ((abs&0x3FF)|0x400L) << ((exp&1)+10);
				exp /= 2;
				for(long bit=0x100000L; bit; bit>>=2)
				{
					if(r < m+bit)
						m >>= 1;
					else
					{
						r -= m + bit;
						m = (m>>1) + bit;
					}
				}
				uint16 value = (exp<<10) | (m&0x3FF);
				if(half::round_style == std::round_to_nearest)
					value += r > m;
				else if(half::round_style == std::round_toward_infinity)
					value += r != 0;
				return half(binary, value);
			}

			/// Cubic root implementation.
			/// \param arg function argument
			/// \return function value
			static half cbrt(half arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::cbrt(arg));
			#else
				if(builtin_isnan(arg) || builtin_isinf(arg))
					return half(arg);
				return half(builtin_signbit(arg) ? -static_cast<float>(std::pow(-static_cast<double>(arg), 1.0/3.0)) : 
					static_cast<float>(std::pow(static_cast<double>(arg), 1.0/3.0)));
			#endif
				int abs = arg.data_ & 0x7FFF;
				if(!abs || abs >= 0x7C00)
					return arg;
				int exp = 15;
				for(; abs<0x400; abs<<=1, --exp);
				exp += abs >> 10;
				long m = 0, r = ((abs&0x3FF)|0x400L) << ((exp&1)+12);
				exp /= 2;
				for(long bit=0x400000L; bit; bit>>=2)
				{
					if(r < m+bit)
						m >>= 1;
					else
					{
						r -= m + bit;
						m = (m>>1) + bit;
					}
				}
				int g = m & 1, s = r != 0;
				uint16 value = (arg.data_&0x8000) | (exp<<10) | ((m>>1)&0x3FF);
				if(half::round_style == std::round_to_nearest)
					#if HALF_ROUND_TIES_TO_EVEN
						value += g & (s|value);
					#else
						value += g;
					#endif
				else if(half::round_style == std::round_toward_infinity)
					value += ~(value>>15) & (g|s);
				else if(half::round_style == std::round_toward_neg_infinity)
					value += (value>>15) & (g|s);
				return half(binary, value);
			}

			/// Hypotenuse implementation.
			/// \param x first argument
			/// \param y second argument
			/// \return function value
			static half hypot(half x, half y)
			{
				int absx = x.data_ & 0x7FFF, absy = y.data_ & 0x7FFF;
				if(absx == 0x7C00 || absy == 0x7C00)
					return half(binary, 0x7C00);
				if(absx > 0x7C00)
					return x;
				if(absy > 0x7C00)
					return y;
				if(!absx)
					return half(binary, absy);
				if(!absy)
					return half(binary, absx);
				int expx = 0, expy = 0;
				for(; absx<0x400; absx<<=1,--expx) ;
				for(; absy<0x400; absy<<=1,--expy) ;
				unsigned long mx = (absx&0x3FF) | 0x400L, my = (absy&0x3FF) | 0x400L;
				mx *= mx;
				my *= my;
				int ix = mx >> 21, iy = my >> 21;
				expx = 2*(expx+(absx>>10)) - 15 + ix;
				expy = 2*(expy+(absy>>10)) - 15 + iy;
				mx <<= 1 - ix;									//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				my <<= 1 - iy;									//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				if(expy > expx)
				{
					std::swap(mx, my);
					std::swap(expx, expy);
				}
				int exp = expx, d = expx - expy;
				mx <<= 1;
				if(d < 22)										//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				{
					int s = 0;
					for(; d; --d,my>>=1)
						s |= my & 1;
					my = (my<<1) | s;
				}
				else
					my = 1;
				unsigned long r = mx + my, m = 0;
				if(r > 0x7FFFFF)								//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				{
					r = (r|((r&1)<<1)) >> 1;
					++exp;
				}
				int i = (exp+=15) & 1U;
				r <<= i;
				exp = (exp-i) / 2;
				for(long bit=0x400000L; bit; bit>>=2)			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				{
					if(r < m+bit)
						m >>= 1;
					else
					{
						r -= m + bit;
						m = (m>>1) + bit;
					}
				}
				if(exp > 30)
					return half(binary, 0x7BFF+(half::round_style!=std::round_toward_zero && half::round_style!=std::round_toward_neg_infinity));
				if(exp < -10)
					return half(binary, half::round_style==std::round_toward_infinity);
				int s = r != 0;
				s |= (m&0x0) != 0;								//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				m >>= 0;										//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				int g = m & 1;
				uint16 value;
				if(exp > 0)
					value = (exp<<10) | ((m>>1)&0x3FF);
				else if(half::round_style == std::round_to_nearest || half::round_style == std::round_toward_infinity)
				{
					m >>= 1;
					s |= g;
					for(; exp; ++exp,m>>=1)
						s |= m & 1;
					g = m & 1;
					value = m >> 1;
				}
				else
					value = m >> (2-exp);
				if(half::round_style == std::round_to_nearest)
					#if HALF_ROUND_TIES_TO_EVEN
						value += g & (s|value);
					#else
						value += g;
					#endif
				else if(half::round_style == std::round_toward_infinity)
					value += g | s;
				return half(binary, value);
			}

			/// Power implementation.
			/// \param base value to exponentiate
			/// \param exp power to expontiate to
			/// \return function value
			static half pow(float base, float exp) { return half(std::pow(base, exp)); }

			/// Sine implementation.
			/// \param arg function argument
			/// \return function value
			static half sin(float arg) { return half(std::sin(arg)); }

			/// Cosine implementation.
			/// \param arg function argument
			/// \return function value
			static half cos(float arg) { return half(std::cos(arg)); }

			/// Tan implementation.
			/// \param arg function argument
			/// \return function value
			static half tan(float arg) { return half(std::tan(arg)); }

			/// Arc sine implementation.
			/// \param arg function argument
			/// \return function value
			static half asin(float arg) { return half(std::asin(arg)); }

			/// Arc cosine implementation.
			/// \param arg function argument
			/// \return function value
			static half acos(float arg) { return half(std::acos(arg)); }

			/// Arc tangent implementation.
			/// \param arg function argument
			/// \return function value
			static half atan(float arg) { return half(std::atan(arg)); }

			/// Arc tangent implementation.
			/// \param x first argument
			/// \param y second argument
			/// \return function value
			static half atan2(float x, float y) { return half(std::atan2(x, y)); }

			/// Hyperbolic sine implementation.
			/// \param arg function argument
			/// \return function value
			static half sinh(float arg) { return half(std::sinh(arg)); }

			/// Hyperbolic cosine implementation.
			/// \param arg function argument
			/// \return function value
			static half cosh(float arg) { return half(std::cosh(arg)); }

			/// Hyperbolic tangent implementation.
			/// \param arg function argument
			/// \return function value
			static half tanh(float arg) { return half(std::tanh(arg)); }

			/// Hyperbolic area sine implementation.
			/// \param arg function argument
			/// \return function value
			static half asinh(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::asinh(arg));
			#else
				return half((arg==-std::numeric_limits<float>::infinity()) ? arg : static_cast<float>(std::log(arg+std::sqrt(arg*arg+1.0))));
			#endif
			}

			/// Hyperbolic area cosine implementation.
			/// \param arg function argument
			/// \return function value
			static half acosh(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::acosh(arg));
			#else
				return half((arg<-1.0f) ? std::numeric_limits<float>::quiet_NaN() : static_cast<float>(std::log(arg+std::sqrt(arg*arg-1.0))));
			#endif
			}

			/// Hyperbolic area tangent implementation.
			/// \param arg function argument
			/// \return function value
			static half atanh(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::atanh(arg));
			#else
				return half(static_cast<float>(0.5*std::log((1.0+arg)/(1.0-arg))));
			#endif
			}

			/// Error function implementation.
			/// \param arg function argument
			/// \return function value
			static half erf(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::erf(arg));
			#else
				return half(static_cast<float>(erf(static_cast<double>(arg))));
			#endif
			}

			/// Complementary implementation.
			/// \param arg function argument
			/// \return function value
			static half erfc(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::erfc(arg));
			#else
				return half(static_cast<float>(1.0-erf(static_cast<double>(arg))));
			#endif
			}

			/// Gamma logarithm implementation.
			/// \param arg function argument
			/// \return function value
			static half lgamma(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::lgamma(arg));
			#else
				if(builtin_isinf(arg))
					return half(std::numeric_limits<float>::infinity());
				if(arg < 0.0f)
				{
					float i, f = std::modf(-arg, &i);
					if(f == 0.0f)
						return half(std::numeric_limits<float>::infinity());
					return half(static_cast<float>(1.1447298858494001741434273513531-
						std::log(std::abs(std::sin(3.1415926535897932384626433832795*f)))-lgamma(1.0-arg)));
				}
				return half(static_cast<float>(lgamma(static_cast<double>(arg))));
			#endif
			}

			/// Gamma implementation.
			/// \param arg function argument
			/// \return function value
			static half tgamma(float arg)
			{
			#if HALF_ENABLE_CPP11_CMATH
				return half(std::tgamma(arg));
			#else
				if(arg == 0.0f)
					return builtin_signbit(arg) ? half(-std::numeric_limits<float>::infinity()) : half(std::numeric_limits<float>::infinity());
				if(arg < 0.0f)
				{
					float i, f = std::modf(-arg, &i);
					if(f == 0.0f)
						return half(std::numeric_limits<float>::quiet_NaN());
					double value = 3.1415926535897932384626433832795 / (std::sin(3.1415926535897932384626433832795*f)*std::exp(lgamma(1.0-arg)));
					return half(static_cast<float>((std::fmod(i, 2.0f)==0.0f) ? -value : value));
				}
				if(builtin_isinf(arg))
					return half(arg);
				return half(static_cast<float>(std::exp(lgamma(static_cast<double>(arg)))));
			#endif
			}

			/// Floor implementation.
			/// \param arg value to round
			/// \return rounded value
			static half floor(half arg) { return half(binary, round_half<std::round_toward_neg_infinity>(arg.data_)); }

			/// Ceiling implementation.
			/// \param arg value to round
			/// \return rounded value
			static half ceil(half arg) { return half(binary, round_half<std::round_toward_infinity>(arg.data_)); }

			/// Truncation implementation.
			/// \param arg value to round
			/// \return rounded value
			static half trunc(half arg) { return half(binary, round_half<std::round_toward_zero>(arg.data_)); }

			/// Nearest integer implementation.
			/// \param arg value to round
			/// \return rounded value
			static half round(half arg) { return half(binary, round_half_up(arg.data_)); }

			/// Nearest integer implementation.
			/// \param arg value to round
			/// \return rounded value
			static long lround(half arg) { return detail::half2int_up<long>(arg.data_); }

			/// Nearest integer implementation.
			/// \param arg value to round
			/// \return rounded value
			static half rint(half arg) { return half(binary, round_half<half::round_style>(arg.data_)); }

			/// Nearest integer implementation.
			/// \param arg value to round
			/// \return rounded value
			static long lrint(half arg) { return detail::half2int<half::round_style,long>(arg.data_); }

		#if HALF_ENABLE_CPP11_LONG_LONG
			/// Nearest integer implementation.
			/// \param arg value to round
			/// \return rounded value
			static long long llround(half arg) { return detail::half2int_up<long long>(arg.data_); }

			/// Nearest integer implementation.
			/// \param arg value to round
			/// \return rounded value
			static long long llrint(half arg) { return detail::half2int<half::round_style,long long>(arg.data_); }
		#endif

			/// Decompression implementation.
			/// \param arg number to decompress
			/// \param exp address to store exponent at
			/// \return normalized significant
			static half frexp(half arg, int *exp)
			{
				*exp = 0;
				unsigned int m = arg.data_ & 0x7FFF;
				if(m >= 0x7C00 || !m)
					return arg;
				for(; m<0x400; m<<=1,--*exp) ;
				*exp += (m>>10) - 14;
				return half(binary, (arg.data_&0x8000)|0x3800|(m&0x3FF));
			}

			/// Decompression implementation.
			/// \param arg number to decompress
			/// \param iptr address to store integer part at
			/// \return fractional part
			static half modf(half arg, half *iptr)
			{
				unsigned int e = arg.data_ & 0x7FFF;
				if(e >= 0x6400)
					return *iptr = arg, half(binary, arg.data_&(0x8000U|-(e>0x7C00)));
				if(e < 0x3C00)
					return iptr->data_ = arg.data_ & 0x8000, arg;
				e >>= 10;
				unsigned int mask = (1<<(25-e)) - 1, m = arg.data_ & mask;
				iptr->data_ = arg.data_ & ~mask;
				if(!m)
					return half(binary, arg.data_&0x8000);
				for(; m<0x400; m<<=1,--e) ;
				return half(binary, static_cast<uint16>((arg.data_&0x8000)|(e<<10)|(m&0x3FF)));
			}

			/// Scaling implementation.
			/// \param arg number to scale
			/// \param exp power of two to scale by
			/// \return scaled number
			static half scalbln(half arg, long exp)
			{
				unsigned int m = arg.data_ & 0x7FFF;
				if(m >= 0x7C00 || !m)
					return arg;
				for(; m<0x400; m<<=1,--exp) ;
				exp += m >> 10;
				uint16 value = arg.data_ & 0x8000;
				if(exp > 30)
				{
					if(half::round_style == std::round_toward_zero)
						value |= 0x7BFF;
					else if(half::round_style == std::round_toward_infinity)
						value |= 0x7C00 - (value>>15);
					else if(half::round_style == std::round_toward_neg_infinity)
						value |= 0x7BFF + (value>>15);
					else
						value |= 0x7C00;
				}
				else if(exp > 0)
					value |= (exp<<10) | (m&0x3FF);
				else if(exp > -11)
				{
					m = (m&0x3FF) | 0x400;
					if(half::round_style == std::round_to_nearest)
					{
						m += 1 << -exp;
					#if HALF_ROUND_TIES_TO_EVEN
						m -= (m>>(1-exp)) & 1;
					#endif
					}
					else if(half::round_style == std::round_toward_infinity)
						m += ((value>>15)-1) & ((1<<(1-exp))-1U);
					else if(half::round_style == std::round_toward_neg_infinity)
						m += -(value>>15) & ((1<<(1-exp))-1U);
					value |= m >> (1-exp);
				}
				else if(half::round_style == std::round_toward_infinity)
					value -= (value>>15) - 1;
				else if(half::round_style == std::round_toward_neg_infinity)
					value += value >> 15;
				return half(binary, value);
			}

			/// Exponent implementation.
			/// \param arg number to query
			/// \return floating point exponent
			static int ilogb(half arg)
			{
				int abs = arg.data_ & 0x7FFF;
				if(!abs)
					return FP_ILOGB0;
				if(abs < 0x7C00)
				{
					int exp = (abs>>10) - 15;
					if(abs < 0x400)
						for(; abs<0x200; abs<<=1,--exp) ;
					return exp;
				}
				if(abs > 0x7C00)
					return FP_ILOGBNAN;
				return INT_MAX;
			}

			/// Exponent implementation.
			/// \param arg number to query
			/// \return floating point exponent
			static half logb(half arg)
			{
				int abs = arg.data_ & 0x7FFF;
				if(!abs)
					return half(binary, 0xFC00);
				if(abs < 0x7C00)
				{
					int exp = (abs>>10) - 15;
					if(abs < 0x400)
						for(; abs<0x200; abs<<=1,--exp) ;
					uint16 bits = (exp<0) << 15;
					if(exp)
					{
						unsigned int m = std::abs(exp) << 6, e = 18;
						for(; m<0x400; m<<=1,--e) ;
						bits |= (e<<10) + m;
					}
					return half(binary, bits);
				}
				if(abs > 0x7C00)
					return arg;
				return half(binary, 0x7C00);
			}

			/// Enumeration implementation.
			/// \param from number to increase/decrease
			/// \param to direction to enumerate into
			/// \return next representable number
			static half nextafter(half from, half to)
			{
				uint16 fabs = from.data_ & 0x7FFF, tabs = to.data_ & 0x7FFF;
				if(fabs > 0x7C00)
					return from;
				if(tabs > 0x7C00 || from.data_ == to.data_ || !(fabs|tabs))
					return to;
				if(!fabs)
					return half(binary, (to.data_&0x8000)+1);
				bool lt = ((fabs==from.data_) ? static_cast<int>(fabs) : -static_cast<int>(fabs)) < 
					((tabs==to.data_) ? static_cast<int>(tabs) : -static_cast<int>(tabs));
				return half(binary, from.data_+(((from.data_>>15)^static_cast<unsigned>(lt))<<1)-1);
			}

			/// Enumeration implementation.
			/// \param from number to increase/decrease
			/// \param to direction to enumerate into
			/// \return next representable number
			static half nexttoward(half from, long double to)
			{
				if(isnan(from))
					return from;
				long double lfrom = static_cast<long double>(from);
				if(builtin_isnan(to) || lfrom == to)
					return half(static_cast<float>(to));
				if(!(from.data_&0x7FFF))
					return half(binary, (static_cast<detail::uint16>(builtin_signbit(to))<<15)+1);
				return half(binary, from.data_+(((from.data_>>15)^static_cast<unsigned>(lfrom<to))<<1)-1);
			}

			/// Sign implementation
			/// \param x first operand
			/// \param y second operand
			/// \return composed value
			static half copysign(half x, half y) { return half(binary, x.data_^((x.data_^y.data_)&0x8000)); }

			/// Classification implementation.
			/// \param arg value to classify
			/// \retval true if infinite number
			/// \retval false else
			static int fpclassify(half arg)
			{
				unsigned int abs = arg.data_ & 0x7FFF;
				return abs ? ((abs>0x3FF) ? ((abs>=0x7C00) ? ((abs>0x7C00) ? FP_NAN : FP_INFINITE) : FP_NORMAL) :FP_SUBNORMAL) : FP_ZERO;
			}

			/// Classification implementation.
			/// \param arg value to classify
			/// \retval true if finite number
			/// \retval false else
			static bool isfinite(half arg) { return (arg.data_&0x7C00) != 0x7C00; }

			/// Classification implementation.
			/// \param arg value to classify
			/// \retval true if infinite number
			/// \retval false else
			static bool isinf(half arg) { return (arg.data_&0x7FFF) == 0x7C00; }

			/// Classification implementation.
			/// \param arg value to classify
			/// \retval true if not a number
			/// \retval false else
			static bool isnan(half arg) { return (arg.data_&0x7FFF) > 0x7C00; }

			/// Classification implementation.
			/// \param arg value to classify
			/// \retval true if normal number
			/// \retval false else
			static bool isnormal(half arg) { return ((arg.data_&0x7C00)!=0) & ((arg.data_&0x7C00)!=0x7C00); }

			/// Sign bit implementation.
			/// \param arg value to check
			/// \retval true if signed
			/// \retval false if unsigned
			static bool signbit(half arg) { return (arg.data_&0x8000) != 0; }

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if operands equal
			/// \retval false else
			static bool isequal(half x, half y) { return (x.data_==y.data_ || !((x.data_|y.data_)&0x7FFF)) && !isnan(x); }

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if operands not equal
			/// \retval false else
			static bool isnotequal(half x, half y) { return (x.data_!=y.data_ && ((x.data_|y.data_)&0x7FFF)) || isnan(x); }

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if \a x > \a y
			/// \retval false else
			static bool isgreater(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				return xabs<=0x7C00 && yabs<=0x7C00 && (((xabs==x.data_) ? xabs : -xabs) > ((yabs==y.data_) ? yabs : -yabs));
			}

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if \a x >= \a y
			/// \retval false else
			static bool isgreaterequal(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				return xabs<=0x7C00 && yabs<=0x7C00 && (((xabs==x.data_) ? xabs : -xabs) >= ((yabs==y.data_) ? yabs : -yabs));
			}

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if \a x < \a y
			/// \retval false else
			static bool isless(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				return xabs<=0x7C00 && yabs<=0x7C00 && (((xabs==x.data_) ? xabs : -xabs) < ((yabs==y.data_) ? yabs : -yabs));
			}

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if \a x <= \a y
			/// \retval false else
			static bool islessequal(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				return xabs<=0x7C00 && yabs<=0x7C00 && (((xabs==x.data_) ? xabs : -xabs) <= ((yabs==y.data_) ? yabs : -yabs));
			}

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if either \a x > \a y nor \a x < \a y
			/// \retval false else
			static bool islessgreater(half x, half y)
			{
				int xabs = x.data_ & 0x7FFF, yabs = y.data_ & 0x7FFF;
				if(xabs > 0x7C00 || yabs > 0x7C00)
					return false;
				int a = (xabs==x.data_) ? xabs : -xabs, b = (yabs==y.data_) ? yabs : -yabs;
				return a < b || a > b;
			}

			/// Comparison implementation.
			/// \param x first operand
			/// \param y second operand
			/// \retval true if operand unordered
			/// \retval false else
			static bool isunordered(half x, half y) { return isnan(x) || isnan(y); }

		private:
			static half mod_sub(half x, half y)
			{
				int absx = y.data_, absy = x.data_, exp = (absx>>10) + (absx<=0x3FF), d = exp - (absy>>10) - (absy<=0x3FF);
				int m = (((absx&0x3FF)|((absx>0x3FF)<<10))<<1) - (((absy&0x3FF)|((absy>0x3FF)<<10))<<(1-d));
				for(; m<0x800 && exp>1; m<<=1,--exp) ;
				return half(binary, 0x8000|((exp-1)<<10)+(m>>1));
			}

			static double erf(double arg)
			{
				if(builtin_isinf(arg))
					return (arg<0.0) ? -1.0 : 1.0;
				double x2 = arg * arg, ax2 = 0.147 * x2, value = std::sqrt(1.0-std::exp(-x2*(1.2732395447351626861510701069801+ax2)/(1.0+ax2)));
				return builtin_signbit(arg) ? -value : value;
			}

			static double lgamma(double arg)
			{
				double v = 1.0;
				for(; arg<8.0; ++arg) v *= arg;
				double w = 1.0 / (arg*arg);
				return (((((((-0.02955065359477124183006535947712*w+0.00641025641025641025641025641026)*w+
					-0.00191752691752691752691752691753)*w+8.4175084175084175084175084175084e-4)*w+
					-5.952380952380952380952380952381e-4)*w+7.9365079365079365079365079365079e-4)*w+
					-0.00277777777777777777777777777778)*w+0.08333333333333333333333333333333)/arg + 
					0.91893853320467274178032973640562 - std::log(v) - arg + (arg-0.5) * std::log(arg);
			}
		};

		/// Helper class for half casts.
		/// This class template has to be specialized for all valid cast argument to define an appropriate static `cast` member 
		/// function and a corresponding `type` member denoting its return type.
		/// \tparam T destination type
		/// \tparam U source type
		/// \tparam R rounding mode to use
		template<typename T,typename U,std::float_round_style R=(std::float_round_style)(HALF_ROUND_STYLE)> struct half_caster {};
		template<typename U,std::float_round_style R> struct half_caster<half,U,R>
		{
		#if HALF_ENABLE_CPP11_STATIC_ASSERT && HALF_ENABLE_CPP11_TYPE_TRAITS
			static_assert(std::is_arithmetic<U>::value, "half_cast from non-arithmetic type unsupported");
		#endif

			typedef half type;
			static half cast(U arg) { return cast_impl(arg, is_float<U>()); };

		private:
			static half cast_impl(U arg, true_type) { return half(binary, float2half<R>(static_cast<float>(arg))); }
			static half cast_impl(U arg, false_type) { return half(binary, int2half<R>(arg)); }
		};
		template<typename T,std::float_round_style R> struct half_caster<T,half,R>
		{
		#if HALF_ENABLE_CPP11_STATIC_ASSERT && HALF_ENABLE_CPP11_TYPE_TRAITS
			static_assert(std::is_arithmetic<T>::value, "half_cast to non-arithmetic type unsupported");
		#endif

			typedef T type;
			static T cast(half arg) { return cast_impl(arg, is_float<T>()); }

		private:
			static T cast_impl(float arg, true_type) { return static_cast<T>(arg); }
			static T cast_impl(half arg, false_type) { return half2int<R,T>(arg.data_); }
		};
		template<std::float_round_style R> struct half_caster<half,half,R>
		{
			typedef half type;
			static half cast(half arg) { return arg; }
		};
	}

	/// \name Comparison operators
	/// \{

	/// Comparison for equality.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if operands equal
	/// \retval false else
	inline bool operator==(half x, half y) { return detail::functions::isequal(x, y); }

	/// Comparison for inequality.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if operands not equal
	/// \retval false else
	inline bool operator!=(half x, half y) { return detail::functions::isnotequal(x, y); }

	/// Comparison for less than.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x less than \a y
	/// \retval false else
	inline bool operator<(half x, half y) { return detail::functions::isless(x, y); }

	/// Comparison for greater than.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x greater than \a y
	/// \retval false else
	inline bool operator>(half x, half y) { return detail::functions::isgreater(x, y); }

	/// Comparison for less equal.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x less equal \a y
	/// \retval false else
	inline bool operator<=(half x, half y) { return detail::functions::islessequal(x, y); }

	/// Comparison for greater equal.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x greater equal \a y
	/// \retval false else
	inline bool operator>=(half x, half y) { return detail::functions::isgreaterequal(x, y); }

	/// \}
	/// \name Arithmetic operators
	/// \{

	/// Add halfs.
	/// \param x left operand
	/// \param y right operand
	/// \return sum of half expressions
	inline half operator+(half x, half y) { return detail::functions::plus(x, y); }

	/// Subtract halfs.
	/// \param x left operand
	/// \param y right operand
	/// \return difference of half expressions
	inline half operator-(half x, half y) { return detail::functions::minus(x, y); }

	/// Multiply halfs.
	/// \param x left operand
	/// \param y right operand
	/// \return product of half expressions
	inline half operator*(half x, half y) { return detail::functions::multiplies(x, y); }

	/// Divide halfs.
	/// \param x left operand
	/// \param y right operand
	/// \return quotient of half expressions
	inline half operator/(half x, half y) { return detail::functions::divides(x, y); }

	/// Identity.
	/// \param arg operand
	/// \return uncahnged operand
	inline HALF_CONSTEXPR half operator+(half arg) { return arg; }

	/// Negation.
	/// \param arg operand
	/// \return negated operand
	inline HALF_CONSTEXPR half operator-(half arg) { return detail::functions::negate(arg); }

	/// \}
	/// \name Input and output
	/// \{

	/// Output operator.
	/// \param out output stream to write into
	/// \param arg half expression to write
	/// \return reference to output stream
	template<typename charT,typename traits> std::basic_ostream<charT,traits>&
		operator<<(std::basic_ostream<charT,traits> &out, half arg) { return detail::functions::write(out, arg); }

	/// Input operator.
	/// \param in input stream to read from
	/// \param arg half to read into
	/// \return reference to input stream
	template<typename charT,typename traits> std::basic_istream<charT,traits>&
		operator>>(std::basic_istream<charT,traits> &in, half &arg) { return detail::functions::read(in, arg); }

	/// \}
	/// \name Basic mathematical operations
	/// \{

	/// Absolute value.
	/// \param arg operand
	/// \return absolute value of \a arg
	inline half abs(half arg) { return detail::functions::fabs(arg); }

	/// Absolute value.
	/// \param arg operand
	/// \return absolute value of \a arg
	inline half fabs(half arg) { return detail::functions::fabs(arg); }

	/// Remainder of division.
	/// \param x first operand
	/// \param y second operand
	/// \return remainder of floating point division.
	inline half fmod(half x, half y) { return detail::functions::fmod(x, y); }

	/// Remainder of division.
	/// \param x first operand
	/// \param y second operand
	/// \return remainder of floating point division.
	inline half remainder(half x, half y) { return detail::functions::remainder(x, y); }

	/// Remainder of division.
	/// \param x first operand
	/// \param y second operand
	/// \param quo address to store some bits of quotient at
	/// \return remainder of floating point division.
	inline half remquo(half x, half y, int *quo) { return detail::functions::remquo(x, y, quo); }

	/// Fused multiply add.
	/// \param x first operand
	/// \param y second operand
	/// \param z third operand
	/// \return ( \a x * \a y ) + \a z rounded as one operation.
	inline half fma(half x, half y, half z) { return detail::functions::fma(x, y, z); }

	/// Maximum of half expressions.
	/// \param x first operand
	/// \param y second operand
	/// \return maximum of operands
	inline half fmax(half x, half y) { return detail::functions::fmax(x, y); }

	/// Minimum of half expressions.
	/// \param x first operand
	/// \param y second operand
	/// \return minimum of operands
	inline half fmin(half x, half y) { return detail::functions::fmin(x, y); }

	/// Positive difference.
	/// \param x first operand
	/// \param y second operand
	/// \return \a x - \a y or 0 if difference negative
	inline half fdim(half x, half y) { return detail::functions::fdim(x, y); }

	/// Get NaN value.
	/// \param arg descriptive string (ignored)
	/// \return quiet NaN
	inline half nanh(const char *arg) { return detail::functions::nanh(arg); }

	/// \}
	/// \name Exponential functions
	/// \{

	/// Exponential function.
	/// \param arg function argument
	/// \return e raised to \a arg
	inline half exp(half arg) { return detail::functions::exp(arg); }

	/// Exponential minus one.
	/// \param arg function argument
	/// \return e raised to \a arg subtracted by 1
	inline half expm1(half arg) { return detail::functions::expm1(arg); }

	/// Binary exponential.
	/// \param arg function argument
	/// \return 2 raised to \a arg
	inline half exp2(half arg) { return detail::functions::exp2(arg); }

	/// Natural logorithm.
	/// \param arg function argument
	/// \return logarithm of \a arg to base e
	inline half log(half arg) { return detail::functions::log(arg); }

	/// Common logorithm.
	/// \param arg function argument
	/// \return logarithm of \a arg to base 10
	inline half log10(half arg) { return detail::functions::log10(arg); }

	/// Natural logorithm.
	/// \param arg function argument
	/// \return logarithm of \a arg plus 1 to base e
	inline half log1p(half arg) { return detail::functions::log1p(arg); }

	/// Binary logorithm.
	/// \param arg function argument
	/// \return logarithm of \a arg to base 2
	inline half log2(half arg) { return detail::functions::log2(arg); }

	/// \}
	/// \name Power functions
	/// \{

	/// Square root.
	/// \param arg function argument
	/// \return square root of \a arg
	inline half sqrt(half arg) { return detail::functions::sqrt(arg); }

	/// Cubic root.
	/// \param arg function argument
	/// \return cubic root of \a arg
	inline half cbrt(half arg) { return detail::functions::cbrt(arg); }

	/// Hypotenuse function.
	/// \param x first argument
	/// \param y second argument
	/// \return square root of sum of squares without internal over- or underflows
	inline half hypot(half x, half y) { return detail::functions::hypot(x, y); }

	/// Power function.
	/// \param base first argument
	/// \param exp second argument
	/// \return \a base raised to \a exp
	inline half pow(half base, half exp) { return detail::functions::pow(base, exp); }

	/// \}
	/// \name Trigonometric functions
	/// \{

	/// Sine function.
	/// \param arg function argument
	/// \return sine value of \a arg
	inline half sin(half arg) { return detail::functions::sin(arg); }

	/// Cosine function.
	/// \param arg function argument
	/// \return cosine value of \a arg
	inline half cos(half arg) { return detail::functions::cos(arg); }

	/// Tangent function.
	/// \param arg function argument
	/// \return tangent value of \a arg
	inline half tan(half arg) { return detail::functions::tan(arg); }

	/// Arc sine.
	/// \param arg function argument
	/// \return arc sine value of \a arg
	inline half asin(half arg) { return detail::functions::asin(arg); }

	/// Arc cosine function.
	/// \param arg function argument
	/// \return arc cosine value of \a arg
	inline half acos(half arg) { return detail::functions::acos(arg); }

	/// Arc tangent function.
	/// \param arg function argument
	/// \return arc tangent value of \a arg
	inline half atan(half arg) { return detail::functions::atan(arg); }

	/// Arc tangent function.
	/// \param x first argument
	/// \param y second argument
	/// \return arc tangent value
	inline half atan2(half x, half y) { return detail::functions::atan2(x, y); }

	/// \}
	/// \name Hyperbolic functions
	/// \{

	/// Hyperbolic sine.
	/// \param arg function argument
	/// \return hyperbolic sine value of \a arg
	inline half sinh(half arg) { return detail::functions::sinh(arg); }

	/// Hyperbolic cosine.
	/// \param arg function argument
	/// \return hyperbolic cosine value of \a arg
	inline half cosh(half arg) { return detail::functions::cosh(arg); }

	/// Hyperbolic tangent.
	/// \param arg function argument
	/// \return hyperbolic tangent value of \a arg
	inline half tanh(half arg) { return detail::functions::tanh(arg); }

	/// Hyperbolic area sine.
	/// \param arg function argument
	/// \return area sine value of \a arg
	inline half asinh(half arg) { return detail::functions::asinh(arg); }

	/// Hyperbolic area cosine.
	/// \param arg function argument
	/// \return area cosine value of \a arg
	inline half acosh(half arg) { return detail::functions::acosh(arg); }

	/// Hyperbolic area tangent.
	/// \param arg function argument
	/// \return area tangent value of \a arg
	inline half atanh(half arg) { return detail::functions::atanh(arg); }

	/// \}
	/// \name Error and gamma functions
	/// \{

	/// Error function.
	/// \param arg function argument
	/// \return error function value of \a arg
	inline half erf(half arg) { return detail::functions::erf(arg); }

	/// Complementary error function.
	/// \param arg function argument
	/// \return 1 minus error function value of \a arg
	inline half erfc(half arg) { return detail::functions::erfc(arg); }

	/// Natural logarithm of gamma function.
	/// \param arg function argument
	/// \return natural logarith of gamma function for \a arg
	inline half lgamma(half arg) { return detail::functions::lgamma(arg); }

	/// Gamma function.
	/// \param arg function argument
	/// \return gamma function value of \a arg
	inline half tgamma(half arg) { return detail::functions::tgamma(arg); }

	/// \}
	/// \name Rounding
	/// \{

	/// Nearest integer not less than half value.
	/// \param arg half to round
	/// \return nearest integer not less than \a arg
	inline half ceil(half arg) { return detail::functions::ceil(arg); }

	/// Nearest integer not greater than half value.
	/// \param arg half to round
	/// \return nearest integer not greater than \a arg
	inline half floor(half arg) { return detail::functions::floor(arg); }

	/// Nearest integer not greater in magnitude than half value.
	/// \param arg half to round
	/// \return nearest integer not greater in magnitude than \a arg
	inline half trunc(half arg) { return detail::functions::trunc(arg); }

	/// Nearest integer.
	/// \param arg half to round
	/// \return nearest integer, rounded away from zero in half-way cases
	inline half round(half arg) { return detail::functions::round(arg); }

	/// Nearest integer.
	/// \param arg half to round
	/// \return nearest integer, rounded away from zero in half-way cases
	inline long lround(half arg) { return detail::functions::lround(arg); }

	/// Nearest integer using half's internal rounding mode.
	/// \param arg half expression to round
	/// \return nearest integer using default rounding mode
	inline half nearbyint(half arg) { return detail::functions::rint(arg); }

	/// Nearest integer using half's internal rounding mode.
	/// \param arg half expression to round
	/// \return nearest integer using default rounding mode
	inline half rint(half arg) { return detail::functions::rint(arg); }

	/// Nearest integer using half's internal rounding mode.
	/// \param arg half expression to round
	/// \return nearest integer using default rounding mode
	inline long lrint(half arg) { return detail::functions::lrint(arg); }
#if HALF_ENABLE_CPP11_LONG_LONG
	/// Nearest integer.
	/// \param arg half to round
	/// \return nearest integer, rounded away from zero in half-way cases
	inline long long llround(half arg) { return detail::functions::llround(arg); }

	/// Nearest integer using half's internal rounding mode.
	/// \param arg half expression to round
	/// \return nearest integer using default rounding mode
	inline long long llrint(half arg) { return detail::functions::llrint(arg); }
#endif

	/// \}
	/// \name Floating point manipulation
	/// \{

	/// Decompress floating point number.
	/// \param arg number to decompress
	/// \param exp address to store exponent at
	/// \return significant in range [0.5, 1)
	inline half frexp(half arg, int *exp) { return detail::functions::frexp(arg, exp); }

	/// Multiply by power of two.
	/// \param arg number to modify
	/// \param exp power of two to multiply with
	/// \return \a arg multplied by 2 raised to \a exp
	inline half ldexp(half arg, int exp) { return detail::functions::scalbln(arg, exp); }

	/// Extract integer and fractional parts.
	/// \param arg number to decompress
	/// \param iptr address to store integer part at
	/// \return fractional part
	inline half modf(half arg, half *iptr) { return detail::functions::modf(arg, iptr); }

	/// Multiply by power of two.
	/// \param arg number to modify
	/// \param exp power of two to multiply with
	/// \return \a arg multplied by 2 raised to \a exp
	inline half scalbn(half arg, int exp) { return detail::functions::scalbln(arg, exp); }

	/// Multiply by power of two.
	/// \param arg number to modify
	/// \param exp power of two to multiply with
	/// \return \a arg multplied by 2 raised to \a exp
	inline half scalbln(half arg, long exp) { return detail::functions::scalbln(arg, exp); }

	/// Extract exponent.
	/// \param arg number to query
	/// \return floating point exponent
	/// \retval FP_ILOGB0 for zero
	/// \retval FP_ILOGBNAN for NaN
	/// \retval MAX_INT for infinity
	inline int ilogb(half arg) { return detail::functions::ilogb(arg); }

	/// Extract exponent.
	/// \param arg number to query
	/// \return floating point exponent
	inline half logb(half arg) { return detail::functions::logb(arg); }

	/// Next representable value.
	/// \param from value to compute next representable value for
	/// \param to direction towards which to compute next value
	/// \return next representable value after \a from in direction towards \a to
	inline half nextafter(half from, half to) { return detail::functions::nextafter(from, to); }

	/// Next representable value.
	/// \param from value to compute next representable value for
	/// \param to direction towards which to compute next value
	/// \return next representable value after \a from in direction towards \a to
	inline half nexttoward(half from, long double to) { return detail::functions::nexttoward(from, to); }

	/// Take sign.
	/// \param x value to change sign for
	/// \param y value to take sign from
	/// \return value equal to \a x in magnitude and to \a y in sign
	inline half copysign(half x, half y) { return detail::functions::copysign(x, y); }

	/// \}
	/// \name Floating point classification
	/// \{


	/// Classify floating point value.
	/// \param arg number to classify
	/// \retval FP_ZERO for positive and negative zero
	/// \retval FP_SUBNORMAL for subnormal numbers
	/// \retval FP_INFINITY for positive and negative infinity
	/// \retval FP_NAN for NaNs
	/// \retval FP_NORMAL for all other (normal) values
	inline int fpclassify(half arg) { return detail::functions::fpclassify(arg); }

	/// Check if finite number.
	/// \param arg number to check
	/// \retval true if neither infinity nor NaN
	/// \retval false else
	inline bool isfinite(half arg) { return detail::functions::isfinite(arg); }

	/// Check for infinity.
	/// \param arg number to check
	/// \retval true for positive or negative infinity
	/// \retval false else
	inline bool isinf(half arg) { return detail::functions::isinf(arg); }

	/// Check for NaN.
	/// \param arg number to check
	/// \retval true for NaNs
	/// \retval false else
	inline bool isnan(half arg) { return detail::functions::isnan(arg); }

	/// Check if normal number.
	/// \param arg number to check
	/// \retval true if normal number
	/// \retval false if either subnormal, zero, infinity or NaN
	inline bool isnormal(half arg) { return detail::functions::isnormal(arg); }

	/// Check sign.
	/// \param arg number to check
	/// \retval true for negative number
	/// \retval false for positive number
	inline bool signbit(half arg) { return detail::functions::signbit(arg); }

	/// \}
	/// \name Comparison
	/// \{

	/// Comparison for greater than.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x greater than \a y
	/// \retval false else
	inline bool isgreater(half x, half y) { return detail::functions::isgreater(x, y); }

	/// Comparison for greater equal.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x greater equal \a y
	/// \retval false else
	inline bool isgreaterequal(half x, half y) { return detail::functions::isgreaterequal(x, y); }

	/// Comparison for less than.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x less than \a y
	/// \retval false else
	inline bool isless(half x, half y) { return detail::functions::isless(x, y); }

	/// Comparison for less equal.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if \a x less equal \a y
	/// \retval false else
	inline bool islessequal(half x, half y) { return detail::functions::islessequal(x, y); }

	/// Comarison for less or greater.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if either less or greater
	/// \retval false else
	inline bool islessgreater(half x, half y) { return detail::functions::islessgreater(x, y); }

	/// Check if unordered.
	/// \param x first operand
	/// \param y second operand
	/// \retval true if unordered (one or two NaN operands)
	/// \retval false else
	inline bool isunordered(half x, half y) { return detail::functions::isunordered(x, y); }

	/// \name Casting
	/// \{

	/// Cast to or from half-precision floating point number.
	/// This casts between [half](\ref half_float::half) and any built-in arithmetic type. Floating point types are 
	/// converted via an explicit cast to/from `float` (using the rounding mode of the built-in single precision 
	/// implementation) and thus any possible warnings due to an otherwise implicit conversion to/from `float` will be 
	/// suppressed. Integer types are converted directly using the given rounding mode, without any roundtrip over `float` 
	/// that a `static_cast` would otherwise do. It uses the default rounding mode.
	///
	/// Using this cast with neither of the two types being a [half](\ref half_float::half) or with any of the two types 
	/// not being a built-in arithmetic type (apart from [half](\ref half_float::half), of course) results in a compiler 
	/// error and casting between [half](\ref half_float::half)s is just a no-op.
	/// \tparam T destination type (half or built-in arithmetic type)
	/// \tparam U source type (half or built-in arithmetic type)
	/// \param arg value to cast
	/// \return \a arg converted to destination type
	template<typename T,typename U> typename detail::half_caster<T,U>::type half_cast(U arg) { return detail::half_caster<T,U>::cast(arg); }

	/// Cast to or from half-precision floating point number.
	/// This casts between [half](\ref half_float::half) and any built-in arithmetic type. Floating point types are 
	/// converted via an explicit cast to/from `float` (using the rounding mode of the built-in single precision 
	/// implementation) and thus any possible warnings due to an otherwise implicit conversion to/from `float` will be 
	/// suppressed. Integer types are converted directly using the given rounding mode, without any roundtrip over `float` 
	/// that a `static_cast` would otherwise do.
	///
	/// Using this cast with neither of the two types being a [half](\ref half_float::half) or with any of the two types 
	/// not being a built-in arithmetic type (apart from [half](\ref half_float::half), of course) results in a compiler 
	/// error and casting between [half](\ref half_float::half)s is just a no-op.
	/// \tparam T destination type (half or built-in arithmetic type)
	/// \tparam R rounding mode to use.
	/// \tparam U source type (half or built-in arithmetic type)
	/// \param arg value to cast
	/// \return \a arg converted to destination type
	template<typename T,std::float_round_style R,typename U> typename detail::half_caster<T,U,R>::type half_cast(U arg)
		{ return detail::half_caster<T,U,R>::cast(arg); }
	/// \}
}


/// Extensions to the C++ standard library.
namespace std
{
	/// Numeric limits for half-precision floats.
	/// Because of the underlying single-precision implementation of many operations, it inherits some properties from 
	/// `std::numeric_limits<float>`.
	template<> class numeric_limits<half_float::half> : public numeric_limits<float>
	{
	public:
		/// Supports signed values.
		static HALF_CONSTEXPR_CONST bool is_signed = true;

		/// Is not exact.
		static HALF_CONSTEXPR_CONST bool is_exact = false;

		/// Doesn't provide modulo arithmetic.
		static HALF_CONSTEXPR_CONST bool is_modulo = false;

		/// IEEE conformant.
		static HALF_CONSTEXPR_CONST bool is_iec559 = true;

		/// Supports infinity.
		static HALF_CONSTEXPR_CONST bool has_infinity = true;

		/// Supports quiet NaNs.
		static HALF_CONSTEXPR_CONST bool has_quiet_NaN = true;

		/// Supports subnormal values.
		static HALF_CONSTEXPR_CONST float_denorm_style has_denorm = denorm_present;

		/// Rounding mode.
		/// Due to the mix of internal single-precision computations (using the rounding mode of the underlying 
		/// single-precision implementation) with the rounding mode of the single-to-half conversions, the actual rounding 
		/// mode might be `std::round_indeterminate` if the default half-precision rounding mode doesn't match the 
		/// single-precision rounding mode.
		static HALF_CONSTEXPR_CONST float_round_style round_style = (std::numeric_limits<float>::round_style==
			half_float::half::round_style) ? half_float::half::round_style : round_indeterminate;

		/// Significant digits.
		static HALF_CONSTEXPR_CONST int digits = 11;

		/// Significant decimal digits.
		static HALF_CONSTEXPR_CONST int digits10 = 3;

		/// Required decimal digits to represent all possible values.
		static HALF_CONSTEXPR_CONST int max_digits10 = 5;

		/// Number base.
		static HALF_CONSTEXPR_CONST int radix = 2;

		/// One more than smallest exponent.
		static HALF_CONSTEXPR_CONST int min_exponent = -13;

		/// Smallest normalized representable power of 10.
		static HALF_CONSTEXPR_CONST int min_exponent10 = -4;

		/// One more than largest exponent
		static HALF_CONSTEXPR_CONST int max_exponent = 16;

		/// Largest finitely representable power of 10.
		static HALF_CONSTEXPR_CONST int max_exponent10 = 4;

		/// Smallest positive normal value.
		static HALF_CONSTEXPR half_float::half min() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x0400); }

		/// Smallest finite value.
		static HALF_CONSTEXPR half_float::half lowest() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0xFBFF); }

		/// Largest finite value.
		static HALF_CONSTEXPR half_float::half max() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x7BFF); }

		/// Difference between one and next representable value.
		static HALF_CONSTEXPR half_float::half epsilon() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x1400); }

		/// Maximum rounding error.
		static HALF_CONSTEXPR half_float::half round_error() HALF_NOTHROW
			{ return half_float::half(half_float::detail::binary, (round_style==std::round_to_nearest) ? 0x3800 : 0x3C00); }

		/// Positive infinity.
		static HALF_CONSTEXPR half_float::half infinity() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x7C00); }

		/// Quiet NaN.
		static HALF_CONSTEXPR half_float::half quiet_NaN() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x7FFF); }

		/// Signalling NaN.
		static HALF_CONSTEXPR half_float::half signaling_NaN() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x7DFF); }

		/// Smallest positive subnormal value.
		static HALF_CONSTEXPR half_float::half denorm_min() HALF_NOTHROW { return half_float::half(half_float::detail::binary, 0x0001); }
	};

#if HALF_ENABLE_CPP11_HASH
	/// Hash function for half-precision floats.
	/// This is only defined if C++11 `std::hash` is supported and enabled.
	template<> struct hash<half_float::half> //: unary_function<half_float::half,size_t>
	{
		/// Type of function argument.
		typedef half_float::half argument_type;

		/// Function return type.
		typedef size_t result_type;

		/// Compute hash function.
		/// \param arg half to hash
		/// \return hash value
		result_type operator()(argument_type arg) const
			{ return hash<half_float::detail::uint16>()(static_cast<unsigned>(arg.data_)&-(arg.data_!=0x8000)); }
	};
#endif
}


#undef HALF_CONSTEXPR
#undef HALF_CONSTEXPR_CONST
#undef HALF_NOEXCEPT
#undef HALF_NOTHROW
#ifdef HALF_POP_WARNINGS
	#pragma warning(pop)
	#undef HALF_POP_WARNINGS
#endif

#endif

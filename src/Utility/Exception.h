//
// File: Exception.h
//
// Some types of useful exceptions, used in DSCPP project.
//
// Shining Yang <y.s.n@live.com>, 2014-10-08
//
#pragma once

namespace DSCPP {
namespace Utils {
// @Description:
//  The required data size not meet.
// @Example:
//  Dimension of array or matrix
class SizeNotMatch {};

// @Description:
//  Usually indicates that indices are not in a valid range.
// @Example:
//  The index provided is out the range of array.
class OutOfRange {};

// @Description:
//  This is usually similar as OutOfRange. They may be interchangeable.
class OutOfBounds {};

// @Description:
//  Not enough memory to hold specified data or memory allocation failed
class OutOfMemory {};

// @Description:
//  It generally indicates wrong arguments passed to constructor.
class BadInitializer {};

// @Description:
//  The arguments passed to a method is unacceptable or invalid.
class InvalideArgument {};

// @Description:
//  Target item does not exist when try to perform operation on it.
class ItemNotExisted {};

// @Description:
//  Usually means the target is already existing when try to add.
class ItemAlreadyExisted {};

// @Description:
//  When attempting to add a data element, it would go out of the upper bound.
class ItemOverFlow {};

// @Description:
//  When attempting to remove a data element, it would go out of the lower
//  bound.
class ItemUnderFlow {};
} // namespace Utils
} // namespace DSCPP
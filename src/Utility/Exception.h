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
        class SizeNotMatch {
        };

        class OutOfRange {
        };

        class OutOfBounds {
        };

        class OutOfMemory {
        };

        class BadInitializer {
        };

        class InvalideArgument {
        };

        class ItemNotExisted {
        };

        class ItemAlreadyExisted {
        };

        class ItemOverFlow {
        };

        class ItemUnderFlow {
        };
    }
}
// The MIT License (MIT)
//
// Copyright (c) 2013-2015 Tino Bog
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef AUTOARGS_AUTOARGS_HPP_
#define AUTOARGS_AUTOARGS_HPP_

// --- Internal Includes ---
#include "BooleanArgument.hpp"
#include "StringArgument.hpp"
#include "GenericNumericArgument.hpp"
#include "GenericArgumentParser.hpp"
#include "DefaultHelpMessageCreator.hpp"
#include "DefaultInputFileReader.hpp"

namespace autoargs
{
typedef adhocpp::utilities::BooleanArgument BoolArg;
typedef adhocpp::utilities::StringArgument StringArg;
typedef adhocpp::utilities::GenericNumericArgument<double> DoubleArg;
typedef adhocpp::utilities::GenericNumericArgument<float> FloatArg;
typedef adhocpp::utilities::GenericNumericArgument<short> ShortArg;
typedef adhocpp::utilities::GenericNumericArgument<int> IntArg;
typedef adhocpp::utilities::GenericNumericArgument<size_t> SizeArg;

typedef adhocpp::utilities::GenericArgumentParser<adhocpp::utilities::DefaultHelpMessageCreator,
    adhocpp::utilities::CoutAndExitPolicy, adhocpp::utilities::DefaultInputFileReader> ArgumentParser;

typedef adhocpp::utilities::GenericArgumentParser<adhocpp::utilities::DefaultHelpMessageCreator,
    adhocpp::utilities::AdhocppExceptionPolicy, adhocpp::utilities::DefaultInputFileReader> TestArgumentParser;
}  // namespace autoargs

#endif // AUTOARGS_AUTOARGS_HPP_

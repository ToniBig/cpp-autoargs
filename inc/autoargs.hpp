/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_AUTOARGS_HPP_
#define UTILITIES_AUTOARGS_HPP_

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

#endif // UTILITIES_AUTOARGS_HPP_

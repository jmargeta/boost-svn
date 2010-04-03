//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_REPLACE_COPY_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_REPLACE_COPY_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function replace_copy
    ///
    /// range-based version of the replace_copy std algorithm
    ///
    /// \pre ForwardRange is a model of the ForwardRangeConcept
    template< class ForwardRange, class OutputIterator, class Value >
    inline OutputIterator
    replace_copy(ForwardRange& rng, OutputIterator out_it, const Value& what,
            const Value& with_what)
    {
        boost::function_requires< ForwardRangeConcept<ForwardRange> >();
        return std::replace_copy(boost::begin(rng), boost::end(rng), out_it,
            what, with_what);
    }
}

#endif // include guard
// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: the present implementation has not been tested.

#ifndef BOOST_IOSTREAMS_CONVERTING_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONVERTING_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif          

#include <boost/iostreams/detail/config/wide_streams.hpp>
#if defined(BOOST_IOSTREAMS_NO_WIDE_STREAMS) || \
    defined(BOOST_IOSTREAMS_NO_LOCALE) \
    /**/
# error code conversion not supported on this platform
#endif

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/detail/converting_chain.hpp>

namespace boost { namespace iostreams {

BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF( 
    converting_streambuf, detail::converting_chain, wchar_t 
)

} } // End namespace iostreams, boost

#endif // #ifndef BOOST_IOSTREAMS_CONVERTING_STREAMBUF_HPP_INCLUDED

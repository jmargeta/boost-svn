
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_mem_fun.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/tti/mf/mf_has_member_function.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // someFunctionMember does not exist at all
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(someFunctionMember)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      short,
                      boost::mpl::vector
                        <
                        double,
                        int,
                        long
                        >
                      >
                  ));
  
  return 0;

  }

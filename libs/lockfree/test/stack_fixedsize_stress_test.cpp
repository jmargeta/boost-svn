#include <boost/lockfree/stack.hpp>

#define BOOST_TEST_MAIN
#ifdef BOOST_LOCKFREE_INCLUDE_TESTS
#include <boost/test/included/unit_test.hpp>
#else
#include <boost/test/unit_test.hpp>
#endif

#include "test_common.hpp"


BOOST_AUTO_TEST_CASE( stack_test_fixed_size )
{
    typedef queue_stress_tester<> tester_type;
    boost::scoped_ptr<tester_type> tester(new tester_type(4, 4) );

    boost::lockfree::stack<long, boost::lockfree::capacity<8> > q;
    tester->run(q);
}

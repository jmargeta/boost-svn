
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include <boost/assert.hpp>
#include <boost/context/all.hpp>

namespace ctx = boost::ctx;

ctx::fcontext_t fcm, fc1, fc2;

void f1( intptr_t)
{
        std::cout << "f1: entered" << std::endl;
        std::cout << "f1: call jump_fcontext( & fc1, & fc2, 0)" << std::endl;
        ctx::jump_fcontext( & fc1, & fc2, 0);
        std::cout << "f1: return" << std::endl;
        ctx::jump_fcontext( & fc1, & fcm, 0);
}

void f2( intptr_t)
{
        std::cout << "f2: entered" << std::endl;
        std::cout << "f2: call jump_fcontext( & fc2, & fc1, 0)" << std::endl;
        ctx::jump_fcontext( & fc2, & fc1, 0);
        BOOST_ASSERT( false && ! "f2: never returns");
}

int main( int argc, char * argv[])
{
        ctx::stack_allocator alloc1, alloc2;

        fc1.fc_stack.base = alloc1.allocate(ctx::minimum_stacksize());
        fc1.fc_stack.size = ctx::minimum_stacksize();
        ctx::make_fcontext( & fc1, f1);

        fc2.fc_stack.base = alloc2.allocate(ctx::minimum_stacksize());
        fc2.fc_stack.size = ctx::minimum_stacksize();
        ctx::make_fcontext( & fc2, f2);

        std::cout << "main: call start_fcontext( & fcm, & fc1, 0)" << std::endl;
        ctx::jump_fcontext( & fcm, & fc1, 0);

        std::cout << "main: done" << std::endl;

        return EXIT_SUCCESS;
}

// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/object_protocol.hpp>
#include <boost/python/errors.hpp>
#include <boost/python/object.hpp>

namespace boost { namespace python { 

object getattr(object const& target, object const& key)
{
    return object((object::new_pyobject_reference*)PyObject_GetAttr(&*target, &*key));
}
    
void setattr(object const& target, object const& key, object const& value)
{
    if (PyObject_SetAttr(&*target, &*key, &*value) == -1)
        throw_error_already_set();
}

object getitem(object const& target, object const& key)
{
    return object((object::new_pyobject_reference*)PyObject_GetItem(&*target, &*key));
}
    
void setitem(object const& target, object const& key, object const& value)
{
    if (PyObject_SetItem(&*target, &*key, &*value) == -1)
        throw_error_already_set();
}

}} // namespace boost::python

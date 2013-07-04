// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)_cpp_copyright_

$template_start$
$template_copyright$

#ifndef BOOST_$template_LIBRARY$_$template_LIBRARY$_HPP
#define BOOST_$template_LIBRARY$_$template_LIBRARY$_HPP

namespace boost {
namespace $template_library$ {

/// The $template_library$ class does nothing.
/** \ingroup group_nothing
    \param T The type on which $template_library$ does nothing.
    \warning This class does nothing.
    \todo Make this class do something.
    \bug This class does do something.

    Since $template_library$ does nothing, it is not very useful.
*/
template<typename T
#ifndef DOXYGEN_DOCS_ONLY
    , typename Enable=void // maybe documentation doesn't need to know about this.
#endif
>
class $template_library$
{
public:
    /// Default constructor.
    /** This constructor actually does something.  It sets the internal
        counters to 0.
    */
    $template_library$() : nothing_count(0), call_count(0) {}

    /// This function does nothing with the passed parameter.
    void nothing(T t)
    {
        nothing_count++;
        call_count++;
    }

    /// This function does nothing with the passed parameter a specified number of times.
    /** \param n Number of times nothing is done.
    
        This function is equivalent to calling nothing n times.
    */
    void nothing(T t, unsigned n)
    {
        call_count++;
        for (unsigned i=0; i<n; i++)
            nothing(t);
        call_count-=n;
    }

    /// This function can be used to determine how many times nothing has been done.
    /** \returns count of how many times nothing has been done.
    */
    int get_nothing_count()
    {
        return nothing_count;
    }
    /// This function can be used to determine how many calls have been made to the object.
    /** \returns count of how many times a method of this object has been called by the user.
    */
    int get_call_count()
    {
        return call_count;
    }
protected:
    /// The number of times this object did nothing.
    int nothing_count;
private:
    // Number of times the member function was called.
    int call_count;
};

} // namespace $template_library$
} // namespace boost

#endif // BOOST_$template_LIBRARY$_$template_LIBRARY$_HPP


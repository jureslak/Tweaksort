#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
/**
 * @file exceptions.hpp
 * Defines the thweaksort exceptions.
 *
 * @author Jure Slak (JS), jure.slak@gmail.com
 * @version 1.0
 * @since 2011-02-01 02:46:48 PM
 */
#include <stdexcept>

namespace tweaksort {

/**
 * Parse error class, used when parsing conf 
 */
class ParseError : public std::runtime_error
{
  public:
    /** 
     * Constructor for ParseError.
     * @param what_arg Error message
     */
    explicit ParseError(const std::string& what_arg)
        : std::runtime_error(what_arg) {}
};

}
#endif

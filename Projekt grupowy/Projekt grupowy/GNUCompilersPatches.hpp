#ifndef GNU_COMPILERS_PATCHES_HPP
#define GNU_COMPILERS_PATCHES_HPP

#include <string>
#include <sstream>

/*
 * Gathers function definitions that should be used instead of the specified to be compatible with GNU compilers.
 */
namespace gnu
{
    /*
     * Use this to replace std::to_string(...) function of Visual Studio implementation.
     */
    template<typename T> std::string to_string( const T & typeToConvert )
    {
        std::ostringstream converter;
        converter << typeToConvert;
        return converter.str();
    }
}

#endif // ! GNU_COMPILERS_PATCHES_HPP

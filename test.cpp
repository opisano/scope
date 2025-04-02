#include "scope.hpp"

#include <iostream>
#include <stdexcept>


int main()
{
    // check that SCOPE EXIT AND SUCCESS work and are called in reverse order
    {
        SCOPE_SUCCESS([]{ std::cout << "be written\n"; })
        SCOPE_EXIT([]{ std::cout << "This should "; })
        SCOPE_FAILURE([]{ std::cout << "This should not be written\n";})
    }

    // check SCOPE_SUCCESS does nothing when an exception is thrown 
    try
    {
        {
            SCOPE_SUCCESS([]{ std::cout << "This Should not be written\n"; })
            throw std::runtime_error("");
        }
    }
    catch (const std::runtime_error& )
    {

    }

    // check that SCOPE_FAILURE work 
    try
    {
        {
            SCOPE_FAILURE([]{ std::cout << "This Should be written\n"; })
            throw std::runtime_error("");
        }
    }
    catch (const std::runtime_error& )
    {
        
    }
}

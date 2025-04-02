# Scope guards à la D in C++ 

## Purpose 

Scope guards are a nice feature in the D programming language that enable us to register statements to be executed at certain conditions if the current block is left. 

    - scope(exit) will always call the statements
    - scope(success) statements are called when no exceptions have been thrown
    - scope(failure) denotes statements that will be called when an exception has been thrown before the block's end

Scope guards simplify transactional code (a.k.a "all or nothing"). They also improve readability by placing resource allocation and clean up code next to each other. 
The C++ ISO commitee has put scope_guards in [standard libraries extensions v3](https://en.cppreference.com/w/cpp/experimental/lib_extensions_3), so they may arrive in the C++ standard some day.


## Use

This library is a header only library which is easy to integrate in any of your projects. The license is Boost, which is basically the most permissive license out there.  
The libray provides three macros that take a lambda as argument to mimic their D counterpart : 

    SCOPE_EXIT(<lambda>)  // execute lambda at scope exit

    SCOPE_SUCCESS(<lambda>)  // execute lambda at scope exit, if exiting normally 

    SCOPE_FAILURE(<lambda>)  // execute lambda at scope exit, if an exception is thrown

  

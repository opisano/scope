#ifndef OP_SCOPE_HPP
#define OP_SCOPE_HPP

#include <exception>
#include <functional>

namespace op {

    /**
     * Registers a function to be called when we exit the current scope.
     */
    struct ScopeExit
    {
        explicit ScopeExit(std::function<void ()> func)
            : m_func(func)
        {

        }

        ~ScopeExit() 
        {
            m_func();
        }

    private:
        const std::function<void ()> m_func;
    };

    /** 
     * Registers a function to be called when we exit the current scope normally.
     */
    struct ScopeSuccess
    {
        /**
         * Store the amount of active exceptions when the object is created on the stack.
         */
        explicit ScopeSuccess(std::function<void ()> func) : 
            m_func(func),
            m_thrown_exceptions(std::uncaught_exceptions())
        {

        }

        ~ScopeSuccess() 
        {
            /* If the amount of active exceptions is the same as the stored one, we 
              exited the scope normally. */
            if (std::uncaught_exceptions() == m_thrown_exceptions)
            {
                m_func();
            }
        }

    private:
        const std::function<void ()> m_func;
        const int m_thrown_exceptions;
    };


    /** 
     * Registers a function to be called when we exit the current scope because of an 
     * exception.
     */
    struct ScopeFailure
    {
        /**
         * Store the amount of active exceptions when the object is created on the stack.
         */
        explicit ScopeFailure(std::function<void ()> func) : 
            m_func(func),
            m_thrown_exceptions(std::uncaught_exceptions())
        {

        }

        ~ScopeFailure() 
        {
            /* If the amount of active exceptions is greater than the stored one, we 
              exited the scope with an exception. */
            if (std::uncaught_exceptions() > m_thrown_exceptions)
            {
                m_func();
            }
        }

    private:
        const std::function<void ()> m_func;
        const int m_thrown_exceptions;
    };

}

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)


#define SCOPE_EXIT(f) op::ScopeExit TOKENPASTE2(se, __LINE__ ) (f);
#define SCOPE_SUCCESS(f) op::ScopeSuccess TOKENPASTE2(se, __LINE__ ) (f);
#define SCOPE_FAILURE(f) op::ScopeFailure TOKENPASTE2(se, __LINE__ ) (f);

#endif // OP_SCOPE_HPP

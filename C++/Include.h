#pragma once

#include <string>
#include <vector>
#include <memory>


// unpack vector of any into function parameters
template<class Params, class ReturnType, class... Args, std::size_t... Indices>
ReturnType applyParams(Params&& params, ReturnType(*callback)(Args...), std::index_sequence<Indices...>)
{
    return callback(std::any_cast<Args>(params[Indices])...);
}

template<class Params, class ReturnType, class... Args>
ReturnType applyParams(Params&& params, ReturnType(*function)(Args...))
{
    return applyParams(params, function, std::make_index_sequence<sizeof...(Args)>{});
}



// concatenate variadic number of parameters by delimeter
template< typename ... Args >
std::string concatenateByDelimeter(char delimeter, Args const& ... args)
{
    std::ostringstream stream;
    using List = int[];

    /*
    This call creates a (compile-time) recursive initialization list construction to create an unused, unnamed, dummy int array,
    but the expression ( (void)(stream << args), 0 ) has the side-effect of streaming the args into the stream (before returning the second 0)
    */
    (void)List
    {
        0, ((void)(stream << args << delimeter), 0) ...
    };

    return stream.str();
}



// split string by delimeter into vector
std::vector<std::string> split(const std::string& stringToSplit, char delimeter)
{
    std::vector<std::string> elements;
    std::stringstream stringStream(stringToSplit);
    std::string item;

    while (std::getline(stringStream, item, delimeter))
    {
        elements.push_back(item);
    }
    return elements;
}




// basic shrink-wrapped pimpl helper class
template<typename T> class pimpl
{
    std::unique_ptr<T> impl;

public:
    pimpl() : impl{ new T{} } {}
    template <typename ...Args>
    pimpl(Args&& ...args) : impl{ std::forward<Args>(args)... } {}

    ~pimpl() = default;

    T* operator-> () { return impl.get(); }
    T& operator* () { return *impl.get(); }
};
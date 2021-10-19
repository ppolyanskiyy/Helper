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


template< typename ... Args >
std::string concatenateByDelimeter(const std::string delimeter, Args const& ... args)
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
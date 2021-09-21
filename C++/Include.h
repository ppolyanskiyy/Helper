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



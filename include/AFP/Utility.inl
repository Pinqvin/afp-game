///
template <typename T>
std::string AFP::toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

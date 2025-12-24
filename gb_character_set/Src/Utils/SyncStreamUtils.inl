template <typename T>
std::osyncstream CSyncStreamUtils::operator <<(const T& value) const
{
	std::osyncstream cout_stream(std::cout);
	cout_stream << value;
	return cout_stream;
}
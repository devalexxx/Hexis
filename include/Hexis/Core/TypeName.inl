#if defined(__clang__) || defined(__GNUG__)
#	include <cxxabi.h>
#endif

#include <cstdlib>
#include <typeinfo>

namespace Hx
{

	template<typename T>
	std::string TypeName()
	{
		std::string tname = typeid(T).name();

#if defined(__clang__) || defined(__GNUG__)
		int status;
		char *demangled_name = abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);
		if(status == 0)
		{
			tname = demangled_name;
			std::free(demangled_name);
		}
#endif

		return tname;
	}

}
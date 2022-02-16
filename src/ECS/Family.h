#pragma once

#include <cstdio>





class Family {
	static std::size_t identifier() noexcept {
		static std::size_t value = 0;
		return value++;
	}

public:
	template<typename>
	static std::size_t type() noexcept {
		static const std::size_t value = identifier();
		return value;
	}
};
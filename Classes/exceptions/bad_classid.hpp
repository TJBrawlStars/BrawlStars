/** @author  ±ÃÏ“› */
#include <exception>

class bad_classid :public std::exception
{
public:
	explicit bad_classid(std::string classid) noexcept
		:exception("the class isnt in the factory map")
	{
		_classid = _classid;
	}

	bad_classid(const bad_classid& other) noexcept
		:exception("the class isnt in the factory map")
	{
		*this = other;
	}

	bad_classid(bad_classid&& other) noexcept
		:exception("the class isnt in the factory map")
	{
		*this = other;
	}

	bad_classid& operator=(bad_classid const& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		this->_classid = other._classid;
		return *this;
	}

	std::string classid() const noexcept { return _classid; }

private:
	std::string _classid;
};
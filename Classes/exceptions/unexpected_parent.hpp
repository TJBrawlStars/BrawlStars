/** @author  ±ÃÏ“› */
#include <exception>
#include "cocos2d.h"

class unexpected_parent :public std::exception
{
public:
	explicit unexpected_parent(cocos2d::Node* parentNode) noexcept
		:exception("the parent node is unexcepted")
	{
		_parentNode = parentNode;
	}

	unexpected_parent(const unexpected_parent& other) noexcept
		:exception("the parent node is unexcepted")
	{
		*this = other;
	}

	unexpected_parent(unexpected_parent&& other) noexcept
		:exception("the parent node is unexcepted")
	{
		*this = other;
		other._parentNode = nullptr;
	}

	unexpected_parent& operator=(unexpected_parent const& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		this->_parentNode = other._parentNode;
		return *this;
	}

	cocos2d::Node* parentNode() const noexcept { return _parentNode; }

private:
	cocos2d::Node* _parentNode;
};
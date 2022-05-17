#pragma once
/**
* @author 张靖凯
* @brief 排行榜(由STL组合)
***********************************************************************************************************
* @本hpp包含C++加分项特性如下：
* 1:constexpr
* 2:using声明                                 （没用using指示符）
* 3:智能指针                                   shared_ptr
* 4:函数对象                                   function object（key_value_less）
* 5:函数重载                                   key_value_less重载了()运算符
* 6:explicit                                   LeaderBoard单参构造防止隐式转换
* 7:模板类                                     初期key先绑定角色名称，后期计划绑定账号
* 8:noexcept                                   移动构造函数指定不抛出异常
* 9:移动构造、移动赋值运算符                   优化性能，并且delete了拷贝的
* 10:右值引用                                  用于移动构造
* 11:反向迭代器                                从大到小返回
* 12:STL的无序map和set运用                     红黑树和哈希特性
* 13:类型推断auto
* 14:lambda表达式                              匿名函数，方便
* 15:初始化列表
* 16:STL的emplace函数                          将参数传递给构造函数，emplace使用这些参数在容器管理的内存空间中直接构造元素
*
* 接口:insert_sum 总排行榜，可以试试整成全局变量，开一个全局变量的cpp或者h文件，我寻思毕竟是这个榜单要存在于整个程序运行过程的
* 所以还是用这个类建立一个全局对象作为总排行榜，使用insert_sum函数插入对应的内容
* 
* 接口:insert 单局游戏的排行榜，还是这个类创建的东西，使用insert函数即可
* 
* 有疑问：为什么不能类内成员重载+
*/
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>

template <class Key, class T>
class LeaderBoard {
public:
    using key_type = Key;
    using value_type = T;
    using size_type = std::size_t;

    // default: care of top 1000
    static constexpr size_type default_top = 1000;

    struct key_value_type
    {
        key_type first;
        value_type second;
        key_value_type(const key_type& k, const value_type& v) : first(k), second(v) {}
    };

    using key_value_ptr = std::shared_ptr<key_value_type>;

    struct key_value_less
    {
        constexpr bool operator()(const key_value_ptr& left,
            const key_value_ptr& right) const {
            if (left->second == right->second) 
            {
                return left->first < right->first;
            }
            return left->second < right->second;
        }
    };

    LeaderBoard() : _top(default_top) {}
    explicit LeaderBoard(size_type top) : _top(top == 0 ? default_top : top) {}
    LeaderBoard(const LeaderBoard&) = delete;
    LeaderBoard& operator=(const LeaderBoard&) = delete;
    ~LeaderBoard() = default;

    LeaderBoard(LeaderBoard&& right) noexcept
    {
        _top = right._top;
        _map = std::move(right._map);
        _set = std::move(right._set);
        return *this;
    }

    LeaderBoard& operator=(LeaderBoard&& right) noexcept
    {
        _top = right._top;
        _map = std::move(right._map);
        _set = std::move(right._set);
        return *this;
    }

    // ranged-for: large->small
    auto begin() const { return _set.rbegin(); }
    auto end() const { return _set.rend(); }

    auto find(key_type k) { return _map.find(k); }
    auto _mapend() { return _map.end(); }
    auto _setend() { return _set.end(); }


    //总榜单
    void insert_sum(const key_type& k, const value_type& v)
    {
        auto add = [&] {
            key_value_ptr ptr = std::make_shared<key_value_type>(k, v);
            _map.emplace(k, ptr);
            _set.insert(ptr);
        };

        auto it = _map.find(k);
        if (it == _map.end())
        {
            if (_set.size() < _top)
            {
                add();
            }
            else if (_set.size() == _top)
            {
                auto val = v;
                if (val < (*_set.begin())->second)
                    return;

                _map.erase((*_set.begin())->first);
                _set.erase(_set.begin());
                add();
            }
        }
        else
        {
            //不同于下一个insert
            value_type tmp_value = ((*it).second)->second;
            value_type res_value = v + tmp_value;

            _set.erase(it->second);
            _map.erase(it);

            _map.emplace(k, std::make_shared<key_value_type>(k, res_value));
            _set.insert(std::make_shared<key_value_type>(k, res_value));
        }
    }

    //一次游戏的榜单
    void insert(const key_type& k, const value_type& v)
    {
        auto add = [&] {
            key_value_ptr ptr = std::make_shared<key_value_type>(k, v);
            _map.emplace(k, ptr);
            _set.insert(ptr);
        };

        auto it = _map.find(k);
        if (it == _map.end())
        {
            if (_set.size() < _top)
            {
                add();
            }
            else if (_set.size() == _top)
            {
                auto val = v;
                if (val < (*_set.begin())->second)
                    return;

                _map.erase((*_set.begin())->first);
                _set.erase(_set.begin());
                add();
            }
        }
        else
        {
            _set.erase(it->second);
            _map.erase(it);
            add();
        }
    }

    void erase(const key_type& k) {
        auto it = _map.find(k);

        if (it == _map.end())
            return;

        _set.erase(it->second);
        _map.erase(it);
    }

    void clear() {
        _set.clear();
        _map.clear();
    }

    size_type size() { return _set.size(); }

    size_type rank(const key_type& k) {
        auto it = _map.find(k);

        if (it == _map.end() || _set.empty())
            return 0;

        size_type rank = 0;

        for (auto n = _set.rbegin(); n != _set.rend(); ++n) {
            ++rank;
            if ((*n)->first == k)
                return rank;
        }

        return 0;
    }

private:
    size_type _top;
    std::unordered_map<key_type, key_value_ptr> _map;
    std::set<key_value_ptr, key_value_less> _set;
};

struct Rank
{
    int _trophy = 0;
    int _chicken = 0;

    bool operator<(const Rank& r)
    {
        if (_chicken == r._chicken)
            return _trophy > r._trophy;

        return _chicken < r._chicken;
    }

    bool operator==(const Rank& r)
    {
        return _trophy == r._trophy && _chicken == r._chicken;
    }

    //Rank operator+(const Rank& r)
    //{
    //    return Rank(this->_chicken + r._chicken, this->_trophy + r._trophy);
    //}

    friend Rank operator+(const Rank& l, const Rank& r);
    Rank(int chicken, int trophy) :_chicken(chicken), _trophy(trophy) {}
};

Rank operator+(const Rank& l, const Rank& r)
{

    return Rank(l._chicken + r._chicken, l._trophy + r._trophy);
}
#pragma once

#include <vector>
#include <queue>
#include <set>

#include <boost/optional.hpp>

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

template<class T>
using UniquePtr = std::unique_ptr<T>;
template<class T>
using SharedPtr = std::shared_ptr<T>;
template<class T>
using WeakPtr = std::weak_ptr<T>;

template<class T>
using Optional = boost::optional<T>;

template<typename Key, typename Value>
using Map = std::unordered_map<Key, Value>;

template<class Key, class Allocator = std::allocator<Key>>
using Vector = std::vector<Key, Allocator>;
template<typename Key, typename Container = std::deque<Key>>
using Queue = std::queue<Key, Container>;
template<typename Key, typename Pr = std::less<Key>, typename Allocator = std::allocator<Key>>
using Set = std::set<Key, Pr, Allocator>;

using String = std::string;

using hvint8 = int8_t;
using hvint16 = int16_t;
using hvint64 = int64_t;

using hvuint = uint32_t;
using hvuint8 = uint8_t;
using hvuint16 = uint16_t;
using hvuint64 = uint64_t;

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using DurationMS = std::chrono::duration<float, std::milli>;

} // hvgs
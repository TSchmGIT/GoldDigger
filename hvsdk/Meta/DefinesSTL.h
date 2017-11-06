#pragma once

template<typename T>
using UniquePtr = std::unique_ptr<T>;
template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename Key, typename Value>
using Map = boost::unordered_map<Key, Value>;

template<typename Key>
using Vector = std::vector<Key>;

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

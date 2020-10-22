// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <optional>
#include <utility>

// unsure if this is a good idea.
namespace TurtleGraphics {

using string = std::string;

template <typename T>
using vector = std::vector<T>;

template <typename T>
using list = std::list<T>;

template <typename K, typename V>
using map = std::map<K, V>;

template <typename A, typename B>
using pair = std::pair<A, B>;

template <typename Ty>
using optional = std::optional<Ty>;

}  // namespace TurtleGraphics


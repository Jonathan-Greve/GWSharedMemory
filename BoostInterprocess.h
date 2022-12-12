#pragma once
#pragma warning(push)
#pragma warning(disable : 4459)
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#pragma warning(pop)

using namespace boost::interprocess;

// Boost shared memory definitions. https://www.boost.org/doc/libs/1_54_0/doc/html/interprocess/quick_guide.html
// https://www.boost.org/doc/libs/1_54_0/doc/html/interprocess/allocators_containers.html#interprocess.allocators_containers.containers_explained.containers_of_containers

typedef managed_shared_memory::segment_manager segment_manager_t;
typedef allocator<void, segment_manager_t> void_allocator;

// Vector of ints
typedef allocator<int, segment_manager_t> int_allocator;
typedef vector<int, int_allocator> int_vector;

// Vector of vector of ints
typedef allocator<int_vector, segment_manager_t> int_vector_allocator;
typedef vector<int_vector, int_vector_allocator> int_vector_vector;

// String
typedef allocator<char, segment_manager_t> char_allocator;
typedef basic_string<char, std::char_traits<char>, char_allocator> char_string;

// Set of strings
typedef allocator<char_string, segment_manager_t> char_string_allocator;
typedef set<char_string, std::less<char_string>, char_string_allocator> char_string_set;

inline char_string string_to_char_string(std::string string_in, char_allocator char_allocator)
{
    char_string string_out(char_allocator);
    string_out = string_in.c_str();

    return string_out;
}

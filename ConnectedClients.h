#pragma once

class ConnectedClients
{
public:
    // https://www.boost.org/doc/libs/1_54_0/doc/html/interprocess/allocators_containers.html#interprocess.allocators_containers.containers_explained.containers_of_containers
    // void allocator automatically converted to correct allocator.
    ConnectedClients(const void_allocator& void_alloc)
        : m_connected_shared_memory_names(void_alloc)
        , m_char_allocator(void_alloc)
    {
    }
    void connect(std::string shared_memory_name)
    {
        scoped_lock<interprocess_mutex> lock(m_mutex);

        m_connected_shared_memory_names.insert(string_to_char_string(shared_memory_name, m_char_allocator));
    }

    void disconnect(std::string shared_memory_name)
    {
        scoped_lock<interprocess_mutex> lock(m_mutex);

        m_connected_shared_memory_names.erase(string_to_char_string(shared_memory_name, m_char_allocator));
    }

    char_string_set get_connected_shared_memory_names() { return m_connected_shared_memory_names; }

private:
    interprocess_mutex m_mutex;

    char_allocator m_char_allocator;
    char_string_set m_connected_shared_memory_names;
};

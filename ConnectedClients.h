#pragma once
#include <windows.h>
#include "ClientSharedMemory.h"

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
    bool connect(const ClientSharedMemory& client_shared_memory, HANDLE mutex, HANDLE event)
    {
        WaitForSingleObject(mutex, INFINITE);
        m_connected_shared_memory_names.insert(
          string_to_char_string(client_shared_memory.get_sm_name(), m_char_allocator));

        ReleaseMutex(mutex);

        if (! SetEvent(event))
            return false;

        return true;
    }

    bool disconnect(const ClientSharedMemory& client_shared_memory, HANDLE mutex, HANDLE event)
    {
        WaitForSingleObject(mutex, INFINITE);
        m_connected_shared_memory_names.erase(
          string_to_char_string(client_shared_memory.get_sm_name(), m_char_allocator));

        ReleaseMutex(mutex);

        if (! SetEvent(event))
            return false;

        return true;
    }

    char_string_set get_connected_shared_memory_names() { return m_connected_shared_memory_names; }

private:
    char_allocator m_char_allocator;
    char_string_set m_connected_shared_memory_names;
};

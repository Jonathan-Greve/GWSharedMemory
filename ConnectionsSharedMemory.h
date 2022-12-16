#pragma once
#include "windows.h"

class ConnectionsSharedMemory
{
public:
    // Init and return true if succeeded and false otherwise.
    bool init()
    {
        m_connections_managed_shared_memory = managed_shared_memory(open_or_create, "connections", 65536);

        // Get handles to synchronization objects.
        m_mutex_handle = CreateMutex(
          NULL, // default security attributes.
          FALSE, // initially not owned.
          TEXT("connections_sm_mutex")); // named mutex to allow other processes to retrieve handle.

        m_event_handle = CreateEvent(NULL, // default security attributes
                                     TRUE, // manual-reset event
                                     FALSE, // initial state is nonsignaled
                                     TEXT("connections_sm_event") // object name
        );

        return (m_mutex_handle != NULL) && (m_event_handle != NULL);
    }

    ConnectedClients* get_connected_clients()
    {
        if (! m_connected_clients)
        {
            auto connected_clients =
              m_connections_managed_shared_memory.find<ConnectedClients>(unique_instance).first;
            if (! connected_clients)
            {
                void_allocator void_alloc(m_connections_managed_shared_memory.get_segment_manager());
                connected_clients = m_connections_managed_shared_memory.construct<ConnectedClients>(
                  unique_instance)(void_alloc);
            }
            m_connected_clients = connected_clients;
        }

        return m_connected_clients;
    }

    HANDLE get_mutex_handle() { return m_mutex_handle; }
    HANDLE get_event_handle() { return m_event_handle; }

private:
    managed_shared_memory m_connections_managed_shared_memory;
    ConnectedClients* m_connected_clients;

    HANDLE m_mutex_handle;
    HANDLE m_event_handle;
};

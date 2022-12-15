#pragma once

using namespace boost::interprocess;

class SharedMemory
{
public:
    SharedMemory() = default;
    ~SharedMemory()
    {
        shared_memory_object::remove(m_name.c_str());
        if (m_is_initialized)
        {
            auto connected_clients = GetConnectedClientsSM();
            connected_clients->disconnect(m_name);
            //if (connected_clients->get_connected_shared_memory_names().size() == 0)
            //{
            //    m_connections_managed_shared_memory.destroy_ptr(connected_clients);
            //    shared_memory_object::remove(m_connections_shared_memory_name.c_str());
            //}
        }
    }

    void init(std::string shared_memory_name)
    {
        m_name = shared_memory_name;

        shared_memory_object::remove(m_name.c_str());
        m_managed_shared_memory = managed_shared_memory(open_or_create, m_name.c_str(), 65536);

        m_connections_managed_shared_memory =
          managed_shared_memory(open_or_create, m_connections_shared_memory_name.c_str(), 65536);

        void_allocator void_alloc(m_connections_managed_shared_memory.get_segment_manager());

        // Construct shared_memory singleton shared by all connected GW clients. This can be used by external processes for finding the shared memory for each client.
        auto connected_clients = GetConnectedClientsSM();
        connected_clients->connect(m_name);

        m_is_initialized = true;
    }

    managed_shared_memory& get()
    {
        if (! m_is_initialized)
            throw "Not initialized.";

        return m_managed_shared_memory;
    }

private:
    bool m_is_initialized{false};

    std::string m_connections_shared_memory_name = "connections";
    std::string m_name;

    managed_shared_memory m_managed_shared_memory;
    managed_shared_memory m_connections_managed_shared_memory;

    ConnectedClients* GetConnectedClientsSM()
    {
        auto connected_clients =
          m_connections_managed_shared_memory.find<ConnectedClients>(unique_instance).first;
        if (! connected_clients)
        {
            void_allocator void_alloc(m_connections_managed_shared_memory.get_segment_manager());
            connected_clients =
              m_connections_managed_shared_memory.construct<ConnectedClients>(unique_instance)(void_alloc);
        }

        return connected_clients;
    }
};

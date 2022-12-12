#pragma once

using namespace boost::interprocess;

class SharedMemory
{
public:
    SharedMemory() = default;
    ~SharedMemory()
    {
        //shared_memory_object::remove(m_name.c_str());
        void_allocator void_alloc(m_connections_managed_shared_memory.get_segment_manager());
        auto connected_clients =
          m_managed_shared_memory.find_or_construct<ConnectedClients>(unique_instance)(void_alloc);

        connected_clients->disconnect(m_name);
    }

    void init(std::string shared_memory_name)
    {
        m_name = shared_memory_name;

        shared_memory_object::remove(m_name.c_str());
        m_managed_shared_memory = managed_shared_memory(open_or_create, m_name.c_str(), 65536);

        m_connections_managed_shared_memory = managed_shared_memory(open_or_create, "connections", 65536);
        void_allocator void_alloc(m_connections_managed_shared_memory.get_segment_manager());

        // Construct shared_memory singleton shared by all connected GW clients. This can be used by external processes for finding the shared memory for each client.
        auto connected_clients = m_connections_managed_shared_memory.find_or_construct<ConnectedClients>(
          unique_instance)(void_alloc);
        connected_clients->connect(m_name);
    }

    managed_shared_memory& get() { return m_managed_shared_memory; }

private:
    std::string m_name;
    managed_shared_memory m_managed_shared_memory;
    managed_shared_memory m_connections_managed_shared_memory;
};

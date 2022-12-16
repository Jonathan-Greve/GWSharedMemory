#pragma once

class ClientSharedMemory
{
public:
    ~ClientSharedMemory() { shared_memory_object::remove(m_client_shared_memory_name.c_str()); }

    bool init(std::string client_shared_memory_name)
    {
        m_client_shared_memory_name = client_shared_memory_name;

        shared_memory_object::remove(m_client_shared_memory_name.c_str());
        m_client_managed_shared_memory =
          managed_shared_memory(open_or_create, m_client_shared_memory_name.c_str(), 65536);

        return true;
    }

    managed_shared_memory& get() { return m_client_managed_shared_memory; }

    // Get shared memory name;
    const std::string& get_sm_name() const { return m_client_shared_memory_name; }

private:
    std::string m_client_shared_memory_name;

    managed_shared_memory m_client_managed_shared_memory;
};

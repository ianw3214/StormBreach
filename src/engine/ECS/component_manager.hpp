#pragma once

#include <vector>

template<typename T>
class ComponentManager {

public:

    ComponentManager() {
        m_ids.reserve(30);
        m_components.reserve(30);
    }
    ~ComponentManager() {
        // Do nothing...
    }

    std::vector<T>& getComponents() {
        return m_components;
    }
    Reference<T> addComponent(unsigned int id, T data) {
        // Direct insert should be fine, since most inserts should have larger IDs
        unsigned int insert_index = m_ids.size();
        while(insert_index > 0) {
            if (m_ids[insert_index - 1] > id) {
                insert_index--;
            } else {
                break;
            }
        }
        // At this point, insert_index is the index that the new element should be inserted into
        if (insert_index > m_ids.size() - 1) {
            m_ids.push_back(insert_index);
            m_components.push_back(data);
        } else {
            m_ids.insert(m_ids.begin() + insert_index, id);
            m_components.insert(m_components.begin() + insert_index, data);
        }
        return Reference<T>(&m_components[insert_index]);
    }
    Reference<T> getComponent(unsigned int id) {
        // Do a binary search on m_ids to find the right component
        int mid, low=0, high = m_ids.size() - 1;
        int result = -1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (m_ids[mid] > id)
                high = mid -1;
            else if (m_ids[mid] < id)
                low = mid + 1;
            else {
                result = mid;
                break;
            }
        }
        if (result < 0) {
            return nullptr;
        }
        return Reference<T>(&m_components[result]);
    }

    const std::vector<unsigned int>& getIds() { return m_ids; }

private:

    std::vector<unsigned int> m_ids;
    std::vector<T> m_components;

};
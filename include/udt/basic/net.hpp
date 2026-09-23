#include "cfrost/types.h"

template <typename T>
class net
{
private:
    struct node
    {
        ocf::str name;
        T element;
        ocf::hash_map<ocf::str, node> neighbors;
    };

    size_t number_of_node = 1;
    node current;

protected:
    void clear(node root)
    {
        for (auto neighbor : root.neighbors)
        {
            root.name.clear();
            clear(neighbor.second);
            root.neighbors.clear();
        }
    }

public:
    net(const ocf::str &n) : current.name(n) {}
    net(const ocf::str &n, const T &e) : current.name(n), current.element(e) {}
    net(const net &other) : current(other.current), number_of_node(other.number_of_node) {}
    ~net() { clear(); };

    void move(const ocf::str &name)
    {
        if (current.neighbors.contains(name))
        {
            current = current.neighbors[name];
        }
    }

    void add_net(const ocf::str &name)
    {
        if (current.neighbors.contains(name))
            return;
        number_of_node++;
        current.neighbors[name] = node(name);
        current.neighbors[name].add_net(current.name);
    }

    void remove_net(const ocf::str &name)
    {
        if (!current.neighbors.contains(name))
            return;
        current.neighbors.erase(name);
        number_of_node--;
    }

    void clear() { clear(current); }

    ocf::vec<ocf::str> list_neighbors()
    {
        ocf::vec<ocf::str> result;
        for (auto neighbor : current.neighbors)
        {
            result.push_back(neighbor.first);
        }
        return result;
    }

    void show()
    {
        std::cout << "Current node: " << current.name << std::endl;
        std::cout << "Neighbors: ";
        for (auto neighbor : current.neighbors)
        {
            std::cout << neighbor.first << " ";
        }
        std::cout << std::endl;
    }

    T get_element() { return current.element; }

    ocf::hash_map<ocf::str, T> get_neighbors_elements()
    {
        ocf::hash_map<ocf::str, T> result;
        for (auto neighbor : current.neighbors)
        {
            result[neighbor.first] = neighbor.second.element;
        }
        return result;
    }

    void operator=(const net &other)
    {
        if (this != &other)
        {
            clear();
            current = other.current;
            number_of_node = other.number_of_node;
        }
    }

    void operator=(const T &element)
    {
        current.element = element;
    }

    void operator+=(const T &element)
    {
        current.element += element;
    }

    void operator-=(const T &element)
    {
        current.element -= element;
    }

    void operator*=(const T &element)
    {
        current.element *= element;
    }

    void operator/=(const T &element)
    {
        current.element /= element;
    }

    void operator%=(const T &element)
    {
        current.element %= element;
    }

    void operator&=(const T &element)
    {
        current.element &= element;
    }

    void operator|=(const T &element)
    {
        current.element |= element;
    }

    void operator^=(const T &element)
    {
        current.element ^= element;
    }

    void operator++()
    {
        ++current.element;
    }

    void operator--()
    {
        --current.element;
    }

    T operator+(const T &element)
    {
        return current.element + element;
    }

    T operator-(const T &element)
    {
        return current.element - element;
    }

    T operator*(const T &element)
    {
        return current.element * element;
    }

    T operator/(const T &element)
    {
        return current.element / element;
    }

    T operator%(const T &element)
    {
        return current.element % element;
    }

    T operator&(const T &element)
    {
        return current.element & element;
    }

    T operator|(const T &element)
    {
        return current.element | element;
    }

    T operator^(const T &element)
    {
        return current.element ^ element;
    }
};
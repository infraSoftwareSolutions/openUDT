/**
 * @file net.hpp
 * @brief Defines a templated network of named nodes holding values of type T.
 *
 * A net tracks a current node and its named neighbors. The template is declared
 * at global scope; unlike most openUDT types, it is not in namespace `udt`.
 */
#include "cfrost/types.h"
#pragma once
/**
 * @brief A named-node network whose nodes hold values of type T.
 * @tparam T Type stored at each node. Arithmetic operators require the
 * corresponding operation to be supported by T.
 *
 * The public operations act on the current node. Use `move` to select one of
 * its neighbors before querying or changing that node's value.
 */
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
    /// @brief Creates a network with a current node named @p n.
    /// @param n Name assigned to the initial node.
    net(const ocf::str &n) : current.name(n) {}

    /// @brief Creates a network with a named current node and initial value.
    /// @param n Name assigned to the initial node.
    /// @param e Value stored at the initial node.
    net(const ocf::str &n, const T &e) : current.name(n), current.element(e) {}

    /// @brief Creates a copy of another network.
    /// @param other Network to copy.
    net(const net &other) : current(other.current), number_of_node(other.number_of_node) {}

    /// @brief Destroys the network and clears its current node.
    ~net() { clear(); };

    /// @brief Moves to a neighbor of the current node when it exists.
    /// @param name Name of the neighbor to select.
    /// @note If no neighbor with this name exists, the current node is unchanged.
    void move(const ocf::str &name)
    {
        if (current.neighbors.contains(name))
        {
            current = current.neighbors[name];
        }
    }

    /// @brief Adds a neighbor with the given name to the current node.
    /// @param name Name of the node to add.
    /// @note Adding a neighbor whose name is already present has no effect.
    void add_net(const ocf::str &name)
    {
        if (current.neighbors.contains(name))
            return;
        number_of_node++;
        current.neighbors[name] = node(name);
        current.neighbors[name].add_net(current.name);
    }

    /// @brief Removes a named neighbor from the current node when present.
    /// @param name Name of the neighbor to remove.
    void remove_net(const ocf::str &name)
    {
        if (!current.neighbors.contains(name))
            return;
        current.neighbors.erase(name);
        number_of_node--;
    }

    /// @brief Clears the network starting from the current node.
    void clear() { clear(current); }

    /// @brief Returns the names of the current node's neighbors.
    /// @return A vector containing the neighbor names.
    ocf::vec<ocf::str> list_neighbors()
    {
        ocf::vec<ocf::str> result;
        for (auto neighbor : current.neighbors)
        {
            result.push_back(neighbor.first);
        }
        return result;
    }

    /// @brief Writes the current node name and its neighbors to standard output.
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

    /// @brief Gets the value stored at the current node.
    /// @return A copy of the current node's value.
    T get_element() { return current.element; }

    /// @brief Gets the values stored at the current node's neighbors.
    /// @return A map from each neighbor name to its stored value.
    ocf::hash_map<ocf::str, T> get_neighbors_elements()
    {
        ocf::hash_map<ocf::str, T> result;
        for (auto neighbor : current.neighbors)
        {
            result[neighbor.first] = neighbor.second.element;
        }
        return result;
    }

    /// @brief Replaces this network's state with a copy of another network.
    /// @param other Network whose state is copied.
    void operator=(const net &other)
    {
        if (this != &other)
        {
            clear();
            current = other.current;
            number_of_node = other.number_of_node;
        }
    }

    /// @brief Replaces the current node's value.
    /// @param element Value to assign.
    void operator=(const T &element)
    {
        current.element = element;
    }

    /// @brief Adds a value to the current node's value.
    /// @param element Value to add.
    void operator+=(const T &element)
    {
        current.element += element;
    }

    /// @brief Subtracts a value from the current node's value.
    /// @param element Value to subtract.
    void operator-=(const T &element)
    {
        current.element -= element;
    }

    /// @brief Multiplies the current node's value by a value.
    /// @param element Value to multiply by.
    void operator*=(const T &element)
    {
        current.element *= element;
    }

    /// @brief Divides the current node's value by a value.
    /// @param element Divisor.
    void operator/=(const T &element)
    {
        current.element /= element;
    }

    /// @brief Applies the modulo assignment operation to the current value.
    /// @param element Modulo operand.
    void operator%=(const T &element)
    {
        current.element %= element;
    }

    /// @brief Applies the bitwise AND assignment operation to the current value.
    /// @param element Bitwise operand.
    void operator&=(const T &element)
    {
        current.element &= element;
    }

    /// @brief Applies the bitwise OR assignment operation to the current value.
    /// @param element Bitwise operand.
    void operator|=(const T &element)
    {
        current.element |= element;
    }

    /// @brief Applies the bitwise XOR assignment operation to the current value.
    /// @param element Bitwise operand.
    void operator^=(const T &element)
    {
        current.element ^= element;
    }

    /// @brief Increments the current node's value.
    void operator++()
    {
        ++current.element;
    }

    /// @brief Decrements the current node's value.
    void operator--()
    {
        --current.element;
    }

    /// @brief Adds a value to the current value and returns the result.
    /// @param element Value to add.
    /// @return The sum.
    T operator+(const T &element)
    {
        return current.element + element;
    }

    /// @brief Subtracts a value from the current value and returns the result.
    /// @param element Value to subtract.
    /// @return The difference.
    T operator-(const T &element)
    {
        return current.element - element;
    }

    /// @brief Multiplies the current value by a value and returns the result.
    /// @param element Value to multiply by.
    /// @return The product.
    T operator*(const T &element)
    {
        return current.element * element;
    }

    /// @brief Divides the current value by a value and returns the result.
    /// @param element Divisor.
    /// @return The quotient.
    T operator/(const T &element)
    {
        return current.element / element;
    }

    /// @brief Applies modulo to the current value and returns the result.
    /// @param element Modulo operand.
    /// @return The remainder.
    T operator%(const T &element)
    {
        return current.element % element;
    }

    /// @brief Applies bitwise AND to the current value and returns the result.
    /// @param element Bitwise operand.
    /// @return The bitwise AND result.
    T operator&(const T &element)
    {
        return current.element & element;
    }

    /// @brief Applies bitwise OR to the current value and returns the result.
    /// @param element Bitwise operand.
    /// @return The bitwise OR result.
    T operator|(const T &element)
    {
        return current.element | element;
    }

    /// @brief Applies bitwise XOR to the current value and returns the result.
    /// @param element Bitwise operand.
    /// @return The bitwise XOR result.
    T operator^(const T &element)
    {
        return current.element ^ element;
    }
};
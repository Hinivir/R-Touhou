/*
** EPITECH PROJECT, 2023
** R-Touhou_Bootstrap
** File description:
** SparseArray.hpp
*/

#ifndef SPARSE_ARRAY_H_
#define SPARSE_ARRAY_H_

#include <memory>
#include <optional>
#include <vector>

/// @brief Array which can have empty slots
/// @tparam Component Type of the component to store
template <typename Component>

class SparseArray
{
  public:
    /// @brief Type of the value stored in the array
    using ValueType = std::optional<Component>;
    /// @brief Type of the reference to the value stored in the array
    using ReferenceType = ValueType &;
    /// @brief Type of the const reference to the value stored in the array
    using ConstReferenceType = ValueType const &;
    /// @brief Type of the container used to store the values
    using ContainerType = std::vector<ValueType>;

    /// @brief Type of the size of the array
    using SizeType = typename ContainerType::size_type;

    /// @brief Type of the iterator of the array
    using Iterator = typename ContainerType::iterator;
    /// @brief Type of the const iterator of the array
    using ConstIterator = typename ContainerType::const_iterator;

    /// @brief Default constructor
    SparseArray(){};

    /// @brief Constructor
    /// @param sparseArray Sparse array to copy
    SparseArray(SparseArray const &sparseArray) : _data(sparseArray._data){};

    /// @brief Default destructor
    ~SparseArray() = default;

    /// @brief Copy assignment operator
    /// @param sparseArray Sparse array to copy
    /// @return A reference to the sparse array
    SparseArray &operator=(SparseArray const &data)
    {
        _data = data._data;
        return *this;
    };
    /// @brief Move assignment operator
    /// @param sparseArray Sparse array to move
    /// @return A reference to the sparse array
    SparseArray &operator=(SparseArray &&data) noexcept
    {
        _data = data._data;
        return *this;
    };

    /// @brief Overload for the [] operator
    /// @param idx Index of the value to get
    /// @return A reference to the value at the given index
    ReferenceType operator[](SizeType idx) { return _data[idx]; };
    /// @brief Overload for the [] operator
    /// @param idx Index of the value to get
    /// @return A const reference to the value at the given index
    ConstReferenceType operator[](SizeType idx) const { return _data[idx]; };

    /// @brief Get the beginning of the array
    /// @return An iterator to the beginning of the array
    Iterator begin() { return _data.begin(); };
    /// @brief Get the beginning of the array
    /// @return A const iterator to the beginning of the array
    ConstIterator begin() const { return _data.begin(); };
    /// @brief Get the beginning of the array
    /// @return A const iterator to the beginning of the array
    ConstIterator cbegin() const { return _data.cbegin(); };

    /// @brief Get the end of the array
    /// @return An iterator to the end of the array
    Iterator end() { return _data.end(); };
    /// @brief Get the end of the array
    /// @return A const iterator to the end of the array
    ConstIterator end() const { return _data.end(); };
    /// @brief Get the end of the array
    /// @return A const iterator to the end of the array
    ConstIterator cend() const { return _data.cend(); };

    /// @brief Get the size of the array
    /// @return The size of the array
    SizeType size() const { return _data.size(); };

    /// @brief Insert a copy of the given value at the given position
    /// @param pos Position to insert the value
    /// @param comp Copy of the Component to insert
    /// @return A reference to the newly inserted value
    ReferenceType insertAt(SizeType pos, Component const &comp)
    {
        if (_data.size() < pos + 1)
            _data.resize(pos + 1);
        _data[pos] = comp;
        return _data[pos];
    };
    /// @brief Insert the component at the given position
    /// @param pos Position to insert the value
    /// @param comp Component to insert
    /// @return A reference to the newly inserted value
    ReferenceType insertAt(SizeType pos, Component &&comp)
    {
        if (_data.size() < pos + 1)
            _data.resize(pos + 1);
        _data[pos] = comp;
        return _data[pos];
    };

    /// @brief Creates the component at the specified position.
    /// @param pos Position to create the component at.
    /// @return A reference to the created component.
    ReferenceType emplaceAt(SizeType pos)
    {
        auto &ret = insertAt(pos, Component());
        return ret;
    };

    /// @brief Creates the component at the specified position.
    /// @tparam Params Types of the parameters to pass to the constructor.
    /// @param pos Position to create the component at.
    /// @param ...params Variadic parameters of the position to insert at.
    /// @return A reference to the created component.
    template <class... Params>
    ReferenceType emplaceAt(SizeType pos, Params &&...params)
    {
        auto &ret = insertAt(pos, Component());

        emplaceAt(params...);
        return ret;
    };

    /// @brief Erase the value at the given position
    /// @param pos Position to erase the value
    void erase(SizeType pos)
    {
        if (_data.size() > pos && _data[pos].has_value())
            _data[pos].reset();
    };

    /// @brief Get the index of the given value
    /// @param val Value to get the index of
    /// @return The index of the given value
    SizeType getIndex(ValueType const &val) const
    {
        for (SizeType pos = 0; pos < _data.size(); pos++)
            if (std::addressof(_data[pos]) == std::addressof(val))
                return pos;
    };

    /// @brief Resize the array
    /// @param size New size of the array
    void resize(SizeType &size) { _data.resize(size); };

  private:
    /// @brief Container used to store the values
    ContainerType _data;
};

#endif // SPARSE_ARRAY_H_

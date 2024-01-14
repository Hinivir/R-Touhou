.. _sparse_array_class:

SparseArray Class
================

Overview
--------

The ``SparseArray`` class in the R-Touhou_Bootstrap project is designed to represent an array that can have empty slots. It is a templated class, allowing storage of components of any type.

Usage
-----

The ``SparseArray`` class can be used to manage arrays with potential empty slots, and it provides functionalities for inserting, erasing, and retrieving values. The class is particularly useful in ECS (Entity-Component-System) architectures.

Table of Contents
-----------------

1. :ref:`sparse_array_how_to_use`
2. :ref:`sparse_array_explanation`

How to Use the SparseArray Class
------------------------------

Before using the ``SparseArray`` class, ensure that you have a basic understanding of the ECS architecture and its components.

1. Instantiate the ``SparseArray`` class with the desired component type.
2. Use the provided methods to manipulate the array, such as insertion, erasure, and retrieval.

Example:

.. code-block:: cpp

   SparseArray<int> sparseIntArray;
   sparseIntArray.insertAt(0, 42);

Explanation of the SparseArray Class
------------------------------------

The ``SparseArray`` class consists of the following components:

1. **Type Definitions**

   - ``ValueType``: Type of the value stored in the array (``std::optional<Component>``).
   - ``ReferenceType``: Type of the reference to the value stored in the array.
   - ``ConstReferenceType``: Type of the const reference to the value stored in the array.
   - ``ContainerType``: Type of the container used to store the values (``std::vector<ValueType>``).
   - ``SizeType``: Type of the size of the array (``typename ContainerType::size_type``).
   - ``Iterator``: Type of the iterator of the array (``typename ContainerType::iterator``).
   - ``ConstIterator``: Type of the const iterator of the array (``typename ContainerType::const_iterator``).

2. **Default Constructor**

   The default constructor initializes an empty ``SparseArray``.

   Example:

   .. code-block:: cpp

      SparseArray(){};

3. **Copy Constructor**

   The copy constructor creates a new ``SparseArray`` by copying the content of another ``SparseArray``.

   Example:

   .. code-block:: cpp

      SparseArray(SparseArray const &sparseArray) : _data(sparseArray._data){};

4. **Destructor**

   The default destructor cleans up resources associated with the ``SparseArray``.

   Example:

   .. code-block:: cpp

      ~SparseArray() = default;

5. **Copy Assignment Operator**

   The copy assignment operator assigns the content of another ``SparseArray`` to the current one.

   Example:

   .. code-block:: cpp

      SparseArray &operator=(SparseArray const &data)
      {
          _data = data._data;
          return *this;
      };

6. **Move Assignment Operator**

   The move assignment operator assigns the content of another ``SparseArray`` through a move operation.

   Example:

   .. code-block:: cpp

      SparseArray &operator=(SparseArray &&data) noexcept
      {
          _data = data._data;
          return *this;
      };

7. **Overload for the [] Operator**

   The ``operator[]`` overloads allow accessing values at specific indices in the array.

   Example:

   .. code-block:: cpp

      ReferenceType operator[](SizeType idx) { return _data[idx]; };
      ConstReferenceType operator[](SizeType idx) const { return _data[idx]; };

8. **Iterators**

   The class provides methods to obtain iterators for traversing the array.

   Example:

   .. code-block:: cpp

      Iterator begin() { return _data.begin(); };
      ConstIterator begin() const { return _data.begin(); };
      ConstIterator cbegin() const { return _data.cbegin(); };
      Iterator end() { return _data.end(); };
      ConstIterator end() const { return _data.end(); };
      ConstIterator cend() const { return _data.cend(); };

9. **Size Method**

   The ``size()`` method returns the size of the array.

   Example:

   .. code-block:: cpp

      SizeType size() const { return _data.size(); };

10. **Insertion Methods**

   - ``insertAt(SizeType pos, Component const &comp)``: Inserts a copy of the given value at the specified position.
   - ``insertAt(SizeType pos, Component &&comp)``: Inserts the component at the specified position.
   - ``emplaceAt(SizeType pos)``: Creates the component at the specified position.
   - ``emplaceAt(SizeType pos, Params &&...params)``: Creates the component at the specified position with additional parameters.

   Examples:

   .. code-block:: cpp

      ReferenceType insertAt(SizeType pos, Component const &comp);
      ReferenceType insertAt(SizeType pos, Component &&comp);
      ReferenceType emplaceAt(SizeType pos);
      ReferenceType emplaceAt(SizeType pos, Params &&...params);

11. **Erasure Method**

   The ``erase(SizeType pos)`` method erases the value at the specified position.

   Example:

   .. code-block:: cpp

      void erase(SizeType pos);

12. **Index Retrieval Method**

   The ``getIndex(ValueType const &val)`` method returns the index of the given value.

   Example:

   .. code-block:: cpp

      SizeType getIndex(ValueType const &val) const;

13. **Resize Method**

   The ``resize(SizeType &size)`` method resizes the array.

   Example:

   .. code-block:: cpp

      void resize(SizeType &size);

Private Member
--------------

- ``_data``: Container used to store the values.

   Example:

   .. code-block:: cpp

      ContainerType _data;

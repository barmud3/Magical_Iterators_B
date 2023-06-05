#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

namespace ariel {};

class MagicalContainer {
private:
    vector<int*> magicCon;          // Vector to store elements
    vector<int*> sortMagicCon;      // Vector to store sorted elements
    vector<int*> primeMagicCon;     // Vector to store prime elements

public:
    // Default constructor
    MagicalContainer() {}

    // Copy constructor
    MagicalContainer(const MagicalContainer& other)
        : magicCon(other.magicCon), sortMagicCon(other.sortMagicCon), primeMagicCon(other.primeMagicCon) {}

    // Destructor
    ~MagicalContainer();

    // Move constructor
    MagicalContainer(MagicalContainer&& other) noexcept
        : magicCon(std::move(other.magicCon)),
          sortMagicCon(std::move(other.sortMagicCon)),
          primeMagicCon(std::move(other.primeMagicCon)) {}

    // Move assignment operator
    MagicalContainer& operator=(MagicalContainer&& other) noexcept;

    // Assignment operator
    MagicalContainer& operator=(const MagicalContainer& other);

    // Add an element to the container
    void addElement(int element);

    // Add an element to the sorted container
    void addElementSort(int* element);

    // Add an element to the prime container
    void addElementPrime(int* element);

    // Check if an element is prime
    static bool isPrime(int* element);

    // Remove an element from the container
    void removeElement(int element);

    // Get the size of the container
    std::vector<int>::size_type size() const {
        return magicCon.size();
    }

    // Iterator for ascending order traversal
    class AscendingIterator {
    private:
        MagicalContainer* myContainer;
        int index;

    public:
        AscendingIterator(MagicalContainer& container)
            : myContainer(&container), index(0) {}

        AscendingIterator(MagicalContainer& container, int index)
            : myContainer(&container), index(index) {}

        int operator*();

        // Pre-increment operator
        AscendingIterator& operator++();

        // Post-increment operator
        AscendingIterator operator++(int);

        bool operator==(const AscendingIterator& rhs) const;

        bool operator!=(const AscendingIterator& rhs) const;

        AscendingIterator& operator=(const AscendingIterator& rhs);

        bool operator>(const AscendingIterator& rhs) const;

        bool operator<(const AscendingIterator& rhs) const;

        // Iterator points to the beginning of the container
        AscendingIterator begin();

        // Iterator points to the end of the container
        AscendingIterator end();
    };

    // Iterator for side cross traversal
    class SideCrossIterator {
    private:
        const MagicalContainer* container;
        int index;

    public:
        SideCrossIterator(const MagicalContainer& container)
            : container(&container), index(0) {}

        SideCrossIterator(const MagicalContainer& container, int index)
            : container(&container), index(index) {}

        int operator*() const;

        // Pre-increment operator
        SideCrossIterator& operator++();

        // Post-increment operator
        SideCrossIterator operator++(int);

        bool operator==(const SideCrossIterator& rhs) const;

        bool operator!=(const SideCrossIterator& rhs) const;

        SideCrossIterator& operator=(const SideCrossIterator& rhs);

        bool operator>(const SideCrossIterator& rhs) const;

        bool operator<(const SideCrossIterator& rhs) const;

        // Iterator points to the beginning of the container
        SideCrossIterator begin();

        // Iterator points to the end of the container
        SideCrossIterator end();
    };

    // Iterator for prime traversal
    class PrimeIterator {
    private:
        const MagicalContainer* container;
        int index;

    public:
        PrimeIterator(const MagicalContainer& container)
            : container(&container), index(0) {}

        PrimeIterator(const MagicalContainer& container, int index)
            : container(&container), index(index) {}

        int operator*() const;

        // Pre-increment operator
        PrimeIterator& operator++();

        // Post-increment operator
        PrimeIterator operator++(int);

        bool operator==(const PrimeIterator& rhs) const;

        bool operator!=(const PrimeIterator& rhs) const;

        PrimeIterator& operator=(const PrimeIterator& rhs);

        bool operator>(const PrimeIterator& rhs) const;

        bool operator<(const PrimeIterator& rhs) const;

        // Iterator points to the beginning of the container
        PrimeIterator begin();

        // Iterator points to the end of the container
        PrimeIterator end();
    };
};

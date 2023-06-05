#include "MagicalContainer.hpp"


//~~MagicalContainer~~ : 

        MagicalContainer::~MagicalContainer(){
            for (int* element : magicCon) 
            {
                delete element;
            }
        }

        // Move assignment operator for MagicalContainer
        MagicalContainer& MagicalContainer::operator=(MagicalContainer&& other) noexcept{
            if (this != &other) {
                magicCon = std::move(other.magicCon);
                sortMagicCon = std::move(other.sortMagicCon);
                primeMagicCon = std::move(other.primeMagicCon);
            }
            return *this;
        }

        MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other) {
                if (this != &other) {
                    magicCon = other.magicCon;
                    sortMagicCon = other.sortMagicCon;
                    primeMagicCon = other.primeMagicCon;
                }
                return *this;
         }

        // Add an element to the container
        void MagicalContainer::addElement(int element) {
                int* elementPointer = new int(element);
                magicCon.emplace_back(elementPointer);
                addElementSort(elementPointer);
                addElementPrime(elementPointer);
        }

        // Add an element to the sorted container
        void MagicalContainer::addElementSort(int* element)
            {
                auto insertPosition = sortMagicCon.begin();
                while (insertPosition != sortMagicCon.end() && *(*insertPosition) < *element)
                {
                    insertPosition++;
                }
                sortMagicCon.insert(insertPosition, element);
            }

        // Add an element to the prime container if it is prime
        void MagicalContainer::addElementPrime(int* element)
        {
            if (isPrime(element))
            {
                auto insertPosition = primeMagicCon.begin();
                while (insertPosition != primeMagicCon.end() && *(*insertPosition) < *element)
                {
                    insertPosition++;
                }
                primeMagicCon.insert(insertPosition, element);
            }
        }

        // Check if an element is prime
        bool MagicalContainer::isPrime(int* element)
        {
            if (*element <= 1)
            {
                return false;
            }
            for (int i = 2; i <= sqrt(*element); i++)
            {
                if(*element % i == 0)
                {
                    return false;
                }
            }
            return true;
        }

        // Remove an element from the container
        void MagicalContainer::removeElement(int element) { 
            int* myPointerElement = nullptr;
                for(int* pointer : this->magicCon)
                {
                    if (*pointer == element)
                    {
                        myPointerElement = pointer;
                    }
                }
                if (myPointerElement == nullptr)
                {
                    throw std::runtime_error("Element not found in MagicalContainer");
                    return;
                }
                auto iterator = std::find(magicCon.begin(), magicCon.end(), myPointerElement);
                magicCon.erase(iterator);
        }

//~~AscendingIterator~~ :

        // Dereference operator to get the value at the current iterator position
        int MagicalContainer::AscendingIterator::operator*(){
            return *(myContainer->sortMagicCon[static_cast<size_t>(index)]);
        }

        // Pre-increment operator to move the iterator to the next position
        MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
            if (this->index == static_cast<int>(this->myContainer->sortMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
        	++ this->index;
            return *this;
        }

        // Post-increment operator to move the iterator to the next position
        MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::operator++(int) {
            if (this->index == static_cast<int>(this->myContainer->sortMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
            AscendingIterator temp = *this;
        	this->index++;
            return temp;
        }

        // Equality comparison operator to check if two iterators are equal
        bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator&  rhs) const {
            if (this->myContainer!= rhs.myContainer)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
        	return (this->index == rhs.index);
        }

        // Inequality comparison operator to check if two iterators are not equal
        bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& rhs) const {
        	return !(*this == rhs);
        }

        // Assignment operator for AscendingIterator
        MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator&  rhs) {
            if (this->myContainer!= rhs.myContainer)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
            if (this == &rhs) {
                return *this;
            }
            // Copy the member variables from rhs to this object
            myContainer = rhs.myContainer;
            index = rhs.index;
            return *this;
        }

        // Greater than comparison operator to check if one iterator is greater than the other
        bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& rhs) const {
        	return this->index > rhs.index;
        }

        // Less than comparison operator to check if one iterator is less than the other
        bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& rhs) const {
        	return this->index < rhs.index;
        }

        // Get an iterator pointing to the beginning of the container
        MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
        {
            return AscendingIterator(*myContainer);
        }

        // Get an iterator pointing to the end of the container
        MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
        {
            return AscendingIterator{*myContainer, static_cast<int>(myContainer->sortMagicCon.size())};
        }


//~~SideCrossIterator~~ :

        // Dereference operator to get the value at the current iterator position
        int MagicalContainer::SideCrossIterator::operator*() const{

			if (this->index%2 == 0) // cross side will be left
            {
                return *(*container).magicCon[static_cast<size_t>(this->index/2)]; 
            }
            // cross side will be right
            size_t disFromEnd = static_cast<size_t>((*container).size() -1 - static_cast<size_t>(this->index/2));
            return *(*container).magicCon[disFromEnd];
        }

        // Pre-increment operator to move the iterator to the next position
        MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
            if (this->index == static_cast<int>(this->container->magicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
			++ this->index;
            return *this;
        }

        // Post-increment operator to move the iterator to the next position
        MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::operator++(int) {
            if (this->index == static_cast<int>(this->container->magicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
			SideCrossIterator temp = *this;
            this->index++;
            return temp;
        }

        // Equality comparison operator to check if two iterators are equal
        bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator&  rhs) const {
            if (this->container!= rhs.container)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
			return (this->index == rhs.index);
        }
    
        bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& rhs) const {
        	return !(*this == rhs);
        }

        // Assignment operator for SideCrossIterator
        MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator&  rhs) {
            if (this->container!= rhs.container)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
            if (this == &rhs) {
                return *this;
            }
            // Copy the member variables from rhs to this object
            container = rhs.container;
            index = rhs.index;
            return *this;
        }
    
        bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& rhs) const {
        	return this->index > rhs.index;
        }
    
        bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& rhs) const {
        	return this->index < rhs.index;
        }
    
        MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
        {
            return SideCrossIterator{*container};
        }
    
        MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
        {
            return SideCrossIterator{*container, static_cast<int>(container->magicCon.size())};
        }



//~~PrimeIterator~~ :

        // Dereference operator to get the value at the current iterator position
        int MagicalContainer::PrimeIterator::operator*() const{
            return *(container->primeMagicCon[static_cast<size_t>(index)]);
        }

        // Pre-increment operator to move the iterator to the next position
        MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
            if (this->index == static_cast<int>(this->container->primeMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
            ++ this->index;
            return *this;
        }

        // Post-increment operator to move the iterator to the next position
        MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++(int) {
            if (this->index == static_cast<int>(this->container->primeMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
            PrimeIterator temp = *this;
			this->index++;
            return temp;
        }

        // Equality comparison operator to check if two iterators are equal
        bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator&  rhs) const {
            if (this->container!= rhs.container)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
			return (this->index == rhs.index);
        }

        // Inequality comparison operator to check if two iterators are not equal
        bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& rhs) const {
        	return !(*this == rhs);
        }

        MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator&  rhs) {
            if (this->container!= rhs.container)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
            if (this == &rhs) {
                return *this;
            }
            // Copy the member variables from rhs to this object
            container = rhs.container;
            index = rhs.index;
            return *this;
        }

        bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& rhs) const {
        	return this->index > rhs.index;
        }

        bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& rhs) const {
        	return this->index < rhs.index;
        }

        MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
        {
            return PrimeIterator{*container};
        }

        MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
        {
            return PrimeIterator{*container ,static_cast<int>((*container).primeMagicCon.size())};
        }
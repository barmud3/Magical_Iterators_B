#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
namespace ariel{};


class MagicalContainer{
private:
    vector<int> magicCon;
    vector<int> sortMagicCon;
    vector<int> primeMagicCon;
public:

    // Default constructor
    MagicalContainer() {}


    // Copy constructor
    MagicalContainer(const MagicalContainer& other) : magicCon(other.magicCon) , sortMagicCon(other.sortMagicCon) , primeMagicCon(other.primeMagicCon){
    }

    // Destructor
    ~MagicalContainer() {}
    
    // Move constructor
    MagicalContainer(MagicalContainer&& other) noexcept
    : magicCon(std::move(other.magicCon)),
        sortMagicCon(std::move(other.sortMagicCon)),
        primeMagicCon(std::move(other.primeMagicCon)) {}

    // Move assignment operator
    MagicalContainer& operator=(MagicalContainer&& other) noexcept {
        if (this != &other) {
            magicCon = std::move(other.magicCon);
            sortMagicCon = std::move(other.sortMagicCon);
            primeMagicCon = std::move(other.primeMagicCon);
        }
        return *this;
    }
    // Assignment operator
    MagicalContainer& operator=(const MagicalContainer& other) {
        if (this != &other) {
            magicCon = other.magicCon;
            sortMagicCon = other.sortMagicCon;
            primeMagicCon = other.primeMagicCon;
        }
        return *this;
    }

    void addElement(int element) {
        magicCon.emplace_back(element);
        addElementSort(element);
        addElementPrime(element);
    }

    void addElementSort(int element)
    {
        auto insertPosition = lower_bound(sortMagicCon.begin(), sortMagicCon.end(), element);
        sortMagicCon.emplace(insertPosition, element);
    }

    void addElementPrime(int element)
    {
        if (isPrime(element))
        {
            auto insertPosition = lower_bound(primeMagicCon.begin(), primeMagicCon.end(), element);
            primeMagicCon.emplace(insertPosition, element);
        }
    }

    static bool isPrime(int element)
    {
        if (element <= 1)
        {
            return false;
        }
        
        for (int i = 2; i <= sqrt(element); i++)
        {
            if(element % i == 0)
            {
                return false;
            }
        }
        return true;
        
    }

    void removeElement(int element) {
        
        auto iterator = std::find(magicCon.begin(), magicCon.end(), element);
        if (iterator == magicCon.end()) {
            throw std::runtime_error("Element not found in MagicalContainer");
        }
        magicCon.erase(iterator);
    }

    std::vector<int>::size_type size() const {
    return magicCon.size();
    }

    class AscendingIterator  {

	    private:
        MagicalContainer* myContainer;
        int index;

	    public:

		AscendingIterator (MagicalContainer& container)
			: myContainer(&container) , index(0){
		}

        AscendingIterator (MagicalContainer& container, int index)
			: myContainer(&container) , index(index){
		}

		int operator*() {
           
			return (*myContainer).sortMagicCon[static_cast<size_t>(index)];
		}

		// ++i;
		AscendingIterator& operator++() {
			if (this->index == static_cast<int>(this->myContainer->sortMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
			++ this->index;
            return *this;
		}

		// i++;
		AscendingIterator operator++(int) {
            if (this->index == static_cast<int>(this->myContainer->sortMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
            AscendingIterator temp = *this;
			this->index++;
            return temp;
		}

		bool operator==(const AscendingIterator&  rhs) const {
            if (this->myContainer!= rhs.myContainer)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
			return (this->index == rhs.index);
		}

		bool operator!=(const AscendingIterator& rhs) const {
			return !(*this == rhs);
		}

        AscendingIterator& operator=(const AscendingIterator&  rhs) {
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

        bool operator>(const AscendingIterator& rhs) const {
			return this->index > rhs.index;
		}

        bool operator<(const AscendingIterator& rhs) const {
			return this->index < rhs.index;
		}

        AscendingIterator& operator=(AscendingIterator&&) noexcept = default;
        AscendingIterator(const AscendingIterator&) = default;
        AscendingIterator(AscendingIterator&&) noexcept = default;
        ~AscendingIterator() = default;

        AscendingIterator begin()
        {
            return AscendingIterator(*myContainer);
        }

        AscendingIterator end() 
        {
            return AscendingIterator(*myContainer , static_cast<int>((*myContainer).size()));
        }

	}; 



    class SideCrossIterator{

        private:

        const MagicalContainer* container;
        int index;

        public:

        SideCrossIterator (const MagicalContainer& container)
			: container(&container) , index(0) {
		}

        SideCrossIterator (const MagicalContainer& container, int index)
			: container(&container) , index(index) {
		}

        int operator*() const {
			//return *pointer_to_current_node;
			if (this->index%2 == 0) // cross side will be left
            {
                return (*container).magicCon[static_cast<size_t>(this->index/2)]; 
            }
            // cross side will be right
            size_t disFromEnd = static_cast<size_t>((*container).size() -1 - static_cast<size_t>(this->index/2));
            return (*container).magicCon[disFromEnd];
		}

        // ++i;
		SideCrossIterator& operator++() {
            if (this->index == static_cast<int>(this->container->magicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
			++ this->index;
            return *this;
		}

		// i++;
		SideCrossIterator operator++(int) {
            if (this->index == static_cast<int>(this->container->magicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
			SideCrossIterator temp = *this;
            this->index++;
            return temp;
		}

        bool operator==(const SideCrossIterator&  rhs) const {
            if (this->container!= rhs.container)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
			return (this->index == rhs.index);
		}

		bool operator!=(const SideCrossIterator& rhs) const {
			return !(*this == rhs);
		}

        SideCrossIterator& operator=(const SideCrossIterator&  rhs) {
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

        bool operator>(const SideCrossIterator& rhs) const {
			return this->index > rhs.index;
		}

        bool operator<(const SideCrossIterator& rhs) const {
			return this->index < rhs.index;
		}
        
        SideCrossIterator(const SideCrossIterator&) = default;
        SideCrossIterator(SideCrossIterator&&) noexcept = default;
        SideCrossIterator& operator=(SideCrossIterator&&) noexcept = default;
        ~SideCrossIterator() = default;

        SideCrossIterator begin()
        {
        return SideCrossIterator{*container};
        }

        SideCrossIterator end() {
        return SideCrossIterator{*container, static_cast<int>((*container).size())};

        }

    };

    
    class PrimeIterator{

        private:

        const MagicalContainer* container;
        int index;

        public:

        PrimeIterator (const MagicalContainer& container)
			: container(&container) , index(0) {
		}

        PrimeIterator (const MagicalContainer& container, int index)
			: container(&container) , index(index) {
		}

		int operator*() const {
            return (*container).primeMagicCon[static_cast<size_t>(index)];
		}

		// ++i;
		PrimeIterator& operator++() {
            if (this->index == static_cast<int>(this->container->primeMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
            ++ this->index;
            return *this;
		}

		// i++;
		PrimeIterator operator++(int) {
            if (this->index == static_cast<int>(this->container->primeMagicCon.size()))
            {
                throw std::runtime_error("Element not found in MagicalContainer");
            }
            PrimeIterator temp = *this;
			this->index++;
            return temp;
		}

		bool operator==(const PrimeIterator&  rhs) const {
            if (this->container!= rhs.container)
            {
                throw std::runtime_error("Can't create iterator over differnt container");
            }
			return (this->index == rhs.index);
		}

		bool operator!=(const PrimeIterator& rhs) const {
			return !(*this == rhs);
		}

        PrimeIterator& operator=(const PrimeIterator&  rhs) {
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

        bool operator>(const PrimeIterator& rhs) const {
			return this->index > rhs.index;
		}

        bool operator<(const PrimeIterator& rhs) const {
			return this->index < rhs.index;
		}

        PrimeIterator(const PrimeIterator&) = default;
        PrimeIterator(PrimeIterator&&) noexcept = default;
        PrimeIterator& operator=(PrimeIterator&&) noexcept = default;
        ~PrimeIterator() = default;
        
        PrimeIterator begin()
        {
        return PrimeIterator{*container};
        }

        PrimeIterator end() {
        return PrimeIterator{*container ,static_cast<int>((*container).primeMagicCon.size())};
        }
    };
};
// Tag dispatching is used to select the correct overload for a function based on type traits.
// A common example uses iterators to illustrate the concept.

#include <iterator>
#include <vector>
#include <list>

template<typename Iterator>
void advance(Iterator& iterator, intptr_t distance, std::forward_iterator_tag)
{
    printf("I'm advancing a forward iterator.\n");
    iterator ++;
}

template<typename Iterator>
void advance(Iterator& iterator, intptr_t distance, std::random_access_iterator_tag)
{
    printf("I'm advancing a random access iterator.\n");
    iterator += distance;
}

template<typename Iterator>
void advance(Iterator& iterator, intptr_t distance, std::bidirectional_iterator_tag)
{
    printf("I'm advancing a bidirectional iterator.\n");

    if (distance < 0)
    {
        while (distance)
        {
            iterator--;
            distance++;
        }
    }
    else if (distance > 0)
    {
        while (distance)
        {
            iterator++;
            distance--;
        }
    }
}

// Catch anything else here.
template<typename Iterator, typename T>
void advance(Iterator& iterator, intptr_t distance, T)
{
    static_assert(0, "I don't know how to move this type of iterator.\n");
}

template<typename T>
void advance(T& iterator, intptr_t distance)
{
    advance(iterator, distance, T::iterator_category{});
}

template<typename T>
struct my_forward_iterator
{
    using iterator_category = std::forward_iterator_tag;
    void operator++(int) { /*Do nothing*/ }
};

template<typename T>
struct my_unsupported_iterator
{
    using iterator_category = std::output_iterator_tag;
};

int main(size_t argc, char** argv)
{
    std::vector<int> my_vector { 1, 2, 3, 4, 5 };
    std::list<int> my_list { 1, 2, 3, 4, 5 };

    advance(my_vector.begin(), 3);
    advance(my_list.begin(), 3);
    advance(my_forward_iterator<int>(), 3);

    // Enabling this will cause the static assert to fire.
    // advance(my_unsupported_iterator<int>(), 3);

    // EXPECTED OUTPUT:
    // I'm advancing a random access iterator.
    // I'm advancing a bidirectional iterator.
    // I'm advancing a forward iterator.
}

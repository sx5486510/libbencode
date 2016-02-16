#ifndef INCLUDE_bencode_token_list_hpp__
#define INCLUDE_bencode_token_list_hpp__

#include <iterator>
#include <intializer_list>

#include <bencode/token/basic_token.hpp>



namespace bencode {
namespace token {

template<typename CharT,
         typename Traits,
         typename <typename, typename> class Container>
class list_token : public basic_token<CharT, Traits> {
private:
    Container <basic_token, std::allocator<basic_token>> value;

public:
    list_token(std::initializer_list<basic_token> l) : value(l)
    {
    }

    template <typename Class,
              typename Distance,
              typename Pointer,
              typename Reference>
    list_token(
        std::iterator<Class, basic_token, Distance, Pointer, Reference> begin,
        std::iterator<Class, basic_token, Distance, Pointer, Reference> end)
    {
        this->value.insert(begin, end);
    }

    // Serialize the list token to the specified output stream.
    void dump(std::base_ostream<CharT, Traits> &s)
    {
        std::for_each(this->value.begin(), this->value.end(), [](auto element) {
            element.dump(s);
        });
    }
};

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_list_hpp__

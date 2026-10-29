

#include <string_view>


static constexpr std::string_view WHITESPACES = " \n\t";
std::string_view trim(std::string_view sv){

    auto s = sv.find_first_not_of(WHITESPACES);
    if (s == std::string_view::npos){
        return {};
    }
    auto e = sv.find_last_not_of(WHITESPACES);

    return sv.substr(s, e-s+1);
}

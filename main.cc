#pragma once 
/*
Maximos Nolan std::optional libary
Created: 3/13/22 
Designed for C++ 20 onward
*/
#include <optional>
#include <variant>
#include <vector>
#include <string> 
#include <functional>
#include <numeric>
#include <ostream>
#include <iostream>
#include <algorithm>


template <typename T>
class mOptional{
private:
    std::optional<T> m_optional; 
    [[maybe_unused]] std::vector<T> *ts_container; 
public:

    mOptional(): m_optional{std::nullopt} {}

    mOptional(T value){
        m_optional = value; 
    } 
    [[no_discard]] inline std::optional<T> unwrap_optional(){
        return (m_optional.has_value()) ? m_optional : std::nullopt;
    }

    [[no_discard]] inline std::optional<T> wrapOptional(T value, const bool override) noexcept{
        auto wrapped = [=](T value) -> std::optional<T> {
            return std::optional<std::reference_wrapper<T>>{value}; 
        }(value);
        if(override) [[likely]]
            m_optional = wrapped;
        return wrapped;
    }

    [[carries_dependency, no_discard]] inline T opt_safe_accumulate(std::vector<std::optional<T>> &victim, auto& lambda){
        ts_container = new std::vector<T>;  
        for (auto &itr : victim){
            if (itr.has_value()) ts_container->push_back(*itr);
        }
        T ret_val = std::accumulate(std::next(ts_container.begin()), ts_container.end(), ts_container.front(), lambda);
        delete ts_container;
        return ret_val;
    }
    [[no_discard]] const inline bool has_value() const {
        return m_optional.has_value() || !*m_optional;
    }

    [[no_discard]] const inline T fetch_value() const {
        return m_optional.value();
    }
    friend std::ostream& operator<< (std::ostream &out, const mOptional & m_optional) noexcept {
        std::string output = (m_optional.has_value()) ? std::to_string(m_optional.fetch_value()) : "no value present";
        std::cout << output; 
        //std::cout << "Hello\n";
        return out;
    }

    [[no_discard]] inline float safe(std::vector<T> &victim) {
        if(victim.size() == 0) throw std::runtime_error("Empty container");
        auto safe = [](std::vector<T> victim) -> bool {
            for (auto & itr : victim) {
                if(!*itr) return false; 
            }
            return true; 
        }(victim);
        return safe; 
    }

    static void remove_unsafe(std::vector<mOptional<T>> &victim) {
        if(victim.size() == 0) throw std::runtime_error("Empty container");
        std::remove_if(victim.begin(), victim.end(), [](mOptional<T> v){return v.has_value();});
       
    }
};

int main(){
    mOptional victim = mOptional(5);
    std::cout << victim << "\n";
    std::vector<mOptional<int>> container = {1,2,3, {},5};
    std::cout << "Pre process\n";
    for (auto &itr : container){
        std::cout << itr << "\n";
    }
    std::cout << "Post process\n";
    mOptional<int>::remove_unsafe(container);
    for (auto &itr : container){
        std::cout << itr << "\n";
    }
    std::cout << container.size();  
}

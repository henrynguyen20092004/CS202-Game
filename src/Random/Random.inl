#include <stdexcept>

template <typename T>
T Random<T>::generate(T min, T max) {
    if constexpr (std::is_floating_point_v<T>) {
        return std::uniform_real_distribution<T>(min, max)(mEngine);
    } else if constexpr (std::is_integral_v<T>) {
        return std::uniform_int_distribution<T>(min, max)(mEngine);
    }

    throw std::invalid_argument("Invalid type");
    return T();
}

template <typename T>
T Random<T>::generate(const std::vector<T>& list) {
    return list[Random<size_t>::generate(0, list.size() - 1)];
}

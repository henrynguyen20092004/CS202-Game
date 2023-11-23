#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum ID { None, Title, Menu, Game, Loading, Pause };
}

namespace Textures {
enum class ID {
    Car,
    Truck,
};
}

namespace Fonts {
enum class ID {
    Main,
};
}

namespace Music {
enum class ID {
    None,
};
}

#endif  // IDENTIFIER_HPP

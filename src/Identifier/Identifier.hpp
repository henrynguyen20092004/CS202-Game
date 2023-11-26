#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum class ID { None, Title, Menu, Game, Loading, Pause };
}

namespace Directions {
enum class ID {
    Up,
    Down,
    Left,
    Right,
};
}

namespace Textures {
enum class ID {
    Car,
    Truck,

    Cat,
    Elephant,
    Pug,
    Phoenix,
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

namespace Sound {
enum class ID {
    Elephant,
    Pug,
    Phoenix,
    Cat,
};
}

#endif  // IDENTIFIER_HPP

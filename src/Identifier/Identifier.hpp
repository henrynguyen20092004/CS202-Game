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
    Player,
    Background,

    Car,
    Truck,

    Cat,
    Elephant,
    Pug,
    Phoenix,

    VehicleLane,
};
}

namespace Fonts {
enum class ID {
    Dosis,
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

#endif

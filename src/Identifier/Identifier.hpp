#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum class ID {
    None,
    Title,
    Menu,
    Game,
    Loading,
    Pause,
    Setting,
};
}

namespace Directions {
enum class ID {
    None,
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
    MenuBackground,

    CarLeft,
    CarRight,
    Truck,
    TrainLeft,
    TrainRight,

    Cat,
    Elephant,
    Pug,
    Phoenix,

    VehicleLane,
    TrainLane,

    ButtonNormal,
    ButtonSelected,
    ButtonPressed,
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

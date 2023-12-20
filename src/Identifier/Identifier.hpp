#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum class ID {
    Title,
    Menu,
    Game,
    Loading,
    Pause,
    Setting,
    GameOver,
    None,
};
}

namespace Directions {
enum class ID {
    Up,
    Down,
    Left,
    Right,
    None,
};
}

namespace Textures {
enum class ID {
    Player,

    MenuBackground,

    CarLeft,
    CarRight,
    Truck,
    TrainLeft,
    TrainRight,

    Cat,
    Elephant,
    Phoenix,
    PolarBear,
    Pug,

    Rock,

    VehicleLane,
    TrainLane,
    ObstacleLane,

    ButtonNormal,
    ButtonSelected,
    ButtonPressed,

    TrafficLight,
};
}

namespace Fonts {
enum class ID {
    Dosis,
    Pacifico,
};
}

namespace Music {
enum class ID {
    None,
};
}

namespace Sound {
enum class ID {
    Cat,
    Elephant,
    Phoenix,
    PolarBear,
    Pug,
};
}

#endif

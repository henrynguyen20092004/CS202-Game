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
    GameOver,
};
}

namespace TrafficLightStates {
enum class ID {
    Red,
    Yellow,
    Green,
    None,
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

    VehicleLane,
    TrainLane,

    ButtonNormal,
    ButtonSelected,
    ButtonPressed,

    TrafficLight,
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
    Cat,
    Elephant,
    Phoenix,
    PolarBear,
    Pug,
};
}

#endif

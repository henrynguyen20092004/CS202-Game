#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum class ID {
    Title,
    Menu,
    Game,
    Loading,
    Pause,
<<<<<<< HEAD
    Setting,
    GameOver,
<<<<<<< HEAD
=======
=======
    Settings,
>>>>>>> 827b0b4 (Add SettingState)
};
}

namespace TrafficLightStates {
enum class ID {
    Red,
    Yellow,
    Green,
>>>>>>> 49249ce (Add SettingState)
    None,
};
}

namespace Directions {
enum class ID {
    Up,
    Down,
    Left,
    Right,
    DirectionCount,
    None,
};
}

namespace Textures {
enum class ID {
    Player,

    MenuBackground,

    Car,
    Truck,
    Train,
    Bus,
    PoliceCar,

    Cat,
    Elephant,
    Phoenix,
    PolarBear,
    Pug,

    Rock,
    TrafficLight,

    ShortLog,
    MediumLog,
    LongLog,

    VehicleLane,
    TrainLane,
    ObstacleLane,
    River,

    ButtonNormal,
    ButtonSelected,
    ButtonPressed,
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

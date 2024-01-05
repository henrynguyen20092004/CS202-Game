#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum class ID {
    Title,
    Menu,
    Game,
    MultiplayerGame,
    Pause,
    GameOver,
    MultiplayerGameOver,
    Settings,
    None,
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
    BlueNinja,
    BlackNinja,

    TitleBackground,
   
    Blood,
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
    Tree,
    Log,
    ShortLog,
    MediumLog,
    LongLog,
    RailwaySignal,
    TrafficLight,

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
    VTV323,
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

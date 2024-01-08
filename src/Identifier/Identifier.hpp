#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

namespace States {
enum class ID {
    Title,
    Menu,
    SelectPlayer1Single,
    SelectPlayer1Multi,
    SelectPlayer2Multi,
    Game,
    MultiplayerGame,
    HighScore,
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
    PlayerChoice1,
    PlayerChoice2,
    PlayerChoice3,
    PlayerChoice4,
    PlayerChoice5,
    PlayerChoice6,
    Player1SelectedChoice,
    Player2SelectedChoice,
    Halo,

    TitleBackground,
    MenuBackground,
    SettingBackground,
    Frame,

    Car,
    PoliceCar,
    Van,
    Bus,
    Train,

    Cat,
    Dog,
    Lion,
    Cow,
    Horse,

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

    ButtonBack,
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
    Minecraft,
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
    Dog,
    Lion,
    Cow,
    Horse,
};
}

#endif

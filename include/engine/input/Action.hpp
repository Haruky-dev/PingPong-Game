#pragma once

enum class Action {
        None,

        raiseMain,
        raisePause,
        raisePlay,
        raiseSett,
        raiseQuit,

        dropOverlap,
        dropGameOv, // basically goto Play state
        dropSett
};
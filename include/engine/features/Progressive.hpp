/*
    Defines a loading system based on arbitrary set 'work units' /
    'cost of loading' that an object takes to load.
    (e.g Loading a textures takes up to 3 work units)
*/

#pragma once


class Progressive {
    public:
        virtual void addTotal( int units ) = 0;
        virtual void incCount( int units=1 ) = 0;

        virtual ~Progressive() = default;
};
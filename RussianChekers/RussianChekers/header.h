#pragma once
#include <SFML/Graphics.hpp>
#include "vector.h"

const int rows = 8;
const int cols = 8;
const int cellSize = 100;
const int ChekerRaduis = 50;

sf::Color lightBrown(244, 164, 96);
sf::Color darkBrown(139, 69, 19);

struct Cheker {
    sf::CircleShape cheker;
    sf::Color color;
    short row;
    short coll;
    bool king;
    int id = -1;

    // Конструктор
    Cheker(sf::Color color, sf::Color thicknessColor, int row, int coll, int id) {
        this->color = color;
        this->row = row;
        this->coll = coll;
;        cheker = sf::CircleShape(ChekerRaduis);
        cheker.setFillColor(color);
        cheker.setOutlineThickness(2);
        cheker.setOutlineColor(thicknessColor);
        cheker.setPosition(coll * cellSize, row * cellSize);
        this->id = id;
        king = false;
    }

    Cheker() {}

    Cheker& operator=(const Cheker& other) {
        if (this != &other) { 
            this->cheker = other.cheker;
            this->color = other.color;
            this->row = other.row;
            this->coll = other.coll;
            this->king = other.king;
            this->id = other.id;
        }
        return *this;
    }
};

struct FieldCells {
    sf::RectangleShape square;
    short row;
    short coll;
    bool empty;
    FieldCells(sf::Color СolorField, int row, int coll) {
        this->row = row;
        this->coll = coll;
        //Задаём параметры клетки
        square = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
        square.setOutlineThickness(2);
        square.setOutlineColor(sf::Color::Black);
        square.setFillColor(СolorField);
        square.setPosition(coll * cellSize, row * cellSize);
        empty = true;
    }
    FieldCells() {}

    FieldCells& operator=(const FieldCells& other) {
        if (this != &other) {
            row = other.row;
            coll = other.coll;
            empty = other.empty;
            square = other.square; // Копируем RectangleShape
        }
        return *this;
    }
};

struct gamestats {
    bool move = true;
    bool Final = false;
    bool isActive = false;
    int IDActiveCheker = -1;
};

struct Moves {
    FieldCells move;
    Cheker IdCheker;
    bool Mandatorymove = false;
};
#include "grafic.h"
#include "func.h"
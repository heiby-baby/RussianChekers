#pragma once
#include "header.h"



void renderField(
    sf::RenderWindow& window, 
    const Vector<Vector<FieldCells>>& field, 
    Vector<Cheker>& WhiteChekers,
    Vector<Cheker>& BlackChekers) {
    for (const auto& row : field) {
        for (const auto& cell : row) {
            window.draw(cell.square);
        }
    }
    for (auto& cheker : WhiteChekers) {
        window.draw(cheker.cheker);
    }
    for (auto& cheker : BlackChekers) {
        window.draw(cheker.cheker);
    }
}

void CreateTable(Vector<Vector<FieldCells>>& field) {
    for (int i = 0; i < rows; ++i) {
        Vector<FieldCells> row;
        for (int j = 0; j < cols; ++j) {
            sf::Color color = (i + j) % 2 == 0 ? lightBrown : darkBrown;
            FieldCells cell(color, i, j);
            row.push_back(cell);
        }
        field.push_back(row);
    }
}

void CreateChekers(
    Vector<Cheker>& WhiteChekers,
    Vector<Cheker>& BlackChekers,
    Vector<Vector<FieldCells>>& field) {
    int id = 0;
    for (int row = 0; row < 3; row++) {
        for (int coll = 0; coll < 8; coll++) {
            if (row == 0) {
                if (coll % 2 == 1) {
                    std::cout << "aboba";
                    field[row][coll].empty = false;
                    BlackChekers.push_back(Cheker(sf::Color::Black, sf::Color::White, row, coll, id++));
                }
            }
            else if (row == 1) {
                if (coll % 2 == 0) {
                    field[row][coll].empty = false;
                    BlackChekers.push_back(Cheker(sf::Color::Black, sf::Color::White, row, coll, id++));
                }
            }
            else if (row == 2) {
                if (coll % 2 == 1) {
                    field[row][coll].empty = false;
                    BlackChekers.push_back(Cheker(sf::Color::Black, sf::Color::White, row, coll, id++));
                }
            }
        }
    }
    for (int row = 5; row < 8; row++) {
        for (int coll = 0; coll < 8; coll++) {
            if (row == 5) {
                if (coll % 2 == 0) {
                    field[row][coll].empty = false;
                    WhiteChekers.push_back(Cheker(sf::Color::White, sf::Color::Black, row, coll, id++));
                }
            }
            else if (row == 6) {
                if (coll % 2 == 1) {
                    field[row][coll].empty = false;
                    WhiteChekers.push_back(Cheker(sf::Color::White, sf::Color::Black, row, coll, id++));
                }
            }
            else if (row == 7) {
                if (coll % 2 == 0) {
                    field[row][coll].empty = false;
                    WhiteChekers.push_back(Cheker(sf::Color::White, sf::Color::Black, row, coll, id++));
                }
            }
        }
    }

}
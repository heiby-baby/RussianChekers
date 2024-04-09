#include "header.h"


int Evalution(Vector<Vector<FieldCells>>& field, //игровое поле
Vector<Cheker>& WhiteChekers, // Фишки игрока
Vector<Cheker>& BlackChekers) {
    int wc = WhiteChekers.size();
    int bc = BlackChekers.size();
    int kwc = 0;
    int kbc = 0;
    for (auto& i : WhiteChekers) {
        if (i.king) {
            kwc++;
        }
    }
    for (auto& i : BlackChekers) {
        if (i.king) {
            kbc++;
        }
    }
    return (wc - bc) + (10 * (kwc - kbc));
}

int gameValid(Vector<Vector<FieldCells>>& field,
    Vector<Cheker>& WhiteChekers,
    Vector<Cheker>& BlackChekers) {
    if (WhiteChekers.size() == 0) {
        return INT16_MIN;
    }
    else if (BlackChekers.size() == 0) {
        return INT16_MAX;
    }
    for (auto wc : WhiteChekers) {
        if (generateMoves(wc, field, WhiteChekers, BlackChekers, false).size() != 0) {
            return Evalution(field, WhiteChekers, BlackChekers);
        }
        return INT16_MIN;
    }
    for (auto bc : BlackChekers) {
        if (generateMoves(bc, field, WhiteChekers, BlackChekers, false).size() != 0) {
            return Evalution(field, WhiteChekers, BlackChekers);
        }
        return INT16_MAX;
    }
}

struct MMreturn {
    int chekerID;
    FieldCells cell;
    int evol;
};

MMreturn Minimax(Vector<Vector<FieldCells>>& field, Vector<Cheker>& WhiteChekers, Vector<Cheker>& BlackChekers, gamestats& gms, int depth, bool move) {
    int gameval = gameValid(field, WhiteChekers, BlackChekers);
    if (depth == 0 || gameval == INT16_MAX || gameval == INT16_MIN) {
        return { {},{},{gameval} };
    }
}


int main() {

    sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "Russian Chekers");

    gamestats gms;
    Vector<Vector<FieldCells>> field; //игровое поле
    Vector<Cheker> WhiteChekers; // Фишки игрока
    Vector<Cheker> BlackChekers; // Фишки бота
    Vector<Moves> moves;
    CreateTable(field);
    CreateChekers(WhiteChekers, BlackChekers, field);
    for (auto i : WhiteChekers) {
        std::cout << i.id << std::endl;;
    }
    std::cout << WhiteChekers.size() << " " << BlackChekers.size() << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
                std::cout <<"Mouse Pos" << mousePos.x << " " << mousePos.y << std::endl;
                if(gms.isActive == false)
                {

                    if (gms.move) {
                        //ход белых (выбирают фигуру)
                        Vector<int> chekerID = ShouldEatChecker(WhiteChekers, BlackChekers, field, gms.move);
                        bool flag = static_cast<bool>(chekerID.size());
                        for (auto& wc : WhiteChekers) {
                            if (flag == true) {
                                for (auto& cID : chekerID) {
                                    if (cID == wc.id) {
                                        if (wc.cheker.getGlobalBounds().contains(mousePos)) {
                                            moves = generateMoves(wc, field, WhiteChekers, BlackChekers, true);
                                            for (auto& i : moves) {
                                                field[i.move.row][i.move.coll].square.setFillColor(sf::Color::Green);
                                            }
                                            gms.isActive = true;
                                            gms.IDActiveCheker = wc.id;
                                            break;
                                        }
                                    }
                                }
                            }
                            else {
                                if (wc.cheker.getGlobalBounds().contains(mousePos)) {
                                    moves = generateMoves(wc, field, WhiteChekers, BlackChekers, false);
                                    for (auto& i : moves) {
                                        field[i.move.row][i.move.coll].square.setFillColor(sf::Color::Green);
                                    }
                                    gms.isActive = true;
                                    gms.IDActiveCheker = wc.id;
                                    break;
                                }
                            }
                        }
                        if (moves.size() == 0) {
                            gms.isActive = false;
                            gms.IDActiveCheker = -1;
                        }
                    }
                    else {
                        //ход черных (выбирают фигуру)
                        Vector<int> chekerID = ShouldEatChecker(WhiteChekers, BlackChekers, field, gms.move);
                        bool flag = static_cast<bool>(chekerID.size());
                        for (auto& bc : BlackChekers) {
                            if (flag == true) {
                                for (auto& cID : chekerID) {
                                    if (cID == bc.id) {
                                        if (bc.cheker.getGlobalBounds().contains(mousePos)) {
                                            moves = generateMoves(bc, field, WhiteChekers, BlackChekers, true);
                                            for (auto& i : moves) {
                                                field[i.move.row][i.move.coll].square.setFillColor(sf::Color::Green);
                                            }
                                            gms.isActive = true;
                                            gms.IDActiveCheker = bc.id;
                                            break;
                                        }
                                    }
                                }
                            }
                            else {
                                if (bc.cheker.getGlobalBounds().contains(mousePos)) {
                                    moves = generateMoves(bc, field, WhiteChekers, BlackChekers, false);
                                    for (auto& i : moves) {
                                        field[i.move.row][i.move.coll].square.setFillColor(sf::Color::Green);
                                    }
                                    gms.isActive = true;
                                    gms.IDActiveCheker = bc.id;
                                    break;
                                }
                            }
                        }
                        if (moves.size() == 0) {
                            gms.isActive = false;
                            gms.IDActiveCheker = -1;
                        }
                    }
                }
                else {
                    //белые (выбирают куда сходить)
                    if (gms.move) {
                        for (auto& i : moves) {
                            if (i.Mandatorymove == false) {
                                //если ход у нас без съеданий
                                if (i.move.square.getGlobalBounds().contains(mousePos)) {
                                    for (auto& wc : WhiteChekers) {
                                        if (wc.id == gms.IDActiveCheker) {
                                            field[wc.row][wc.coll].empty = true;
                                            wc.row = i.move.row;
                                            wc.coll = i.move.coll;
                                            wc.cheker.setPosition(wc.coll * cellSize, wc.row * cellSize);
                                            field[wc.row][wc.coll].empty = false;
                                            for (auto& i : moves) {
                                                field[i.move.row][i.move.coll].square.setFillColor((i.move.row + i.move.coll) % 2 == 0 ? lightBrown : darkBrown);
                                            }
                                            gms.move = false;
                                            gms.isActive = false;
                                            gms.IDActiveCheker = -1;
                                            if (wc.row == 0) {
                                                wc.king = true;
                                            }
                                        }
                                    }
                                }   
                            }
                            //если едим
                            else {
                                if (i.move.square.getGlobalBounds().contains(mousePos)) {
                                    for (auto& wc : WhiteChekers) {
                                        if (wc.id == gms.IDActiveCheker) {
                                            field[wc.row][wc.coll].empty = true;
                                            wc.row = i.move.row;
                                            wc.coll = i.move.coll;
                                            wc.cheker.setPosition(wc.coll * cellSize, wc.row * cellSize);
                                            field[wc.row][wc.coll].empty = false;

                                            for (auto& i : moves) {
                                                field[i.move.row][i.move.coll].square.setFillColor((i.move.row + i.move.coll) % 2 == 0 ? lightBrown : darkBrown);
                                            }

                                            for (int bc = 0; bc < BlackChekers.size(); bc++) {
                                                if (BlackChekers[bc].id == i.IdCheker.id) {
                                                    field[BlackChekers[bc].row][BlackChekers[bc].coll].empty = true;
                                                    BlackChekers.erase(bc);
                                                }
                                            }
                                            if (wc.row == 0) {
                                                wc.king = true;
                                            }
                                            moves.clear();
                                            moves = generateMoves(wc, field, WhiteChekers, BlackChekers, true);
                                            if (moves.size() == 0) {
                                                gms.move = false;
                                                gms.isActive = false;
                                                gms.IDActiveCheker = -1;
                                                break;
                                            }
                                            else {
                                                for (auto& i : moves) {
                                                    field[i.move.row][i.move.coll].square.setFillColor(sf::Color::Green);
                                                }
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //Черные выбирают куда сходить
                    else {
                        for (auto& i : moves) {
                            if (i.Mandatorymove == false) {
                                //если ход у нас без съеданий
                                if (i.move.square.getGlobalBounds().contains(mousePos)) {
                                    for (auto& bc : BlackChekers) {
                                        if (bc.id == gms.IDActiveCheker) {
                                            field[bc.row][bc.coll].empty = true;
                                            bc.row = i.move.row;
                                            bc.coll = i.move.coll;
                                            bc.cheker.setPosition(bc.coll * cellSize, bc.row * cellSize);
                                            field[bc.row][bc.coll].empty = false;
                                            for (auto& i : moves) {
                                                field[i.move.row][i.move.coll].square.setFillColor((i.move.row + i.move.coll) % 2 == 0 ? lightBrown : darkBrown);
                                            }
                                            gms.move = true;
                                            gms.isActive = false;
                                            gms.IDActiveCheker = -1;
                                            std::cout << WhiteChekers.size();
                                            if (bc.row == 7) {
                                                bc.king = true;
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                if (i.move.square.getGlobalBounds().contains(mousePos)) {
                                    for (auto& bc : BlackChekers) {
                                        if (bc.id == gms.IDActiveCheker) {
                                            field[bc.row][bc.coll].empty = true;
                                            bc.row = i.move.row;
                                            bc.coll = i.move.coll;
                                            bc.cheker.setPosition(bc.coll * cellSize, bc.row * cellSize);
                                            field[bc.row][bc.coll].empty = false;
                                            
                                            for (auto& i : moves) {
                                                field[i.move.row][i.move.coll].square.setFillColor((i.move.row + i.move.coll) % 2 == 0 ? lightBrown : darkBrown);
                                            }

                                            for (int wc = 0; wc < WhiteChekers.size(); wc++) {
                                                if (WhiteChekers[wc].id == i.IdCheker.id) {
                                                    field[WhiteChekers[wc].row][WhiteChekers[wc].coll].empty = true;
                                                    WhiteChekers.erase(wc);
                                                }
                                            }
                                            if (bc.row == 7) {
                                                bc.king = true;
                                            }
                                            moves.clear();
                                            moves = generateMoves(bc, field, WhiteChekers, BlackChekers, true);
                                            if (moves.size() == 0) {
                                                gms.move = true;
                                                gms.isActive = false;
                                                gms.IDActiveCheker = -1;
                                                break;
                                            }
                                            else {
                                                for (auto& i : moves) {
                                                    field[i.move.row][i.move.coll].square.setFillColor(sf::Color::Green);
                                                }
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
            window.clear();
            renderField(window, field, WhiteChekers, BlackChekers);
            window.display();
    }

    return 0;
}

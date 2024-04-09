#pragma once
#include "header.h"
Cheker ChekerOnRowAndCol(Vector<Cheker>& WhiteChekers, Vector<Cheker>& BlackChekers, int row, int coll) {
    if (row < 0 || row > 8 || coll < 0 || coll > 8) {
        throw std::invalid_argument("Неверные параметры столбца или строки");
    }
    for (auto& i : WhiteChekers) {
        if (i.row == row && i.coll == coll) {
            return i;
        }
    }
    for (auto& i : BlackChekers) {
        if (i.row == row && i.coll == coll) {
            return i;
        }
    }
    return Cheker(sf::Color::Blue, sf::Color::Blue, row, coll, -1);
}



Vector<Moves> generateMoves(
    Cheker& cheker,
    Vector<Vector<FieldCells>>& field,
    Vector<Cheker>& WhiteCheker,
    Vector<Cheker>& BlackCkeher,
    bool mode) {
    Vector<Moves> moves;
    if (cheker.king == false) {
        int TopRow = cheker.row - 1;
        int BackRow = cheker.row + 1;
        int LeftColl = cheker.coll - 1;
        int RightColl = cheker.coll + 1;
        if (cheker.color == sf::Color::White) {

            //проверка на верх лево
            if (TopRow >= 0 && LeftColl >= 0 && field[TopRow][LeftColl].empty) {
                moves.push_back({
                    field[TopRow][LeftColl],
                    {},
                    false
                    });
            }
            //проверка на съедание
            else if (TopRow > 0 && LeftColl > 0 && field[TopRow - 1][LeftColl - 1].empty == true &&
                ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, LeftColl).color == sf::Color::Black) {
                moves.push_back({
                    field[TopRow - 1][LeftColl - 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, LeftColl),
                    true
                    });
            }
            //проверка на верх право
            if (TopRow >= 0 && RightColl <= 7 && field[TopRow][RightColl].empty) {
                moves.push_back({
                    field[TopRow][RightColl],
                    {},
                    false
                    });
            }
            else if (TopRow > 0 && RightColl < 7 && field[TopRow - 1][RightColl + 1].empty == true &&
                ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, RightColl).color == sf::Color::Black) {
                moves.push_back({
                    field[TopRow - 1][RightColl + 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, RightColl),
                    true
                    });
            }
            //проверка на низ лево
            if (BackRow < 7 && LeftColl > 0 && field[BackRow + 1][LeftColl - 1].empty == true
                && ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, LeftColl).color == sf::Color::Black) {
                moves.push_back({
                    field[BackRow + 1][LeftColl - 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, LeftColl), true });
            }
            //проверка на низ право
            if (BackRow < 7 && RightColl < 7 && field[BackRow + 1][RightColl + 1].empty == true
                && ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, RightColl).color == sf::Color::Black) {
                moves.push_back({
                    field[BackRow + 1][RightColl + 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, RightColl),
                    true 
                    });
            }
        }
        else {
            //проверка на низ лево
            if (BackRow <= 7 && LeftColl >= 0 && field[BackRow][LeftColl].empty == true) {
                moves.push_back({
                    field[BackRow][LeftColl],
                    {},
                    false
                    });
            }
            else if (
                BackRow < 7 &&
                LeftColl > 0 &&
                field[BackRow + 1][LeftColl - 1].empty == true &&
                ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, LeftColl).color == sf::Color::White) {
                moves.push_back({
                    field[BackRow + 1][LeftColl - 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, LeftColl),
                    true
                    });
            }
            //проверка на низ право 
            if (BackRow <= 7 && RightColl <= 7 && field[BackRow][RightColl].empty) {
                moves.push_back({
                    field[BackRow][RightColl],
                    {},
                    false
                    });
            }
            else if (BackRow < 7 && RightColl < 7 && field[BackRow + 1][RightColl + 1].empty &&
                ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, RightColl).color == sf::Color::White) {
                moves.push_back({
                    field[BackRow + 1][RightColl + 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, RightColl),
                    true
                    });
            }
            //проверка на верх лево(только съедание)
            if (TopRow > 0 && LeftColl > 0 && field[TopRow - 1][LeftColl - 1].empty &&
                ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, LeftColl).color == sf::Color::White) {
                moves.push_back({
                    field[TopRow - 1][LeftColl - 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, LeftColl),
                    true
                    });
            }
            //проверка на верх право(только съедание)
            if (TopRow > 0 && RightColl < 7 && field[TopRow - 1][RightColl + 1].empty == true &&
                ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, RightColl).color == sf::Color::White) {
                moves.push_back({
                    field[TopRow - 1][RightColl + 1],
                    ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, RightColl),
                    true
                    });
            }
        }
        Vector<Moves> returnMoves;
        for (auto& i : moves) {
            if (i.Mandatorymove) {
                returnMoves.push_back(i);
            }
        }
        return (mode == false) ? moves : returnMoves;
    }
    else {
        Vector<Moves> UL;
        Vector<Moves> UR;
        Vector<Moves> DL;
        Vector<Moves> DR;
        if (cheker.color == sf::Color::White) {
            sf::Color color = sf::Color::Black;
            //проверка на вверх лево
            for (int TopRow = cheker.row - 1, LeftColl = cheker.coll - 1; TopRow >= 0 && LeftColl >= 0; TopRow--, LeftColl--) {
                if (TopRow >= 0 && LeftColl >= 0) {
                    if (field[TopRow][LeftColl].empty) {
                        UL.push_back({
                            field[TopRow][LeftColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (TopRow > 0 && LeftColl > 0 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, LeftColl).color == color &&
                            field[TopRow - 1][LeftColl - 1].empty) {
                            std::pair<int, int> delChek = { TopRow, LeftColl };
                            UL.clear();
                            UL.push_back({
                                     field[TopRow - 1][LeftColl - 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /*TopRow--;
                            LeftColl--;
                            while (TopRow != 0 && LeftColl != 0) {
                                UL.push_back({
                                    field[TopRow][LeftColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                TopRow--;
                                LeftColl--;
                                if (field[TopRow][LeftColl].empty == false) {
                                    break;
                                }
                            }*/
                            break;
                        }
                        break;
                    }
                }
            }
            //проверка на верх право 
            for (int TopRow = cheker.row - 1, RightColl = cheker.coll + 1; TopRow >= 0 && RightColl <= 7; TopRow--, RightColl++) {
                if (TopRow >= 0 && RightColl <= 7) {
                    if (field[TopRow][RightColl].empty) {
                        UR.push_back({
                            field[TopRow][RightColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (TopRow > 0 && RightColl < 7 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, RightColl).color == color &&
                            field[TopRow - 1][RightColl + 1].empty) {
                            std::pair<int, int> delChek = { TopRow, RightColl };
                            UR.clear();
                            UR.push_back({
                                    field[TopRow - 1][RightColl + 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /*TopRow--;
                            RightColl++;
                            while (TopRow != 0 && RightColl != 7) {
                                UR.push_back({
                                    field[TopRow][RightColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                TopRow--;
                                RightColl++;
                                if (field[TopRow][RightColl].empty == false) {
                                    break;
                                }
                            }
                            break*/;
                        }
                        break;
                    }
                }
            }
            //проверка на низ лево
            for (int BackRow = cheker.row + 1, LeftColl = cheker.coll - 1; BackRow <= 7 && LeftColl >= 0; BackRow++, LeftColl--) {
                if (BackRow <= 7 && LeftColl >= 0) {
                    if (field[BackRow][LeftColl].empty) {
                        DL.push_back({
                            field[BackRow][LeftColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (BackRow < 7 && LeftColl > 0 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, LeftColl).color == color &&
                            field[BackRow + 1][LeftColl - 1].empty) {
                            std::pair<int, int> delChek = { BackRow, LeftColl };
                            DL.clear();
                            DL.push_back({
                                     field[BackRow + 1][LeftColl - 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                           /* BackRow++;
                            LeftColl--;
                            while (BackRow != 7 && LeftColl != 0) {
                                DL.push_back({
                                    field[BackRow][LeftColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                BackRow++;
                                LeftColl--;
                                if (field[BackRow][LeftColl].empty == false) {
                                    break;
                                }
                            }
                            break;*/
                        }
                        break;
                    }
                }
            }
            //проверка на низ право
            for (int BackRow = cheker.row + 1, RightColl = cheker.coll + 1; BackRow <= 7 && RightColl <= 7; BackRow++, RightColl++) {
                if (BackRow <= 7 && RightColl <= 7) {
                    if (field[BackRow][RightColl].empty) {
                        DR.push_back({
                            field[BackRow][RightColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (BackRow < 7 && RightColl < 7 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, RightColl).color == color &&
                            field[BackRow + 1][RightColl + 1].empty) {
                            std::pair<int, int> delChek = { BackRow, RightColl };
                            DR.clear();
                            DR.push_back({
                                    field[BackRow + 1][RightColl + 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /*BackRow++;
                            RightColl++;
                            while (BackRow != 7 && RightColl != 7) {
                                DR.push_back({
                                    field[BackRow][RightColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                BackRow++;
                                RightColl++;
                                if (field[BackRow][RightColl].empty == false) {
                                    break;
                                }
                            }
                            break;*/
                        }
                        break;
                    }
                }
            }
        }
        else {
            sf::Color color = sf::Color::White;
            //проверка на вверх лево
            for (int TopRow = cheker.row - 1, LeftColl = cheker.coll - 1; TopRow >= 0 && LeftColl >= 0; TopRow--, LeftColl--) {
                if (TopRow >= 0 && LeftColl >= 0) {
                    if (field[TopRow][LeftColl].empty) {
                        UL.push_back({
                            field[TopRow][LeftColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (TopRow > 0 && LeftColl > 0 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, LeftColl).color == color &&
                            field[TopRow - 1][LeftColl - 1].empty) {
                            std::pair<int, int> delChek = { TopRow, LeftColl };
                            UL.clear();
                            UL.push_back({
                                     field[TopRow - 1][LeftColl - 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /*TopRow--;
                            LeftColl--;
                            while (TopRow != 0 && LeftColl != 0) {
                                UL.push_back({
                                    field[TopRow][LeftColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                TopRow--;
                                LeftColl--;
                                if (field[TopRow][LeftColl].empty == false) {
                                    break;
                                }
                            }*/
                            break;
                        }
                        break;
                    }
                }
            }
            //проверка на верх право 
            for (int TopRow = cheker.row - 1, RightColl = cheker.coll + 1; TopRow >= 0 && RightColl <= 7; TopRow--, RightColl++) {
                if (TopRow >= 0 && RightColl <= 7) {
                    if (field[TopRow][RightColl].empty) {
                        UR.push_back({
                            field[TopRow][RightColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (TopRow > 0 && RightColl < 7 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, TopRow, RightColl).color == color &&
                            field[TopRow - 1][RightColl + 1].empty) {
                            std::pair<int, int> delChek = { TopRow, RightColl };
                            UR.clear();
                            UR.push_back({
                                    field[TopRow - 1][RightColl + 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /*TopRow--;
                            RightColl++;
                            while (TopRow != 0 && RightColl != 7) {
                                UR.push_back({
                                    field[TopRow][RightColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                TopRow--;
                                RightColl++;
                                if (field[TopRow][RightColl].empty == false) {
                                    break;
                                }
                            }
                            break*/;
                        }
                        break;
                    }
                }
            }
            //проверка на низ лево
            for (int BackRow = cheker.row + 1, LeftColl = cheker.coll - 1; BackRow <= 7 && LeftColl >= 0; BackRow++, LeftColl--) {
                if (BackRow <= 7 && LeftColl >= 0) {
                    if (field[BackRow][LeftColl].empty) {
                        DL.push_back({
                            field[BackRow][LeftColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (BackRow < 7 && LeftColl > 0 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, LeftColl).color == color &&
                            field[BackRow + 1][LeftColl - 1].empty) {
                            std::pair<int, int> delChek = { BackRow, LeftColl };
                            DL.clear();
                            DL.push_back({
                                     field[BackRow + 1][LeftColl - 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /* BackRow++;
                             LeftColl--;
                             while (BackRow != 7 && LeftColl != 0) {
                                 DL.push_back({
                                     field[BackRow][LeftColl],
                                      ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                      true
                                     });
                                 BackRow++;
                                 LeftColl--;
                                 if (field[BackRow][LeftColl].empty == false) {
                                     break;
                                 }
                             }
                             break;*/
                        }
                        break;
                    }
                }
            }
            //проверка на низ право
            for (int BackRow = cheker.row + 1, RightColl = cheker.coll + 1; BackRow <= 7 && RightColl <= 7; BackRow++, RightColl++) {
                if (BackRow <= 7 && RightColl <= 7) {
                    if (field[BackRow][RightColl].empty) {
                        DR.push_back({
                            field[BackRow][RightColl],
                            {},
                            false
                            });
                    }
                    else {
                        if (BackRow < 7 && RightColl < 7 &&
                            ChekerOnRowAndCol(WhiteCheker, BlackCkeher, BackRow, RightColl).color == color &&
                            field[BackRow + 1][RightColl + 1].empty) {
                            std::pair<int, int> delChek = { BackRow, RightColl };
                            DR.clear();
                            DR.push_back({
                                    field[BackRow + 1][RightColl + 1],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                });
                            /*BackRow++;
                            RightColl++;
                            while (BackRow != 7 && RightColl != 7) {
                                DR.push_back({
                                    field[BackRow][RightColl],
                                     ChekerOnRowAndCol(WhiteCheker, BlackCkeher, delChek.first, delChek.second),
                                     true
                                    });
                                BackRow++;
                                RightColl++;
                                if (field[BackRow][RightColl].empty == false) {
                                    break;
                                }
                            }
                            break;*/
                        }
                        break;
                    }
                }
            }
            }
        for (auto& i : UL) {
            moves.push_back(i);
        }
        for (auto& i : UR) {
            moves.push_back(i);
        }
        for (auto& i : DL) {
            moves.push_back(i);
        }
        for (auto& i : DR) {
            moves.push_back(i);
        }
        Vector<Moves> returnMoves;
        for (auto& i : moves) {
            if (i.Mandatorymove) {
                returnMoves.push_back(i);
            }
        }
        return (mode == false) ? moves : returnMoves;
    }
}

Vector<int> ShouldEatChecker(
    Vector<Cheker>& WhiteChekers,
    Vector<Cheker>& BlackCkekers,
    Vector<Vector<FieldCells>>& field,
    bool move) {
    Vector<int> ChekerId;
    if (move) {
        for (auto& wc : WhiteChekers) {
            if (generateMoves(wc, field, WhiteChekers, BlackCkekers, true).size() != 0) {
                ChekerId.push_back(wc.id);
            }
        }
    }
    else {
        for (auto& bc : BlackCkekers) {
            if (generateMoves(bc, field, WhiteChekers, BlackCkekers, true).size() != 0) {
                ChekerId.push_back(bc.id);
            }
        }
    }
    return ChekerId;
}


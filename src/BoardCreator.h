//
// Created by busby08 on 29/07/25.
//

#ifndef BOARDCREATOR_H
#define BOARDCREATOR_H

#include <string>
#include <vector>


class BoardCreator {
private:
    std::string HorizontalChar = "─";
    std::string VerticalChar = "│";
    std::string TopLeftCornerChar = "┌";
    std::string TopRightCornerChar = "┐";
    std::string BottomRightCornerChar = "┘";
    std::string BottomLeftCornerChar = "└";
    std::string VerticalAndRightCrossChar = "├";
    std::string VerticalAndLeftCrossChar = "┤";
    std::string HorizontalAndDownCrossChar = "┬";
    std::string HorizontalAndUpCrossChar = "┴";
    std::string CrossChar = "┼";
    char EndChar = '\n';

    std::string TopLeftCornerTemplate () const {
        return
        TopLeftCornerChar + MultiplyString(HorizontalChar, propertySize) + HorizontalAndDownCrossChar + EndChar
        + VerticalChar + "{}" + VerticalChar + EndChar
        + VerticalChar + MultiplyString(" ", propertySize) + VerticalChar + EndChar
        + VerticalChar + "{}" + VerticalChar + EndChar
        + VerticalAndRightCrossChar + MultiplyString(HorizontalChar, propertySize) + HorizontalChar + EndChar;
    };
    std::string TopRightCornerTemplate;
    std::string BottomRightCornerTemplate;
    std::string BottomLeftCornerTemplate;
    std::string PropertyTemplate;

    static std::string MultiplyString(const std::string &input, int size);
    static std::string CenterString(const std::string &input, int size);
public:
    int propertySize = 12;
    int topLeftCorner;
    int topRightCorner;
    int bottomLeftCorner;
    int bottomRightCorner;
    std::vector<int> topRow;
    std::vector<int> bottomRow;
    std::vector<int> leftColumn;
    std::vector<int> rightColumn;

    BoardCreator();

    // std::string GenerateBoard();
};



#endif //BOARDCREATOR_H

//
// Created by busby08 on 16/06/25.
//

#include <array>
#include "Board.h"
#include "Property.h"

void Board::populate_properties() {
    Property old_kent_road("Old Kent Road", 60, PropertyColorSet::Brown);
    Property whitechapel_road("Whitechapel Road", 60, PropertyColorSet::Brown);

    Property angel_islington("The Angel Islington", 100, PropertyColorSet::LightBlue);
    Property euston("Euston", 100, PropertyColorSet::LightBlue);
    Property pentonville_road("Pentonville Road", 120, PropertyColorSet::LightBlue);

    Property pall_mall("Pall Mall", 140, PropertyColorSet::Pink);
    Property whitehall("Whitehall", 140, PropertyColorSet::Pink);
    Property northumberland_avenue("Northumberland Avenue", 160, PropertyColorSet::Pink);

    Property bow_street("Bow Street", 180, PropertyColorSet::Orange);
    Property marlborough_street("Marlborough Street", 180, PropertyColorSet::Orange);
    Property vine_street("Vine Street", 200, PropertyColorSet::Orange);

    Property strand("Strand", 220, PropertyColorSet::Red);
    Property fleet_street("Fleet Street", 220, PropertyColorSet::Red);
    Property trafalgar_square("Trafalgar Square", 240, PropertyColorSet::Red);

    Property leicester_square("Leicester Square", 260, PropertyColorSet::Yellow);
    Property coventry_street("Coventry Street", 260, PropertyColorSet::Yellow);
    Property piccadilly("Piccadilly", 280, PropertyColorSet::Yellow);

    Property regent_street("Regent Street", 280, PropertyColorSet::Green);
    Property oxford_street("Oxford Street", 280, PropertyColorSet::Green);
    Property bond_street("Bond Street", 300, PropertyColorSet::Green);

    Property park_lane("Park Lane", 350, PropertyColorSet::DarkBlue);
    Property mayfair("Mayfair", 400, PropertyColorSet::DarkBlue);

    properties = std::array {
    old_kent_road, whitechapel_road,
    angel_islington, euston, pentonville_road,
    pall_mall, whitehall, northumberland_avenue,
    bow_street, marlborough_street, vine_street,
    strand, fleet_street, trafalgar_square,
    leicester_square, coventry_street, piccadilly,
    regent_street, oxford_street, bond_street,
    park_lane, mayfair};
}

SpaceActions Board::get_space_action(int space_number) {
    switch (space_number) {
        case 0:
            return SpaceActions::Go;

        case 1:
        case 3:
        case 5:
        case 6:
        case 8:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 18:
        case 19:
        case 21:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 31:
        case 32:
        case 34:
        case 35:
        case 37:
        case 39:
            return SpaceActions::Property;

        case 4: return SpaceActions::IncomeTax;

        case 7:
        case 22:
        case 36:
            return SpaceActions::Chance;

        case 2:
        case 17:
        case 33:
            return SpaceActions::CommunityChest;

        case 10:
            return SpaceActions::Jail;

        case 20:
            return SpaceActions::FreeParking;

        case 38:
            return SpaceActions::LuxuryTax;

        case 30:
            return SpaceActions::GoToJail;

        default:
            return SpaceActions::Invalid;
    }
}


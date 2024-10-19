//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_GAMETEXT_H_
#define INCLUDE_GAMETEXT_H_

#include <string>

namespace GameText {
const char title[] =
    "\n"
    "████████▄     ▄████████    ▄████████    ▄██████▄   ▄██████▄  ███▄▄▄▄      "
    "        \n"
    "███   ▀███   ███    ███   ███    ███   ███    ███ ███    ███ ███▀▀▀██▄    "
    "        \n"
    "███    ███   ███    ███   ███    ███   ███    █▀  ███    ███ ███   ███    "
    "        \n"
    "███    ███  ▄███▄▄▄▄██▀   ███    ███  ▄███        ███    ███ ███   ███    "
    "        \n"
    "███    ███ ▀▀███▀▀▀▀▀   ▀███████████ ▀▀███ ████▄  ███    ███ ███   ███    "
    "        \n"
    "███    ███ ▀███████████   ███    ███   ███    ███ ███    ███ ███   ███    "
    "        \n"
    "███   ▄███   ███    ███   ███    ███   ███    ███ ███    ███ ███   ███    "
    "        \n"
    "████████▀    ███    ███   ███    █▀    ████████▀   ▀██████▀   ▀█   █▀     "
    "        \n"
    "             ███    ███                                                   "
    "        \n"
    "             ▄████████  ▄█          ▄████████ ▄██   ▄      ▄████████    "
    "▄████████ \n"
    "            ███    ███ ███         ███    ███ ███   ██▄   ███    ███   "
    "███    ███ \n"
    "            ███    █▀  ███         ███    ███ ███▄▄▄███   ███    █▀    "
    "███    ███ \n"
    "            ███        ███         ███    ███ ▀▀▀▀▀▀███  ▄███▄▄▄      "
    "▄███▄▄▄▄██▀ \n"
    "          ▀███████████ ███       ▀███████████ ▄██   ███ ▀▀███▀▀▀     "
    "▀▀███▀▀▀▀▀   \n"
    "                   ███ ███         ███    ███ ███   ███   ███    █▄  "
    "▀███████████ \n"
    "             ▄█    ███ ███▌    ▄   ███    ███ ███   ███   ███    ███   "
    "███    ███ \n"
    "           ▄████████▀  █████▄▄██   ███    █▀   ▀█████▀    ██████████   "
    "███    ███ \n"
    "                       ▀                                               "
    "███    ███ \n"
    "               2024 J. Holloway, Dorgee Lama, and John Nisperos           "
    "        \n";

const char title2[] =
    "      d8b                                                \n"
    "      88P                                                \n"
    "     d88                                                 \n"
    " d888888    88bd88b d888b8b   d888b8b   d8888b   88bd88b \n"
    "d8P' ?88    88P'  `d8P' ?88  d8P' ?88  d8P' ?88  88P' ?8b\n"
    "88b  ,88b  d88     88b  ,88b 88b  ,88b 88b  d88 d88   88P\n"
    "`?88P'`88bd88'     `?88P'`88b`?88P'`88b`?8888P'd88'   88b\n"
    "                                    )88                  \n"
    "                                   ,88P                  \n"
    "                               `?8888P                   \n"
    "             d8b                                         \n"
    "             88P                                         \n"
    "            d88                                          \n"
    "     .d888b,888   d888b8b  ?88   d8P  d8888b  88bd88b    \n"
    "     ?8b,   ?88  d8P' ?88  d88   88  d8b_,dP  88P'  `    \n"
    "       `?8b  88b 88b  ,88b ?8(  d88  88b     d88         \n"
    "    `?888P'   88b`?88P'`88b`?88P'?8b `?888P'd88'         \n"
    "                                  )88                    \n"
    "                                 ,d8P                    \n"
    "                              `?888P'                    \n"

    "  2024 J. Holloway, Dorgee Lama, and John Nisperos       \n";

const char welcomeText[] =
    "You are but a humble peasant, hoping for a life of adventure and riches!\n"
    "You hear rumors of wild beasts roaming the land and great monsters "
    "terrorizing the kingdom\n"
    "King Erebus, the ruler of this land promises riches and more to whomever "
    "is brave enough to bring peace to his kingdom\n"
    "\n"
    "Will you heed the call of adventure?";

const char winnerText[] =
    "               Congratulations %s you've won the game!\n"
    "For slaying the dragon King Erebus grants you knighthood and a new "
    "home\n\n"
    "    |>>>                                                      |>>>\n"
    "    |                     |>>>          |>>>                  |\n"
    "    *                     |             |                     *\n"
    "   / \\                    *             *                    / \\\n"
    "  /___\\                 _/ \\           / \\_                 /___\\\n"
    "  [   ]                |/   \\_________/   \\|                [   ]\n"
    "  [ I ]                /     \\       /     \\                [ I ]\n"
    "  [   ]_ _ _          /       \\     /       \\          _ _ _[   ]\n"
    "  [   ] U U |        {#########}   {#########}        | U U [   ]\n"
    "  [   ]====/          \\=======/     \\=======/          \\====[   ]\n"
    "  [   ]    |           |   I |_ _ _ _| I   |           |    [   ]\n"
    "  [___]    |_ _ _ _ _ _|     | U U U |     |_ _ _ _ _ _|    [___]\n"
    "  \\===/  I | U U U U U |     |=======|     | U U U U U | I  \\===/\n"
    "   \\=/     |===========| I   | + W + |   I |===========|     \\=/\n"
    "    |  I   |           |     |_______|     |           |   I  |\n"
    "    |      |           |     |||||||||     |           |      |\n"
    "    |      |           |   I ||vvvvv|| I   |           |      |\n"
    "_-_-|______|-----------|_____||     ||_____|-----------|______|-_-_\n"
    "   /________\\         /______||     ||______\\         /________\\\n"
    "  |__________|-------|________\\_____/________|-------|__________|\n"
    "\n                  Enter \"exit\" to leave game";

const char helpText[] =
    "Commands - Enter the following\n"
    "\n"
    "\"exit\" or \"quit\" to end game\n\n"
    "\"look\" followed by specified object\n"
    "\t\"look west\" - look in a direction\n"
    "\t\"look at DarkKnight\" - look in a item or creature\n"
    "\t\"look inventory\" - Look at the player inventory\n"
    "go - go in a direction\n"
    "\t eg: go west\n"
    "\n"
    "pickup - pickup item\n"
    "\t eg: \"pickup speer\" to pickup speer from current location\n"
    "eat - consume edible items\n"
    "\t eg: \"eat magicpotion\" to eat the magicpotion in inventory\n"
    "Attack - attack an enemy in the current location\n"
    "\t\"Attack DarkKnight\" - attack the local enemy\n"
    "\t\"Attack DarkKnight with muffin\" - attack enemy with inventory item\n";

}  // namespace GameText

#endif  // INCLUDE_GAMETEXT_H_

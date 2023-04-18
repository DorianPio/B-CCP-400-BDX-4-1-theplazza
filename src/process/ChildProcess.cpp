/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** ChildProcess
*/

#include "Kitchens.hpp"
#include "Cook.hpp"
#include "NamedPipe.hpp"

int makeChildProcess(plazza::Kitchens &&toAdd, plazza::NamedPipe &pipe) noexcept
{
    std::vector<std::string> pizza;
    int nb_places = 0;
    std::string status_to_send = "";
    std::string receive = "";
    std::string to_send = "";
    std::string nb_place_in_str= "";

    while (1) {
        receive << pipe;

        if (receive.compare("nb_cook") == 0) {
            nb_places = toAdd.getNbPlace();
            nb_place_in_str = std::to_string(nb_places);
            nb_place_in_str >> pipe;
        } else if (receive.compare("finish") == 0) {
            if (toAdd.canClose() == true) {
                to_send = "yes";
            } else {
                to_send = "no";
            }
            to_send >> pipe;
        } else if (receive.compare("status") == 0) {
            status_to_send = toAdd.prepareStatus();
            status_to_send >> pipe;
        } else {
            if (receive.compare("none") != 0) {
                toAdd.addPizzaToQueue(receive);
            }
        }
        toAdd.refill();
    }
    pipe.closeFd();
    return 0;
}

//
// Created by achille on 13/10/15.
//

#ifndef FODUS_MAIN_HPP
#define FODUS_MAIN_HPP

// config.h includes build & project config parameters
#include "config.h"
#include "global.hpp"

// Standard Lib
#include <string>
#include <iostream>
#include <time.h>
// Project includes
#include "boot/Bootstrap.hpp"

// Easylogging startup macro
INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]);

#endif //FODUS_MAIN_HPP

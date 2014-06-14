/*!
 * \file            config_getopt.cpp
 * \brief           Implementation of command line functionality.
 * \details         Included in separate file to isolate usage of non-standard
 * getopt library.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  UNIX feature test macro for getopt library  */
#define _XOPEN_SOURCE 600

#include <memory>
#include <getopt.h>

#include "config.h"

using namespace genleg;

void Config::populate_from_cmdline(const int argc, char * const * argv) {

    /*  Allocate and populate array of struct option for getopt_long()  */

    const size_t list_size = m_opts_supp.size() + 1;
    std::unique_ptr<struct option[]> opts(new struct option[list_size]);

    size_t idx = 0;
    for ( const auto& pair : m_opts_supp ) {
        struct option& opt = opts.get()[idx++];

        opt.name = pair.first.c_str();
        opt.flag = nullptr;
        opt.val = 0;
        switch ( pair.second ) {
            case Argument::NO_ARG:
                opt.has_arg = no_argument;
                break;

            case Argument::OPT_ARG:
                opt.has_arg = optional_argument;
                break;

            case Argument::REQ_ARG:
                opt.has_arg = required_argument;
                break;
        }
    }

    /*  Zero out last element of array  */

    struct option& opt = opts.get()[idx];
    opt.name = nullptr;
    opt.flag = nullptr;
    opt.val = 0;
    opt.has_arg = 0;
    
    /*  Reinitialize getopt()  */

    optind = 0;

    /*  Get and store recognized options from the command line  */

    int c, opt_ind = 0;
    while ( (c = getopt_long(argc, argv, "", opts.get(), &opt_ind)) != -1 ) {
        std::string option_name = opts.get()[opt_ind].name;
        std::string option_arg = optarg ? optarg : "";

        switch ( c ) {
            case 0:
                m_opts_set[option_name] = option_arg;
                break;

            case '?':
                throw ConfigBadOption("");
                break;
        }
    }
}


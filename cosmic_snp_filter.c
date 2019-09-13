/*
 * Author: Alessandro Coppe
 * Purpose: filter an annotated VCF file based on dbNSFP_FATHMM_rankscore 
 * Language: C
 * 
 *  (c) 2019 Coppe
 *  This code is licensed under WTFPL license (see COPYING for details)
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include<ctype.h>
#include"is_a_snp_in_cosmic.h"
#include "uthash.h"


int main(int argc, char *argv[]){
    char c;
    size_t len = 0;
    int hflag = 0;
    char *is_a_snp = NULL;
    struct cosmic_entry *s;
    struct cosmic_entry *cosmic_hash = NULL;

    /* Help string */
    char help[] = "Usage: filter_by_FATHMM  [OPTION]... VCF_file\n  "
        "-h\tshow help options";

    while ((c = getopt (argc, argv, "hs:")) != -1) {
        switch (c) {
            case 'h':
                hflag = 1;
                puts(help);
                break;
            case '?':
                if (optopt == 's')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    }

    argc -= optind;
    argv += optind;


    /* Check if there is a VCF file argument */
    if (argc < 1) {
        fprintf(stderr, "Cosmic VCF file not specified\n");
        return -1;
    }



    
    cosmic_hash = create_cosmic_hash(argv[0], cosmic_hash);

    HASH_FIND_STR( cosmic_hash, "COSM5424721", s);
    HASH_FIND_STR( cosmic_hash, "COSM6378026", s);
    printf("%i\n", HASH_COUNT(cosmic_hash));

    print_HASH_FIND_STR_RESULT(s);

    delete_cosmic_hash(cosmic_hash, s);


    return 0;
}

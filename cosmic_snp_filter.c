/*
 * Author: Alessandro Coppe
 * Purpose: removes variants annotated with Cosmic that are indicated as SNP
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
#include "get_ids.h"


int main(int argc, char *argv[]){
    char c;
    size_t len = 0;
    int hflag = 0;
    char *is_a_snp = NULL;
    struct cosmic_entry *s = NULL;
    struct cosmic_entry *cosmic_hash = NULL;

    /* Help string */
    char help[] = "Usage: cosmic_snp_filter  [OPTION]... COSMIC_VCF VCF_to_filter\n  "
        "-h\tshow help options";

    while ((c = getopt (argc, argv, "hs:")) != -1) {
        switch (c) {
            case 'h':
                hflag = 1;
                puts(help);
                return(0);
            case '?':
                if (isprint(optopt))
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
    if (argc < 2) {
        fprintf(stderr, "You need to specify 2 arguments: COSMIC_VCF and VCF_to_filter\n");
        return -1;
    }



    
    cosmic_hash = create_cosmic_hash(argv[0], cosmic_hash);


    /* Found in the cosmic_hash because is a SNP. SNP -> found */
    /*HASH_FIND_STR( cosmic_hash, "COSM5424721", s);*/

    /* Not found in the cosmic_hash */
    /*HASH_FIND_STR( cosmic_hash, "COSM6378026", s);*/
    /*printf("%i\n", HASH_COUNT(cosmic_hash));*/

    /*print_HASH_FIND_STR_RESULT(s);*/



    char *line;
    FILE *vcf = NULL;
    ssize_t read;
    char *ids_from_vcf = NULL;
    bio_id *bio_ids_list = NULL;
    bio_id *bio_id_element;
    char *bio_id_to_check;
    char *original_line;
    

    /*If the VCF file is not present */
    if (!(vcf = fopen(argv[1], "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", argv[1]);
        exit(-1);
    }
    

    while ((read = getline(&line, &len, vcf ) ) != -1) {

        int l = strlen(line);
        char *original_line = malloc(l * sizeof(char));
        original_line = strdup(line);

        if (line[0] == '#')
            printf("%s", original_line);
        else {
            ids_from_vcf = get_ids(line);
            bio_ids_list = get_cosmic_ids(ids_from_vcf);

            int is_snp = 0;
            while (bio_ids_list->next != NULL) {
                bio_id_to_check = bio_ids_list->identifier;
                HASH_FIND_STR( cosmic_hash, bio_id_to_check, s);
                /*print_HASH_FIND_STR_RESULT(s);*/
                if (s) {
                    is_snp = 1;
                    break;
                }

                bio_ids_list = bio_ids_list->next;
            }

            bio_id_to_check = bio_ids_list->identifier;

            HASH_FIND_STR( cosmic_hash, bio_id_to_check, s);
            if (s) {
                is_snp = 1;
            }

            if (is_snp == 0)
                printf("%s", original_line);
        }
        
        free(original_line);
        free_cosmic_ids(bio_ids_list);
    }


    delete_cosmic_hash(cosmic_hash, s);


    return 0;
}

gcc -o lesamnta_hash lesamnta_hash.c lesamnta-LW.c -O3
./lesamnta_hash 

gcc -DUQUARK -o MD_quark_hash MD_quark_hash.c quark.c -O3
gcc -DSQUARK -o MD_quark_hash MD_quark_hash.c quark.c -O3
gcc -DCQUARK -o MD_quark_hash MD_quark_hash.c quark.c -O3
./MD_quark_hash

 gcc -D_PHOTON80_ -o Photon_hash Photon_hash.c photon.c -O3 
gcc -D_PHOTON128_ -o Photon_hash Photon_hash.c photon.c -O3
gcc -D_PHOTON256_ -o Photon_hash Photon_hash.c photon.c -O3
./Photon_hash

gcc -D_SPONGENT088080008_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT088176088_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT128128008_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT128256128_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT160160016_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT160160080_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT160320160_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT224224016_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT224224112_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT224448224_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT256256016_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT256256128_ -o Spongent_hash Spongent_hash.c spongent.c -O3
gcc -D_SPONGENT256512256_ -o Spongent_hash Spongent_hash.c spongent.c -O3


gcc -o photon_beetle_hash main.c hash.c photon.c -std=c99
./photon-beetle_hash

gcc -o Xoodyak_hash Xoodyak_hash.c Xoodyak.c Xoodoo-reference.c -std=c99
./Xoodyak_hash

gcc -o knot_hash knot_hash.c hash.c -std=c99
./knot_hash


gcc -o orange_hash orange_hash.c hash.c -std=c99
./orange_hash

gcc -o shamas_hash  shamas_hash.c hash.c -std=c99 
./shamash_test

gcc -o sivrijndael_hash  sivrijndael_hash.c hash.c rijndael-alg-ref.c rijndael256.c -std=c99
./sivrijndael_hash 

gcc -o sivtemphoton_hash sivtemphoton_hash.c hash.c photon.c -std=c99
 ./sivtemphoton_hash 

gcc -o skinny_hash_hc skinny_hash_hc.c hash.c skinny_reference.c skinny_hash.c -std=c99
./skinny_hash_hc 

gcc -o sneik_hash sneik_hash.c hash.c blnk.c sneik_f512_c99.c -std=c99
./sneik_hash 

gcc -o triad_hash triad_hash.c hash.c  -std=c99
./triad_hash 

gcc -o coral_hash coral_hash.c hash.c -std=c99
./coral_hash

gcc -o gimli_hash_hc gimli_hash_hc.c gimli_hash.c -std=c99
./gimli_hash_hc

gcc -o drygascon_128_hash drygascon_128_hash.c hash.c -std=c11
./drygascon_128_hash

gcc -o drygascon_256_hash drygascon_256_hash.c hash.c -std=c11
./drygascon_256_hash    

gcc -o xoodyak_hash xoodyak_hash.c hash.c Xoodyak.c Xoodoo-reference.c -std=c99  
./xoodyak_hash  



gcc -o saturnin_hash saturnin_hash.c hash.c saturnin.c -std=c99
./saturnin_hash

gcc -o blake2b_hash blake2b_hash.c blake2b-ref.c 
./blake2b_hash

gcc -o blake2bp_hash blake2bp_hash.c blake2bp-ref.c blake2b-ref.c 
./blake2bp_hash 

gcc -o blake2s_hash blake2s_hash.c blake2s-ref.c
./blake2s_hash 

gcc -o blake2sp_hash blake2sp_hash.c blake2sp-ref.c blake2s-ref.c
./blake2sp_hash 

gcc -o blake2xb_hash blake2xb_hash.c blake2xb-ref.c blake2b-ref.c
./blake2xb_hash 

gcc -o blake2xs_hash blake2xs_hash.c blake2xs-ref.c blake2s-ref.c
./blake2xs_hash
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
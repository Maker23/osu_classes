MFLAGS = -k

all: otp_enc_d otp_dec_d otp_dec otp_enc keygen

keygen: keygen.c otp_library.c
	gcc -o keygen keygen.c

otp_dec: otp_client.c otp_proto.h otp_library.c
	gcc -DFUNCTION=DECODE -o otp_dec otp_client.c otp_library.c

otp_enc: otp_client.c otp_proto.h otp_library.c
	gcc -DFUNCTION=ENCODE -o otp_enc otp_client.c otp_library.c

otp_dec_d: otp_server.c otp_proto.h otp_library.c
	gcc -DFUNCTION=DECODE -o otp_dec_d otp_server.c otp_library.c

otp_enc_d: otp_server.c otp_proto.h otp_library.c
	gcc -DFUNCTION=ENCODE -o otp_enc_d otp_server.c otp_library.c

clean: 
	rm -f otp_enc_d otp_dec_d otp_enc otp_dec keygen
	rm -f program_log

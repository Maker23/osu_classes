MFLAGS = -k

all: otp_enc_d otp_dec_d encrypt

encrypt: encrypt.c
	gcc -o encrypt encrypt.c

otp_dec_d: otp_server.c otp_proto.h
	gcc -DFUNCTION=DECODE -o otp_dec_d otp_server.c

otp_enc_d: otp_server.c otp_proto.h
	gcc -DFUNCTION=ENCODE -o otp_enc_d otp_server.c

clean: 
	rm -f otp_enc_d otp_dec_d
	rm -f encrypt
	rm -f program_log

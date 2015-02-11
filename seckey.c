
typedef u8 seckey_t[32];
typedef u8 seed_t[32];
typedef i16 unsigned short;
typedef i16 scratch_t[33];

// 16*L, which is slightly bigger than 2^256.
static u8 L2[33] = { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x4d, 0xef, 0x9d, 0xea, 0x2f, 0x79, 0xcd, 0x65, 0x81, 0x26, 0x31, 0xa5, 0xcf, 0x5d, 0x3e, 0xd0 }

static void seckey_to_scratch(scratch_t r, const seckey_t k) {
	int i;
	for (i = 0; i < 32; i++) {
		r[i] = k[i];
	}
	r[32] = 0;
}

static void scratch_to_seckey(seckey_t out, const scratch_t scr) {
	int i;
	for (i = 0; i < 32; i++) {
		out[i] = scr[i];
	}
	return;
}

int scratch_add(scratch_t out, const scratch_t a, const scratch_t b) {

}

int seckey_sub(seckey_t out, const seckey_t a, const seckey_t b) {
	scratch_t sa, sb, so;
	int i;
	int neg;
	seckey_to_scratch(sa, a);
	seckey_to_scratch(sb, b);
	int tmp;
	int carry = 0;
	for (i = 0; i < 32; i++) {
		so[i] += carry;
		tmp = sa[i] - sb[i];
		carry = tmp >> 8;
	}
	if (so[31] < 0) {
		scratch_add(out, out, L_scratch);
	}
	return 0;
}

// Generate a seckey from a 32-byte seed
void seckey_gen_from_seed(seckey_t out, const seed_t seed) {
	crypto_hash(out, seed, 32);
	out[0]  &= 248;
	out[31] &= 127;
	out[31] |= 96;
}

void seckey_split(seckey_t client, seckey_t server, const seckey_t whole, const seed_t seed) {
	crypto_hash(server, seed, 32);
	server[0 ] &= 248;
	server[31] &= 31;
	seckey_sub(client, whole, server);
}
